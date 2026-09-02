//Riqueza Acumulada
//Arbol general donde sus nodos pueden estar vivos o muertos, me dan un nodo n para que la reparta entre sus herederos.
//Herederos son sus hijos y los muertos los hijos de estos. Si sobra se lo queda lo publico. 

struct persona{
    bool estado;
    int cantidad;


};


bool tieneDescendenciaViva(Agen<persona> &A, typename Agen<persona>::nodo n)
{

    bool descendencia = false;

    if (n == A.NODO_NULO)
        return false;

    typename Agen<persona>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO && !descendencia)
    {

        if (A.elemento(hijo).estado)
            return true;

        else if (A.hijoIzqdo(hijo) != A.NODO_NULO)
           if (tieneDescendenciaViva(A, A.hijoIzqdo(hijo)))
           {
                descendencia = true;
           }
        hijo = A.hermDrcho(hijo);
    }

    return descendencia;
}

void Reparto(Agen<persona>& A, typename Agen<persona>::nodo na)
{
    if(na != Agen<persona>::NODO_NULO)
    {
        if(A.elemento(na).cantidad > 0)
        {
            //Cuento la descendencia que esta viva 

            typename Agen<persona>::nodo HijoI= A.hijoIzqdo(na);

            int vivos = 0;

            while(HijoI != Agen<persona>::NODO_NULO)
            {
                if(A.elemento(HijoI).estado)
                {
                    vivos++;
                }
                else{
                    if(tieneDescendenciaViva(A,HijoI))
                    {
                        vivos++;
                    }
                }

                HijoI=A.hermDrcho(HijoI);
            }

            int recibe=0;

            if(vivos>0)
            {
                recibe=A.elemento(na).cantidad/vivos;
                A.elemento(na).cantidad = 0;
            }

            //Reparto entre todos los vivos
            HijoI= A.hijoIzqdo(na);
            while(HijoI != Agen<persona>::NODO_NULO)
            {
                if(A.elemento(HijoI).estado)
                {
                    A.elemento(HijoI).cantidad+=recibe;
                }
                else{
                    if (tieneDescendenciaViva(A, HijoI))
                    {
                        A.elemento(HijoI).cantidad = recibe;
                        Reparto(A, HijoI);
                    }
                }
                 HijoI=A.hermDrcho(HijoI);

            }

        }
    }
}