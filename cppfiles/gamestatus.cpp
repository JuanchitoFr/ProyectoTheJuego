#include "pch.h"
#include "../doth/gamestatus.h"



GameStatus::GameStatus(std::stack<GameStatus*>* Statetype, RenderWindow* ventana)
{
	this->Statetype = Statetype;
	this->ventana = ventana;
	this->end = false;
}

GameStatus::~GameStatus()
{
}

void GameStatus::render(RenderTarget* drawObj)
{
}

void GameStatus::run()
{
}

void GameStatus::checkKeyboardEvents()
{
}

void GameStatus::Update(const double& deltaTime)
{
}

void GameStatus::endState()
{
	this->end = true;
}

bool GameStatus::getEndState() const
{
	return this->end;
}



