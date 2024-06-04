#include <iostream>

#include <SFML/Window.hpp>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <omp.h>

#define WIDTH 1920
#define HEIGHT 1080

int max_iterations = 100;
const double x_min = -2;
const double x_max = 1;

const double y_min = -1;
const double y_max = 1;
int num_cores = 0;

static unsigned int *pixel_buffer = nullptr;

#define PALETTE_SIZE 16

uint32_t _bswap32(uint32_t a) {
    return
            ((a & 0x000000FF) << 24) |
            ((a & 0x0000FF00) << 8) |
            ((a & 0x00FF0000) >> 8) |
            ((a & 0xFF000000) >> 24);
}

//creando vector. (16)
std::vector<unsigned int> color_ramp = {
        _bswap32(0xEF1019FF),
        _bswap32(0xE01123FF),
        _bswap32(0xD1112DFF),
        _bswap32(0xC11237FF),
        _bswap32(0xB21341FF),
        _bswap32(0xA3134BFF),
        _bswap32(0x931455FF),
        _bswap32(0x84145EFF),
        _bswap32(0x751568FF),
        _bswap32(0x651672FF),
        _bswap32(0x56167CFF),
        _bswap32(0x471786FF),
        _bswap32(0x371790FF),
        _bswap32(0x28189AFF),
        _bswap32(0x1919A4FF)
};

//class para que el compilador no dependa de algo externo
enum class runtime_type_enum {
    rtCPU, rtOpenMp
};

static runtime_type_enum runtime_type = runtime_type_enum::rtCPU;

unsigned int divergente(double cx, double cy) {
    int iter = 0;

    // copy for vector
    double vx = cx;
    double vy = cy;

    while (iter < max_iterations && (vx * vx + vy * vy) <= 4) {
        //Zn+1 = Zn^2 + C

        double tx = vx * vx - vy * vy + cx; //vx^2 -vy^2 +cx;
        double ty = 2 * vx * vy + cy; // 2vx vy +cy

        vx = tx;
        vy = ty;
        iter++;
    }

    if (iter > 0 && iter < max_iterations) {
        //diverge
        int color_idx = iter % PALETTE_SIZE;
        return color_ramp[color_idx]; //retorna color que necesitamos...
    } else {
        //converge
//        return 0xFF0000FF;
        return 0;
    }
}


void mandelbrotCpu() {

    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            double x = x_min + i * dx;
            double y = y_max - j * dy;

            // C = X+Yi
            unsigned int color = divergente(x, y);

            pixel_buffer[j * WIDTH + i] = color;

        }
    }
}


//usando pragma omp = OpenMp
void mandelbrotOpenMp() {

    double dx = (x_max - x_min) / WIDTH;
    double dy = (y_max - y_min) / HEIGHT;

#pragma omp parallel
    {
        int threads = omp_get_num_threads();
        int id_threads = omp_get_thread_num();

        //i
        int size_i = WIDTH / threads;
        int start_i = id_threads * size_i;
        int end_i = (1 + id_threads) * size_i;

        if (id_threads == threads - 1) end_i = WIDTH;

        //j
        int size_j = HEIGHT / threads;
        int start_j = id_threads * size_j;
        int end_j = (1 + id_threads) * size_j;

        if (id_threads == threads - 1) end_j = HEIGHT;

        for (int i = start_i; i < end_i; i++) {
            for (int j = start_j; j < end_j; j++) {

                double x = x_min + i * dx;
                double y = y_max - j * dy;
                // C = X+Yi
                unsigned int color = divergente(x, y);
                pixel_buffer[j * WIDTH + i] = color;
            }
        }

    };

//#pragma omp parallel for default(none) shared(dx, dy, pixel_buffer) num_threads(32)
//
//    for (int i = 0; i < WIDTH; i++) {
//        for (int j = 0; j < HEIGHT; j++) {
//            double x = x_min + i * dx;
//            double y = y_max - j * dy;
//
//            // C = X+Yi
//            unsigned int color = divergente(x, y);
//
//            pixel_buffer[j * WIDTH + i] = color;
//
//        }
//    }
}

int main() {
    sf::Text text;
    sf::Font font;

    pixel_buffer = new unsigned int[WIDTH * HEIGHT];

    {
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("Ejemplo OPENMP");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setPosition(10, 10);
    }
    sf::Text textOptions;
    {
        font.loadFromFile("arial.ttf");
        textOptions.setFont(font);
        textOptions.setCharacterSize(24);
        textOptions.setFillColor(sf::Color::White);
        textOptions.setStyle(sf::Text::Bold);
        textOptions.setString("Option: [1] CPU [2] OpenMP");
    }

    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update((const sf::Uint8 *) pixel_buffer);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    //auto = var
    auto window = sf::RenderWindow{{WIDTH, HEIGHT}, "CMake SFML Project"};
    window.setFramerateLimit(165);

    //time -> frames and fps
    sf::Clock clock;
    int frames = 0;
    int fps = 0;

#pragma omp parallel
    {
        num_cores = omp_get_num_threads();
    }
    //siempre va estar abierto
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                textOptions.setPosition(10, window.getView().getSize().y - 40);
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.scancode) {
                    case sf::Keyboard::Scan::Num1:
                        //cpu
#pragma omp master
                    {
                        num_cores = omp_get_num_threads();
                    }
                        runtime_type = runtime_type_enum::rtCPU;
                        break;
                    case sf::Keyboard::Scan::Num2:
                        //openMp
#pragma omp parallel
                    {
                        num_cores = omp_get_num_threads();
                    }
                        runtime_type = runtime_type_enum::rtOpenMp;
                        break;
                }
            }

//        fmt::println("generando imagen");
        if (runtime_type == runtime_type_enum::rtCPU) {
            mandelbrotCpu();
        } else {
            mandelbrotOpenMp();
        }
        //textura actualizada after condicion line 177
        texture.update((const sf::Uint8 *) pixel_buffer);
        textOptions.setPosition(40, 40);
        sf::Image img;
        img.create(WIDTH, HEIGHT, (const sf::Uint8 *) pixel_buffer);
        img.saveToFile("C:/conan/complejo.jpg");

        // formatear el texto
//        auto msg = fmt :: format("Ejemplo OpenMP, FPS: {}", fps);
//        text.setString(msg);
        std::string msg = fmt::format("MANDELBROT SET::Mode={}, FPS:{}, Cores: {}",
                                      runtime_type == runtime_type_enum::rtCPU ? "CPU" : "OpenMp", fps, num_cores);
        text.setString(msg);

        if (clock.getElapsedTime().asSeconds() >= 1.0) {
            fps = frames;
            frames = 0;
            clock.restart();
        }

        frames++;

        window.clear();
        {
            window.draw(sprite);
            window.draw(text);
            window.draw(textOptions);
        }
        window.display();
    }

    delete[] pixel_buffer;
}