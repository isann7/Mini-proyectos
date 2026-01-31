#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <iostream>

enum Color
{
    ROJO,
    NEGRO
};

template <typename T>
struct Nodo
{
    Color color;
    T valor;
    Nodo<T> *izq, *der, *arr; // Quitamos *raiz de aquí, no la necesita el nodo
};

template <typename T>
struct Arbol
{
    Nodo<T> *raiz = nullptr;

    Nodo<T> *crearNodo(T valor)
    {
        Nodo<T> *nuevo = new Nodo<T>;
        nuevo->valor = valor;
        nuevo->color = ROJO;
        nuevo->izq = nuevo->der = nuevo->arr = nullptr;
        return nuevo;
    }

    void rotIzq(Nodo<T> *nodo)
    {
        if (nodo == nullptr || nodo->der == nullptr)
        {
            return;
        }

        Nodo<T> *hijo = nodo->der;

        nodo->der = hijo->izq;
        if (hijo->izq != nullptr)
        {
            hijo->izq->arr = nodo;
        }

        hijo->arr = nodo->arr;
        if (nodo->arr == nullptr)
        {
            raiz = hijo;
        }
        else if (nodo == nodo->arr->izq)
        {
            nodo->arr->izq = hijo;
        }
        else
        {
            nodo->arr->der = hijo;
        }

        hijo->izq = nodo;
        nodo->arr = hijo;
    }

    void rotDer(Nodo<T> *nodo)
    {
        if (nodo == nullptr || nodo->izq == nullptr)
        {
            return;
        }

        Nodo<T> *hijo = nodo->izq;

        nodo->izq = hijo->der;
        if (hijo->der != nullptr)
        {
            hijo->der->arr = nodo;
        }

        hijo->arr = nodo->arr;
        if (nodo->arr == nullptr)
        {
            raiz = hijo;
        }
        else if (nodo == nodo->arr->der)
        {
            nodo->arr->der = hijo;
        }
        else
        {
            nodo->arr->izq = hijo;
        }

        hijo->der = nodo;
        nodo->arr = hijo;
    }

    void insertarNodo(T dato)
    {
        Nodo<T> *nuevo = crearNodo(dato);
        Nodo<T> *actual = raiz, *padre = nullptr;
        while (actual != nullptr)
        {
            padre = actual;
            if (nuevo->valor < actual->valor)
            {
                actual = actual->izq;
            }
            else
            {
                actual = actual->der;
            }
        }
        nuevo->arr = padre;
        if (padre == nullptr)
        {
            raiz = nuevo;
        }
        else if (nuevo->valor < padre->valor)
        {
            padre->izq = nuevo;
        }
        else
        {
            padre->der = nuevo;
        }
        arreglarArbol(nuevo);
    }

    void arreglarArbol(Nodo<T> *nodo)
    {
        Nodo<T> *tio;
        while (nodo->arr != nullptr && nodo->arr->color == ROJO)
        {
            if (nodo->arr == nodo->arr->arr->izq)
            {
                tio = nodo->arr->arr->der;
                if (tio != nullptr && tio->color == ROJO)
                {
                    nodo->arr->color = NEGRO;
                    tio->color = NEGRO;
                    nodo->arr->arr->color = ROJO;
                    nodo = nodo->arr->arr;
                }
                else
                {
                    if (nodo == nodo->arr->der)
                    {
                        nodo = nodo->arr;
                        rotIzq(nodo);
                    }
                    nodo->arr->color = NEGRO;
                    nodo->arr->arr->color = ROJO;
                    rotDer(nodo->arr->arr);
                }
            }
            else
            {
                tio = nodo->arr->arr->izq;
                if (tio != nullptr && tio->color == ROJO)
                {
                    nodo->arr->color = NEGRO;
                    tio->color = NEGRO;
                    nodo->arr->arr->color = ROJO;
                    nodo = nodo->arr->arr;
                }
                else
                {
                    if (nodo == nodo->arr->izq)
                    {
                        nodo = nodo->arr;
                        rotDer(nodo);
                    }
                    nodo->arr->color = NEGRO;
                    nodo->arr->arr->color = ROJO;
                    rotIzq(nodo->arr->arr);
                }
            }
        }
        raiz->color = NEGRO;
    }
};

template <typename T>
void imprimirArbol(Nodo<T> *nodo, std::string prefijo = "", bool esDerecho = true)
{
    if (nodo == nullptr)
        return;

    // 1. Procesar hijo derecho
    if (nodo->der)
    {
        imprimirArbol(nodo->der, prefijo + (esDerecho ? "        " : " |      "), true);
    }

    // 2. Imprimir el nodo actual
    std::cout << prefijo;
    std::cout << (esDerecho ? " /--- " : " \\--- ");

    std::string colorStr = (nodo->color == ROJO) ? "[R]" : "[N]";
    std::cout << nodo->valor << colorStr << std::endl;

    // 3. Procesar hijo izquierdo
    if (nodo->izq)
    {
        imprimirArbol(nodo->izq, prefijo + (esDerecho ? " |      " : "        "), false);
    }
}

int main()
{
    Arbol<int> miArbol;
    for (int i = 20; i < 50; ++i)
    {
        miArbol.insertarNodo(i);
    }

    imprimirArbol(miArbol.raiz);

    return 0;
}