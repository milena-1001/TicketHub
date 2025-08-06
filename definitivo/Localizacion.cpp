#include "Localizacion.h"

Localizacion::Localizacion() {}

Localizacion::Localizacion(string nombre, string direccion, int aforo):
    _nombre(nombre),
    _direccion(direccion),
    _aforo(aforo),
    _reservados()
{}

string Localizacion::getNombre()
{
    return _nombre;
}

vector <Evento*>& Localizacion:: getReservados()
{
    return _reservados;
}

string Localizacion:: getDireccion()
{
    return _direccion;
}

bool Localizacion :: disponibleFecha(int fecha) const
{
    for(size_t i = 0; i < _reservados.size(); i ++)
    {
        if(_reservados[i]->getFecha() == fecha)
            return 0;
    }
    return 1; //sí esta disponible
}

void Localizacion :: setNombre(const string& nombre)
{
    _nombre = nombre;
}

void Localizacion ::setDireccion(const string& direccion)
{
    _direccion = direccion;
}

void Localizacion ::setAforo(int aforo)
{
    _aforo = aforo;
}

int Localizacion :: getAforo()
{
    return _aforo;
}

void Localizacion :: eliminarReservado(Evento* reservado)
{
    for (size_t i = 0; i < _reservados.size(); i ++)
    {
        if(_reservados[i] == reservado)
        {
            _reservados.erase(_reservados.begin() + i);
            //aqui no hago delete!!! -> memory leak
            break;
        }
    }
}

void Localizacion :: mostrarInfo()
{
    cout << "• Localizacion: " << _nombre << " | Dirección: " << _direccion
         << " | Aforo: " << _aforo << "\nLista de eventos reservados: ";
    for(size_t i = 0; i < _reservados.size(); i ++)
    {
        cout << _reservados[i] << ", ";
    }
}
