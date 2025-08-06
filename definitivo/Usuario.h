#ifndef USUARIO_H
#define USUARIO_H


#include <iostream>
#include <string>
#include <vector>

class Plataforma;

using namespace std;

class Usuario
{
protected:
    string _nombre;
    string _contrasena;
public:
    Usuario();
    Usuario(string nombre, string contrasena);
    virtual ~Usuario();
    virtual void mostrarMenu() const = 0; //metodo virtual puro, con implementacion en las respectivas clases derivadas
    //virtual void mostrarInfo() const = 0;
    //hacer un método virtual que sea setDatos para aplicar polimorfismo segun los datos que se quieran cambiar de cada clase?
    void setNombre(string nombre);
    void setContrasena(string contrasena);
    string getNombre() const;
    string getContrasena() const;
    bool verificarContrasena(string contra);
};
#endif // USUARIO_H
