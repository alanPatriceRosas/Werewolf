#include "WerewolfClient.h"
#include <iostream>
#include <SFML/Network.hpp> 

int main() 
{
    string serverIp;
    unsigned short serverPort;

    cout << "Ingresa la IP del servidor: ";
    cin >> serverIp;
    cout << "Ingresa el puerto del servidor: ";
    cin >> serverPort;

    WerewolfClient client(serverIp, serverPort);

    bool connected = false;
    while (!connected) 
    {
        if (!client.connectToServer()) 
        {
            cerr << "No se pudo conectar al servidor." << endl;
            cerr << "Intentando nuevamente..." << endl;
            sf::sleep(sf::seconds(1)); 
        }
        else 
        {
            connected = true;
        }
    }

    client.run();

    return 0;
}

