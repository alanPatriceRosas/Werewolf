#include "WerewolfClient.h"

WerewolfClient::WerewolfClient(const string& playerName): playerName(playerName), running(true) {}

void WerewolfClient::run(const string& serverIp, unsigned short serverPort) 
{
    if (socket.connect(serverIp, serverPort) != sf::Socket::Done) 
    {
        cerr << "Error al conectar al servidor" << endl;
        return;
    }

    // Enviar el nombre del jugador al servidor
    sf::Packet packet;
    packet << playerName;
    socket.send(packet);

    receiveThread = thread(&WerewolfClient::receiveMessages, this);

    while (running) 
    {
        string input;
        getline(cin, input);

        if (!input.empty()) 
        {
            sf::Packet packet;
            packet << input;
            socket.send(packet);
        }
    }

    if (receiveThread.joinable()) 
    {
        receiveThread.join();
    }
}

void WerewolfClient::receiveMessages() 
{
    while (running) 
    {
        sf::Packet packet;
        if (socket.receive(packet) == sf::Socket::Done) 
        {
            string message;
            packet >> message;
            cout << "Server: " << message << endl;

            if (message == "Juego Iniciado") 
            {
                handleGameStart();
            }
        }
        else 
        {
            running = false;
        }
    }
}

void WerewolfClient::handleGameStart() 
{
    cout << "El juego ha comenzado!" << endl;
}

void WerewolfClient::handleVotePhase() 
{
    cout << "Es hora de votar! Elige a un jugador para eliminar:" << endl;
    // Lógica para manejar la fase de votación
}

void WerewolfClient::handleNightPhase() 
{
    cout << "Es de noche. Espera a que los roles actúen..." << endl;
    // Lógica para manejar la fase de noche
}
