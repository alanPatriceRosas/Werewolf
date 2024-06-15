#include "WerewolfClient.h"
#include <iostream>

int main() {
    int puerto;
    string nombreJugador, serverIp;

    cout << "Introduce tu nombre de jugador: ";
    getline(cin, nombreJugador);

    cout << "Introduce la IP del servidor: ";
    getline(cin, serverIp);

    cout << "Introduce el puerto del servidor: ";
    cin >> puerto;

    WerewolfClient client(nombreJugador);
    client.run(serverIp, puerto);

    return 0;
}
