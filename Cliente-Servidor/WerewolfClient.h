#ifndef WEREWOLFCLIENT_H
#define WEREWOLFCLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <string>


using std::cout;
using std::cin;
using std::string;
using std::cerr;
using std::endl;
using std::getline;



class WerewolfClient {
public:
    WerewolfClient(const string& serverIp, unsigned short serverPort);
    bool connectToServer();
    void sendName(const string& name);
    void receiveMessages();
    void sendVote(const string& vote);
    void performNightAction(const string& action);
    void run();

private:
    void handleGameStart();
    void handleVotePhase();
    void handleNight();
    void handleWerewolfPhase();
    void handleRoleMessage(const string& message);

    sf::TcpSocket socket;
    string serverIp;
    unsigned short serverPort;
};

#endif
