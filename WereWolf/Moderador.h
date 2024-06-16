#pragma once
class Moderador
{
    void levantarRol();      // el moderador elige a quien levantar pero debe de levantare a todos los roles nocturnos
    void dormirRol();        // cuando se van a doprmir empieza la ronda
    void cambiarRonda();     // cada que pasa una noche se cambia de ronda
    void avisoDeSalvacion(); // aqui avisa quien se salvo en la noche
    void responder();        // cada que pregunte el vidente quienes el el lobo
    void paseDeRonda();
};

