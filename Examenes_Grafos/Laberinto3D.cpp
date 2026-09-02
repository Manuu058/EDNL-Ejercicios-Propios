
#include "../Grafos/alg_grafoPMC.h"
#include <vector>
#include <utility>

using std::vector;

typedef std::pair<typename GrafoP<int>::tCamino, int> Camino_Coste;

struct Casilla
{
    size_t x, y, z;

    Casilla(size_t i, size_t j, size_t k) : x{i}, y{j}, z{k} {}
};

typedef std::pair<Casilla, Casilla> Pared;

typename GrafoP<int>::vertice CasillaToVertice(const Casilla& c, int N)
{
    return c.x + c.y * N + c.z * N * N;
}

Camino_Coste escaparLaberinto(int N,
                              const vector<Pared>& Paredes,
                              const Casilla& entrada,
                              const Casilla& salida)
{
    GrafoP<int> laberinto(N * N * N);

    // Construir conexiones entre casillas vecinas
    for (size_t z = 0; z < N; z++)
    {
        for (size_t y = 0; y < N; y++)
        {
            for (size_t x = 0; x < N; x++)
            {
                typename GrafoP<int>::vertice posActual =
                    CasillaToVertice(Casilla(x, y, z), N);

                // IZQUIERDA
                if (x > 0)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x - 1, y, z), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }

                // DERECHA
                if (x + 1 < N)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x + 1, y, z), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }

                // ATRÁS
                if (y > 0)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x, y - 1, z), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }

                // ADELANTE
                if (y + 1 < N)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x, y + 1, z), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }

                // ABAJO
                if (z > 0)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x, y, z - 1), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }

                // ARRIBA
                if (z + 1 < N)
                {
                    typename GrafoP<int>::vertice v =
                        CasillaToVertice(Casilla(x, y, z + 1), N);

                    laberinto[posActual][v] = 1;
                    laberinto[v][posActual] = 1;
                }
            }
        }
    }

    // Colocar paredes
    for (const Pared& p : Paredes)
    {
        typename GrafoP<int>::vertice v1 = CasillaToVertice(p.first, N);
        typename GrafoP<int>::vertice v2 = CasillaToVertice(p.second, N);

        laberinto[v1][v2] = GrafoP<int>::INFINITO;
        laberinto[v2][v1] = GrafoP<int>::INFINITO;
    }

    typename GrafoP<int>::vertice vertEntrada = CasillaToVertice(entrada, N);
    typename GrafoP<int>::vertice vertSalida = CasillaToVertice(salida, N);

    vector<typename GrafoP<int>::vertice> P(laberinto.numVert());

    vector<int> Coste = Dijkstra(laberinto, vertEntrada, P);

    int costeTotal = Coste[vertSalida];

    typename GrafoP<int>::tCamino C;

    // Si no hay camino
    if (costeTotal == GrafoP<int>::INFINITO)
    {
        return std::make_pair(C, costeTotal);
    }

    // Reconstruir camino desde salida hasta entrada
    typename GrafoP<int>::vertice v = vertSalida;

    C.insertar(v, C.primera());

    while (v != vertEntrada)
    {
        v = P[v];
        C.insertar(v, C.primera());
    }

    return std::make_pair(C, costeTotal);
}