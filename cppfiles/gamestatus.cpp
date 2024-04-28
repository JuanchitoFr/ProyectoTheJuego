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

void GameStatus::checkKeyboardEvents(float deltaT)
{
}

void GameStatus::Update(float deltaTime)
{
}

void GameStatus::updateMousePos()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->ventana);
	this->mousePosView = this->ventana->mapPixelToCoords(Mouse::getPosition(*this->ventana));
}

void GameStatus::endState()
{
	this->end = true;
}

void GameStatus::parcialEndState()
{
	this->parcialEnd = true;
}

bool GameStatus::getEndState() const
{
	return this->end;
}

bool GameStatus::getParcialEndState() const
{
	return this->parcialEnd;
}

RenderWindow* GameStatus::getWindow()
{
	return this->ventana;
}



