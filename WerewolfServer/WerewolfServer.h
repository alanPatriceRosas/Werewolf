#pragma once
#ifndef WEREWOLFSERVER_H
#define WEREWOLFSERVER_H

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "Role.h"

using std::cerr;
using std::getline;
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::map;
using std::vector;
using std::shuffle;
typedef unsigned short us;
typedef unsigned short int usi;


class WerewolfServer {
public:
    WerewolfServer(us port);
    void run();

private:
    void startGame();
    void handleVotes();
    void handleDayPhase();
    void handleNightPhase();
    void handleWerewolfPhase();
    void broadcastMessage(const string& mensaje);
    void broadcastPlayerList();
    void assignRoles();
    string roleToString(Role role);

    sf::TcpListener listener;
    vector<sf::TcpSocket*> clients;
    map<sf::TcpSocket*, string> clientNames;
    map<sf::TcpSocket*, Role> clientRoles;
    vector<string> playerNames;
    bool gameStarted = false;
};

#endif
