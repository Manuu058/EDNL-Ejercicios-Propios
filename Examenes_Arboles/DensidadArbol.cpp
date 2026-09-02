//Calcular la densidad
//El grado maximo es el numero de hijos del nodo que mas tenga entre las hojas 

template<typename T>
void GradoMaximo(const Agen<T>& A, typename Agen<T>::nodo na, int &nGrado)
{
    if(na!=Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo=A.hijoIzqdo(na);

        int nHijos=0;
        while(hijo!=Agen<T>::NODO_NULO)
        {
            nHijos++;

            GradoMaximo(A, hijo, nGrado);

            hijo=A.hermDrcho(hijo);
        }

        if(nHijos>nGrado)
        {
            nGrado=nHijos;
        }
    }
}
template<typename T>
void nHojas(const Agen<T>& A, typename Agen<T>::nodo na, int &hojas)
{
    if(na!=Agen<T>::NODO_NULO)
    {
        typename Agen<T>::nodo hijo=A.hijoIzqdo(na);
        
        if(hijo==Agen<T>::NODO_NULO)
        {
            hojas++;
        }
        while(hijo!=Agen<T>::NODO_NULO)
        {
            nHojas(A, hijo, hojas);
            hijo=A.hermDrcho(hijo);
        }
    }
}


template<typename T>
double DensidadArbol(const Agen<T>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    int nGrado=0;
    GradoMaximo(A, A.raiz(), nGrado);
    int hojas=0;
    nHojas(A, A.raiz(), hojas);

    return nGrado/hojas;
}