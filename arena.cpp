#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>

const int VENTANA_ANCHO = 800;
const int VENTANA_ALTO = 600;
const int CELLSIZE = 16;

const int COLUMNAS = VENTANA_ANCHO / CELLSIZE;
const int FILAS = VENTANA_ALTO / CELLSIZE;

int cuadricula[FILAS][COLUMNAS] = {0};

sf::RenderWindow window(sf::VideoMode({VENTANA_ANCHO, VENTANA_ALTO}), "Simulador de Arena");

enum elementos
{
    vacio = 0,
    arena = 1,
    agua = 2
};

void dibujar()
{
    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            if (cuadricula[f][c] == arena)
            {
                sf::RectangleShape grano(sf::Vector2f(CELLSIZE - 1, CELLSIZE - 1));
                grano.setFillColor(sf::Color::Yellow);
                grano.setPosition({(float)c * CELLSIZE, (float)f * CELLSIZE});
                window.draw(grano);
            }
            if (cuadricula[f][c] == agua)
            {
                sf::RectangleShape gota(sf::Vector2f(CELLSIZE - 1, CELLSIZE - 1));
                gota.setFillColor(sf::Color::Cyan);
                gota.setPosition({(float)c * CELLSIZE, (float)f * CELLSIZE});
                window.draw(gota);
            }
        }
    }
}

void update()
{
    for (int f = FILAS - 2; f >= 0; f--)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            switch (cuadricula[f][c])
            {
            case arena:
            {
                if (cuadricula[f + 1][c] == vacio)
                {
                    cuadricula[f + 1][c] = arena;
                    cuadricula[f][c] = vacio;
                    continue;
                }
                if (cuadricula[f + 1][c] == arena)
                {
                    int random = (rand() % 2) * 2 - 1;
                    if (cuadricula[f + 1][c - random] == vacio)
                    {
                        cuadricula[f + 1][c - random] = arena;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                    if (cuadricula[f + 1][c + random] == vacio)
                    {
                        cuadricula[f + 1][c + random] = arena;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                }
                if (cuadricula[f + 1][c] == agua)
                {
                    cuadricula[f + 1][c] = arena;
                    cuadricula[f][c] = agua;
                    continue;
                }
                int random = (rand() % 2) * 2 - 1;
                if (cuadricula[f + 1][c - random] == agua)
                {
                    cuadricula[f + 1][c - random] = arena;
                    cuadricula[f - 1][c] = agua;
                    continue;
                }
                if (cuadricula[f + 1][c + random] == agua)
                {
                    cuadricula[f + 1][c + random] = arena;
                    cuadricula[f - 1][c] = agua;
                    continue;
                }
                break;
            }
            case agua:
            {
                if (cuadricula[f + 1][c] == vacio)
                {
                    cuadricula[f + 1][c] = agua;
                    cuadricula[f][c] = vacio;
                }
                else
                {
                    int random = (rand() % 2) * 2 - 1;
                    if (cuadricula[f + 1][c - random] == vacio)
                    {
                        cuadricula[f + 1][c - random] = agua;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                    if (cuadricula[f + 1][c + random] == vacio)
                    {
                        cuadricula[f + 1][c + random] = agua;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                    if (cuadricula[f][c - random] == vacio)
                    {
                        cuadricula[f][c - random] = agua;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                    if (cuadricula[f][c + random] == vacio)
                    {
                        cuadricula[f][c + random] = agua;
                        cuadricula[f][c] = vacio;
                        continue;
                    }
                }
                break;
            }
            }
        }
    }
}

int main()
{
    sf::Clock Reloj;
    Reloj.restart();
    int spawn = 0;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        if (Reloj.getElapsedTime().asSeconds() >= 0.1f)
        {
            spawn = (spawn % 2) + 1;
            cuadricula[0][COLUMNAS / 2] = spawn;
            Reloj.restart();
        }
        update();
        window.clear();
        dibujar();
        window.display();
    }

    return 0;
}