#include "pch.h"
#include "GameStatus.h"




GameStatus::GameStatus()
{
	this->estadosArrSize = 0; this->textures = NULL; this->textureArrSize = 0;
	this->estados = nullptr; this->ventana = nullptr; this->fin = false; this->playerArrSize = 0; this->backLayersArrSize = 0;
	this->backLayersArr = nullptr; this->buttons = nullptr; this->isMenu = false; this->buttonArrSize = 0;
}

GameStatus::GameStatus(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr)
{
	this->ventana = ventana; this->estados = estados; this->textureArrSize = 0;
	this->estadosArrSize = 0; this->textures = NULL; this->fin = false; this->active = true;
	this->playerArrSize = 0; this->backLayersArrSize = 0; this->backLayersArr = nullptr;
	this->buttons = nullptr; this->isMenu = false; this->buttonArrSize = 0;
}

GameStatus::~GameStatus()
{
}

void GameStatus::render(RenderTarget* drawObj)
{
}


void GameStatus::checkKeyboardEvents(float deltaT)
{
}

void GameStatus::Update(float deltaTime)
{
}

void GameStatus::GUI()
{
}



void GameStatus::updateMousePos()
{
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->ventana);
	this->mousePosView = this->ventana->mapPixelToCoords(Mouse::getPosition(*this->ventana));
}




RenderWindow* GameStatus::getWindow()
{
	return this->ventana;
}

GameStatus* GameStatus::getEstado(unsigned int num)
{
	return this->estados[num];
}

Texture* GameStatus::getTexture(unsigned int num)
{
	return &this->textures[num];
}

unsigned int GameStatus::getTextureArrSize()
{
	return this->textureArrSize;
}

unsigned int GameStatus::getEstadosArrSize()
{
	return this->estadosArrSize;
}

unsigned int GameStatus::setEstadosArrSize(unsigned int arrSize)
{
	return this->estadosArrSize = arrSize;
}

bool GameStatus::getFin()
{
	return this->fin;
}

void GameStatus::findEstado()
{
	this->fin = true;
}

void GameStatus::setActive(bool isActive)
{
	this->active = isActive;
}

void GameStatus::setPlayer(unsigned int num, Player* player)
{
	this->player[num] = player;
}

bool GameStatus::getIsMenu()
{
	return this->isMenu;
}

void GameStatus::setIsMenu(bool menu)
{
	this->isMenu = menu;
}


Entity* GameStatus::getPlayer(unsigned int i)
{
	return this->player[i];
}

unsigned int GameStatus::getAmoutPlayer()
{
	return this->playerArrSize;
}




