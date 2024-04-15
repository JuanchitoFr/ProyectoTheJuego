#include "pch.h"
#include "../doth/game.h"

Game::Game(int altoV = 0, int anchoV = 0, short framerate = 0, String tituloJ = "")
{
	this->altoVentana = altoV;
	this->anchoVentana = anchoV;
	this->tituloJuego = tituloJ;
	this->ventana = new RenderWindow(VideoMode(anchoV, altoV), tituloJuego);
	this->ventana->setFramerateLimit(framerate);
	initStates();
}

Game::~Game()
{
	
	while (!this->estados.empty()) {
		delete this->estados.top();
		this->estados.pop();
	}
	delete ventana;
}

void Game::render()
{
	this->ventana->clear();
	if (!this->estados.empty()) {
		this->estados.top()->render(this->ventana);
	}
	ventana->display();

}


void Game::run()
{
	while (this->ventana->isOpen()) {
		checkStop();
		render();
	}
}

void Game::checkStop()
{
	while (ventana->pollEvent(eventos))
	{
		if (eventos.type == Event::Closed)
		{
			ventana->close();
		}

	}
}

void Game::initStates()
{
	this->estados.push(new Ingame(&this->estados, this->ventana));
}

