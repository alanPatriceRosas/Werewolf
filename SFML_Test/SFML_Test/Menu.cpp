#include "Menu.h"

Menu::Menu()
{
	if (!backgroundTexture.loadFromFile("Imagenes/Fondos/fondo.png"))
	{
		std::cerr << "Error: no se pudo cargar el fondo!" << std::endl;
		exit(EXIT_FAILURE);
	}

	backgroundSprite.setTexture(backgroundTexture);

	if (!font.loadFromFile("FuentesTexto/EduTASBeginner-Bold.ttf"))
	{
		std::cerr << "Error: no se pudo cargar el texto!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Menu::showMainMenu()
{
	//Crear la ventana
	window.create(sf::VideoMode(640, 480), "Werewolf", sf::Style::Default);
	//Abrir la ventana
	while (window.isOpen())
	{
		/*-----------------LEER EVENTOS------------------*/
		while (window.pollEvent(clicker))
		{
			//Cerrar la ventana
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				window.close();
			}
		}

		/*---------------RENDERIZADO------------------*/
		playItem.setSize(sf::Vector2f(100, 50));
		playItem.setPosition(sf::Vector2f(280, 270));
		playItem.setFillColor(sf::Color::Blue);

		outItem.setSize(sf::Vector2f(100, 50));
		outItem.setPosition(sf::Vector2f(280, 330));
		outItem.setFillColor(sf::Color::Red);

		playText.setFont(font);
		playText.setString("JUGAR");
		playText.setCharacterSize(24);
		playText.setFillColor(sf::Color::White);
		playText.setPosition(playItem.getPosition().x + (playItem.getSize().x / 2) - (playText.getLocalBounds().width / 2), playItem.getPosition().y + (playItem.getSize().y / 2) - (playText.getLocalBounds().height / 2));

		outText.setFont(font);
		outText.setString("SALIR");
		outText.setCharacterSize(24);
		outText.setFillColor(sf::Color::White);
		outText.setPosition(outItem.getPosition().x + (outItem.getSize().x / 2) - (outText.getLocalBounds().width / 2), outItem.getPosition().y + (outItem.getSize().y / 2) - (outText.getLocalBounds().height / 2));

		window.draw(backgroundSprite);
		window.draw(playItem);
		window.draw(playText);
		window.draw(outItem);
		window.draw(outText);

		window.display();
		/*-----------------MODIFICAR------------------*/
	}
}

void Menu::showJoinMenu()
{

}

void Menu::showCreateMenu()
{

}

void Menu::showSettings()
{

}