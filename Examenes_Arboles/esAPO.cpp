//Comprobar si es un APO


template<typename T>
bool hijosMayores(const Abin<T>& A, typename Abin<T>::nodo na)
{
    if(na==Abin<T>::NODO_NULO)
    {
        return true;
    }

    if(A.hijoIzqdo(na)!= Abin<T>::NODO_NULO)
    {
        if(A.elemento(na)>A.elemento(A.hijoIzqdo(na)))
        {
            return false;
        }
    }
    if(A.hijoDrcho(na)!= Abin<T>::NODO_NULO)
    {
        if(A.elemento(na)>A.elemento(A.hijoDrcho(na)))
        {
            return false;
        }
    }

    return hijosMayores(A, A.hijoIzqdo(na)) && hijosMayores(A, A.hijoDrcho(na));
}


template<typename T>
bool esCompleto(cosnt Abin<T>& A)
{
    Cola c;
    bool nuloPrevio = false;

    c.push(A.raiz());
    while (!c.vacia())
    {
        typename Abin<T>::nodo actual = c.frente();
        c.pop();

        if (actual == Abin<T>::NODO_NULO)
        {
            nuloPrevio = true;
        }
        else
        {
            if (nuloPrevio)
                return false;

            c.push(A.hijoIzqdo(actual));
            c.push(A.hijoDrcho(actual));
        }
    }

    return true;
}




template<typename T>
bool esAPO(const Abin<T>& A)
{
    return esCompleto(A) && hijosMayores(A, A.raiz());
}



//Todo en una funcion
template<typename T>
bool esAPO(const Abin<T>& A)
{
    if(A.vacio())
        return true;

    Cola<typename Abin<T>::nodo> c;
    bool nuloPrevio = false;

    c.push(A.raiz());

    while(!c.vacia())
    {
        typename Abin<T>::nodo actual = c.frente();
        c.pop();

        if(actual == Abin<T>::NODO_NULO)
        {
            nuloPrevio = true;
        }
        else
        {
            if(nuloPrevio)
                return false;

            typename Abin<T>::nodo hi = A.hijoIzqdo(actual);
            typename Abin<T>::nodo hd = A.hijoDrcho(actual);

            if(hi != Abin<T>::NODO_NULO &&
               A.elemento(actual) > A.elemento(hi))
            {
                return false;
            }

            if(hd != Abin<T>::NODO_NULO &&
               A.elemento(actual) > A.elemento(hd))
            {
                return false;
            }

            c.push(hi);
            c.push(hd);
        }
    }

    return true;
}