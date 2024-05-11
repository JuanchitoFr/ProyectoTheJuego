#include "pch.h"
#include "../doth/game.h"

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
	this->currentEstadoIndex = this->estados->getEstadosArrSize() - 1;
	
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
			this->estados->render(this->ventana);
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

		if (this->currentEstadoIndex >= 0 && this->currentEstadoIndex < this->estados->getEstadosArrSize())
		{
			// Actualiza el estado actual
			this->estados[this->currentEstadoIndex].Update(this->deltaT);

			// Verifica si el estado actual ha terminado
			if (this->estados[this->currentEstadoIndex].getFin())
			{

				this->estados[this->currentEstadoIndex].findEstado();

				// Elimina el estado actual (en este caso, simplemente marca el estado como no activo)
				this->estados[this->currentEstadoIndex].setActive(false);

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
		this->estados = new Menu(&this->estados, this->ventana);
		this->estados->setEstadosArrSize(newArrSize);
	}
}

void Game::recibirDatos()
{
	IpAddress emisor;
}

