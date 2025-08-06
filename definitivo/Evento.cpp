#include "Evento.h"

Evento::Evento() {}

Evento::Evento(string nombre, Localizacion* localizacion, int fecha, float precio, int entradas, bool vip)
:
    _nombreEvento(nombre),
    _localizacion(localizacion),
    _fecha(fecha),
    _precio(precio),
    _entradas(entradas),
    _esVip(vip)
{}

Evento::~Evento() {}

string Evento :: getNombre()
{
    return _nombreEvento;
}

int Evento :: getFecha()
{
    return _fecha;
}

Localizacion* Evento :: getLocation()
{
    return _localizacion;
}

int Evento :: getEntradas()
{
    return _entradas;
}
bool Evento :: getEsVip()
{
    return _esVip;
}
float Evento :: getPrecio()
{
    return _precio;
}
void Evento :: setEntradas(int entradas_actuales)
{
    _entradas = entradas_actuales;
}
void Evento :: setNombre(string nombre)
{
    _nombreEvento = nombre;
}
void Evento :: setFecha(int fecha)
{
    _fecha = fecha;
}
void Evento :: setPrecio(float precio)
{
    _precio = precio;
}

void Evento :: setLocation(Localizacion* loc)
{
    this->_localizacion = loc;
}

void Evento :: setVip(bool vip)
{
    _esVip = vip;
}

void Evento :: mostrarEvento() const
{
    cout << "Evento: " << _nombreEvento <<  "| Fecha: " << _fecha
         << " | Precio: " << _precio << " | Entradas: " << _entradas << " | VIP: ";
    if (_esVip)
        cout << "Sí" << endl;
    else
        cout << "No" << endl;
}
