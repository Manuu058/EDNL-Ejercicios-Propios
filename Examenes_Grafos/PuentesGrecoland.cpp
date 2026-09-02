#include "../Grafos/alg_grafoPMC.h"
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Ciudad {
    double x;
    double y;
};

double distanciaEuclidea(const Ciudad& a, const Ciudad& b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double viajeGrecoland(
    const vector<Ciudad>& ciudadesFobos,
    const vector<Ciudad>& ciudadesDeimos,
    const vector<bool>& ciudadCosteraFobos,
    const vector<bool>& ciudadCosteraDeimos,
    typename GrafoP<double>::vertice origen,
    typename GrafoP<double>::vertice destino
) {
    const size_t nFobos = ciudadesFobos.size();
    const size_t nDeimos = ciudadesDeimos.size();
    const size_t nTotal = nFobos + nDeimos;

    GrafoP<double> Grafo(nTotal);

    double distanciaMaxima = 0;

    // Construir carreteras dentro de Fobos
    for (size_t i = 0; i < nFobos; i++) {
        for (size_t j = 0; j < nFobos; j++) {
            if (i == j) {
                Grafo[i][j] = 0;
            } else {
                double distancia = distanciaEuclidea(ciudadesFobos[i], ciudadesFobos[j]);
                Grafo[i][j] = distancia;
                distanciaMaxima = max(distanciaMaxima, distancia);
            }
        }
    }

    // Construir carreteras dentro de Deimos
    for (size_t i = 0; i < nDeimos; i++) {
        for (size_t j = 0; j < nDeimos; j++) {
            size_t gi = i + nFobos;
            size_t gj = j + nFobos;

            if (i == j) {
                Grafo[gi][gj] = 0;
            } else {
                double distancia = distanciaEuclidea(ciudadesDeimos[i], ciudadesDeimos[j]);
                Grafo[gi][gj] = distancia;
                distanciaMaxima = max(distanciaMaxima, distancia);
            }
        }
    }

    // Construir posibles puentes entre ciudades costeras
    for (size_t i = 0; i < nFobos; i++) {
        for (size_t j = 0; j < nDeimos; j++) {
            if (ciudadCosteraFobos[i] && ciudadCosteraDeimos[j]) {
                size_t fobosGlobal = i;
                size_t deimosGlobal = j + nFobos;

                double costePuente =
                    distanciaEuclidea(ciudadesFobos[i], ciudadesDeimos[j])
                    + distanciaMaxima;

                Grafo[fobosGlobal][deimosGlobal] = costePuente;
                Grafo[deimosGlobal][fobosGlobal] = costePuente;
            }
        }
    }

    // Reconstruir el archipiélago al mínimo coste
    Grafo = Kruskall(Grafo);

    // Quitar la penalización artificial de los puentes
    for (size_t i = 0; i < Grafo.numVert(); i++) {
        for (size_t j = 0; j < Grafo.numVert(); j++) {
            if (Grafo[i][j] != GrafoP<double>::INFINITO &&
                Grafo[i][j] > distanciaMaxima) {
                Grafo[i][j] -= distanciaMaxima;
            }
        }
    }

    vector<typename GrafoP<double>::vertice> P(Grafo.numVert());

    vector<double> costeViajar = Dijkstra(Grafo, origen, P);

    return costeViajar[destino];
}

