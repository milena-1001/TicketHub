#ifndef ASISTENTE_H
#define ASISTENTE_H

#include <map>
#include "Usuario.h"
#include "Artista.h"
#include "Evento.h"
// #include "Plataforma.h"

class Asistente : public Usuario
{
protected:
    string _DNI;
    float _cartera;
    float _recompensas;
    vector<Evento*> _entradas; //lista de entradas
    bool _esVip;

public:
    Asistente();
    Asistente(string nombre, string contrasena, string DNI, float cartera, float recompensas, vector <Evento*> lista_entradas, bool vip);
    ~Asistente();
    virtual void mostrarMenu() const = 0;
    virtual void verEventos(vector <Evento*> eventos, Plataforma* p) const = 0;
    virtual void comprarEntradas(Plataforma* plataforma) = 0;
    virtual void venderEntradas(Plataforma* plataforma);
    void verEntradas() const; //a esta funcion hay que meterle el map o hacer algo
    void setCartera(float dinero);
    void verArtista(Plataforma* plataforma);
    float getCartera() const;
    vector <Evento*>& getEntradas();
    string getDNI();
    int buscarEntrada(const string& nombre);
    void verCartera() const;
    void misRecompensas();
};

#endif // ASISTENTE_H
