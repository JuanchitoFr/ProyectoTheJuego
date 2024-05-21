#include "pch.h"
#include "Game.h"

Game::Game(unsigned int altoV = 0, unsigned int anchoV = 0, unsigned int framerate = 0, String tituloJ = "")
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
			
			networkType();

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
		/*this->recibirDatos();
		this->enviarDatos();*/
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

void Game::initServer()
{
	// Create a server socket to accept new connections
	bool isConnected = true;
	const auto tries = 3;
	const unsigned short port = 50002;
	server = IpAddress::getLocalAddress();
	for (auto connectionTry = 1; socket.bind(port,server) != Socket::Done; ++connectionTry)
	{
		cout << "Intentando bindear el puerto... Conectando..." << endl;
		if(connectionTry >= tries)
		{
			cout << "No se pudo bindear el puerto" << endl;
			isConnected = false;
			break;
		}
	}

		if(isConnected)
		{
			cout << "Servidor escuchando en el puerto: " << port << endl;
		
			cout << "IpServer: " << server << endl;
			
			isSocketServer = true;
			socket.setBlocking(true);
		}
	
	while(isConnected)
	{
		auto connection = Client{};
		if(socket.receive(packet,connection.clientAdress,connection.port) == Socket::Done)
		{
			
			Entity playerC;
			string message;
			packet >>  playerC;

			cout << "Recibido de" << " ( " << connection.clientAdress.toString()  << ":" << connection.port << " ) " << endl << message << endl;
			cout << "Estadisticas del cliente: " << playerC;

			packet.clear();
			getline(cin >> ws, message);
			Entity playerS;
			
			if(message == "1")
			{
				playerS.asignarEstadisticas(*playerS.getStats(), 27, 10, 16, 26, 10, 11);
				cout << "Antes de la variacion de -10_10%: " << endl << playerS;
				playerS.variacionStats();
				packet << playerS;
			}
			else if(message == "2")
			{
				playerS.asignarEstadisticas(*playerS.getStats(), 10, 16, 10, 11, 27, 26);
				cout << "Antes de la variacion de -10_10%: " << playerS;
				playerS.variacionStats();
				packet << playerS;
			}
			
			
			if(socket.send(packet, connection.clientAdress, connection.port) == Socket::Done)
			{
				cout << "Mensaje enviado por el servidor a: " << " ( " << connection.clientAdress.toString() << ":" << connection.port << " ) " << endl<< message << endl;
				cout << "Estadisticas enviadas por el servidor: " << playerS << endl;
			}
			else
			{
				cout << "No se pudo enviar el mensaje por el servidor a: " << " ( " << connection.clientAdress.toString() << ":" << connection.port << " ) " << endl;
			}
		}
		else
		{
			sleep(milliseconds(100));
		}
	}
	
}


void Game::initClient()
{
	const unsigned short port = 50002;
	cout << "Digitar ip del servidor: ";
	cin >> server;
	cout << "Send message state" << endl;
	auto state = CommunicationState::Send;
	bool isConnected = true;
	isSocketClient = true;
	while(isConnected)
	{
		if(state == CommunicationState::Send)
		{
			string message;
			packet.clear();
			getline(cin >> ws, message);
			Entity playerC;
			if (message == "1")
			{
				playerC.asignarEstadisticas(*playerC.getStats(), 27, 10, 16, 26, 10, 11);
				cout << "Antes de la variacion de -10_10%: " << playerC;
				playerC.variacionStats();
				packet << playerC;
			}
			else if (message == "2")
			{
				playerC.asignarEstadisticas(*playerC.getStats(), 10, 16, 10, 11, 27, 26);
				cout << "Antes de la variacion de -10_10%: " << playerC;
				playerC.variacionStats();
				packet << playerC;
			}
			else
			{
				packet << message;
			}
			
				
			if (socket.send(packet, server, port) == Socket::Done)
			{
				cout << "Enviado a el servidor " << " ( " << server.toString() << ":" << port << " ) " << endl;
				cout << "Enviadas la estadisticas: " << playerC << " al servidor" << endl;
				state = CommunicationState::Receive;
			}
			else
			{
				cout << "No se pudo enviar el mensaje a el servidor: " << " ( " << server.toString() << ":" << port << " ) " << endl;
			}

		}
		else
		{
			auto ipAdress = IpAddress{};
			packet.clear();
			unsigned short port = 0;
			if(socket.receive(packet,ipAdress,port) == Socket::Done)
			{
				Entity playerS;
				packet >> playerS;
				cout << "Recibido de el servidor: ( " << ipAdress.toString() << ":" << port << " ) " << endl;
				cout << " Estadisticas: " << playerS<< endl;
				state = CommunicationState::Send;
			}
			else
			{
				cout << "No se pudo recibir el mensaje de parte del servidor" << endl;
				state = CommunicationState::Send;
				sleep(milliseconds(100));
			}
		}
	}
	
	
}

void Game::recibirDatosS()
{
	
}

void Game::enviarDatosS()
{
}

void Game::recibirDatosC()
{

}

void Game::enviarDatosC()
{
	
		
}

void Game::isServer()
{
	this->isSocketServer = true;
}

void Game::networkType()
{
	
	if(this->estados[0]->getButtons() != nullptr && this->estados[0]->getIsMenu() == true)
	{
		Buttons* newButtons = this->estados[0]->getButtons();
		if (newButtons[1].isPressed())
		{
			initServer();
		}
		else if (newButtons[2].isPressed())
		{
			initClient();
		}
	}
	
}

IpAddress Game::getIpAdressServer()
{
	return this->server;
}





UdpSocket& Game::getSocket()
{
	return this->socket;
}




