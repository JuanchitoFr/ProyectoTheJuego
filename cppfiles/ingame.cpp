#include "pch.h"
#include "../doth/ingame.h"


Ingame::Ingame(std::stack<GameStatus*>* Statetype, RenderWindow* ventana) : GameStatus(Statetype,ventana)
{
	initTextures();
	initPlayer();
}

Ingame::~Ingame()
{
	delete jugadores;
}

void Ingame::render(RenderTarget* drawObj)
{
	if (!drawObj) {
		drawObj = this->ventana;
	}
	
	this->jugadores->render(this->ventana);
}

void Ingame::run()
{
}

void Ingame::initTextures()
{
	Texture texture;
	if (!texture.loadFromFile("assets/Spritesheets/Red.png")) {
		std::cout << " No se pudo cargar, tal vez ruta incorrecta" << std::endl;
	}
	this->textures["Player1"] = texture;
}

void Ingame::initPlayer()
{
	this->jugadores = new Player(&this->textures["Player1"]);
}
