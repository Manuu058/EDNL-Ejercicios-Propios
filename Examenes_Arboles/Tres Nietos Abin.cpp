#include <iostream>
#include "abin.h"

template <typename T>
int nietosNodo(const Abin<T>& A, typename Abin<T>::nodo na)
{
    if (na == Abin<T>::NODO_NULO)
        return 0;

    int n = 0;

    typename Abin<T>::nodo hi = A.hijoIzqdo(na);
    typename Abin<T>::nodo hd = A.hijoDrcho(na);

    // Nietos por el hijo izquierdo
    if (hi != Abin<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(hi) != Abin<T>::NODO_NULO)
            n++;

        if (A.hijoDrcho(hi) != Abin<T>::NODO_NULO)
            n++;
    }

    // Nietos por el hijo derecho
    if (hd != Abin<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(hd) != Abin<T>::NODO_NULO)
            n++;

        if (A.hijoDrcho(hd) != Abin<T>::NODO_NULO)
            n++;
    }

    return n;
}

template <typename T>
int NodosVerdesRec(const Abin<T>& A, typename Abin<T>::nodo na)
{
    if (na == Abin<T>::NODO_NULO)
        return 0;

    int suma = 0;

    if (nietosNodo(A, na) == 3)
        suma = 1;

    return suma +
           NodosVerdesRec(A, A.hijoIzqdo(na)) +
           NodosVerdesRec(A, A.hijoDrcho(na));
}

template <typename T>
int NodosVerdes(const Abin<T>& A)
{
    return NodosVerdesRec(A, A.raiz());
}