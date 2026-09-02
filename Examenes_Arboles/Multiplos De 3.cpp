//Todos menos el nodo, comprobar multiplo y hacer el porcentaje.
template<typename T>
int Descendientes(const Agen<T>& A, typename Agen<T>::nodo na)
{
    if(na == Agen<T>::NODO_NULO)
    {
        return 0;
    }

    int total = 0;

    typename Agen<T>::nodo hijo = A.hijoIzqdo(na);

    while(hijo != Agen<T>::NODO_NULO)
    {
        total = total + 1; // cuento al hijo

        total = total + Descendientes(A, hijo); // cuento sus descendientes

        hijo = A.hermDrcho(hijo); // paso al siguiente hermano
    }

    return total;
}

template<typename T>
int DescendientesMultiplos(const Agen<T>& A, typename Agen<T>::nodo na)
{
    if(na == Agen<T>::NODO_NULO)
    {
        return 0;
    }

    int total = 0;

    typename Agen<T>::nodo hijo = A.hijoIzqdo(na);

    while(hijo != Agen<T>::NODO_NULO)
    {
        if(A.elemento(hijo)%3==0)
        {
            total= total +1;
        }

        total = total + DescendientesMultiplos(A, hijo); // cuento sus descendientes

        hijo = A.hermDrcho(hijo); // paso al siguiente hermano
    }

    return total;
}



template<typename T>
double PorcentajeMultiplo3(const Agen<T>& A)
{
    if(A.vacio())
    {
        return 0;
    }

    return (DescendientesMultiplos(A, A.raiz())/Descendientes(A, A.raiz()))*100;
}