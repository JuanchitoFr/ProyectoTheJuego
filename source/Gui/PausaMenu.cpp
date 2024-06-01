#include "pch.h"
#include "PausaMenu.h"



PausaMenu::PausaMenu(RenderWindow& ventana, Font& fuenteMenu) : fuenteMenu(fuenteMenu), ventana(&ventana)
{
	this->background.setSize(Vector2f(static_cast<float>(ventana.getSize().x), static_cast<float>(ventana.getSize().y)));
	this->background.setFillColor(Color(20, 20, 20, 100));

	this->container.setSize(Vector2f(static_cast<float>(ventana.getSize().x) / 4.f, static_cast<float>(ventana.getSize().y)));
	this->container.setFillColor(Color(20, 20, 20, 100));
	this->container.setPosition(static_cast<float>(ventana.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);
	this->size = 2;
	this->menuText.setFont(fuenteMenu);
	this->menuText.setFillColor(Color::Magenta);
	this->menuText.setCharacterSize(64);
	this->menuText.setString("MENU DE PAUSA");
	this->menuText.setOrigin(this->menuText.getGlobalBounds().width / 2.f, this->menuText.getGlobalBounds().height / 2.f);
	this->menuText.setPosition(this->container.getPosition().x  + this->container.getSize().x / 2.f, this->container.getPosition().y / 2.f + 60.f);
}

PausaMenu::~PausaMenu()
{
	for(auto map : botones)
	{
		delete map.second;
	}
	
}

void PausaMenu::createNewButton(float xPos, float yPos, const string key, const string text)
{
	this->botones[key] = new Gui::Buttons(xPos, yPos, 250,150, &fuenteMenu, text, Texture(), Texture(), Texture());
	
}

void PausaMenu::update(const Vector2f& mousePos)
{
	for(auto map : botones)
	{
		map.second->update(mousePos);
	}
}

bool PausaMenu::checkIsUnPause()
{
	return false;
}


void PausaMenu::render(RenderTarget* objTarget)
{
	objTarget->draw(background);
	objTarget->draw(container);

	for(auto map : botones)
	{
		map.second->render(objTarget);
	}

	objTarget->draw(menuText);
}

const bool PausaMenu::IsButtonPressed(const string key)
{
	return this->botones[key]->isPressed();
}

Mapa<string, Gui::Buttons*> PausaMenu::getBotones()
{
	return this->botones;
}
