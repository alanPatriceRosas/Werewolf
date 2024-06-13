#include "WerewolfServer.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::string;

WerewolfServer::WerewolfServer(unsigned short port) 
{
    if (listener.listen(port) != sf::Socket::Done) 
    {
        cerr << "Error al iniciar el servidor en el puerto: " << port << endl;
    }
    else 
    {
        cout << "Servidor iniciado en el puerto: " << port << endl;
    }
}

void WerewolfServer::startGame() 
{
    gameStarted = true;
    broadcastMessage("Game started");
    broadcastPlayerList();
    // Lógica adicional para iniciar el juego, por ejemplo, asignar roles, etc.
}

void WerewolfServer::handleVotes() 
{
    std::map<string, int> voteCount;
    for (auto& client : clients) 
    {
        sf::Packet packet;
        if (client->receive(packet) == sf::Socket::Done) 
        {
            string vote;
            packet >> vote;
            voteCount[vote]++;
        }
    }

    // Encontrar el jugador con más votos
    string playerToEliminate;
    int maxVotes = 0;
    for (const auto& vote : voteCount) 
    {
        if (vote.second > maxVotes) 
        {
            maxVotes = vote.second;
            playerToEliminate = vote.first;
        }
    }

    if (!playerToEliminate.empty()) 
    {
        broadcastMessage("El jugador " + playerToEliminate + " ha sido eliminado.");
        // Lógica adicional para manejar la eliminación del jugador
    }
}

void WerewolfServer::broadcastMessage(const string& message) 
{
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << message;
        client->send(packet);
    }
}

void WerewolfServer::broadcastPlayerList() 
{
    string playerList = "Player list: ";
    for (const auto& name : playerNames) 
    {
        playerList += name + " ";
    }
    broadcastMessage(playerList);
}

void WerewolfServer::run() 
{
    while (true) 
    {
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done) 
        {
            clients.push_back(client);
            cout << "Nuevo cliente conectado: " << client->getRemoteAddress() << endl;

            // Recibir nombre del jugador
            sf::Packet packet;
            if (client->receive(packet) == sf::Socket::Done) 
            {
                string playerName;
                packet >> playerName;
                clientNames[client] = playerName;
                playerNames.push_back(playerName);
            }

            if (clients.size() == 3) // para simular con 3 clientes
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

