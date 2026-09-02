//Ciudades Rebeldes
//Viajar entre dos ciudades cualesquiera de un pais llamado Zuelandia
//Solo un sentido de la circulacion, arcos.
//Ciudades tomadas
//Carreteras cortadas
//Pasar por la capital al 100x100
#include<iostream>
#include<vector>


typedef std::pair(size_t, size_t) Carretera;

template <typename tCoste>
matriz<tCoste> CiudadesRebeldes(GrafoP<tCoste>& Zuelandia, vector<bool>& CiudadesTomadas, vector<Carretera>& CarreteraCortada, 
    typename GrafoP<tCoste>::vertice Capital)
{
    //Primero habra que eliminar las Ciudades que estan tomadas
    for(size_t i=0;i<CiudadesTomadas.size();i++)
    {
        if(CiudadesTomadas[i])
        {
           for(size_t j=0;j<CiudadesTomadas.size();j++)
           {
                Zuelandia[i][j]=GrafoP<tCoste>::INFINITO;
                Zuelandia[j][i]=GrafoP<tCoste>::INFINITO;
           }
        }
    }

    //Segundo quitar las carreteras cortadas
    for(Carretera c : CarreteraCortada)
    {
            Zuelandia[c.first][c.second]=GrafoP<tCoste>::INFINITO;
    }

    //Ahora declaramos todo lo necesario para aplicar dijkstra ya que como tenemos que pasar por la capital habra que hacer 
    //todas la combinaciones posibles hasta la Capital y luego todas desde la capital.

    //Necesitamos un vector de precesores
    vector<typename GrafoP<tCoste>::vertice>P(Zuelandia.numVert());
    vector<tCoste> DesdeCapital=Dijkstra(Zuelandia, Capital, P);
    vector<tCoste> HaciaCapital=DijkstraInv(Zuelandia, Capital, P);

    //Ahora montamos la matriz que hay que devolver
    matriz<tCoste> viaje(Zuelandia.numVert(), GrafoP<tCoste>::INFINITO);

    for(size_t i=0;i<Zuelandia.numVert();i++)
    {
        for(size_t j=0;j<Zuelandia.numVert();j++)
        {
            if(i==j)
            {
                viaje[i][j]=0;
            }
            else{
                viaje[i][j]=suma(HaciaCapital[i], DesdeCapital[j]);
            }
        }
    }

    return viaje;
}

//DijkstraInverso
template <typename tCoste>
vector<tCoste> DijkstraInv(
    const GrafoP<tCoste>& G,
    typename GrafoP<tCoste>::vertice destino,
    vector<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    size_t n = G.numVert();

    vector<tCoste> D(n);
    vector<bool> S(n, false);

    // Inicialización
    for(vertice i = 0; i < n; i++)
    {
        D[i] = G[i][destino];
        P[i] = destino;
    }

    D[destino] = 0;
    S[destino] = true;

    // Algoritmo
    for(size_t i = 1; i < n; i++)
    {
        tCoste minimo = GrafoP<tCoste>::INFINITO;
        vertice w;

        // Buscar mínimo
        for(vertice j = 0; j < n; j++)
        {
            if(!S[j] && D[j] < minimo)
            {
                minimo = D[j];
                w = j;
            }
        }

        S[w] = true;

        // Relajar
        for(vertice v = 0; v < n; v++)
        {
            if(!S[v])
            {
                if(suma(G[v][w], D[w]) < D[v])
                {
                    D[v] = suma(G[v][w], D[w]);
                    P[v] = w;
                }
            }
        }
    }

    return D;
}
