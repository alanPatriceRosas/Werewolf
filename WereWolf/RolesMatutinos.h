#pragma once
class RolesMatutinos
{
public:
    void votacion()
    {
        return; // debera de regresar la votacion de cada participante exluyendo al moderador
    }
    bool dormir()
    {
        // todos los roles se pueden dormir
        return; // bool
    }
    bool despertar()
    {
        //  los roles matutinos no se pueden despertar durante la noche
    }
};


class Borracho : public RolesMatutinos
{
public:
    void hacerGestos();
};


class Aldeano : public RolesMatutinos
{
public:
    // No se que atributos o metodos pueda tener un aldeano que no herede ya de los roles
};



