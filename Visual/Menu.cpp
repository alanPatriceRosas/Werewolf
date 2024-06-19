#include "Menu.h"

Menu::Menu() //Constructos
{
	if (!backgroundTexture.loadFromFile("Imagenes/Fondos/fondo.png")) //Cargar el fondo inicial
	{
		std::cerr << "Error: no se pudo cargar el fondo!" << std::endl;
		exit(EXIT_FAILURE);
	}

	backgroundSprite.setTexture(backgroundTexture); //Establecer la textura

	if (!font.loadFromFile("FuentesTexto/EduTASBeginner-Bold.ttf")) //Cargar la fuente de texto
	{
		std::cerr << "Error: no se pudo cargar el texto!" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!icon.loadFromFile("Imagenes/icono.png")) //Cargar el ícono
	{
		std::cerr << "Error: no se pudo cargar el texto!" << std::endl;
		exit(EXIT_FAILURE);
	}

	loadAvatars(); //Cargar los avatares
	updateAvatarsSprite(); //Actualizar los avatares
}

void Menu::loadAvatars() //Función para agregar imágenes al menú
{
	std::vector<std::string> avatarFiles = {
	   "Imagenes/Avatares/chica_uno.png",
	   "Imagenes/Avatares/chico_uno.png",
	   "Imagenes/Avatares/chica_dos.png",
	   "Imagenes/Avatares/chico_dos.png",
	   "Imagenes/Avatares/chica_tres.png",
	   "Imagenes/Avatares/chico_tres.png"
	};

	for (const auto& file : avatarFiles)
	{
		sf::Image image;
		if (!image.loadFromFile(file))
		{
			std::cerr << "Error: no se pudo cargar el avatar " << file << std::endl;
			exit(EXIT_FAILURE);
		}
		avatars.push_back(image);
		std::cout << "Avatar cargado: " << file << std::endl;
	}
}

void Menu::updateAvatarsSprite() //Función para actualizar los avatares en pantalla
{
	if (!avatars.empty())
	{
		if (!avatarTexture.loadFromImage(avatars[currentAvatarIndex]))
		{
			std::cerr << "Error: no se pudo cargar la textura del avatar!" << std::endl;
			exit(EXIT_FAILURE);
		}

		avatarSprite.setTexture(avatarTexture);
		avatarSprite.setPosition(360, 230);

		// Escalar el sprite del avatar para que tenga un tamaño fijo
		float desiredSize = 100.0f; // Tamaño deseado del sprite del avatar
		float scaleFactor = desiredSize / std::max(avatarTexture.getSize().x, avatarTexture.getSize().y);
		avatarSprite.setScale(scaleFactor, scaleFactor);

		std::cout << "Avatar actualizado: índice " << currentAvatarIndex << std::endl;
	}
	else
	{
		std::cerr << "Error: No hay avatares cargados!" << std::endl;
	}
}

