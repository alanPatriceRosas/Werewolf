#pragma once
#ifndef WEREWOLFCLIENT_H
#define WEREWOLFCLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include "Role.h"

class WerewolfClient {
public:
    WerewolfClient(const sf::IpAddress& serverIp, unsigned short serverPort, const std::string& playerName);
    void run();

private:
    void handleGameStart();
    void handleDayPhase();
    void handleVotingPhase();
    std::string roleToString(Role role);

    sf::TcpSocket socket;
    std::string playerName;
};

#endif