//Subarbol Izquierdo menor que el derecho, esto claramente es comprobar un ABB

template <typename T>
bool EsABB(const Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return EsABB_rec(A, A.raiz());
    }
    else{
        return true;
    }
}

template <typename T>
bool EsABB_rec(const Abin<T>& A, typename Abin<T>::nodo na)
{
    if(na!=Abin<T>::NODO_NULO)
    {
        return todos_min(A, A.elemento(na), A.hijoIzqdo(na)) && todos_max(A, A.elemento(na), A.hijoDrcho(na)) && EsABB_rec(A,A.hijoIzqdo(na)) && EsABB_rec(A,A.hijoDrcho(na));
    }
    else{
        return true;
    }
}

template <typename T>
bool todos_min(const Abin<T>& A,const T& elemento, typename Abin<T>::nodo na)
{
    if(na!=Abin<T>::NODO_NULO)
    {
        if(elemento>A.elemento(na))
        {
            return todos_min(A, elemento, A.hijoIzqdo(na)) && todos_min(A, elemento, A.hijoDrcho(na));
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
}

template <typename T>
bool todos_max(const Abin<T>& A,const T& elemento, typename Abin<T>::nodo na)
{
    if(na!=Abin<T>::NODO_NULO)
    {
        if(elemento<A.elemento(na))
        {
            return todos_max(A, elemento, A.hijoIzqdo(na)) && todos_max(A, elemento, A.hijoDrcho(na));
        }
        else{
            return false;
        }
    }
    else{
        return true;
    }
}




///Ejercicio chat
template <typename T>
bool EsABB_rec(const Abin<T>& A,
               typename Abin<T>::nodo na,
               const T* min,
               const T* max)
{
    if(na == Abin<T>::NODO_NULO)
        return true;

    T e = A.elemento(na);

    if((min != nullptr && e <= *min) ||
       (max != nullptr && e >= *max))
        return false;

    return EsABB_rec(A, A.hijoIzqdo(na), min, &e) &&
           EsABB_rec(A, A.hijoDrcho(na), &e, max);
}

template <typename T>
bool EsABB(const Abin<T>& A)
{
    if(A.vacio())
        return true;

    return EsABB_rec(A, A.raiz(), nullptr, nullptr);
}