#include "WerewolfClient.h"

WerewolfClient::WerewolfClient(const sf::IpAddress& servIP, unsigned short servPuerto, const std::string& Jugador) : playerName(Jugador)
{
    if (socket.connect(servIP, servPuerto) != sf::Socket::Done) {
        std::cerr << "Error al conectar al servidor" << std::endl;
    }
    else {
        std::cout << "Conectado al servidor en " << servIP << ":" << servPuerto << std::endl;
        // Enviar nombre del jugador al servidor
        sf::Packet packet;
        packet << Jugador;
        socket.send(packet);
    }
}

void WerewolfClient::run() {
    while (true) {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            std::string message;
            packet >> message;

            if (message == "Game started") {
                handleGameStart();
            }
            else if (message.find("Player list:") != std::string::npos) {
                std::cout << message << std::endl;
            }
            else if (message.find("Player") != std::string::npos && message.find("has been eliminated") != std::string::npos) {
                std::cout << message << std::endl;
            }
        }
    }
}

void WerewolfClient::handleGameStart() {
    std::cout << "El juego ha comenzado!" << std::endl;
    handleDayPhase();
    handleVotingPhase();
}

void WerewolfClient::handleDayPhase() {
    std::cout << "Es de día. Discute y prepárate para la votación..." << std::endl;
}

void WerewolfClient::handleVotingPhase() {
    std::cout << "Es hora de votar. Vota para eliminar a un sospechoso..." << std::endl;
    std::string vote;
    std::cout << "Ingresa el nombre del jugador para votar: ";
    std::cin >> vote;

    sf::Packet packet;
    packet << vote;
    socket.send(packet);
}

std::string WerewolfClient::roleToString(Role role) {
    switch (role) {
    case Role::Aldeano: return "Aldeano";
    case Role::HombreLobo: return "Hombre Lobo";
    case Role::Vidente: return "Vidente";
    case Role::Cazador: return "Cazador";
    case Role::Bruja: return "Bruja";
    default: return "Desconocido";
    }
}