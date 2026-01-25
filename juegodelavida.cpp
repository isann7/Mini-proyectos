#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <iostream>

const int VENTANA_ANCHO = 1080;
const int VENTANA_ALTO = 720;
const int CELLSIZE = 16;

const int COLUMNAS = VENTANA_ANCHO / CELLSIZE;
const int FILAS = VENTANA_ALTO / CELLSIZE;

int cuadricula[FILAS][COLUMNAS] = {0};

sf::RenderWindow window(sf::VideoMode({VENTANA_ANCHO, VENTANA_ALTO}), "Simulador del juego de la vida");

int contarVecinos(int f, int c)
{
    int contador = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!i && !j)
            {
                continue;
            }
            if (f + i >= 0 && f + i < FILAS && c + j >= 0 && c + j < COLUMNAS) {
                if (cuadricula[f + i][c + j] == 1) {
                    contador++;
                }
            }
        }
    }
    return contador;
}

void borrar()
{
    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            cuadricula[f][c] = 0;
        }
    }
}

void updateVida()
{
    int proxima_cuadricula[FILAS][COLUMNAS] = {0};

    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            int vecinos = contarVecinos(f, c);

            if (cuadricula[f][c] == 1)
            {
                if (vecinos == 2 || vecinos == 3)
                    proxima_cuadricula[f][c] = 1;
                else
                    proxima_cuadricula[f][c] = 0;
            }
            else
            {
                if (vecinos == 3)
                    proxima_cuadricula[f][c] = 1;
            }
        }
    }

    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            cuadricula[f][c] = proxima_cuadricula[f][c];
        }
    }
}

void dibujar()
{
    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLUMNAS; c++)
        {
            if (cuadricula[f][c] == 1)
            {
                sf::RectangleShape celula(sf::Vector2f(CELLSIZE - 1, CELLSIZE - 1));
                celula.setFillColor(sf::Color::White);
                celula.setPosition({(float)c * CELLSIZE, (float)f * CELLSIZE});
                window.draw(celula); 
            }
        }
    }
}

int main()
{
    bool pausado = true;
    int nuevaVelocidad = 1000;
    window.setFramerateLimit(60);
    sf::Clock Reloj;
    Reloj.restart();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Space)
                {
                    pausado = !pausado;
                }
                if (keyPressed->code == sf::Keyboard::Key::I) // 'I' de Input
                {
                    pausado = true;
                    window.setTitle("INTRODUCE DATOS EN LA CONSOLA...");

                    std::cout << "Introduce el nuevo intervalo (ms): ";
                    std::cin >> nuevaVelocidad;
                    std::cout << "Valor actualizado. Puedes volver a la ventana." << std::endl;
                }
                if (keyPressed->code == sf::Keyboard::Key::Delete)
                {
                    borrar();
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                int c = mousePos.x / CELLSIZE;
                int f = mousePos.y / CELLSIZE;

                if (f >= 0 && f < FILAS && c >= 0 && c < COLUMNAS)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                        cuadricula[f][c] = 1;
                    else
                        cuadricula[f][c] = 0;
                }
            }
        }
        if (!pausado && Reloj.getElapsedTime().asMilliseconds() >= nuevaVelocidad)
        {
            updateVida();
            Reloj.restart();
        }
        window.clear();
        dibujar();
        if (pausado)
        {
            window.setTitle("Simulador - PAUSADO (Espacio para continuar) - Pulsa I para introducir intervalo");
        }
        else
        {
            window.setTitle("Simulador - CORRIENDO - Pulsa I para introducir intervalo");
        }
        window.display();
    }
    return 0;
}