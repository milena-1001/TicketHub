#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Usuario.h"
#include "Plataforma.h"

class Administrador : public Usuario
{
public:
    Administrador();
    ~Administrador();
    Administrador(string nombre, string contrasena);
    virtual void mostrarMenu() const override;
    void crearUsuario(vector<Usuario*>& usuarios,  Plataforma* i); //qué tipo de usuario quieres crear?
    void modificarUsuario(vector<Usuario*>& usuarios);
    void eliminarUsuario(vector <Usuario*>& usuarios);
    void verArtista(Plataforma* plataforma);
};

#endif // ADMINISTRADOR_H
