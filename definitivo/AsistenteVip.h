#ifndef ASISTENTEVIP_H
#define ASISTENTEVIP_H

#include "Asistente.h"

class AsistenteVip : public Asistente
{
public:
    AsistenteVip();
    AsistenteVip(string nombre, string contrasena, string DNI, float cartera, float recompensas, vector <Evento*> lista_entradas, bool vip);
    ~AsistenteVip();
    virtual void mostrarMenu() const override;
    virtual void verEventos(vector <Evento*> eventos, Plataforma* p) const override;
    virtual void comprarEntradas(Plataforma* plataforma) override;
    // virtual void venderEntradas(vector <Evento*>& entradas, Plataforma* plataforma) override;
};

#endif // ASISTENTEVIP_H
