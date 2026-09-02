#include <iostream>
#include "agen.h"
//Funcion auxiliar para contar el numero de hijos de los nodos
template <typename T>
int nHijos(typename Agen<T>::nodo na, const Agen<T>& A)
{
    if(na==Agen<T>::NODO_NULO)
    {
        return 0;
    }
    int n=0;

    typename Agen<T>::nodo hijo=A.hijoizq(na);
    while(hijo!=Agen<T>::NODO_NULO)
    {
        n++;
        hijo=A.hijodcho(hijo);
    }
    return n;
}

template <typename T>
bool SimilarRec(const Agen<T>& A,typename Agen<T>::nodo na,const Agen<T>& B,typename Agen<T>::nodo nb)
{
    if(na==Agen<T>::NODO_NULO && nb==Agen<T>::NODO_NULO)
    {
        return true;
    }
    else{
        if((na==Agen<T>::NODO_NULO && nb!=Agen<T>::NODO_NULO) || (na!=Agen<T>::NODO_NULO && nb==Agen<T>::NODO_NULO))
        {
            return false;
        }
        else{
            if(nHijos(na,A)!=nhijos(nb,B))
            {
                return false;
            }
            else{
                if(nHijos(na,A)==0)
                {
                    return A.elemento(na)==B.elemento(nb);
                }
                else{
                    typename Agen<T>::nodo hijoA=A.hijoizq(na);
                    typename Agen<T>::nodo hijoB=B.hijoizq(nb);

                    bool valor=true;
                    while(hijoA!= Agen<T>::NODO_NULO && hijoB!= Agen<T>::NODO_NULO && valor)
                    {
                        valor &= SimilarRec(A,hijoA, B,hijoB);
                        hijoA=A.hermanoDrcho(hijoA);
                        hijoB=B.hermanoDrcho(hijoB);
                    }
                    return valor;
                }
            }
        }
    }
}
template <typename T>
bool Similar(const Agen<T>& A, const Agen<T>& B)
{
    if(A.vacio() && B.vacio())
    {
        return true;
    }
    return SimilarRec(A,A.raiz(), B,B.raiz());
}

