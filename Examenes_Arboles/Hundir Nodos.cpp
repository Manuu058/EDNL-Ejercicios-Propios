#include <iostream>
#include "Abin.h"

template <typename T>
void HundirNodo(Abin<T>& A, const T& e){
    if(!A.arbolVacio())
    {
        typename Abin<T>::nodo encontrado=Abin<T>::NODO_NULO;
        Buscar(A, A.raiz(), e, encontrado);
        if(encontrado != Abin<T>::NODO_NULO)
        {
            HundirNodoRec(A,encontrado);
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
void HundirNodoRec(Abin<T>& A, typename Abin<T>::nodo nodo)
{
    if(nodo!= Abin<T>::NODO_NULO)
    {
        T elemento_aux;
        if(A.hijoIzqdo(nodo)!=  Abin<T>::NODO_NULO)
        {
            elemento_aux=A.elemento(A.hijoIzqdo(nodo));
            A.elemento(A.hijoIzqdo(nodo))=A.elemento(nodo);
            A.elemento(nodo)=elemento_aux;
            HundirNodoRec(A, A.hijoIzqdo(nodo));
        }
        else if(A.hijoDrcho(nodo)!=  Abin<T>::NODO_NULO){
            elemento_aux=A.elemento(A.hijoDrcho(nodo));
            A.elemento(A.hijoDrcho(nodo))=A.elemento(nodo);
            A.elemento(nodo)=elemento_aux;
            HundirNodoRec(A, A.hijoDrcho(nodo));
        }
        else if(A.hijoIzqdo(nodo)==  Abin<T>::NODO_NULO &&A.hijoDrcho(nodo)==  Abin<T>::NODO_NULO)
        {
            A.elemento(nodo)=Abin<T>::NODO_NULO;
        }
    }
}