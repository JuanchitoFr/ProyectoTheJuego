#include "pch.h"
#include "../doth/menu.h"

Menu::Menu(std::stack<GameStatus*>* stateType, RenderWindow* window) : GameStatus(stateType,window)
{
}

Menu::~Menu()
{
}

void Menu::render(RenderTarget* drawObj)
{
}

void Menu::checkKeyboardEvents()
{
}

void Menu::run()
{
}

void Menu::initTextures()
{
}

void Menu::endState()
{
}
