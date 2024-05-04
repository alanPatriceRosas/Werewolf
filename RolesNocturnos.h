#pragma once
class RolesNocturnos
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

class HombreLobo : public RolesNocturnos
{
public:
    int matar(); // votacion entre hombres lobo para ver a quien matar
};

class Bruja : public RolesNocturnos // La bruja puede salvar o matar a alguien una vez cada accion
{
public:
    int salvar();
    int matar();
};

class Vidente : public RolesNocturnos // el Vidente le puede preguntar al mod quien es hombre lobo y el mod debe de respoonder si o no
{
public:
    void preguntarAlMod();
};

class Doctor : public RolesNocturnos
{
public:
    void salvar();
};

class HombreLoboAlfa : public RolesNocturnos // el tiene que decir "hombre lobo" por al menos una vez cada vez que se discuta
{
public:
    bool SiDijoHombreLobo() ;
};
