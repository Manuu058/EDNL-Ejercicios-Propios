//Grecoland2
//Formado por dos ciudades, con sus respectivas costas. El coste de construccion se considera irrelevante, viajar entre todas las ciudades de las dos islas(huele a Floyd)
//Distancia euclidea
//TODOS LOS TRAYECTOS SON IGUAL DE IMPORTANTE=hay que comparar todos y quedarse con el minimo.
#include "alg_GRAFOPMC.h"
#include <cmath>
using namespace std;

struct Ciudad{
    double x,y;

    Ciudad(double x_, double y_): x(x_), y(y_){}
};

double DistanciaEuclidea(const Ciudad& A, const Ciudad& B)
{
    return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

struct Puente{
    size_t CiudadA, CiudadB;
    double coste;

    Puente(size_t a, size_t b, double c): CiudadA(a), CiudadB(b), coste(c){}
};

Puente Grecoland2(const matriz<bool>& Fobos, const matriz<bool>& Deimos, vector<Ciudad>& CiudadFobos, vector<Ciudad>& CiudadDeimos, vector<bool>& CostaFobos, 
    vector<bool>& CostaDeimos)
{
    int N1=Fobos.size();
    int N2=Deimos.size();
    int N=N1+N2;

    //Creamos el grafo total con las distancias
    GrafoP<double> Grecoland(N);

    //Metemos las ciudades de Fobos
    for(size_t i=0; i<N1; i++)
    {
        for(size_t j=0; j<N1; j++)
        {
            if(Fobos[i][j])
            {
                double distancia=DistanciaEuclidea(CiudadFobos[i], CiudadFobos[j]);

                Grecoland[i][j]=distancia;
            }
        }
    }
    //Metemos Deimos
    for(size_t i=0; i<N2; i++)
    {
        for(size_t j=0; j<N2; j++)
        {
            if(Deimos[i][j])
            {
                double distancia=DistanciaEuclidea(CiudadDeimos[i], CiudadDeimos[j]);

                Grecoland[i+N1][j+N1]=distancia;
            }
        }
    }

    //Ahora buscamos el menor coste de los puentes 

    double costeMin=GrafoP<double>::INFINITO;
    Puente bueno(0, 0, GrafoP<double>::INFINITO);
    for(size_t i=0; i<N1; i++)
    {
        for(size_t j=0; j<N2; j++)
        {
            if(CostaFobos[i] && CostaDeimos[j])
            {
               GrafoP<double> aux(Grecoland);

               double distancia=DistanciaEuclidea(CiudadFobos[i], CiudadDeimos[j]);

               aux[i][j+N1]=distancia;
               aux[j+N1][i]=distancia;

               //Ahora teniendo solo este puente comparamos metiendo floyd 
                matriz<typename GrafoP<double>::vertice> Antecesores(Grecoland.numVert());
                matriz<double> CostesMinimos=Floyd(aux, Antecesores);

                //Recorro floyd porque solo tengo metido ese puente y lo recorro con todas las ciudades 
                double costes=0;
                for(size_t k=0; k<N; k++)
                {
                    for(size_t h=0; h<N; h++)
                    {
                        costes+=CostesMinimos[k][h];
                    }
                }
                
                if(costes<costeMin)
                {
                    costeMin=costes;
                    bueno.CiudadA=i;
                    bueno.CiudadB=j;
                    bueno.coste=costes;
                }

            }
        }
    }

    return bueno;
}