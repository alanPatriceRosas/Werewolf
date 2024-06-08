#include "WerewolfClient.h"
#include <iostream>

WerewolfClient::WerewolfClient(const sf::IpAddress& serverIp, unsigned short serverPort) {
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done) {
        std::cerr << "Unable to connect to server" << std::endl;
    }
    else {
        std::cout << "Connected to server at " << serverIp << ":" << serverPort << std::endl;
    }
}

void WerewolfClient::run() {
    while (true) {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) {
            std::string message;
            packet >> message;
            if (message == "Game started") {
                std::cout << "The game has started!" << std::endl;
            }
            else if (message == "Night phase") {
                handleNightPhase();
            }
            else if (message == "Day phase") {
                handleDayPhase();
            }
            else if (message == "Voting phase") {
                handleVotingPhase();
            }
            else {
                int roleInt;
                packet >> roleInt;
                Role role = static_cast<Role>(roleInt);
                std::cout << "Your role is: " << roleToString(role) << std::endl;
            }
        }
    }
}

void WerewolfClient::handleNightPhase() {
    std::cout << "It's night time. Performing night actions..." << std::endl;
    std::string action = "select victim";
    sf::Packet packet;
    packet << action;
    socket.send(packet);
}

void WerewolfClient::handleDayPhase() {
    std::cout << "It's daytime. Discuss and prepare for voting..." << std::endl;
}

void WerewolfClient::handleVotingPhase() {
    std::cout << "It's voting time. Vote to eliminate a suspect..." << std::endl;
    std::string vote = "vote player";
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
    default: return "Unknown";
    }
}
