#include <cstdlib>
#include <iostream>
#include <functional>

template <typename T>

struct Nodo
{
    T valor;
    struct Nodo<T> *next = nullptr, *prev = nullptr;
};

template <typename T, typename Func>
void generarLista(int inicio, int fin, Nodo<T> *&nodo, Func condicion)
{
    for (int i = inicio; i <= fin; ++i)
    {
        if (condicion(i))
        {
            insertarNodo(static_cast<T>(i), nodo);
        }
    }
}

template <typename T>
void insertarNodo(T valor, struct Nodo<T> *&nodo)
{
    struct Nodo<T> *nuevo = new struct Nodo<T>;
    nuevo->valor = valor;
    nuevo->next = nullptr;

    if (nodo == nullptr)
    {
        nuevo->prev = nullptr;
        nodo = nuevo;
        return;
    }
    struct Nodo<T> *actual = nodo;
    while (actual->next != nullptr)
    {
        actual = actual->next;
    }

    actual->next = nuevo;
    nuevo->prev = actual;
}

template <typename T>
void imprimirLista(struct Nodo<T> *&nodo)
{
    struct Nodo<T> *aux = nodo;
    while (aux != nullptr)
    {
        std::cout << "Nodo: " << aux->valor << " <-> ";
        aux = aux->next;
    }
    std::cout << "NULL" << std::endl;
}

template <typename T>
int buscar(T valorDeseado, struct Nodo<T> *&nodo)
{
    int i = 0;
    struct Nodo<T> *aux = nodo;
    while (aux != nullptr)
    {
        if (aux->valor == valorDeseado)
        {
            return i;
        }
        ++i;
        aux = aux->next;
    }
    return -1;
}

template <typename T>
void borrarLista(struct Nodo<T> *&nodo)
{
    struct Nodo<T> *aux = nodo, *aux2;
    while (aux != nullptr)
    {
        aux2 = aux->next;
        delete aux;
        aux = aux2;
    }
    nodo = nullptr;
}

template <typename T>
void eliminarNodo(int indice, struct Nodo<T> *&nodo)
{
    if (nodo == nullptr)
    {
        return;
    }
    struct Nodo<T> *aux = nodo;
    for (int i = 0; i < indice; ++i)
    {
        if (aux->next != nullptr)
        {
            aux = aux->next;
        }
        else
        {
            std::cout << "Índice fuera de rango" << std::endl;
            return;
        }
    }
    if (aux == nodo)
    {
        nodo = aux->next;
    }
    if (aux->next != nullptr)
    {
        aux->next->prev = aux->prev;
    }
    if (aux->prev != nullptr)
    {
        aux->prev->next = aux->next;
    }

    delete aux;
}

int main()
{
    struct Nodo<int> *nodo1 = nullptr;
    generarLista(0, 100, nodo1, [](int n)
                 { return !(n % 2); });
    imprimirLista(nodo1);
    return 0;
}