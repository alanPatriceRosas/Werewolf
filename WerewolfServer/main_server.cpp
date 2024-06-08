#include "WerewolfServer.h"


using std::cout;

int main() {
    sf::IpAddress localIp = sf::IpAddress::getLocalAddress();
    std::cout << "La direcci<< char()ó <<n IP del servidor es: " << localIp.toString() << std::endl;
    unsigned short port = 53000; // Ejemplo de puerto
    WerewolfServer server(port);
    server.run();
    return 0;
}
