#include "../Grafos/alg_grafoPMC.h"
#include <vector>
#include <utility>

using std::vector;
typedef pair<typename GrafoP<int>::tCamino, int> Camino_Coste;

Camino_Coste ViajesMedios(const GrafoP<int>& Tren, const GrafoP<int>& Bus, const GrafoP<int>& Avion, typename GrafoP<int>::vertice Origen, 
typename GrafoP<int>::vertice Destino, int trenbus, int aeropuerto_tren_bus)
{
    typedef typename GrafoP<int>::vertice vertice;
    int N=Tren.numVert();

    vertice origenFicticio = 3 * N;
    vertice destinoFicticio = 3 * N + 1;

    //Deberiamos crear un supergrafo para calcular el coste minimo con dijkstra
    GrafoP<int> SuperGrafo(3*N + 2);

    //Primero vamos a rellenar las conexiones por el mismo medio
    for(size_t i=0; i<N;i++)
    {
        for(size_t j = 0; j < N; j++)
        {
            //El tren 
            SuperGrafo[i][j]=Tren[i][j];
            //Bus
            SuperGrafo[i+N][j+N]=Bus[i][j];
            //Avion
            SuperGrafo[i+2*N][j+2*N]=Avion[i][j];
        }
    }

    //Ahora las conexiones para los trasbordos del tren al bus y viceversa
    for(size_t i = 0; i < N; i++)
    {
        vertice tren = i;
        vertice bus = N + i;
        vertice avion = 2 * N + i;

        SuperGrafo[tren][bus] = trenbus;
        SuperGrafo[bus][tren] = trenbus;

        SuperGrafo[tren][avion] = aeropuerto_tren_bus;
        SuperGrafo[avion][tren] = aeropuerto_tren_bus;

        SuperGrafo[bus][avion] = aeropuerto_tren_bus;
        SuperGrafo[avion][bus] = aeropuerto_tren_bus;
    }
    //Ahora necesitamos crear orgienes ficticios 
    //Origen ficticio conectado a la ciudad origen en los 3 medios
    SuperGrafo[origenFicticio][Origen] = 0;          // origen en tren
    SuperGrafo[origenFicticio][N + Origen] = 0;      // origen en bus
    SuperGrafo[origenFicticio][2 * N + Origen] = 0;  // origen en avión

    //Destino Ficticio
    SuperGrafo[Destino][destinoFicticio]=0;
    SuperGrafo[Destino + N][destinoFicticio]=0;
    SuperGrafo[Destino + 2*N][destinoFicticio]=0;

    //Para ello hay que ir aplicando dijkstra 
    vector<vertice> Antecesores(SuperGrafo.numVert());
    vector<int> DesdeOrigen=Dijkstra(SuperGrafo, origenFicticio, Antecesores);

    //Construimos el camino

    int CosteMinimo=DesdeOrigen[destinoFicticio];
    typename GrafoP<int>::tCamino Camino;
    vertice v=destinoFicticio;

    Camino.insertar(v);

    while(v!=origenFicticio)
    {
        v=Antecesores[v];
        Camino.insertar(v);
    }

    return make_pair(Camino, CosteMinimo);

}