bool Menu::isMouseOverText(const sf::Text& text, sf::RenderWindow& window) //Función para que los clics tengan efecto
{
	sf::FloatRect boundingBox = text.getGlobalBounds();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	return boundingBox.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Menu::setWindowIcon(sf::RenderWindow& window) //Establecer el ícono
{
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
/*---------------------DEFINIR VENTANA INICIAL-------------------------*/
void Menu::showMainMenu()
{
	mainWindow.create(sf::VideoMode(640, 480), "Werewolf", sf::Style::Default);
	setWindowIcon(mainWindow);
	
	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent(clicker))
		{
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				mainWindow.close();
			}

			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				if (isMouseOverText(playText, mainWindow))
				{
					mainWindow.close();
					secondWindow.create(sf::VideoMode(630, 500), "Werewolf", sf::Style::Default); //Crear la ventana del menú
					showJoinMenu();
				}
				if (isMouseOverText(outText, mainWindow))
				{
					mainWindow.close();
				}
			}
		}

		mainWindow.clear();
		/*---------------------ESPECIFICACIONES DE LA VENTANA INICIAL-------------------------*/
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
		/*---------------------DIBUJAR EN LA VENTANA INICIAL-------------------------*/
		mainWindow.draw(backgroundSprite);
		mainWindow.draw(title);
		mainWindow.draw(playText);
		mainWindow.draw(outText);

		mainWindow.display();
	}
}
/*---------------------DEFINIR MENU PARA UNIRSE A PARTIDA-------------------------*/
void Menu::showJoinMenu()
{
	setWindowIcon(secondWindow);

	while (secondWindow.isOpen())
	{
		while (secondWindow.pollEvent(clicker))
		{
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				secondWindow.close();
			}
			/*---------------------EVENTOS DEL MOUSE-------------------------*/
			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				/*---------------------CAMBIAR ENTRE AVATARES-------------------------*/
				if (isMouseOverText(avatarL, secondWindow))
				{
					currentAvatarIndex = (currentAvatarIndex - 1 + avatars.size()) % avatars.size();
					updateAvatarsSprite();
				}
				if (isMouseOverText(avatarR, secondWindow))
				{
					currentAvatarIndex = (currentAvatarIndex + 1) % avatars.size();
					updateAvatarsSprite();
				}
				/*---------------------CAMBIAR ENTRE VENTANAS DESDE LA BARRA DE NAVEGACIÓN-------------------------*/
				if (isMouseOverText(joinText, secondWindow))
				{
					showJoinMenu();
				}
				if (isMouseOverText(createText, secondWindow))
				{
					showCreateMenu();
				}
				if (isMouseOverText(leaveText, secondWindow))
				{
					secondWindow.close();
				}
			}
		}

		secondWindow.clear(sf::Color(169, 169, 169));
		/*---------------------DEFINIR BARRA DE NAVEGACIÓN-------------------------*/
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

		/*---------------------ELEGIR SERVIDOR-------------------------*/
		ip.setFont(font);
		ip.setString("IP de sala:");
		ip.setCharacterSize(24);
		ip.setPosition(300, 50);
		ip.setFillColor(sf::Color::Black);

		address.setPosition(420, 53);
		address.setFillColor(sf::Color::White);
		address.setSize(sf::Vector2f(150, 25));
		address.setOutlineColor(sf::Color::Black);
		address.setOutlineThickness(2);
		/*---------------------DEFINIR APODO DEL JUGADOR-------------------------*/
		nickname.setFont(font);
		nickname.setString("Nombre de jugador:");
		nickname.setCharacterSize(24);
		nickname.setPosition(130, 100);
		nickname.setFillColor(sf::Color::Black);

		nicknamebox.setPosition(320, 105);
		nicknamebox.setFillColor(sf::Color::White);
		nicknamebox.setSize(sf::Vector2f(150, 25));
		nicknamebox.setOutlineColor(sf::Color::Black);
		nicknamebox.setOutlineThickness(2);
		/*---------------------DEFINIR AVATAR DEL JUGADOR-------------------------*/
		avatar.setFont(font);
		avatar.setString("Elige un avatar:");
		avatar.setCharacterSize(24);
		avatar.setPosition(330, 160);
		avatar.setFillColor(sf::Color::Black);

		avatarL.setFont(font);
		avatarL.setString("<");
		avatarL.setCharacterSize(40);
		avatarL.setPosition(297, 253);
		avatarL.setFillColor(sf::Color::White);

		avatarLeft.setPosition(295, 270);
		avatarLeft.setFillColor(sf::Color::Black);
		avatarLeft.setSize(sf::Vector2f(25, 25));
		avatarLeft.setOutlineColor(sf::Color::White);
		avatarLeft.setOutlineThickness(2);

		avatarR.setFont(font);
		avatarR.setString(">");
		avatarR.setCharacterSize(40);
		avatarR.setPosition(497, 253);
		avatarR.setFillColor(sf::Color::White);

		avatarRight.setPosition(495, 270);
		avatarRight.setFillColor(sf::Color::Black);
		avatarRight.setSize(sf::Vector2f(25, 25));
		avatarRight.setOutlineColor(sf::Color::White);
		avatarRight.setOutlineThickness(2);
		/*---------------------BOTÓN PARA COMENZAR PARTIDA-------------------------*/
		start.setFont(font);
		start.setString("INICIAR");
		start.setCharacterSize(24);
		start.setPosition(260, 440);
		start.setFillColor(sf::Color::White);

		startBox.setPosition(255, 440);
		startBox.setFillColor(sf::Color::Green);
		startBox.setSize(sf::Vector2f(110, 30));
		startBox.setOutlineColor(sf::Color::White);
		startBox.setOutlineThickness(2);
		/*---------------------DIBUJAR BARRA DE NAVEGACIÓN-------------------------*/
		secondWindow.draw(joinItem);
		secondWindow.draw(joinText);
		secondWindow.draw(createItem);
		secondWindow.draw(createText);
		secondWindow.draw(settingsItem);
		secondWindow.draw(settingsText);
		secondWindow.draw(leaveItem);
		secondWindow.draw(leaveText);
		/*---------------------SERVIDOR-------------------------*/
		secondWindow.draw(ip);
		secondWindow.draw(address);
		/*---------------------APODO DE JUGADOR-------------------------*/
		secondWindow.draw(nickname);
		secondWindow.draw(nicknamebox);
		/*---------------------AVATAR DE JUGADOR-------------------------*/
		secondWindow.draw(avatar);
		secondWindow.draw(avatarLeft);
		secondWindow.draw(avatarL);
		secondWindow.draw(avatarRight);
		secondWindow.draw(avatarR);
		secondWindow.draw(avatarSprite);
		/*---------------------DEFINIR VENTANA INICIAL-------------------------*/
		secondWindow.draw(startBox);
		secondWindow.draw(start);

		secondWindow.display();
	}
}

