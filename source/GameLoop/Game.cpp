#include "pch.h"
#include "../source/GameLoop/Game.h"


Game::Game(unsigned int altoV = 0, unsigned int anchoV = 0, unsigned int framerate = 0, String tituloJ = "") : nextEntityId(0),
isServerTurn(false), isClientTurn(false)
{
	this->altoVentana = altoV;
	this->anchoVentana = anchoV;
	this->framerate = framerate;
	this->tituloJuego = tituloJ;
	this->deltaT = 0.f;
	this->ventana = new RenderWindow(VideoMode(anchoV, altoV), tituloJuego, Style::Default);
	this->ventana->setFramerateLimit(60);
	this->ventana->setVerticalSyncEnabled(true);
	this->settings.antialiasingLevel = 16;
	initStates();
	this->currentEstadoIndex = this->estados[0]->getEstadosArrSize() - 1;
	
	
}

Game::~Game()
{
	delete this->ventana;
	delete estados;
	
	
}

void Game::render()
{
	try
	{
		this->ventana->clear(Color::Yellow);
		if(this->estados != nullptr)
		{
			this->estados[0]->render(this->ventana);
		}
		ventana->display();
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	

}

void Game::updateState()
{
	try
	{
		this->stateEvents();

		if (this->currentEstadoIndex >= 0 && this->currentEstadoIndex < this->estados[0]->getEstadosArrSize())
		{
			// Actualiza el estado actual
			this->estados[this->currentEstadoIndex]->Update(this->deltaT);

			
			
			// Verifica si el estado actual ha terminado
			if (this->estados[this->currentEstadoIndex]->getFin())
			{

				this->estados[this->currentEstadoIndex]->findEstado();

				// Elimina el estado actual (en este caso, simplemente marca el estado como no activo)
				this->estados[this->currentEstadoIndex]->setActive(false);

				this->currentEstadoIndex--;

				// Si no hay más estados activos, cierra la ventana
				if (this->currentEstadoIndex < 0) 
				{
					this->ventana->close();
				}
			}
		}
		else {
			// Si no hay estados en el array, cierra la ventana
			this->ventana->close();
		}
		
	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::GAME::UPDATESTATE:  " << p.what() << std::endl;
	}
	
}

void Game::updateDeltaT()
{
	
	this->deltaT = this->deltaTclock.restart().asSeconds();
	
}


void Game::run()
{
	while (this->ventana->isOpen()) {
		
		this->updateDeltaT();
		this->updateState();
		this->buttonStatus();
		if (isServer == true) {
			manageDataServer();
		}

		// Lógica de turnos del cliente
		if (isClient == true) {
			manageDataClient();
		}
		

		this->render();
	}
}

void Game::stateEvents()
{
	try
	{
		while (this->ventana->pollEvent(this->event))
		{
			switch (this->event.type)
			{
				case Event::Closed:
				{
					this->ventana->close();
					break;
				}

				case Event::KeyPressed:
				{
					switch (event.key.code)
					{
					case Keyboard::A:
					{
						std::cout << "Se esta presionando la tecla A"  << std::endl;
						break;
					}
					case Keyboard::W:
					{
						std::cout << "Se esta presionando la tecla W" << std::endl;
						break;
					}
					case Keyboard::D:
					{
						std::cout << "Se esta presionando la tecla D" << std::endl;
						break;
					}
					case Keyboard::S:
					{
						std::cout << "Se esta presionando la tecla S" << std::endl;
						break;
					}
						
						default:
							break;
					}
					break;
				}
				case Event::Resized:
				{
					FloatRect area(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
					ventana->setView(View(area));
					std::cout << "Nueva anchura de la pantalla: " << event.size.width << std::endl;
					std::cout << "Nueva altura de la pantalla: " << event.size.height << std::endl;
					break;
				}
				default:
					break;
			}
		}
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	
}


void Game::updateGui()
{
	if(this->estados[0]->getMapPlayer().getSize() > 0 && this->estados[0]->getUiBoxes().getSize() > 0)
	{
		for (auto&& map1 : this->estados[0]->getMapPlayer())
		{
			for (auto&& map2 : this->estados[0]->getUiBoxes())
			{
				if(map1.first == "Player_1")
				{
					if (map2.first == "Attack")
					{
						map1.second->setCurrentAnimation(typeOfAnimation::Attack_Anim);
					}
					else if (map2.first == "Defend")
					{
						map1.second->setCurrentAnimation(typeOfAnimation::Defend_Anim);
					}
					else if (map2.first == "Dead")
					{
						map1.second->setCurrentAnimation(typeOfAnimation::Dead_Anim);
					}
					else if (map2.first == "Hurt")
					{
						map1.second->setCurrentAnimation(typeOfAnimation::Hurt_Anim);
					}
					else if (map2.first == "Walk")
					{
						map1.second->setCurrentAnimation(typeOfAnimation::Walk_Anim);
					}
					else if (map2.first == "Stats")
					{
						std::cout << map1.first << " Stats después de la variación " << endl << *map1.second << endl;
					}
				}
				
			}
		}
	}
	
}

void Game::initStates()
{
	if (this->estados == nullptr)
	{
		unsigned int newArrSize = 1;
		this->estados = new GameStatus *();
		this->estados[0] = new Menu(this->estados, this->ventana);
		this->estados[0]->setEstadosArrSize(newArrSize);
		this->estados[0]->setIsMenu(true);
		
	}
}

void Game::serverSide()
{
	// Crear un socket TCP
	/*sf::TcpListener listener;*/

	// Escuchar al puerto 53000
	if (listener.listen(53000, IpAddress::LocalHost) != sf::Socket::Done)
	{
		std::cout << "Could not bind the server" << endl;
		clientSide();
		isClient = true;
		// Manejar error al escuchar
		return;
	}
	else
	{
		std::cout << "Connected" << endl;
		isServer = true;
		
	}
	// Aceptar una nueva conexión
	/*sf::TcpSocket client;*/
	if (listener.accept(client) != sf::Socket::Done)
	{
		std::cout << "Could not accept the client" << endl;// Manejar error al aceptar la conexión
		return;
	}
	else
	{
		std::cout << "Client accepted" << endl;
	}
	bool bothReady = false;
	int currentCha;

	while (!bothReady) {
		sf::Packet packet;
		
		// Send selected character to client
		std::string message = std::to_string(estados[0]->getChosenCharacter());
		packet << message;

		if (client.send(packet) != sf::Socket::Done) {
			std::cout << "Packet not sent" << std::endl;
			return;
		}

		// Receive selected character from client
		packet.clear();
		if (client.receive(packet) != sf::Socket::Done) {
			std::cout << "Packet not received" << std::endl;
			return;
		}
		else {
			std::string receivedMessage;
			packet >> receivedMessage;
			int chosenCharacter = std::stoi(receivedMessage);
			if (chosenCharacter > 0) {
				currentCha = chosenCharacter;
				this->estados[0]->isAnotherClient(true);
				 // Mark as ready to move to the game state

				sf::Packet readyPacket;
				readyPacket << "READY";
				if (client.send(readyPacket) != sf::Socket::Done) {
					std::cout << "Ready packet not sent" << std::endl;
					return;
				}
				else
				{
					this->estados[0]->thereIsConection(true);
					if (this->estados[0]->getThereIsConection() == true)
					{
						this->estados[0] = new Ingame(this->estados, this->ventana);
						this->estados[0]->setChosenCharacter(currentCha);
						this->estados[0]->isAnotherClient(true);
						this->estados[0]->setEstadosArrSize(1);

					}
					bothReady = true;
				}
				
			}
		}
	}
	sf::sleep(milliseconds(50));
	

	if (this->estados[0]->getThereIsConection() == true)
	{
		sf::Packet statsPacket;
		Entity* serverEntity = new Entity();
		std::cout << "Antes de la variacion (servidor): " << endl << *this->estados[0]->getMapPlayer()["Player_1"] << endl;
		sf::sleep(milliseconds(50));
		this->estados[0]->getMapPlayer()["Player_1"]->variacionStats();
		serverEntity = estados[0]->getMapPlayer()["Player_1"];
		statsPacket << *serverEntity;
		if (client.send(statsPacket) != sf::Socket::Done)
		{
			std::cout << "Stats packet not sent" << std::endl;
			return;
		}
		// Recibir estadísticas del personaje del cliente
		statsPacket.clear();
		if (client.receive(statsPacket) != sf::Socket::Done)
		{
			std::cout << "Stats packet not received" << std::endl;
			return;
		}
		else
		{
			statsPacket >> *this->estados[0]->getMapPlayer()["Player_2"];
			std::cout << "Después de la variación (Cliente): " << *this->estados[0]->getMapPlayer()["Player_2"] << endl;
			sf::sleep(milliseconds(50));
		}
		
	}
	this->client.setBlocking(false);
	this->estados[0]->setSocket(client);
		
}

void Game::clientSide()
{
	
	/*sf::TcpSocket socket;*/
	// Intentar conectar al servidor en el puerto 53000
	if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
	{
		std::cout << "Could not connect to the server" << endl;
		// Manejar error al conectar
		return;
	}
	else
	{
		std::cout << "Connected to the server" << endl;
	}
	bool bothReady = false;
	bool clientCharacterSent = false;
	int currentCha;

	while (!bothReady) 
	{
		sf::Packet packet;
		
		// Receive selected character from server
		if (!clientCharacterSent) {
			if (socket.receive(packet) != sf::Socket::Done) {
				std::cout << "Packet not received" << std::endl;
				return;
			}
			else {
				std::string receivedMessage;
				packet >> receivedMessage;
				int chosenCharacter = std::stoi(receivedMessage);
				if (chosenCharacter > 0) {
					currentCha = chosenCharacter;
					
				}
			}
		}

		// Send selected character to server
		packet.clear();
		std::string message = std::to_string(estados[0]->getChosenCharacter());
		packet << message;

		if (socket.send(packet) != sf::Socket::Done) {
			std::cout << "Packet not sent" << std::endl;
			return;
		}
		else
		{
			this->estados[0]->getMapPlayer();
			clientCharacterSent = true;
		}
		

		// Wait for server to confirm both are ready
		sf::Packet readyPacket;
		if (socket.receive(readyPacket) != sf::Socket::Done) {
			std::cout << "Ready packet not received" << std::endl;
			return;
		}
		else {
			std::string readyMessage;
			readyPacket >> readyMessage;
			if (readyMessage == "READY") {
				this->estados[0]->thereIsConection(true);
				if (this->estados[0]->getThereIsConection() == true)
				{
					this->estados[0] = new Ingame(this->estados, this->ventana);
					this->estados[0]->setChosenCharacter(currentCha);
					this->estados[0]->isAnotherClient(true);
					this->estados[0]->setEstadosArrSize(1);
				}
				bothReady = true;
			}
		}
	}

	if (this->estados[0]->getThereIsConection())
	{
		// Recibir estadísticas del personaje del servidor
		sf::Packet statsPacket;
		if (socket.receive(statsPacket) != sf::Socket::Done)
		{
			std::cout << "Stats packet not received" << std::endl;
			return;
		}
		else
		{
			
			statsPacket >> *estados[0]->getMapPlayer()["Player_2"];
			std::cout << "Después de la variación (Servidor): " << *this->estados[0]->getMapPlayer()["Player_2"] << endl;
			sf::sleep(milliseconds(50));
		}

		// Enviar estadísticas del personaje del cliente al servidor
		statsPacket.clear();
		std::cout << "Antes de la variacion (Cliente): " << endl << *this->estados[0]->getMapPlayer()["Player_1"] << endl;
		sf::sleep(milliseconds(50));
		Entity* clientEntity = estados[0]->getMapPlayer()["Player_1"];
		clientEntity->variacionStats();
		statsPacket << *clientEntity;
		if (socket.send(statsPacket) != sf::Socket::Done)
		{
			std::cout << "Stats packet not sent" << std::endl;
			return;
		}
		
	}
	socket.setBlocking(false);
	this->estados[0]->setSocket(socket);
	
}

void Game::manageDataServer()
{
	
	if (!isServerTurn) return;
	
	sf::Packet actionPacket;
	if (client.receive(actionPacket) != sf::Socket::Done)
	{
		std::cout << "Action packet not received" << std::endl;
		return;
	}
	else
	{
		std::string action, playerKey;
		bool isDefending;
		actionPacket >> action >> playerKey >> isDefending;
		playerKey = "Player_2";
		// Actualizar la animación del jugador correspondiente
		this->estados[0]->updateGuiStatus(playerKey, action);

		switchTurn();

		// Notificar al cliente que el turno ha cambiado
		sf::Packet turnPacket;
		turnPacket << isServerTurn;
		if (client.send(turnPacket) != sf::Socket::Done) {
			std::cout << "Turn packet not sent" << std::endl;
		}
		//sf::Packet damagePacket;
		//int damage = estados[0]->calculateDamage(this->estados[0]->getMapPlayer()["Player_1"]->getAtkFisico(), playerKey, isDefending);
		//this->estados[0]->updateHealth("Player_2", damage);
		//damagePacket << damage << this->estados[0]->getMapPlayer()["Player_1"]->getHp();
		//if (socket.send(damagePacket) != Socket::Done)
		//{
		//	std::cout << "Damage packet not sent" << std::endl;
		//	return;
		//}

		//// Recibir y actualizar la salud del defensor
		//sf::Packet healthPacket;
		//if (socket.receive(healthPacket) != sf::Socket::Done) {
		//	std::cout << "Health packet not received" << std::endl;
		//	return;
		//}

		//std::string updatedDefenderKey;
		//int updatedHealth;
		//healthPacket >> updatedDefenderKey >> updatedHealth;
		//this->estados[0]->getMapPlayer()[updatedDefenderKey]->getStats()->hp = updatedHealth;

		//std::cout << "Salud actualizada de " << updatedDefenderKey << ": " << updatedHealth << std::endl;
	}

	
}

void Game::manageDataClient()
{
	
	sf::Packet turnPacket;
	if (socket.receive(turnPacket) != sf::Socket::Done) {
		std::cout << "Turn packet not received" << std::endl;
		return;
	}
	turnPacket >> isServerTurn;
	if (!isServerTurn) 
	{
		sf::Packet actionPacket;
		if (socket.receive(actionPacket) != sf::Socket::Done)
		{
			std::cout << "Action packet not received" << std::endl;
			return;
		}
		else
		{

			std::string action, playerKey;
			bool isDefending;
			actionPacket >> action >> playerKey >> isDefending;
			playerKey = "Player_2";
			// Actualizar la animación del jugador correspondiente
			this->estados[0]->updateGuiStatus(playerKey, action);

			//sf::Packet damagePacket;
			//int damage = estados[0]->calculateDamage(this->estados[0]->getMapPlayer()["Player_1"]->getAtkFisico(), playerKey, isDefending);
			//this->estados[0]->updateHealth("Player_2", damage);
			//damagePacket << damage << this->estados[0]->getMapPlayer()["Player_1"]->getHp();
			//if(socket.send(damagePacket) != Socket::Done)
			//{
			//	std::cout << "Damage packet not sent" << std::endl;
			//	return;
			//}

			//// Recibir y actualizar la salud del defensor
			//sf::Packet healthPacket;
			//if (socket.receive(healthPacket) != sf::Socket::Done) {
			//	std::cout << "Health packet not received" << std::endl;
			//	return;
			//}

			//std::string updatedDefenderKey;
			//int updatedHealth;
			//healthPacket >> updatedDefenderKey >> updatedHealth;
			//this->estados[0]->getMapPlayer()[updatedDefenderKey]->getStats()->hp = updatedHealth;

			//std::cout << "Salud actualizada de " << updatedDefenderKey << ": " << updatedHealth << std::endl;
		}
	}
	
	
}



void Game::buttonStatus()
{
	if(estados[0]->getButtons() != nullptr)
	{
		Gui::Buttons* newButtons = estados[0]->getButtons();
		if(newButtons[readyButton].isPressed())
		{
			serverSide();
			
		}
	}
}

void Game::switchTurn()
{
	isServerTurn = !isServerTurn;
}

void Game::determineTurn()
{
	auto player1 = this->estados[0]->getMapPlayer()["Player_1"];
	auto player2 = this->estados[0]->getMapPlayer()["Player_2"];

	if (player1->getVelocidad() >= player2->getVelocidad()) {
		isServerTurn = true; // Player_1 (Servidor) juega primero
	}
	else {
		isServerTurn = false; // Player_2 (Cliente) juega primero
	}
}














