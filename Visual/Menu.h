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
	void showJoinMenu(); //Mostrar el menú para unirse a una partida
	void showCreateMenu(); //Mostrar el menú para crear una partida
	
private:
	sf::Event clicker; //Variable para manejar los eventos del mouse

	sf::RenderWindow mainWindow; //Ventana inicial
	sf::RenderWindow secondWindow; //Ventana de menu

	sf::Image icon; //Ícono del juego

	sf::Texture backgroundTexture; //Textura del menú inicial
	sf::Sprite backgroundSprite; //Variable para mostrar el fondo
	
	sf::RectangleShape createItem, joinItem, leaveItem, settingsItem; //Figuras de la barra de navegación

	sf::RectangleShape addPlayer, quitPlayer; //Figuras para agregar o quitar jugadores

	sf::RectangleShape addWolf, addFarmer, addWitch, addVident; //Casillas de selección de roles
	
	sf::RectangleShape avatarLeft, avatarRight; //Casillas de selección de avatares

	sf::RectangleShape address, nicknamebox; //Cajas de texto para poner un nombre y establecer servidor

	sf::RectangleShape startBox; //Botón de inicio

	sf::Font font; //Fuente usada para el texto

	sf::Text title, playText, outText; //Textos del menú inicial

	sf::Text joinText, createText, leaveText, settingsText; //Textos de la barra de navegación

	sf::Text playersNum; //Cantidad de jugadores en texto
	int numPlayers = 2; //Cantidad de jugadores númerica
	
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

	bool isMouseOverText(const sf::Text& text, sf::RenderWindow& window); //Función para los eventos del mouse
	void setWindowIcon(sf::RenderWindow& window); //Establecer ícono de la ventana
	void loadAvatars(); //Cargar las imágenes de los avatares
	void updateAvatarsSprite(); //Actualizar las imágenes con clics
};