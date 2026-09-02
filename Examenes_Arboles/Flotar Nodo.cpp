//Para este ejercicio vamos a implementar un ABB mediante un Abin 

#include <iostream>
#include "abin.h"

template <typename T>
void FlotarNodo(const T& e, Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        //Buscaremos el nodo a flotar
        typename Abin<T>::nodo encontrado=Abin<T>::NODO_NULO;
        Buscar(A, A.raiz(), e, encontrado);
        if(encontrado!=Abin<T>::NODO_NULO)
        {
            FlotarNodoRec(A,encontrado);
        }
    }
}

template <typename T>
void Buscar(const Abin<T>& A, typename Abin<T>::nodo na, const T& e, typename Abin<T>::nodo& encontrado)
{
    if(na!=Abin<T>::NODO_NULO)
    {
        if(A.elemento(na)==e)
        {
            encontrado=na;
            return;
        }
        else{
            Buscar(A, A.hijoDrcho(na), e,encontrado);
            Buscar(A,A.hijoIzqdo(na), e, encontrado);
        }
    }
}


template <typename T>
void FlotarNodoRec(Abin<T>& A, typename Abin<T>::nodo nodo)
{
    if(nodo != Abin<T>::NODO_NULO)
    {
        if(A.raiz() != nodo)
        {
            T elto_aux;
            if(A.elemento(A.padre(nodo))>A.elemento(nodo))
            {
                elto_aux=A.elemento(A.padre(nodo));
                A.elemento(A.padre(nodo))=A.elemento(nodo);
                A.elemento(nodo)=elto_aux;
                FlotarNodoRec(A, A.padre(nodo));
            }
        }
    }
}