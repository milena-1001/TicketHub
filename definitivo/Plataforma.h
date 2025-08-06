#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Usuario.h"
#include "Administrador.h"
#include "Artista.h"
#include "Asistente.h"
#include "AsistenteNormal.h"
#include "AsistenteVip.h"
#include "Localizacion.h"

using namespace std;

class Plataforma {
private:
    float _fondos = 0;
public:
    vector <Evento*> eventos;
    vector <Usuario*> usuarios;
    vector <Localizacion*> localizaciones;
    Usuario* usuarioActual = nullptr; //como no hay constructor inicializo aqui
public:
    //no me interesa que plataforma tenga constructor o destructor (solo quiero que exista 1 plataforma)
    void alpha();
    Usuario* login(const vector<Usuario*>& usuarios);
    void registro(vector<Usuario*>& usuarios);
    void ejecutarOpcion(int opcion);
    void mostrarMenu();
    void mostrarUsuarios(const vector<Usuario*>& usuarios) const;
    void mostrarEventos(const vector <Evento*>& eventos) const;
    vector<Evento*>& getEventos();
    int buscarEvento(const string& nombreEvento) const;
    Evento* obtenerEvento(const string& nombreEvento);
    //void mostrarEventos(); //muestra todos los eventos de la plataforma tanto los vip como los no vip
    //podríamos hacer:  numero de eventos vip: x y mostrar los eventos vip y con los no vip igual
    int buscarUsuario(const string& nombre) const;
    int buscarLocalizacion(const string& nombre) const;
    Localizacion* obtenerLocalizacion(const string& nombre);
    Usuario* obtenerUsuario(const string& nombre);
    void guardarUsuarios(const vector<Usuario*>& usuarios, const string& nombreArchivo);
    bool comprobarFechaLoc(const string& nombre_loc, const string& fecha) const;
    void guardarLocalizaciones(const vector <Localizacion*>& localizaciones);
    void guardarEventos(const vector<Evento*>& eventos);
    void guardarUsuarios(const vector<Usuario*>& usuarios);
    int obtenerFechaDentroDeUnMes();
    int obtenerFechaActual();
    void filtrarLocalizacion(const vector <Localizacion*>& localizacion);
    void filtrarEvento(const vector <Evento*>& evento);
    void filtrarArtista(const vector<Usuario*>& usuarios);
    void filtrarBusqueda(const vector<Usuario*>& u,const vector <Evento*>& e, const vector <Localizacion*>& l);
    void verEstadisticas(const vector<Usuario*>& u,const vector <Evento*>& e, vector <Localizacion*>& l);
    void recaudacion(float dinero);
    void setFondos(float dinero);
    float getFondos();
    // void recaudación(float dinero);
};

#endif // PLATAFORMA_H
