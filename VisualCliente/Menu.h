#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
public:
	Menu();
	~Menu() {};
	void showMainMenu();
	void showJoinMenu();
	void showCreateMenu();
	void showSettings();
	
private:
	sf::RenderWindow window;
	sf::RenderWindow render;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Event clicker;
	sf::RectangleShape createItem;
	sf::RectangleShape joinItem;
	sf::RectangleShape settingsItem;
	sf::RectangleShape leaveItem;
	sf::RectangleShape playItem;
	sf::RectangleShape outItem;
	sf::Font font;
	sf::Text joinText;
	sf::Text createText;
	sf::Text leaveText;
	sf::Text settingsText;
	sf::Text playText;
	sf::Text outText;
};