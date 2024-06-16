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

	if (!icon.loadFromFile("Imagenes/icono.png"))
	{
		std::cerr << "Error: no se pudo cargar el texto!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

bool Menu::isMouseOverText(const sf::Text& text, sf::RenderWindow& window)
{
	sf::FloatRect boundingBox = text.getGlobalBounds();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	return boundingBox.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Menu::setWindowIcon(sf::RenderWindow& window)
{
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Menu::showMainMenu()
{
	//Crear la ventana
	mainWindow.create(sf::VideoMode(640, 480), "Werewolf", sf::Style::Default);
	setWindowIcon(mainWindow);
	//Abrir la ventana
	while (mainWindow.isOpen())
	{
		/*-----------------LEER EVENTOS------------------*/
		while (mainWindow.pollEvent(clicker))
		{
			//Cerrar la ventana con botones
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				mainWindow.close();
			}

			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOverText(playText, mainWindow))
				{
					mainWindow.close();
					secondWindow.create(sf::VideoMode(630, 500), "Werewolf", sf::Style::Default);
					showJoinMenu();
				}
				if (isMouseOverText(outText, mainWindow))
				{
					mainWindow.close();
				}
			}
		}

		mainWindow.clear();

		/*---------------RENDERIZADO------------------*/
		playText.setFont(font);
		playText.setString("JUGAR");
		playText.setCharacterSize(24);
		playText.setFillColor(sf::Color::White);
		playText.setPosition(280, 270);

		outText.setFont(font);
		outText.setString("SALIR");
		outText.setCharacterSize(24);
		outText.setFillColor(sf::Color::White);
		outText.setPosition(280, 350);

		title.setFont(font);
		title.setString("WEREWOLF");
		title.setCharacterSize(42);
		title.setPosition(210, 50);
		title.setFillColor(sf::Color::White);

		mainWindow.draw(backgroundSprite);
		mainWindow.draw(title);
		mainWindow.draw(playText);
		mainWindow.draw(outText);

		mainWindow.display();
		/*-----------------MODIFICAR------------------*/
	}
}

void Menu::showJoinMenu()
{
	setWindowIcon(secondWindow);

	while (secondWindow.isOpen())
	{
		/*-----------------LEER EVENTOS------------------*/
		while (secondWindow.pollEvent(clicker))
		{
			//Cerrar la ventana con botones
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				secondWindow.close();
			}

			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOverText(joinText, secondWindow))
				{
					showJoinMenu();
				}
				if (isMouseOverText(createText, secondWindow))
				{
					showCreateMenu();
				}
				if (isMouseOverText(settingsText, secondWindow))
				{
					showSettings();
				}
				if (isMouseOverText(leaveText, secondWindow))
				{
					secondWindow.close();
					mainWindow.display();
				}
			}
		}

		/*---------------RENDERIZADO------------------*/
		secondWindow.clear(sf::Color(169, 169, 169));

		joinText.setFont(font);
		joinText.setString("BUSCAR PARTIDA");
		joinText.setCharacterSize(24);
		joinText.setFillColor(sf::Color::Black);
		joinText.setPosition(10, 10);

		joinItem.setPosition(5, 10);
		joinItem.setFillColor(sf::Color::White);
		joinItem.setSize(sf::Vector2f(205, 30));
		joinItem.setOutlineColor(sf::Color::Black);
		joinItem.setOutlineThickness(2);

		createText.setFont(font);
		createText.setString("CREAR PARTIDA");
		createText.setCharacterSize(24);
		createText.setFillColor(sf::Color::White);
		createText.setPosition(225, 10);

		createItem.setPosition(220, 10);
		createItem.setFillColor(sf::Color::Black);
		createItem.setSize(sf::Vector2f(190, 30));
		createItem.setOutlineColor(sf::Color::White);
		createItem.setOutlineThickness(2);

		settingsText.setFont(font);
		settingsText.setString("AJUSTES");
		settingsText.setCharacterSize(24);
		settingsText.setFillColor(sf::Color::White);
		settingsText.setPosition(425, 10);

		settingsItem.setPosition(420, 10);
		settingsItem.setFillColor(sf::Color::Black);
		settingsItem.setSize(sf::Vector2f(107, 30));
		settingsItem.setOutlineColor(sf::Color::White);
		settingsItem.setOutlineThickness(2);

		leaveText.setFont(font);
		leaveText.setString("SALIR");
		leaveText.setCharacterSize(24);
		leaveText.setPosition(545, 10);
		leaveText.setFillColor(sf::Color::White);

		leaveItem.setPosition(540, 10);
		leaveItem.setFillColor(sf::Color::Red);
		leaveItem.setSize(sf::Vector2f(80, 30));
		leaveItem.setOutlineColor(sf::Color::White);
		leaveItem.setOutlineThickness(2);

		secondWindow.draw(joinItem);
		secondWindow.draw(joinText);
		secondWindow.draw(createItem);
		secondWindow.draw(createText);
		secondWindow.draw(settingsItem);
		secondWindow.draw(settingsText);
		secondWindow.draw(leaveItem);
		secondWindow.draw(leaveText);

		secondWindow.display();
	}
}

