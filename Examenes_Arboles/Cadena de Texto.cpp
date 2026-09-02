#include <iostream>
#include "abin.h"
#include "colanela.h"

using namespace std;

template<typename T = char>
void MostrarTexto(const Abin<T>& A, typename Abin<T>::nodo na)
{
    if(na != Abin<T>::NODO_NULO)
    {
        cout << A.elemento(na);

        MostrarTexto(A, A.hijoIzqdo(na));
        MostrarTexto(A, A.hijoDrcho(na));
    }
}

template<typename T = char>
void Preorden(const Abin<T>& A)
{
    if(!A.vacio())
        MostrarTexto(A, A.raiz());
}

template<typename T = char>
void ConstruirArbol(Abin<T>& A, const T texto[])
{
    if(texto[0] != '\0')
    {
        Cola<typename Abin<T>::nodo> c;

        A.insertarRaiz(texto[0]);
        c.push(A.raiz());

        int i = 1;

        while(texto[i] != '\0')
        {
            typename Abin<T>::nodo actual = c.frente();
            c.pop();

            if(texto[i] != '\0')
            {
                A.insertarHijoIzqdo(actual, texto[i]);
                c.push(A.hijoIzqdo(actual));
                i++;
            }

            if(texto[i] != '\0')
            {
                A.insertarHijoDrcho(actual, texto[i]);
                c.push(A.hijoDrcho(actual));
                i++;
            }
        }
    }
}

template<typename T = char>
void cifrar(const T texto[])
{
    Abin<T> A;

    ConstruirArbol(A, texto);

    Preorden(A);
}