#include "WerewolfClient.h"

int main() {
    sf::IpAddress serverIp = "127.0.0.1"; // Dirección IP del servidor
    unsigned short serverPort = 53000;    // Puerto del servidor
    WerewolfClient client(serverIp, serverPort);
    client.run();
    return 0;
}
