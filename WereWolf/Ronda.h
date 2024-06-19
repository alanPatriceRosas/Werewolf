#pragma once
class Ronda
{
public:
	void gestionMod();
};


class RondaDiurna : public Ronda
{
public:
	void platica();
	void eliminacion();
};

class RondaNocturna : public Ronda
{
public:
	void dormirGeneral();
	void chat(); // aqui tendriamos que establecer los atributos del mensaje pero no se si dentro de la funcion o creando otra clase de chat

};

