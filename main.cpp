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

    double op = vx * vx + vy * vy;
    if (op > 4) {
        return 0x00000000;
    }

    if (iter > 0 && iter < max_iterations) {
        //diverge
        return 0xFFFFFFFF;
    } else {
        //converge
        return 0xFF0000FF;
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

    #pragma omp parallel for default(none) shared(dx, dy, pixel_buffer) num_threads(32)
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

int main() {
    sf::Text text;
    sf::Font font;

    pixel_buffer = new unsigned int[WIDTH * HEIGHT];

    {
//        font.loadFromFile("arial.ttf");
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

    //siempre va estar abierto
    while (window.isOpen()) {
//        for (auto event = sf::Event{}; window.pollEvent(event);) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
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
        auto msg = fmt::format("MANDELBROT SET::Mode={}, FPS:{}, Cores: {}",
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