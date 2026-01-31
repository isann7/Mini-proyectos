#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <iostream>

const int VENTANA_ANCHO = 1080;
const int VENTANA_ALTO = 720;

sf::RenderWindow window(sf::VideoMode({VENTANA_ANCHO, VENTANA_ALTO}), "Pelota");

class Pelota
{
public:
    float velX;
    float velY;
    float posX;
    float posY;
    float radio;
    sf::CircleShape circulo;
    Pelota(float x, float y, float r, float vx, float vy, sf::Texture *tex)
    {
        posX = x;
        posY = y;
        radio = r;
        velX = vx;
        velY = vy;
        circulo.setRadius(r);
        circulo.setPointCount(100);
        circulo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        circulo.setTexture(tex);
        circulo.setOrigin({r, r});
        circulo.setPosition({x, y});
        window.draw(circulo);
    }
    void updatePelota(int anchoVentana, int altoVentana)
    {
        posX += velX;
        posY += velY;
        if (posX - radio <= 0 || posX + radio >= anchoVentana)
        {
            velX = -velX;
        }
        if (posY - radio <= 0 || posY + radio >= altoVentana)
        {
            velY = -velY;
        }
        circulo.setPosition({posX, posY});
        window.draw(circulo);
    }
};

int main()
{
    window.setFramerateLimit(60);
    sf::Clock Reloj;
    Reloj.restart();
    std::vector<Pelota> listaPelotas;
    sf::Texture texturaCompartida;
    sf::Font fuente;
    if (!fuente.openFromFile("./SIXTY.TTF"))
    {
        std::cout << "Error cargando fuente" << std::endl;
    }
    sf::Text texto(fuente, "Circulos: 0", 30);
    texto.setFillColor(sf::Color::White);
    texto.setPosition({20.f, 20.f});
    if (!texturaCompartida.loadFromFile("./marco.png"))
    {
        std::cout << "textura cargada";
    }
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        if (Reloj.getElapsedTime().asSeconds() >= 1.0f && listaPelotas.size() < 100)
        {
            float radio = 5.f + (rand() % 40);
            float posx = rand() % VENTANA_ANCHO;
            float posy = rand() % VENTANA_ALTO;
            if (posx - radio <= 0)
            {
                posx += radio;
            }
            if (posx + radio >= VENTANA_ALTO)
            {
                posx -= radio;
            }
            if (posy - radio <= 0)
            {
                posy += radio;
            }
            if (posy + radio >= VENTANA_ALTO)
            {
                posy -= radio;
            }
            float velx = (((rand() % 2) * 2 - 1) * 3.f) + rand() % 3;
            float vely = (((rand() % 2) * 2 - 1) * 3.f) + rand() % 3;
            Pelota nuevaPelota(posx, posy, radio, velx, vely, &texturaCompartida);
            listaPelotas.push_back(nuevaPelota);
            texto.setString("Circulos: " + std::to_string(listaPelotas.size()));
            Reloj.restart();
        }
        window.clear();
        for (Pelota &p : listaPelotas)
        {
            p.updatePelota(VENTANA_ANCHO, VENTANA_ALTO);
        }
        window.draw(texto);
        window.display();
    }
    return 0;
}
