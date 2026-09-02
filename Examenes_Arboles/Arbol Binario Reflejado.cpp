//Arbol Binario Reflejado
#include <iostream>
#include "abin.h"

template <typename T>
Abin<T> AbinReflejado(const Abin<T>& A)
{
    Abin<T> Reflejado;
    if(!A.arbolVacio())
    {
        Reflejado.insertarRaiz(A.elemento(A.raiz()));
        AbinReflejado_rec(A.raiz(), Reflejado.raiz(), A, Reflejado);
    }
    return Reflejado;
}

template <typename T>
void AbinReflejado_rec(typename Abin<T>::nodo na, typename Abin<T>::nodo nb, const Abin<T>& A, const Abin<T>& B)
{
    if(na != Abin<T>::NODO_NULO)
    {
        if(A.hijoDrcho(na)!=Abin<T>::NODO_NULO)
        {
            B.insertarHijoIzqdo(nb, A.elemento(A.hijoDrcho(na)));
            AbinReflejado_rec(A.hijoDrcho(na), B.hijoIzqdo(nb), A, B);
        }
        if(A.hijoIzqdo(na)!=Abin<T>::NODO_NULO)
        {
            B.insertarHijoDrcho(nb,A.elemento(A.hijoIzqdo(na)));
            AbinReflejado_rec(A.hijoIzqdo(na), B.hijoDrcho(nb), A,B);
        }
    }
}


/*Para llevar a cabo este ejercicio hemos usado el arbol binario en su representación enlanzada, siendo la parte privada del TAD abin:
    private:
        struct celda{
            T elto;
            nodo padre, hizq, hder;
            celda(const T& e, nodo p=NODO_NULO): elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO){}
        };
        nodo r;
    };
Ademas hemos hecho uso de metodos publicos del TAD abin:
-Abin<T> Abin();
Post Crea y devuelve un Abin vacio
-bool arbolVacio();
Post devuelve true si el arbol esta vacio y false si no lo esta
-void InsertarRaiz(const T& e)
Pre El arbol debe estar vacio
Post Introduce el elemento en la raiz del arbol
-nodo raiz() const
Post Devuelve el nodo que es raiz del arbol
-const T& elemento(nodo n)const
Pre El nodo exista 
Post devuelva el elemento de ese nodo.
-nodo hijoDrcho(nodo n) const;
Pre Exista el nodo n
Post Devuelva el hijoDrcho del nodo n, si no existe el nodo nulo.
-void insertarHijoDrcho(nodo n, const T& e);
Pre exista el nodo n y no tiene hijo derecho previo
Post Se inserta el hijo derecho con el elemento e en el nodo n. 
*/