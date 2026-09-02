template<typename T>
bool comprobarAVLRec(const Abin<T>& A,
                     typename Abin<T>::nodo na,
                     const T* min,
                     const T* max,
                     int& altura)
{
    if(na == Abin<T>::NODO_NULO)
    {
        altura = -1;
        return true;
    }

    T valor = A.elemento(na);

    if((min != nullptr && valor <= *min) ||
       (max != nullptr && valor >= *max))
    {
        return false;
    }

    int alturaIzq, alturaDer;

    bool izq = comprobarAVLRec(A, A.hijoIzqdo(na), min, &valor, alturaIzq);
    bool der = comprobarAVLRec(A, A.hijoDrcho(na), &valor, max, alturaDer);

    altura = 1 + max(alturaIzq, alturaIzq);

    return izq &&
           der &&
           abs(alturaIzq - alturaDer) <= 1;
}

template<typename T>
bool esAVL(const Abin<T>& A)
{
    if(A.vacio())
        return true;

    int altura;

    return comprobarAVLRec(A, A.raiz(), nullptr, nullptr, altura);
}