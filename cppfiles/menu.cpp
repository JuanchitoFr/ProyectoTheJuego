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

void Menu::run()
{
}
