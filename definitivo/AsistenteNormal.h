
#ifndef ASISTENTENORMAL_H
#define ASISTENTENORMAL_H

#include "Asistente.h"
#include "Plataforma.h"

class AsistenteNormal : public Asistente
{
public:
    AsistenteNormal();
    AsistenteNormal(string nombre, string contrasena, string DNI, float cartera, float recompensas, vector <Evento*> lista_entradas, bool vip);
    ~AsistenteNormal();
    virtual void mostrarMenu() const override;
    virtual void verEventos(vector <Evento*> eventos, Plataforma* p) const override;
    virtual void comprarEntradas(Plataforma* plataforma) override;
    // virtual void venderEntradas(vector <Evento*>& entradas, Plataforma* plataforma) override;
};

#endif // ASISTENTENORMAL_H
