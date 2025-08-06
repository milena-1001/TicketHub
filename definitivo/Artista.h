#ifndef ARTISTA_H
#define ARTISTA_H


#include "Usuario.h"
#include "Evento.h"

class Artista : public Usuario
{
private:
    string _nombreArtistico;
    string _estiloMusical;
    string _descripcion;
    vector<Evento*> _listaEventos;
public:
    Artista();
    //constructor parametrizado de prueba, borrar cuando tengas Evento y poner el de abajo
    Artista(string nombre, string contrasena, string nombreArtistico, string estiloMusical, string descripcion, vector<Evento*> lista_eventos);
    ~Artista();
    virtual void mostrarMenu() const override;
    string getNombreArtista() const;
    string getEstiloMusical() const;
    string getDescripcion() const;
    const vector<Evento*> getEventos() const;
    void verMisEventos() const;
    void mostrarInfo(Plataforma* p) const;
    void crearEvento(vector<Evento*>& eventos, Plataforma* p);
    void modificarEvento(Plataforma* p);
    void eliminarEvento(vector <Evento*>& eventos, Plataforma * p);
};

#endif // ARTISTA_H
