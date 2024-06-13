#pragma once
#ifndef WEREWOLFSERVER_H
#define WEREWOLFSERVER_H

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "Role.h"

class WerewolfServer {
public:
    WerewolfServer(unsigned short port);
    void run();

private:
    void startGame();
    void handleVotes();
    void broadcastMessage(const std::string& message);
    void broadcastPlayerList();

    sf::TcpListener listener;
    std::vector<sf::TcpSocket*> clients;
    std::map<sf::TcpSocket*, std::string> clientNames;
    std::vector<std::string> playerNames;
    bool gameStarted = false;
};

#endif