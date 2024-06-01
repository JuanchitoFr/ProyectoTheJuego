#include "pch.h"
#include "GameStatus.h"




GameStatus::GameStatus()
{
	this->estadosArrSize = 0; this->estados = nullptr; this->ventana = nullptr; this->fin = false;
	this->buttons = nullptr; this->isMenu = false; this->buttonArrSize = 0;  this->clientNumber = 1;
	this->characterChosen = 0; this->anotherClient = false;
}

GameStatus::GameStatus(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr)
{
	this->ventana = ventana; this->estados = estados;
	this->estadosArrSize = 0; this->fin = false; this->active = true;
	this->buttons = nullptr; this->isMenu = false; this->buttonArrSize = 0; this->characterChosen = 0;
	this->clientNumber = 1; this->anotherClient = false;
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




unsigned int GameStatus::getEstadosArrSize()
{
	return this->estadosArrSize;
}

unsigned int GameStatus::setEstadosArrSize(unsigned int arrSize)
{
	return this->estadosArrSize = arrSize;
}

void GameStatus::updateGuiStatus(const std::string& playerKey,  std::string& action)
{
}

bool GameStatus::getFin()
{
	return this->fin;
}

void GameStatus::findEstado()
{
	this->fin = true;
}

void GameStatus::pausarEstado()
{
	this->paused = true;
}

void GameStatus::unpauseEstado()
{
	this->paused = false;
}

void GameStatus::setActive(bool isActive)
{
	this->active = isActive;
}



bool GameStatus::getIsMenu()
{
	return this->isMenu;
}

void GameStatus::setIsMenu(bool menu)
{
	this->isMenu = menu;
}

void GameStatus::setChosenCharacter(unsigned int chosen)
{
	this->characterChosen = chosen;
}

const unsigned int& GameStatus::getChosenCharacter()
{
	return this->characterChosen;
}

void GameStatus::thereIsConection(bool conection)
{
	this->conection = conection;
}

const bool GameStatus::getThereIsConection()
{
	return conection;
}

void GameStatus::isSelectedCharacter(bool conection)
{
	this->selectedCharacter = conection;
}

const bool GameStatus::getSelectedCharacter()
{
	return selectedCharacter;
}

void GameStatus::isAnotherClient(bool what)
{
	this->anotherClient = what;
}

const bool GameStatus::getAnotherClient()
{
	return anotherClient;
}

Entity* GameStatus::getPlayer()
{
	return nullptr;
}

Mapa<string, Entity*> GameStatus::getMapPlayer()
{
	return Mapa<string, Entity*>();
}

Mapa<string, Gui::Box*> GameStatus::getUiBoxes()
{
	return Mapa<string, Gui::Box*>();
}

std::pair<bool, string> GameStatus::getPlayerAction(const std::string& playerKey)
{
	return std::pair<bool, string>();
}


void GameStatus::setSocket(TcpSocket& socket)
{
	this->socket = &socket;
}

void GameStatus::handleAttack(const string& attacker, const string& defender)
{
}

int GameStatus::calculateDamage(int attackStat, const std::string& defenderKey, bool isDefending)
{
	return 0;
}

void GameStatus::updateHealth(const std::string& playerKey, int damage)
{
	
}












