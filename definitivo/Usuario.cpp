#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(string nombre, string contrasena)
{
    _nombre = nombre;
    _contrasena = contrasena;
}

Usuario::~Usuario(){}

void Usuario ::setNombre(string nombre)
{
    _nombre = nombre;
}

void Usuario::setContrasena(string contra)
{
    _contrasena = contra;
}

string Usuario::getNombre() const
{
    return _nombre;
}

string Usuario::getContrasena() const
{
    return _contrasena;
}

bool Usuario ::verificarContrasena(string contra)
{
    return (_contrasena == contra);
}
