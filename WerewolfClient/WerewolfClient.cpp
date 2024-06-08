#include "WerewolfClient.h"
#include <iostream>

WerewolfClient::WerewolfClient(const sf::IpAddress& serverIp, unsigned short serverPort) 
{
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done) 
    {
        std::cerr << "Error al conectarse al servidor" << std::endl;
    }
    else 
    {
        std::cout << "Conectado al servidor " << serverIp << ":" << serverPort << std::endl;
    }
}

void WerewolfClient::run() 
{
    while (true) 
    {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) 
        {
            std::string message;
            packet >> message;
            if (message == "!!Inicia el juego!!") 
            {
                std::cout << "Ha comenzado!" << std::endl;
            }
            else if (message == "Noche....") 
            {
                handleNightPhase();
            }
            else if (message == "Dia....") 
            {
                handleDayPhase();
            }
            else if (message == "Hora de Votar") 
            {
                handleVotingPhase();
            }
            else 
            {
                int roleInt;
                packet >> roleInt;
                Role role = static_cast<Role>(roleInt);
                std::cout << "Tu rol es: " << roleToString(role) << std::endl;
            }
        }
    }
}

void WerewolfClient::handleNightPhase() 
{
    std::cout << "Es de noche, has lo tuyo..." << std::endl;
    std::string action = "Selecciona una victima";
    sf::Packet packet;
    packet << action;
    socket.send(packet);
}

void WerewolfClient::handleDayPhase() 
{
    std::cout << "Es de dia, discutan y preparense para votar..." << std::endl;
}

void WerewolfClient::handleVotingPhase() 
{
    std::cout << "Es hora de votar, alguien se va..." << std::endl;
    std::string vote = "Vota por un jugador";
    sf::Packet packet;
    packet << vote;
    socket.send(packet);
}

std::string WerewolfClient::roleToString(Role role) 
{
    switch (role) 
    {
    case Role::Aldeano: return "Aldeano";
    case Role::HombreLobo: return "Hombre Lobo";
    case Role::Vidente: return "Vidente";
    case Role::Cazador: return "Cazador";
    case Role::Bruja: return "Bruja";
    default: return "Unknown";
    }
}
