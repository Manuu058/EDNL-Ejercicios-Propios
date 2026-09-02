template <typename T>
int numHijos(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    else
    {

        int numHijos = 0;

        typename Agen<T>::nodo hijos = A.hijoIzqdo(n);

        while (hijos != A.NODO_NULO)
        {
            numHijos++;
            hijos = A.hermDrcho(hijos);
        }

        return numHijos;
    }
}

template <typename T>
void nodosVerdes(const Agen<T> &A, typename Agen<T>::nodo n, int &nVerdes)
{

    if (n == A.NODO_NULO)
        return;

    int numNietos = 0;

    typename Agen<T>::nodo hijos = A.hijoIzqdo(n);

    while (hijos != A.NODO_NULO)
    {
        numNietos += numHijos(A, hijos);
        nodosVerdes(A, hijos, nVerdes);
        hijos = A.hermDrcho(hijos);
    }

    if (numNietos == 3)
    {
        nVerdes++;
    }
}