
//Chat

template<typename T>
bool Ascendientes(const Abin<T>& A, typename Abin<T>::nodo na, const T& e)
{
    if (na == A.raiz())
        return true;

    typename Abin<T>::nodo p = A.padre(na);

    if (A.elemento(p) <= e)
        return Ascendientes(A, p, e);
    else
        return false;
}

template<typename T>
bool Descendientes(const Abin<T>& A, typename Abin<T>::nodo na, const T& e)
{
    if (na == Abin<T>::NODO_NULO)
        return true;

    if (A.elemento(na) < e)
        return false;

    return Descendientes(A, A.hijoIzqdo(na), e) &&
           Descendientes(A, A.hijoDrcho(na), e);
}

template<typename T>
void eliminarSubarbol(Abin<T>& A, typename Abin<T>::nodo na)
{
    if (na != Abin<T>::NODO_NULO)
    {
        eliminarSubarbol(A, A.hijoIzqdo(na));
        eliminarSubarbol(A, A.hijoDrcho(na));

        if (na == A.raiz())
        {
            A.eliminarRaiz();
        }
        else
        {
            typename Abin<T>::nodo p = A.padre(na);

            if (A.hijoIzqdo(p) == na)
                A.eliminarHijoIzqdo(p);
            else
                A.eliminarHijoDrcho(p);
        }
    }
}

template<typename T>
void DescAscBinarioRec(Abin<T>& A, typename Abin<T>::nodo na)
{
    if (na != Abin<T>::NODO_NULO)
    {
        if (Ascendientes(A, na, A.elemento(na)) &&
            Descendientes(A, na, A.elemento(na)))
        {
            eliminarSubarbol(A, A.hijoIzqdo(na));
            eliminarSubarbol(A, A.hijoDrcho(na));
        }
        else
        {
            DescAscBinarioRec(A, A.hijoIzqdo(na));
            DescAscBinarioRec(A, A.hijoDrcho(na));
        }
    }
}

template<typename T>
void DescAscBinario(Abin<T>& A)
{
    if (!A.vacio())
        DescAscBinarioRec(A, A.raiz());
}