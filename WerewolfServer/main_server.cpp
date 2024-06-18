#include "WerewolfServer.h"
#include <iostream>

int main() {
    us puerto = 5300;
    WerewolfServer server(puerto);

    // getLocalAddress() te da la IP LOCAL del servidor pero como usamos hamachi ponemos la IP de hamachi
    sf::IpAddress ip = /*"25.66.81.128";*/sf::IpAddress::getLocalAddress();
    cout << "Server IP:\t" << ip.toString() << "\nPuerto:\t\t" << puerto << endl;

    server.run();

    return 0;
}

