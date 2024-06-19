#include "WerewolfClient.h"
#include <iostream>

WerewolfClient::WerewolfClient(const string& serverIp, unsigned short serverPort) : serverIp(serverIp), serverPort(serverPort)
{
    socket.setBlocking(true); 
}

bool WerewolfClient::connectToServer()
{
    sf::Socket::Status status = socket.connect(serverIp, serverPort);
    if (status != sf::Socket::Done) 
    {
        cerr << "Error al conectar al servidor." << endl;
        return false;
    }
    socket.setBlocking(false); 
    return true;
}

void WerewolfClient::sendName(const string& name)
{
    sf::Packet packet;
    packet << name;
    socket.send(packet);
}

void WerewolfClient::receiveMessages()
{
    sf::Packet packet;
    if (socket.receive(packet) == sf::Socket::Done)
    {
        string message;
        packet >> message;
        cout << "Mensaje del servidor: " << message << endl;

        if (message == "GAME_START")
        {
            handleGameStart();
        }
        else if (message == "VOTE_PHASE")
        {
            handleVotePhase();
        }
        else if (message == "NIGHT_PHASE")
        {
            handleNight();
        }
        else if (message == "HOMBRES_LOBO_PHASE")
        {
            handleWerewolfPhase();
        }
        else if (message.find("ROLE") == 0)
        {
            handleRoleMessage(message);
        }
        else if (message == "Esperando a al menos 7 jugadores.")
        {
            cout << "Esperando ..." << endl;
        }
    }
}

void WerewolfClient::sendVote(const string& vote)
{
    sf::Packet packet;
    packet << vote;
    socket.send(packet);
}

void WerewolfClient::performNightAction(const string& action)
{
    sf::Packet packet;
    packet << action;
    socket.send(packet);
}

void WerewolfClient::handleGameStart()
{
    cout << "El juego ha comenzado." << endl;
}

void WerewolfClient::handleVotePhase()
{
    cout << "Es la fase de votación. Escribe el nombre del jugador al que deseas votar para eliminar: ";
    string vote;
    cin >> vote;
    sendVote(vote);
}

void WerewolfClient::handleNight()
{
    cout << "Es la fase de noche. Realiza tu acción nocturna según tu rol." << std::endl;
    string nightAction;
    cout << "Escribe el nombre del jugador para tu acción nocturna: ";
    cin >> nightAction;
    performNightAction(nightAction);
}

void WerewolfClient::handleWerewolfPhase()
{
    cout << "Es la fase de los Hombres Lobo. Escribe el nombre del jugador que deseas matar: ";
    string vote;
    cin >> vote;
    performNightAction(vote);
}

void WerewolfClient::handleRoleMessage(const string& message)
{
    string role = message.substr(4); // "ROLE" tiene longitud 4
    cout << "Tu rol es: " << role << endl;
}

void WerewolfClient::run()
{
    string name;
    cout << "Ingresa tu nombre: ";
    cin >> name;

    sendName(name);

    while (true) 
    {
        receiveMessages();
    }
}
