#include "pch.h"
#include "../doth/game.h"

Game::Game(unsigned int altoV = 0, unsigned int anchoV = 0, unsigned int framerate = 0, String tituloJ = "")
{
	this->altoVentana = altoV;
	this->anchoVentana = anchoV;
	this->framerate = framerate;
	this->tituloJuego = tituloJ;
	this->deltaT = 0.f;
	this->ventana = new RenderWindow(VideoMode(anchoV, altoV), tituloJuego);
	this->ventana->setFramerateLimit(framerate);
	initStates();
	run();
}

Game::~Game()
{
	delete this->ventana;
	while (!this->estados.empty()) {
		delete this->estados.top();
		this->estados.pop();
	}
	
}

void Game::render()
{
	try
	{
		this->ventana->clear(Color::Blue);
		if (!this->estados.empty()) {
			this->estados.top()->render(this->ventana);
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
		if (!this->estados.empty())

		{
			this->estados.top()->Update(this->deltaT);

			if (this->estados.top()->getEndState())
			{
				this->estados.top()->endState();
				delete this->estados.top();
				this->estados.pop();
			}
		}
		else
		{
			this->ventana->close();
		}
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	
}


void Game::run()
{
	while (this->ventana->isOpen()) {
		updateState();
		render();
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
					glViewport(0, 0, event.size.width, event.size.height);
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
	this->estados.push(new Ingame(&this->estados, this->ventana));
}

