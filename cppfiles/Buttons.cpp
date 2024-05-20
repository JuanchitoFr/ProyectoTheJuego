#include "pch.h"
#include "../doth/Buttons.h"

Buttons::Buttons( float xPos,  float yPos, float widht, float height, Font* font, string text , Texture textureIdle,
	Texture textureHover, Texture texturePressed)
{
	this->buttonBody.setSize(Vector2f(widht, height));
	this->buttonBody.setPosition(Vector2f(xPos, yPos));
	this->buttonFont = font;
	this->buttonText.setFont(*buttonFont);
	this->buttonText.setString(text);
	this->buttonText.setCharacterSize(20);
	this->buttonText.setOutlineColor(Color::Black);
	this->buttonText.setOutlineThickness(2.f);
	this->buttonText.setFillColor(Color::Yellow);

	this->textureIdle = textureIdle;
	this->textureHover = textureHover;
	this->texturePressed = texturePressed;

	this->buttonBody.setTexture(&textureIdle);
	this->buttonState = idle;
	this->visible = true;
	centerText();
}


Buttons::Buttons()
{
	this->buttonFont = nullptr;
	this->buttonState = idle;
}

Buttons::~Buttons()
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
	if(isVisible() == true)
	{
		drawObj->draw(buttonBody);
		drawObj->draw(buttonText);
	}
	
	
	/*drawObj->draw(buttonText);*/

}

bool Buttons::isPressed() const
{
	try {
		if (this != nullptr && this->buttonState == pressed) {
			cout << buttonState << endl;
			return true;
		}
		else {
			return false;
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		return false; 
	}
}
bool Buttons::isVisible() const
{
	if(visible == true)
	{
		return true;
	}
	else {
		return false;
	}
}
void Buttons::setVisible(bool visible)
{
	this->visible = visible;
}

void Buttons::update(Vector2f mousePos)
{
	this->buttonState = idle;
	if (isVisible() == true) 
	{
		if (this->buttonBody.getGlobalBounds().contains(mousePos))
		{

			this->buttonState = hover;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->buttonState = pressed;
			}
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

Text Buttons::getBttonText()
{
	return this->buttonText;
}


void Buttons::centerText()
{
	FloatRect rectBounds = this->buttonBody.getGlobalBounds();
	float rectWidth = rectBounds.width;
	float rectHeight = rectBounds.height;
	FloatRect textBounds = this->buttonText.getLocalBounds();
	float textoX = (rectBounds.left + (rectWidth / 2.f) - (textBounds.width / 2.f) - textBounds.left);
	float textoY = (rectBounds.top + (rectHeight / 2.f) - (textBounds.height / 2.f) - textBounds.top);

	this->buttonText.setPosition(textoX, textoY);

}

