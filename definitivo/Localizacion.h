#ifndef LOCALIZACION_H
#define LOCALIZACION_H

#include <string>
#include <vector>
#include "Evento.h"

// class Evento; //forward delcaration para evitar problemas de herencia circular

using namespace std;
class Localizacion
{
private:
    string _nombre;
    string _direccion;
    int _aforo;
    vector <Evento*> _reservados;
public:
    Localizacion();
    Localizacion(string nombre, string direccion, int aforo);
    string getNombre();
    vector <Evento*>& getReservados();
    int getAforo();
    string getDireccion();
    bool disponibleFecha(int fecha) const;
    void setNombre(const string& nombre);
    void setDireccion(const string& direccion);
    void setAforo(int aforo);
    void eliminarReservado(Evento* reservado);
    void mostrarInfo();
};

#endif // LOCALIZACION_H
