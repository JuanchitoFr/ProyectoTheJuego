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
	try
	{
		if (!drawObj)
			drawObj = this->ventana;
		this->jugadores->render(this->ventana);
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	
}

void Ingame::checkKeyboardEvents()
{
}

void Ingame::Update(const double& deltaT)
{
}

void Ingame::run()
{
}

void Ingame::initTextures()
{
	Texture texture;
	if (!texture.loadFromFile("assets/Spritesheets/Red.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta" ;
	}
	this->textures["Player1"] = texture;
}

void Ingame::initPlayer()
{
	this->jugadores = new Player(0,0,0,"",0.f,0.f, & this->textures["Player1"]);
}

void Ingame::endState()
{
	this->end = true;
}
