#include "pch.h"
#include "../doth/gamestatus.h"



GameStatus::GameStatus(std::stack<GameStatus*>* Statetype = nullptr, RenderWindow* ventana = nullptr)
{
	this->Statetype = Statetype;
	this->ventana = ventana;
}

GameStatus::~GameStatus()
{
}