void Menu::showCreateMenu()
{
	while (secondWindow.isOpen())
	{
		while (secondWindow.pollEvent(clicker))
		{
			if (clicker.type == sf::Event::EventType::Closed || clicker.key.code == sf::Keyboard::Key::Escape)
			{
				secondWindow.close();
			}
			/*---------------------EVENTOS DEL MOUSE-------------------------*/
			if (clicker.type == sf::Event::MouseButtonPressed && clicker.mouseButton.button == sf::Mouse::Left)
			{
				/*---------------------ACTUALIZAR AVATAR-------------------------*/
				if (isMouseOverText(avatarL, secondWindow))
				{
					currentAvatarIndex = (currentAvatarIndex - 1 + avatars.size()) % avatars.size();
					updateAvatarsSprite();
				}
				if (isMouseOverText(avatarR, secondWindow))
				{
					currentAvatarIndex = (currentAvatarIndex + 1) % avatars.size();
					updateAvatarsSprite();
				}
				/*---------------------AGREGAR JUGADORES-------------------------*/
				if (isMouseOverText(add, secondWindow))
				{
					if (numPlayers < 5)
					{
						numPlayers++;
						playersNum.setString("Jugadores: " + std::to_string(numPlayers));
					}
				}
				if (isMouseOverText(sub, secondWindow))
				{
					if (numPlayers > 2)
					{
						numPlayers--;
						playersNum.setString("Jugadores: " + std::to_string(numPlayers));
					}
				}
				/*---------------------CAMBIAR ENTRE MENÚS-------------------------*/
				if (isMouseOverText(joinText, secondWindow))
				{
					showJoinMenu();
				}
				if (isMouseOverText(createText, secondWindow))
				{
					showCreateMenu();
				}
				if (isMouseOverText(leaveText, secondWindow))
				{
					secondWindow.close();
				}
			}
		}

		secondWindow.clear(sf::Color(169, 169, 169));
		/*-----------------------BARRA DE NAVEGACIÓN--------------------------------*/
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

		/*-----------------------ESPECIFICACIONES DE PARTIDA--------------------------------*/
		/*---------------------DEFINIR CANTIDAD DE JUGADORES-------------------------*/
		players.setFont(font);
		players.setString("Jugadores:");
		players.setCharacterSize(24);
		players.setPosition(30, 50);
		players.setFillColor(sf::Color::Black);

		add.setFont(font);
		add.setString("+");
		add.setCharacterSize(40);
		add.setPosition(215, 37);
		add.setFillColor(sf::Color::White);

		addPlayer.setPosition(212, 53);
		addPlayer.setFillColor(sf::Color::Green);
		addPlayer.setSize(sf::Vector2f(25, 25));
		addPlayer.setOutlineColor(sf::Color::White);
		addPlayer.setOutlineThickness(2);

		sub.setFont(font);
		sub.setString("-");
		sub.setCharacterSize(40);
		sub.setPosition(150, 35);
		sub.setFillColor(sf::Color::White);

		quitPlayer.setPosition(147, 53);
		quitPlayer.setFillColor(sf::Color::Red);
		quitPlayer.setSize(sf::Vector2f(25, 25));
		quitPlayer.setOutlineColor(sf::Color::White);
		quitPlayer.setOutlineThickness(2);

		playersNum.setFont(font);
		playersNum.setString(std::to_string(numPlayers));
		playersNum.setCharacterSize(24);
		playersNum.setPosition(185, 50);
		playersNum.setFillColor(sf::Color::Black);
		/*---------------------DEFINIR SERVIDOR-------------------------*/
		ip.setFont(font);
		ip.setString("IP de sala:");
		ip.setCharacterSize(24);
		ip.setPosition(300, 50);
		ip.setFillColor(sf::Color::Black);

		address.setPosition(420, 53);
		address.setFillColor(sf::Color::White);
		address.setSize(sf::Vector2f(150, 25));
		address.setOutlineColor(sf::Color::Black);
		address.setOutlineThickness(2);
		/*---------------------DEFINIR APODO DE JUGADOR-------------------------*/
		nickname.setFont(font);
		nickname.setString("Nombre de jugador:");
		nickname.setCharacterSize(24);
		nickname.setPosition(130, 100);
		nickname.setFillColor(sf::Color::Black);

		nicknamebox.setPosition(320, 105);
		nicknamebox.setFillColor(sf::Color::White);
		nicknamebox.setSize(sf::Vector2f(150, 25));
		nicknamebox.setOutlineColor(sf::Color::Black);
		nicknamebox.setOutlineThickness(2);
		/*---------------------DEFINIR ROLES PARA LA PARTIDA-------------------------*/
		rols.setFont(font);
		rols.setString("Roles:");
		rols.setCharacterSize(24);
		rols.setPosition(40, 160);
		rols.setFillColor(sf::Color::Black);
		/*---------------------LOBO-------------------------*/
		wolf.setFont(font);
		wolf.setString("Lobo");
		wolf.setCharacterSize(24);
		wolf.setPosition(80, 190);
		wolf.setFillColor(sf::Color::Black);

		addWolf.setPosition(50, 195);
		addWolf.setFillColor(sf::Color::White);
		addWolf.setSize(sf::Vector2f(20, 20));
		addWolf.setOutlineColor(sf::Color::Black);
		addWolf.setOutlineThickness(2);
		/*---------------------GRANJERO-------------------------*/
		farmer.setFont(font);
		farmer.setString("Granjero");
		farmer.setCharacterSize(24);
		farmer.setPosition(80, 220);
		farmer.setFillColor(sf::Color::Black);

		addFarmer.setPosition(50, 225);
		addFarmer.setFillColor(sf::Color::White);
		addFarmer.setSize(sf::Vector2f(20, 20));
		addFarmer.setOutlineColor(sf::Color::Black);
		addFarmer.setOutlineThickness(2);
		/*---------------------VIDENTE-------------------------*/
		vident.setFont(font);
		vident.setString("Vidente");
		vident.setCharacterSize(24);
		vident.setPosition(80, 250);
		vident.setFillColor(sf::Color::Black);

		addVident.setPosition(50, 255);
		addVident.setFillColor(sf::Color::White);
		addVident.setSize(sf::Vector2f(20, 20));
		addVident.setOutlineColor(sf::Color::Black);
		addVident.setOutlineThickness(2);
		/*---------------------BRUJA-------------------------*/
		witch.setFont(font);
		witch.setString("Bruja");
		witch.setCharacterSize(24);
		witch.setPosition(80, 280);
		witch.setFillColor(sf::Color::Black);

		addWitch.setPosition(50, 285);
		addWitch.setFillColor(sf::Color::White);
		addWitch.setSize(sf::Vector2f(20, 20));
		addWitch.setOutlineColor(sf::Color::Black);
		addWitch.setOutlineThickness(2);
		/*---------------------DEFINIR AVATAR DE JUGADOR-------------------------*/
		avatar.setFont(font);
		avatar.setString("Elige un avatar:");
		avatar.setCharacterSize(24);
		avatar.setPosition(330, 160);
		avatar.setFillColor(sf::Color::Black);

		avatarL.setFont(font);
		avatarL.setString("<");
		avatarL.setCharacterSize(40);
		avatarL.setPosition(297, 253);
		avatarL.setFillColor(sf::Color::White);

		avatarLeft.setPosition(295, 270);
		avatarLeft.setFillColor(sf::Color::Black);
		avatarLeft.setSize(sf::Vector2f(25, 25));
		avatarLeft.setOutlineColor(sf::Color::White);
		avatarLeft.setOutlineThickness(2);

		avatarR.setFont(font);
		avatarR.setString(">");
		avatarR.setCharacterSize(40);
		avatarR.setPosition(497, 253);
		avatarR.setFillColor(sf::Color::White);

		avatarRight.setPosition(495, 270);
		avatarRight.setFillColor(sf::Color::Black);
		avatarRight.setSize(sf::Vector2f(25, 25));
		avatarRight.setOutlineColor(sf::Color::White);
		avatarRight.setOutlineThickness(2);
		/*---------------------BOTÓN PARA INICIAR PARTIDA-------------------------*/
		start.setFont(font);
		start.setString("INICIAR");
		start.setCharacterSize(24);
		start.setPosition(260, 440);
		start.setFillColor(sf::Color::White);

		startBox.setPosition(255, 440);
		startBox.setFillColor(sf::Color::Green);
		startBox.setSize(sf::Vector2f(110, 30));
		startBox.setOutlineColor(sf::Color::White);
		startBox.setOutlineThickness(2);
		/*---------------------DIBUJAR BARRA DE NAVEGACIÓN-------------------------*/
		secondWindow.draw(joinItem);
		secondWindow.draw(joinText);
		secondWindow.draw(createItem);
		secondWindow.draw(createText);
		secondWindow.draw(settingsItem);
		secondWindow.draw(settingsText);
		secondWindow.draw(leaveItem);
		secondWindow.draw(leaveText);
		/*---------------------DIBUJAR ESPECIFICACIONES DE PARTIDA-------------------------*/
		/*---------------------JUGADORES-------------------------*/
		secondWindow.draw(players);
		secondWindow.draw(addPlayer);
		secondWindow.draw(add);
		secondWindow.draw(quitPlayer);
		secondWindow.draw(sub);
		secondWindow.draw(playersNum);
		/*---------------------SERVIDOR-------------------------*/
		secondWindow.draw(ip);
		secondWindow.draw(address);
		/*---------------------APODO DE JUGADOR-------------------------*/
		secondWindow.draw(nickname);
		secondWindow.draw(nicknamebox);
		/*---------------------ROLES-------------------------*/
		secondWindow.draw(rols);
		secondWindow.draw(wolf);
		secondWindow.draw(farmer);
		secondWindow.draw(witch);
		secondWindow.draw(vident);
		secondWindow.draw(addWolf);
		secondWindow.draw(addFarmer);
		secondWindow.draw(addWitch);
		secondWindow.draw(addVident);

		/*---------------------DIBUJAR AVATARES-------------------------*/
		secondWindow.draw(avatar);
		secondWindow.draw(avatarLeft);
		secondWindow.draw(avatarL);
		secondWindow.draw(avatarRight);
		secondWindow.draw(avatarR);
		secondWindow.draw(startBox);
		secondWindow.draw(start);
		secondWindow.draw(avatarSprite);

		secondWindow.display();
	}
}