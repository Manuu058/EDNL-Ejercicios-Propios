template <typename tCoste>
vector<bool> alcanzables(
    const GrafoP<tCoste>& carretera,
    const GrafoP<tCoste>& tren,
    const GrafoP<tCoste>& avion,
    typename GrafoP<tCoste>::vertice origen,
    Transporte alergia,
    tCoste dinero)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const GrafoP<tCoste>* A;
    const GrafoP<tCoste>* B;

    int N=carretera.numVert();

    if(alergia == AVION)
    {
        A = &carretera;
        B = &tren;
    }
    else if(alergia == TREN)
    {
        A = &carretera;
        B = &avion;
    }
    else
    {
        A = &tren;
        B = &avion;
    }

    vector<vertice> P1(N);
    vector<vertice> P2(N);

    vector<tCoste> D1 = Dijkstra(*A, origen, P1);
    vector<tCoste> D2 = Dijkstra(*B, origen, P2);

    vector<bool> alcanzable(N, false);

    for(size_t i = 0; i < N; i++)
    {
        if(min(D1[i], D2[i]) <= dinero)
            alcanzable[i] = true;
    }

    return alcanzable;
}