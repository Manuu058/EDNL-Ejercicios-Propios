

template <typename tCoste>
matriz<tCoste> Toxicidad(typename GrafoP<tCoste>::vertice Capital, GrafoP<tCoste>& Zuelandia)
{
    GrafoP<tCoste> Copia(Zuelandia);

    //Hago imposible ir a la capital 
    for(size_t i=0; i<Zuelandia.numVert();i++)
    {
        Copia[i][Capital]=Copia[Capital][i]=GrafoP<tCoste>::INFINITO;
    }

    matriz<typename GrafoP<tCoste>::vertice> P(Copia.numVert());
    vector<typename GrafoP<tCoste>::vertice> p(Copia.numVert());

    //Hago los costes entre todos pero sin ir a capital
    matriz<tCoste> Costes=Floyd(Copia, P);

    //Ahora tengo que añadir los destinos hacia capital o las salidas
    vector<tCoste> desdeCapital=Dijkstra(Zuelandia, Capital, p);
    vector<tCoste> haciaCapital=DijkstraInv(Zuelandia, Capital, p);

    for(size_t i=0;i<Copia.numVert();i++)
    {
        Costes[i][Capital]=haciaCapital[i];
        Costes[Capital][i]=desdeCapital[i];
    }
    
    return Costes;

}


matriz<T> djkistrainverso(const Grafo<T>& g, int origen, vector<int>& antecesores){
    // Implementación del algoritmo de Dijkstra inverso
    // Similar a la implementación estándar pero recorriendo el grafo en sentido inverso
    Grafo<T> g_inverso(g.size());
    for(int i=0; i<g.size(); i++){
        for(int j=0; j<g.size(); j++){
            // Aquí se recorrería el grafo en sentido inverso
            g_inverso[i][j]=g[j][i];
        }
    }

    return djkistra(g_inverso, origen, antecesores);
}