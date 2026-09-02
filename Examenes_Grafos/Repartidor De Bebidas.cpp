//Para realizar este ejercicio necesitas la distancia minima entre todos los pares, eso es FLOYD

//Necesito un cliente con una cantidad de pedido.
struct Cliente
{
    int ctd;

    int pedido(){
        return ctd;
    }

    void entregar(int a) 
    {
        ctd-= a;
    }
};

//Necesito una funcion para averiguar la ubicacion mas cercana, devolvera un vertice y le tendre que pasar los costes(Floyd), donde estoy y los clientes repartidos.

typename GrafoP<double>::vertice UbicacionCercana(const matriz<double>& costesCaminos, typename GrafoP<double>::vertice actual, vector<bool>& clientesRepartidos)
{

    typename GrafoP<double>::vertice destino=actual;
    double distanciacercana = GrafoP<double>::INFINITO;

    for(size_t i=0; i<clientesRepartidos.size();i++)
    {
        if(clientesRepartidos[i]==false)
        {   
            if(costesCaminos[actual][i]<distanciacercana)
            {
                distanciacercana=costesCaminos[actual][i];
                destino=i;
            }
        }
    }

    return destino;
}

//El subprograma pide la distancia total recorrida
double RepartidorBebidas(const GrafoP<double>& reparto, int capacidadMax, vector<Cliente>& clientes,typename GrafoP<double>::vertice fabrica)
{
    //Necesitaremos una variable con la carga actual
    int cargaActual=capacidadMax;
    //Donde esta actualmente
    typename GrafoP<double>::vertice actual=fabrica;
    //Los kilometros totales
    double recorridototal=0;
    //Un vector de booleanos para ir marcando cuales estan compleados
    vector<bool> ClientesRealizados(reparto.numVert(), false);
    ClientesRealizados[fabrica] = true;
    //Aplicamos Floyd para saber las distancias minimas entre todos los puntos 
    //Floyd devuelve un devuelve y necesita un grafo y precesores(matriz)

    matriz<typename GrafoP<double>::vertice> P(reparto.numVert());
    matriz<double> costecaminos = Floyd(reparto, P);

    //Buscamos para el bucle la cantidad de repartidos que nos quedan
    int cantidad=0;
    for(size_t i=0; i<ClientesRealizados.size();i++)
    {
        if(ClientesRealizados[i]==false)
        {
            cantidad++;
        }
    }
    //Comenzamos el reparto
    typename GrafoP<double>::vertice destino=actual;
    while(cantidad > 0)
    {
        destino = UbicacionCercana(costecaminos, actual, ClientesRealizados);
        
        recorridototal += costecaminos[actual][destino];

        actual = destino;

        int pedidoCliente = clientes[actual].pedido();

        if(pedidoCliente > cargaActual)
        {
            clientes[actual].entregar(cargaActual);

            recorridototal += costecaminos[actual][fabrica];
            actual = fabrica;
            cargaActual = capacidadMax;
        }
        else
        {
            clientes[actual].entregar(pedidoCliente);
            cargaActual -= pedidoCliente;

            cantidad--;
            ClientesRealizados[actual] = true;
        }
    }
    if(actual != fabrica)//Alfinal vuelve al almacen
    {
        recorridototal += costecaminos[actual][fabrica];
    }

    return recorridototal;

}



