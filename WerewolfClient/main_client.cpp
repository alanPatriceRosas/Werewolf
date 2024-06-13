// Cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <SFML/Network.hpp>
#include <iostream>
#include "WerewolfClient.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;


int main()
{
    string servIP;
    unsigned short servPuerto;
    string Jugador;

    cout << "Ingresa la dirección IP del servidor: ";
    cin >> servIP;
    cout << "Ingresa el puerto del servidor: ";
    cin >> servPuerto;
    cout << "Ingresa tu nombre de jugador: ";
    cin >> Jugador;

    sf::IpAddress serverIp(servIP);

    WerewolfClient client(servIP, servPuerto, Jugador);
    client.run();

    return 0;
}
// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
