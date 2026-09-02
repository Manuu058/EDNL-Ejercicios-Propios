#include <string>
#include "abb.h"

using namespace std;

struct Persona{
    string nombre;
    string telefono;

    Persona() : nombre(""), telefono(""){}

    Persona(const string& n, const string& t) : nombre(n), telefono(t){}

    bool operator <(const Persona& p){return nombre < p.nombre};

    bool operator >(const Persona& p){return nombre > p.nombre};

    bool operator ==(const Persona& p){return nombre == p.nombre};
};

class Agenda{
    private:
        Abb<Persona> personas;

        bool buscarPorTelefonoRec(string& telefono, const Abb<Persona>& A, Persona& p)
        {
            if (A.vacio())
            {
                return false;
            }
            if(A.elemento().telefono==telefono)
            {
                p = A.elemento();
                return true;
            }
            return buscarPorTelefonoRec(telefono, A.izqdo(), p) ||
               buscarPorTelefonoRec(telefono, A.drcho(), p);
        }
    public:
        void InsertarPersona(const Persona& p){
            personas.insertar(p);
        }
        void EliminarPersona(const Persona& p){
            personas.eliminar(p);
        }

        string getTelefono(string& nombre) const
        {
            Abb<Persona> resultado = personas.buscar(Persona(nombre, ""));

            if (resultado.vacio())
            {
                return "";
            }

            return resultado.elemento().telefono;
        }
        bool getPersonaPorTelefono(const std::string& telefono, Persona& p) const
        {
            return buscarPorTelefonoRec(telefono, personas, p);
        }
}