void Menu::showCreateMenu()
{
	while (secondWindow.isOpen())
	{
		/*-----------------LEER EVENTOS------------------*/
		while (secondWindow.pollEvent(clicker))
		{
			//Cerrar la ventana con botones
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				secondWindow.close();
			}

			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOverText(joinText, secondWindow))
				{
					showJoinMenu();
				}
				if (isMouseOverText(createText, secondWindow))
				{
					showCreateMenu();
				}
				if (isMouseOverText(settingsText, secondWindow))
				{
					showSettings();
				}
				if (isMouseOverText(leaveText, secondWindow))
				{
					secondWindow.close();
					mainWindow.display();
				}
			}
		}

		/*---------------RENDERIZADO------------------*/
		secondWindow.clear(sf::Color(169, 169, 169));

		joinText.setFont(font);
		joinText.setString("BUSCAR PARTIDA");
		joinText.setCharacterSize(24);
		joinText.setFillColor(sf::Color::White);
		joinText.setPosition(10, 10);

		joinItem.setPosition(5, 10);
		joinItem.setFillColor(sf::Color::Black);
		joinItem.setSize(sf::Vector2f(205, 30));
		joinItem.setOutlineColor(sf::Color::White);
		joinItem.setOutlineThickness(2);

		createText.setFont(font);
		createText.setString("CREAR PARTIDA");
		createText.setCharacterSize(24);
		createText.setFillColor(sf::Color::Black);
		createText.setPosition(225, 10);

		createItem.setPosition(220, 10);
		createItem.setFillColor(sf::Color::White);
		createItem.setSize(sf::Vector2f(190, 30));
		createItem.setOutlineColor(sf::Color::Black);
		createItem.setOutlineThickness(2);

		settingsText.setFont(font);
		settingsText.setString("AJUSTES");
		settingsText.setCharacterSize(24);
		settingsText.setFillColor(sf::Color::White);
		settingsText.setPosition(425, 10);

		settingsItem.setPosition(420, 10);
		settingsItem.setFillColor(sf::Color::Black);
		settingsItem.setSize(sf::Vector2f(107, 30));
		settingsItem.setOutlineColor(sf::Color::White);
		settingsItem.setOutlineThickness(2);

		leaveText.setFont(font);
		leaveText.setString("SALIR");
		leaveText.setCharacterSize(24);
		leaveText.setPosition(545, 10);
		leaveText.setFillColor(sf::Color::White);

		leaveItem.setPosition(540, 10);
		leaveItem.setFillColor(sf::Color::Red);
		leaveItem.setSize(sf::Vector2f(80, 30));
		leaveItem.setOutlineColor(sf::Color::White);
		leaveItem.setOutlineThickness(2);

		secondWindow.draw(joinItem);
		secondWindow.draw(joinText);
		secondWindow.draw(createItem);
		secondWindow.draw(createText);
		secondWindow.draw(settingsItem);
		secondWindow.draw(settingsText);
		secondWindow.draw(leaveItem);
		secondWindow.draw(leaveText);

		secondWindow.display();
	}
}

void Menu::showSettings()
{
	while (secondWindow.isOpen())
	{
		/*-----------------LEER EVENTOS------------------*/
		while (secondWindow.pollEvent(clicker))
		{
			//Cerrar la ventana con botones
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				secondWindow.close();
			}

			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOverText(joinText, secondWindow))
				{
					showJoinMenu();
				}
				if (isMouseOverText(createText, secondWindow))
				{
					showCreateMenu();
				}
				if (isMouseOverText(settingsText, secondWindow))
				{
					showSettings();
				}
				if (isMouseOverText(leaveText, secondWindow))
				{
					secondWindow.close();
					mainWindow.display();
				}
			}
		}

		/*---------------RENDERIZADO------------------*/
		secondWindow.clear(sf::Color(169, 169, 169));

		joinText.setFont(font);
		joinText.setString("BUSCAR PARTIDA");
		joinText.setCharacterSize(24);
		joinText.setFillColor(sf::Color::White);
		joinText.setPosition(10, 10);

		joinItem.setPosition(5, 10);
		joinItem.setFillColor(sf::Color::Black);
		joinItem.setSize(sf::Vector2f(205, 30));
		joinItem.setOutlineColor(sf::Color::White);
		joinItem.setOutlineThickness(2);

		createText.setFont(font);
		createText.setString("CREAR PARTIDA");
		createText.setCharacterSize(24);
		createText.setFillColor(sf::Color::White);
		createText.setPosition(225, 10);

		createItem.setPosition(220, 10);
		createItem.setFillColor(sf::Color::Black);
		createItem.setSize(sf::Vector2f(190, 30));
		createItem.setOutlineColor(sf::Color::White);
		createItem.setOutlineThickness(2);

		settingsText.setFont(font);
		settingsText.setString("AJUSTES");
		settingsText.setCharacterSize(24);
		settingsText.setFillColor(sf::Color::Black);
		settingsText.setPosition(425, 10);

		settingsItem.setPosition(420, 10);
		settingsItem.setFillColor(sf::Color::White);
		settingsItem.setSize(sf::Vector2f(107, 30));
		settingsItem.setOutlineColor(sf::Color::Black);
		settingsItem.setOutlineThickness(2);

		leaveText.setFont(font);
		leaveText.setString("SALIR");
		leaveText.setCharacterSize(24);
		leaveText.setPosition(545, 10);
		leaveText.setFillColor(sf::Color::White);

		leaveItem.setPosition(540, 10);
		leaveItem.setFillColor(sf::Color::Red);
		leaveItem.setSize(sf::Vector2f(80, 30));
		leaveItem.setOutlineColor(sf::Color::White);
		leaveItem.setOutlineThickness(2);

		secondWindow.draw(joinItem);
		secondWindow.draw(joinText);
		secondWindow.draw(createItem);
		secondWindow.draw(createText);
		secondWindow.draw(settingsItem);
		secondWindow.draw(settingsText);
		secondWindow.draw(leaveItem);
		secondWindow.draw(leaveText);

		secondWindow.display();
	}
}