#include <iostream>
#include "Agen.h"

template <typename T>
Agen<T> AgenReflejado(const Agen<T>& A)
{
    Agen<T> Reflejado;
    if(!A.arbolVacio())
    {
        Reflejado.insertarRaiz(A.elemento(A.raiz));
        AgenReflejado_rec(na,nb, A, Reflejado);
    }
}

template <typename T>
void AgenReflejado_rec(typename Agen<T>::nodo na, typename Agen<T>::nodo nb, const Agen<T>& A, const Agen<T>& B){
    if(na != A.NODO_NULO)
    {
        typename Agen<T>::nodo aux = A.hijoIzqdo(na);
        while(aux!=Agen<T>::NODO_NULO)
        {
            B.insertarHijoIzqdo(nb,A.elemento(aux))
            AgenReflejado_rec(aux,B.hijoIzqdo(nb) ,A,B);
            aux=A.hermDrcho(aux);
        }
    }
}

/*Para resolver este ejercicio hemos utilizado un arbol general en su representacion enlazada, siendo la parte privada del TAD Agen:
private:
    struct celda{
        T elto;
        nodo padre, hizq, hder;
        celda(const T& e, nodo p=NODO_NULO): elto(e), padre(p), hizq(NODO_NULO), hder(NODO_NULO){}
    };
    nodo r;

Tambien hemos hecho uso de metodos publicos del TAD Agen:

-Agen<T> Agen();
Post: Crea y devuelve un Agen vacio.
-bool arbolVacio();
Post devuelve true si esta vacio y false si no lo esta.
-void insertarRaiz(const T& e);
Pre Existe un elemento e.
Post Inserta en la raiz un elemento si el arbol esta vacio
-const T& elemento(nodo n)const;
Pre El nodo n existe.
Post Devuelve el elemento del nodo n.
-nodo raiz() const;
Post Devuelve el nodo de la raiz y si no devuelve un nodo nulo.
-nodo hijoIzqdo(nodo n)const;
Pre el nodo n exista
Post devuelva el nodo izquierdo de n si existe si no un nodo nulo.
-void insertarHijoIzqdo(nodo n, const T& e);
Pre exista el nodo n y el elemento
Post Se inserte como hijo izquierdo del nodo n el elemento e.
-nodo hermDrcho(nodo n)const;
Pre exista el nodo n en el arbol.
Post devuelve el hermano derecho del nodo n si no existe que devuelva nodo_nulo.
*/