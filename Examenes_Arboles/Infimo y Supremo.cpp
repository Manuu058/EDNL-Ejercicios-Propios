//Infimo/Supremo
//La clave de este ejercicio es descartar subarboles para que asi sea de coste O(logn)
#include<iostream>
#include "abb.h"

using namespace std;

template<typename T>
T minimo(const Abb<T>& A)
{
    if (A.izqdo().vacio())
    {
        return A.elemento();
    }

    return minimo(A.izqdo());
}

template<typename T>
T maximo(const Abb<T>& A)
{
    if(A.drcho().vacio())
    {
        return A.elemento();
    }
    return maximo(A.drcho());
}

template <typename T>
T infimoREC(const Abb<T>& A, const T& x, const T& candidato)
{
    if(A.vacio())
    {
        return candidato;
    }

    const T& raiz=A.elemento();
    if(raiz<x)
    {
        //Buscamos por la parte derecha ya que puede haber un elemento mayor o igual
        return infimoREC(A.drcho(),x,raiz);
    }
    if(raiz>x)
    {
        //Hay que buscar en el subarbol izquierdo
        return infimoREC(A.izqdo(),x, candidato);
    }

    if(raiz==x)
    {
        return raiz;
    }
}

template<typename T>
T supremoREC(const Abb<T>& A, const T& x, const T& candidato)
{
    if(A.vacio())
    {
        return candidato;
    }
    else if(x>A.elemento())
    {
        //Tengo que buscar para la izquierda
        return supremoREC(A.drcho(),x,candidato);
    }
    else if(x<A.elemento())
    {
        //Tengo que buscar por la derecha
        return supremoREC(A.izqdo(),x,A.elemento());
    }
}

template<typename T>
T supremo(const Abb<T>& A, const T& x)
{
    return supremoREC(A, x, maximo(A));
}

template<typename T>
T infimo(const Abb<T>& A, const T& x)
{
    return infimoREC(A, x, minimo(A));
}

