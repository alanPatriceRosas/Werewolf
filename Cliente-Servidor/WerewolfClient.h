#pragma once
#ifndef WEREWOLFCLIENT_H
#define WEREWOLFCLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include "Role.h"

using std::cout;
using std::cin;
using std::string;
using std::cerr;
using std::endl;
using std::getline;
using std::thread;


class WerewolfClient {
public:
    WerewolfClient(const string& playerName);

    void run(const string& serverIp, unsigned short serverPort);

private:
    void receiveMessages();

    void handleGameStart();

    void handleVotePhase();

    void handleNightPhase();

    sf::TcpSocket socket;
    string playerName;
    std::thread receiveThread;
    std::atomic<bool> running;
};

#endif
