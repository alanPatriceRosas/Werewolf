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
	sf::RenderWindow mainWindow;
	sf::RenderWindow secondWindow;
	sf::Image icon;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Event clicker;
	sf::RectangleShape createItem;
	sf::RectangleShape joinItem;
	sf::RectangleShape settingsItem;
	sf::RectangleShape leaveItem;
	sf::Font font;
	sf::Text title;
	sf::Text joinText;
	sf::Text createText;
	sf::Text leaveText;
	sf::Text settingsText;
	sf::Text playText;
	sf::Text outText;

	bool isMouseOverText(const sf::Text& text, sf::RenderWindow& window);
	void setWindowIcon(sf::RenderWindow& window);
};