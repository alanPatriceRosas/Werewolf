#include "WerewolfServer.h"
#include <algorithm>
#include <random>

WerewolfServer::WerewolfServer(us puerto) {
    if (listener.listen(puerto) != sf::Socket::Done) 
    {
        cerr << "Error al iniciar el servidor en el puerto " << puerto << endl;
    }
}

void WerewolfServer::startGame() 
{
    gameStarted = true;
    assignRoles();
    broadcastMessage("Juego Iniciado");
    broadcastPlayerList();
    handleDayPhase();
}

void WerewolfServer::assignRoles() 
{
    vector<Role> roles;
    int numPlayers = clients.size();

    // definimos la cantidad de cada rol según la cantidad de jugadores
    usi numWerewolves = numPlayers / 3;
    usi numVillagers = numPlayers - (numWerewolves + 3); // para incluir roles adicionales
    usi numSeers = 1;
    usi numHunters = 1;
    usi numWitches = 1;

    // llenamos el vector de roles
    for (usi i = 0; i < numWerewolves; ++i) roles.push_back(Role::HombreLobo);
    for (usi i = 0; i < numVillagers; ++i) roles.push_back(Role::Aldeano);
    roles.push_back(Role::Vidente);
    roles.push_back(Role::Cazador);
    roles.push_back(Role::Bruja);

    // barajamos los roles
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(roles.begin(), roles.end(), g);

    // asignamos los roles a los jugadores
    for (usi i = 0; i < clients.size(); ++i) 
    {
        clientRoles[clients[i]] = roles[i];
        sf::Packet packet;
        packet << "Eres:\t" << roleToString(roles[i]);
        clients[i]->send(packet);
    }
}

string WerewolfServer::roleToString(Role role) 
{
    switch (role) 
    {
    case Role::Aldeano: 
        return "Aldeano";
    case Role::HombreLobo: 
        return "Hombre Lobo";
    case Role::Vidente: 
        return "Vidente";
    case Role::Cazador: 
        return "Cazador";
    case Role::Bruja: 
        return "Bruja";
    default: 
        return "Desconocido";
    }
}

void WerewolfServer::handleVotes() 
{
    map<string, int> voteCount;
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
        broadcastMessage("Player " + playerToEliminate + " has been eliminated.");
        // Lógica adicional para manejar la eliminación del jugador
    }
}

void WerewolfServer::handleDayPhase() 
{
    broadcastMessage("Es de día. Discute y prepárate para la votación...");
    handleVotes();
    handleNightPhase();
}

void WerewolfServer::handleNightPhase() 
{
    broadcastMessage("Es de noche. Los roles especiales están actuando...");

    // Vidente
    for (auto& client : clients) 
    {
        if (clientRoles[client] == Role::Vidente) 
        {
            sf::Packet packet;
            packet << "Vidente, elige a un jugador para ver su rol:";
            client->send(packet);

            if (client->receive(packet) == sf::Socket::Done) 
            {
                string playerName;
                packet >> playerName;
                for (auto& target : clients) 
                {
                    if (clientNames[target] == playerName) 
                    {
                        Role role = clientRoles[target];
                        sf::Packet response;
                        response << "El rol de " << playerName << " es " << roleToString(role);
                        client->send(response);
                        break;
                    }
                }
            }
        }
    }

    // Hombres Lobo
    handleWerewolfPhase();

    // Comenzar una nueva fase de día
    handleDayPhase();
}

void WerewolfServer::handleWerewolfPhase() 
{
    broadcastMessage("Hombres Lobo, elijan a un jugador para matar...");

    map<string, int> werewolfVotes;
    for (auto& client : clients) 
    {
        if (clientRoles[client] == Role::HombreLobo) 
        {
            sf::Packet packet;
            packet << "Hombre Lobo, elige a un jugador para matar:";
            client->send(packet);

            if (client->receive(packet) == sf::Socket::Done) 
            {
                string vote;
                packet >> vote;
                werewolfVotes[vote]++;
            }
        }
    }

    string playerToKill;
    int maxVotes = 0;
    for (const auto& vote : werewolfVotes) 
    {
        if (vote.second > maxVotes) 
        {
            maxVotes = vote.second;
            playerToKill = vote.first;
        }
    }

    if (!playerToKill.empty()) 
    {
        broadcastMessage("Los Hombres Lobo han decidido matar a " + playerToKill);
        // Lógica para manejar la eliminación del jugador
    }
}

void WerewolfServer::broadcastMessage(const string& mensaje) 
{
    for (auto& client : clients) 
    {
        sf::Packet packet;
        packet << mensaje;
        client->send(packet);
    }
}

void WerewolfServer::broadcastPlayerList() 
{
    string playerList = "Lista de jugadores: ";
    for (const auto& name : playerNames) 
    {
        playerList += name + "\n";
    }
    broadcastMessage(playerList);
}

void WerewolfServer::run() {
    while (true) 
    {
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) == sf::Socket::Done)
        {
            clients.push_back(client);
            cout << "Nuevo jugador conectado: " << client->getRemoteAddress() << endl;

            sf::Packet packet;
            if (client->receive(packet) == sf::Socket::Done) 
            {
                string playerName;
                packet >> playerName;
                clientNames[client] = playerName;
                playerNames.push_back(playerName);
            }

            if (clients.size() >= 7) // Tener al menos 7 jugadores para iniciar el juego
            { 
                startGame();
            }
            else 
            {
                broadcastMessage("Esperando a al menos 7 jugadores.");
            }
        }
        else {
            delete client;
        }
    }
}
