#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <iostream>
#include <math.h>

const int VENTANA_ANCHO = 1080;
const int VENTANA_ALTO = 720;

sf::RenderWindow window(sf::VideoMode({VENTANA_ANCHO, VENTANA_ALTO}), "Rebote");

class Pelota
{
public:
    float velX;
    float velY;
    float posX;
    float posY;
    float radio;
    sf::CircleShape circulo;
    Pelota(float x, float y, float r, float vx, float vy)
    {
        posX = x;
        posY = y;
        radio = r;
        velX = vx;
        velY = vy;
        circulo.setRadius(r);
        circulo.setPointCount(100);
        circulo.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        circulo.setOrigin({r, r});
        circulo.setPosition({x, y});
        window.draw(circulo);
    }

    void resolverColision(Pelota &otra)
    {
        float distX = otra.posX - posX;
        float distY = otra.posY - posY;
        float distancia = std::sqrt(distX * distX + distY * distY);
        if (distancia <= radio + otra.radio)
        {
            std::swap(velX, otra.velX);
            std::swap(velY, otra.velY);
            float traslape = (radio + otra.radio - distancia) / 2.0f;
            posX -= (distX / distancia) * traslape;
            posY -= (distY / distancia) * traslape;
            otra.posX += (distX / distancia) * traslape;
            otra.posY += (distY / distancia) * traslape;
        }
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
    std::vector<Pelota> listaPelotas;
    window.setFramerateLimit(60);
    listaPelotas.push_back({50, 300, 40, 2, 1});
    listaPelotas.push_back({250, 300, 40, -2, 0});
    listaPelotas.push_back({50, 50, 40, 2, 1.5});
    listaPelotas.push_back({250, 60, 40, -3, 2});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
        for (size_t i = 0; i < listaPelotas.size(); ++i)
        {
            for (size_t j = i + 1; j < listaPelotas.size(); ++j)
            {
                listaPelotas[i].resolverColision(listaPelotas[j]);
            }
        }
        window.clear();
        for (auto &p : listaPelotas)
        {
            p.updatePelota(VENTANA_ANCHO, VENTANA_ALTO);
        }
        window.display();
    }
}