#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <iostream>

const int VENTANA_ANCHO = 1080;
const int VENTANA_ALTO = 720;
const sf::Vector2f g = {0, 0};

sf::RenderWindow window(sf::VideoMode({VENTANA_ANCHO, VENTANA_ALTO}), "");
sf::Clock dt;
class Circulo
{
public:
    sf::Vector2f posicion;
    sf::Vector2f posicion_anterior;
    sf::Vector2f velocidad;
    float masa;
    float radio;
    float damping;
    sf::CircleShape cuerpo;
    Circulo(sf::Vector2f pos, float r, float m, float dmp)
    {
        posicion = pos;
        posicion_anterior = pos;
        masa = m;
        radio = r;
        damping = dmp;
        cuerpo.setRadius(radio);
        cuerpo.setFillColor(sf::Color::White);
        cuerpo.setPointCount(100);
        cuerpo.setOrigin({radio, radio});
        cuerpo.setPosition(posicion);
    }
    void update(float dt)
    {
        velocidad = posicion - posicion_anterior;
        posicion_anterior = posicion;
        posicion = posicion + velocidad + g * (dt * dt);
        if (posicion.x + radio >= VENTANA_ANCHO)
        {
            posicion.x = VENTANA_ANCHO - radio;
            posicion_anterior.x = posicion.x + (velocidad.x * damping);
        }
        else if (posicion.x - radio <= 0)
        {
            posicion.x = radio;
            posicion_anterior.x = posicion.x + (velocidad.x * damping);
        }
        if (posicion.y + radio >= VENTANA_ALTO)
        {
            posicion.y = VENTANA_ALTO - radio;
            posicion_anterior.y = posicion.y + (velocidad.y * damping);
        }
        else if (posicion.y - radio <= 0)
        {
            posicion.y = radio;
            posicion_anterior.y = posicion.y + (velocidad.y * damping);
        }
        cuerpo.setPosition(posicion);
        window.draw(cuerpo);
    }
};

int main()
{
    window.setFramerateLimit(60);
    Circulo pelota({VENTANA_ANCHO / 2, VENTANA_ALTO / 2}, 20, 1, 0.75);
    pelota.posicion_anterior = pelota.posicion - sf::Vector2f{1000,1000} * 0.0166f;
    while (window.isOpen())
    {
        float deltaTime = dt.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
        pelota.update(deltaTime);
        window.display();
    }
}