#include "pch.h"
#include "../doth/Buttons.h"

Buttons::Buttons( float xPos ,  float yPos, float widht,float height, Font* font, Texture textureIdle,
	Texture textureHover, Texture texturePressed)
{
	this->buttonBody.setSize(Vector2f(widht, height));
	this->buttonBody.setPosition(Vector2f(xPos, yPos));
	this->buttonFont = font;
	this->buttonText.setFont(*buttonFont);
	this->buttonText.setCharacterSize(20);
	this->buttonText.setOutlineColor(Color::Black);
	this->buttonText.setOutlineThickness(2.f);

	this->textureIdle = textureIdle;
	this->textureHover = textureHover;
	this->texturePressed = texturePressed;

	this->buttonBody.setTexture(&textureIdle);
	this->buttonState = idle;
}


Buttons::Buttons()
{
}

void Buttons::setPosition(float x, float y)
{
	this->buttonBody.setPosition(Vector2f(x, y));
}
void Buttons::setSize(float width, float height)
{
	this->buttonBody.setSize(Vector2f(width, height));
}

bool Buttons::getButtonState()
{
	return this->buttonState == pressed ? true : false;
}

void Buttons::render(RenderTarget* drawObj)
{
	drawObj->draw(buttonBody);
	/*drawObj->draw(buttonText);*/

}

bool Buttons::isPressed()
{
	if(this->buttonState == pressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Buttons::update(Vector2f mousePos)
{
	this->buttonState = idle;
	if(this->buttonBody.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = hover;
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = pressed;
		}
	}

	switch (this->buttonState)
	{
	case idle:
		this->buttonBody.setTexture(&textureIdle);
		break;
	case hover:
		this->buttonBody.setTexture(&textureHover);
		break;
	case pressed:
		this->buttonBody.setTexture(&texturePressed);
		break;
	default:
		this->buttonBody.setFillColor(Color::Green);
		break;
	}
}

float Buttons::getButtonWidth()
{
	return this->buttonBody.getSize().x;
}

float Buttons::getButtonHeight()
{
	return this->buttonBody.getSize().y;
}

Texture Buttons::getTextureIdle()
{
	return this->textureIdle;
}

Texture Buttons::getTextureHover()
{
	return this->textureHover;
}
Texture Buttons::getTexturePressed()
{
	return this->texturePressed;
}

RectangleShape Buttons::getButtonBody()
{
	return this->buttonBody;
}




