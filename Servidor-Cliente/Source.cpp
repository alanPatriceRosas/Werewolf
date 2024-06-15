#include "WerewolfServer.h"
#include <iostream>

int main() {
    us puerto = 53000;
    WerewolfServer server(puerto);

    // Obtener la IP local del servidor
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    cout << "Server IP:\t " << ip.toString() << "\nPuerto:\t " << puerto << endl;

    server.run();

    return 0;
}

