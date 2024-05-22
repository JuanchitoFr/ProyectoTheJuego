#include "pch.h"
#include "PausaMenu.h"



PausaMenu::PausaMenu(RenderWindow& ventana)
{
	this->background.setSize(Vector2f(static_cast<float>(ventana.getSize().x), static_cast<float>(ventana.getSize().y)));
	this->background.setFillColor(Color(20, 20, 20, 100));

	this->container.setSize(Vector2f(static_cast<float>(ventana.getSize().x) / 4.f, static_cast<float>(ventana.getSize().y)));
	this->container.setFillColor(Color(20, 20, 20, 100));
	this->container.setPosition(static_cast<float>(ventana.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);

}

PausaMenu::~PausaMenu()
{
	if (this->buttons != nullptr)
	{
		for (size_t i = 0; i < this->buttons->getSize(); i++)
		{
			delete buttons[i].getSecond();
		}
	}
	
}

void PausaMenu::update()
{
}


void PausaMenu::render(RenderTarget* objTarget)
{
	objTarget->draw(background);
	objTarget->draw(container);

	/*for (size_t i = 0; i < buttons->getSize(); i++)
	{
		buttons->getSecond()->render(objTarget);
	}*/
}
