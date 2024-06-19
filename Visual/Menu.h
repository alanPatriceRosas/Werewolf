#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
public:
	Menu();
	~Menu() {};
	void showMainMenu(); //Mostrar la ventana inicial
	void showJoinMenu(); //Mostrar el men� para unirse a una partida
	void showCreateMenu(); //Mostrar el men� para crear una partida
	
private:
	sf::Event clicker; //Variable para manejar los eventos del mouse

	sf::RenderWindow mainWindow; //Ventana inicial
	sf::RenderWindow secondWindow; //Ventana de menu

	sf::Image icon; //�cono del juego

	sf::Texture backgroundTexture; //Textura del men� inicial
	sf::Sprite backgroundSprite; //Variable para mostrar el fondo
	
	sf::RectangleShape createItem, joinItem, leaveItem, settingsItem; //Figuras de la barra de navegaci�n

	sf::RectangleShape addPlayer, quitPlayer; //Figuras para agregar o quitar jugadores

	sf::RectangleShape addWolf, addFarmer, addWitch, addVident; //Casillas de selecci�n de roles
	
	sf::RectangleShape avatarLeft, avatarRight; //Casillas de selecci�n de avatares

	sf::RectangleShape address, nicknamebox; //Cajas de texto para poner un nombre y establecer servidor

	sf::RectangleShape startBox; //Bot�n de inicio

	sf::Font font; //Fuente usada para el texto

	sf::Text title, playText, outText; //Textos del men� inicial

	sf::Text joinText, createText, leaveText, settingsText; //Textos de la barra de navegaci�n

	sf::Text playersNum; //Cantidad de jugadores en texto
	int numPlayers = 2; //Cantidad de jugadores n�merica
	
	sf::Text ip, avatar, rols, nickname, players; //Etiquetas de texto

	sf::Text wolf, farmer, witch, vident; //Roles
	
	sf::Text avatarL, avatarR; //Moverse entre avatares
	
	sf::Text add, sub; //Agregar/Quitar jugadores

	sf::Text start; //Iniciar partida

	//Variables para manejar a los avatares
	std::vector<sf::Image> avatars;
	sf::Sprite avatarSprite;
	sf::Texture avatarTexture;
	int currentAvatarIndex = 0;

	bool isMouseOverText(const sf::Text& text, sf::RenderWindow& window); //Funci�n para los eventos del mouse
	void setWindowIcon(sf::RenderWindow& window); //Establecer �cono de la ventana
	void loadAvatars(); //Cargar las im�genes de los avatares
	void updateAvatarsSprite(); //Actualizar las im�genes con clics
};