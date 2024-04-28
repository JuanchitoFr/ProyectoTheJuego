#include "pch.h"
#include "../doth/game.h"

Game::Game(unsigned int altoV = 0, unsigned int anchoV = 0, unsigned int framerate = 0, String tituloJ = "")
{
	this->altoVentana = altoV;
	this->anchoVentana = anchoV;
	this->framerate = framerate;
	this->tituloJuego = tituloJ;
	this->deltaT = 0.f;
	this->ventana = new RenderWindow(VideoMode(anchoV, altoV), tituloJuego, Style::Fullscreen);
	this->ventana->setFramerateLimit(60);
	this->ventana->setVerticalSyncEnabled(true);
	this->settings.antialiasingLevel = 16;
	initStates();
	
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
		this->ventana->clear(Color::Black);
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
			else if (this->estados.top()->getParcialEndState()) {
					this->estados.top()->parcialEndState();
					delete this->estados.top();
					this->estados.pop();
					this->estados.push(new Ingame(&this->estados, this->ventana));
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
		Clock clock;
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
					FloatRect area(0, 0, event.size.width, event.size.height);
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
	
	this->estados.push(new Menu(&this->estados, this->ventana));
	
}

