#include "../Grafos/alg_grafoMA.h"
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Ciudad {
    double x;
    double y;
};

struct LineaAerea {
    size_t ciudadA;
    size_t ciudadB;
    double coste;

    LineaAerea(size_t a = 0, size_t b = 0, double c = 0)
        : ciudadA(a), ciudadB(b), coste(c) {}
};

double distanciaEuclidea(const Ciudad& a, const Ciudad& b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<LineaAerea> Tombuctu2(
    const vector<Ciudad>& ciudades,
    const Grafo& carreteras
)
{
    const size_t n = carreteras.numVert();

    Particion islas(n);

    // 1. Agrupar ciudades que pertenecen a la misma isla
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (carreteras[i][j]) {
                islas.unir(islas.encontrar(i), islas.encontrar(j));
            }
        }
    }

    // 2. Crear una lista de representantes únicos de islas
    vector<size_t> representantes;

    for (size_t i = 0; i < n; i++) {
        size_t rep = islas.encontrar(i);

        bool existe = false;
        for (size_t j = 0; j < representantes.size(); j++) {
            if (representantes[j] == rep) {
                existe = true;
            }
        }

        if (!existe) {
            representantes.push_back(rep);
        }
    }

    const size_t numIslas = representantes.size();

    matriz<double> mejorCoste(numIslas, GrafoP<double>::INFINITO);
    matriz<LineaAerea> mejorLinea(numIslas);

    // 3. Para cada par de ciudades de islas distintas,
    // guardar la línea más corta entre esas dos islas
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {

            size_t repI = islas.encontrar(i);
            size_t repJ = islas.encontrar(j);

            if (repI != repJ) {
                size_t islaI = 0;
                size_t islaJ = 0;

                for (size_t k = 0; k < numIslas; k++) {
                    if (representantes[k] == repI) islaI = k;
                    if (representantes[k] == repJ) islaJ = k;
                }

                double d = distanciaEuclidea(ciudades[i], ciudades[j]);

                if (d < mejorCoste[islaI][islaJ]) {
                    mejorCoste[islaI][islaJ] = d;
                    mejorCoste[islaJ][islaI] = d;

                    mejorLinea[islaI][islaJ] = LineaAerea(i, j, d);
                    mejorLinea[islaJ][islaI] = LineaAerea(j, i, d);
                }
            }
        }
    }

    // 4. Devolver una línea por cada par de islas
    vector<LineaAerea> resultado;

    for (size_t i = 0; i < numIslas; i++) {
        for (size_t j = i + 1; j < numIslas; j++) {
            resultado.push_back(mejorLinea[i][j]);
        }
    }

    return resultado;
}