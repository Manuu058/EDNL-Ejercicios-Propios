/*
Dado un árbol binario de un tipo genérico T calcular el número de nodos que siendo hermanos entre
sí tienen misma raíz y sus subárboles son reflejados (respecto a sus elementos)
*/
#include "abin.h"

using namespace std;

template<typename T>
bool ReflejadoSub(const Abin<T>& A, typename Abin<T>::nodo hi, typename Abin<T>::nodo hd)
{
    if(hi==Abin<T>::NODO_NULO && hd==Abin<T>::NODO_NULO)
    {
        return true;
    }
    if (hi == Abin<T>::NODO_NULO || hd == Abin<T>::NODO_NULO)
        return false;

    return A.elemento(hi) == A.elemento(hd) &&
           ReflejadoSub(A, A.hijoIzqdo(hi), A.hijoDrcho(hd)) &&
           ReflejadoSub(A, A.hijoDrcho(hi), A.hijoIzqdo(hd));
}

template<typename T>
void NodosRefelajadosRec(const Abin<T>& A, typename Abin<T>::nodo na, int& N)
{
    if(na!=Abin<T>::NODO_NULO)
    {

        typename Abin<T>::nodo HijoI=A.hijoIzqdo(na);
        typename Abin<T>::nodo HijoD=A.hijoDrcho(na);
        if(HijoI!=Abin<T>::NODO_NULO && HijoD!=Abin<T>::NODO_NULO && A.elemento(HijoI)==A.elemento(HijoD))
        {
            if(ReflejadoSub(A, HijoI, HijoD))
            {
                N++;
            }
        }

        NodosRefelajadosRec(A, HijoI, N);
        NodosRefelajadosRec(A, HijoD, N);
    }
}

template<typename T>
int NodosRefelajados(const Abin<T>& A)
{
    if(!A.vacio())
    {
        int N=0;
        NodosRefelajadosRec(A, A.raiz(), N);
    }
    elementos{
        return 0;
    }
}

