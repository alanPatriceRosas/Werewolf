#pragma once
#ifndef WEREWOLFSERVER_H
#define WEREWOLFSERVER_H

#include <SFML/Network.hpp>
#include <vector>
#include <map>
#include <thread>
#include "Role.h"
#include "Phase.h"
#include <iostream> 

class WerewolfServer {
public:
    WerewolfServer(unsigned short port);
    void run();

private:
    void acceptClients();
    void startGame();
    void assignRoles();
    void handleGameLogic();
    void handleNightPhase();
    void handleDayPhase();
    void handleVotingPhase();

    sf::TcpListener listener;
    std::vector<sf::TcpSocket*> clients;
    std::map<sf::TcpSocket*, Role> playerRoles;
    const size_t maxPlayers = 10; // Numero maximo de jugadores
    bool gameStarted = false;
    Phase currentPhase = Phase::Night;
};

#endif
