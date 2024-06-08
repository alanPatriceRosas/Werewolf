#pragma once
#ifndef WEREWOLFCLIENT_H
#define WEREWOLFCLIENT_H

#include <SFML/Network.hpp>
#include "Role.h"

class WerewolfClient {
public:
    WerewolfClient(const sf::IpAddress& serverIp, unsigned short serverPort);
    void run();

private:
    void handleNightPhase();
    void handleDayPhase();
    void handleVotingPhase();
    std::string roleToString(Role role);

    sf::TcpSocket socket;
    Role role;
};

#endif
