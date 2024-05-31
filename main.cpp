#include <iostream>

#include <SFML/Window.hpp>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>


#define WIDTH 1920
#define HEIGHT 1080


int max_iterations = 100;
const double x_min = -2;
const double x_max = 1;

const double y_min = -1;
const double y_max = 1;

static  unsigned int*pixel_buffer = nullptr;


unsigned int divergente (double cx, double cy) {
    int iter = 0;

    // copy for vector
    double vx = cx;
    double vy = cy;

    while(iter<max_iterations && (vx*vx+vy*vy)<=4) {
        //Zn+1 = Zn^2 + C

        double tx = vx * vx - vy * vy + cx; //vx^2 -vy^2 +cx;
        double ty = 2 * vx * vy + cy; // 2vx vy +cy

        vx = tx;
        vy = ty;
        iter++;
    }

    if(iter> 0 && iter< max_iterations) {
        //diverge
        return 0xFFFFFFFF;
    }else {
        //converge
        return 0xFF0000FF;
    }
}


void mandelbrotCpu() {

    double dx = (x_max-x_min)/WIDTH;
    double dy = (y_max-y_min) / HEIGHT;

    for(int i = 0; i<WIDTH; i++) {
        for(int j = 0; j<HEIGHT; j++) {
            double x = x_min + i*dx;
            double y = y_max - j*dy;

            // C = X+Yi
            unsigned int color  = divergente(x,y);

            pixel_buffer[ j*WIDTH+i  ]= color;

        }
    }
}

int main()
{
    sf::Text text;
    sf::Font font;

    pixel_buffer = new unsigned int [ WIDTH*HEIGHT];

    {
//        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("Ejemplo OPENMP");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold);
        text.setPosition(10,10);
    }

    sf::Texture texture;
    texture.create(WIDTH,HEIGHT);
    texture.update((const sf::Uint8 *)pixel_buffer);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    //auto = var
    auto window = sf::RenderWindow{ { WIDTH, HEIGHT }, "CMake SFML Project" };
    window.setFramerateLimit(165);

    //time -> frames and fps
    sf:: Clock clock;
    int frames = 0;
    int fps = 0;

    //siempre va estar abierto
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        fmt::println("generando imagen");
        mandelbrotCpu();
        sf:: Image img;
        img.create(WIDTH,HEIGHT, (const sf:: Uint8*)pixel_buffer);
        img.saveToFile("C:/conan/complejo.jpg");

        texture.update((const sf::Uint8 *)pixel_buffer);

        // formatear el texto
        auto msg = fmt :: format("Ejemplo OpenMP, FPS: {}", fps);
        text.setString(msg);

        if(clock.getElapsedTime().asSeconds()>=1.0) {
            fps = frames;
            frames = 0;
            clock.restart();
        }

        frames++;

        window.clear();
        {
            window.draw(sprite);
            window.draw(text);
        }
        window.display();
    }

    delete [ ] pixel_buffer;
}