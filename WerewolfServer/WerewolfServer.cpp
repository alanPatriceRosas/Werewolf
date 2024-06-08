#include "WerewolfServer.h"
#include <iostream>
#include <algorithm>
#include <random>

WerewolfServer::WerewolfServer(unsigned short port) 
{
    if (listener.listen(port) != sf::Socket::Done) 
    {
        std::cerr << "Error al iniciar el server en el puerto: " << port << std::endl;
    }
    else 
    {
        std::cout << "Puerto del server " << port << std::endl;
    }
}

void WerewolfServer::run() 
{
    std::thread acceptThread(&WerewolfServer::acceptClients, this);
    acceptThread.detach();

    while (true) 
    {
        if (gameStarted) {
            handleGameLogic();
        }
    }
}

void WerewolfServer::acceptClients() 
{
    while (true) 
    {
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done) 
        {
            clients.push_back(client);
            std::cout << "Nuevo usuario conectado: " << client->getRemoteAddress() << std::endl;
            if (clients.size() == maxPlayers) 
            {
                startGame();
            }
        }
        else 
        {
            delete client;
        }
    }
}

void WerewolfServer::startGame() 
{
    assignRoles();
    gameStarted = true;
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << "!!Inicia el juego!!";
        client->send(packet);
    }
}

void WerewolfServer::assignRoles() 
{
    std::vector<Role> roles = { Role::HombreLobo, Role::HombreLobo, Role::Vidente, Role::Cazador, Role::Bruja };
    for (size_t i = roles.size(); i < clients.size(); ++i) 
    {
        roles.push_back(Role::Aldeano);
    }
    std::shuffle(roles.begin(), roles.end(), std::mt19937{ std::random_device{}() });

    for (size_t i = 0; i < clients.size(); ++i) 
    {
        playerRoles[clients[i]] = roles[i];
        sf::Packet packet;
        packet << static_cast<int>(roles[i]);
        clients[i]->send(packet);
    }
}

void WerewolfServer::handleGameLogic() 
{
    while (gameStarted) 
    {
        switch (currentPhase) 
        {
        case Phase::Night:
            handleNightPhase();
            break;
        case Phase::Day:
            handleDayPhase();
            break;
        case Phase::Voting:
            handleVotingPhase();
            break;
        }
    }
}

void WerewolfServer::handleNightPhase() 
{
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << "Noche....";
        client->send(packet);
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    currentPhase = Phase::Day;
}

void WerewolfServer::handleDayPhase() 
{
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << "Dia....";
        client->send(packet);
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    currentPhase = Phase::Voting;
}

void WerewolfServer::handleVotingPhase() 
{
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << "Hora de Votar";
        client->send(packet);
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
    currentPhase = Phase::Night;
}
