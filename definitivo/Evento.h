#ifndef EVENTO_H
#define EVENTO_H


#include <iostream>
#include <string>
#include <vector>
// #include <Localizacion.h>

class Localizacion;

using namespace std;

class Evento
{
private:
    string _nombreEvento; //variable representativa del evento
    Localizacion* _localizacion;
    int _fecha;
    float _precio;
    int _entradas;
    bool _esVip;

public:
    Evento();
    //para crear un evento(por parte de un artista), la localizacion tiene que estar
    //disponible en la fecha deseada.
    //por esa razon, al crear un evento no solo tenemos que comprobar eso, sino que tambien
    //tenemos que asegurarnos de que no se repitan en otro evento la misma localizacion y fecha
    //juntas. if ((evento[i].localizacion && evento[i].fecha) == (evento[j].localizacion &&
    //evento[j].fecha))
    Evento(string nombre, Localizacion* localizacion, int fecha, float precio, int entradas, bool VIP);
    ~Evento();
    void mostrarEvento() const;
    string getNombre();
    int getFecha();
    Localizacion* getLocation();
    int getEntradas();
    float getPrecio();
    bool getEsVip();
    void setEntradas(int entradas_actuales);
    void setNombre(string nombre);
    void setFecha(int fecha);
    void setPrecio(float precio);
    void setLocation(Localizacion* loc);
    void setVip(bool vip);
};

#endif // EVENTO_H
