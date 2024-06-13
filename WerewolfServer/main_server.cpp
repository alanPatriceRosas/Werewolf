#include "WerewolfServer.h"

//bajo la misma red

using std::cout;
using std::endl;

int main() 
{
    sf::IpAddress localIp = sf::IpAddress::getLocalAddress();
    cout << "La direcci"<< char(162) <<"n IP del servidor es: " << localIp.toString() << endl;
    unsigned short port = 53000; //ejemplo puerto
    WerewolfServer server(port);
    server.run();
    return 0;
}