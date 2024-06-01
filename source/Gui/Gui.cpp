#include "pch.h"
#include "Gui.h"

Gui::Buttons::Buttons( float xPos,  float yPos, float widht, float height, Font* font, string text , Texture textureIdle,
	Texture textureHover, Texture texturePressed)
{
	this->buttonBody.setSize(Vector2f(widht, height));
	this->buttonBody.setPosition(Vector2f(xPos, yPos));
	this->buttonFont = font;
	this->buttonText.setFont(*buttonFont);
	this->buttonText.setString(text);
	this->buttonText.setCharacterSize(26);
	this->buttonText.setOutlineColor(Color::Black);
	this->buttonText.setOutlineThickness(2.f);
	this->buttonText.setFillColor(Color::Yellow);

	this->textureIdle = textureIdle;
	this->textureHover = textureHover;
	this->texturePressed = texturePressed;

	this->buttonBody.setTexture(&textureIdle);
	this->buttonState = idle;
	this->visible = true;
	this->centerText();
}


Gui::Buttons::Buttons()
{
	this->buttonFont = nullptr;
	this->buttonState = idle;
	this->visible = false;
}

Gui::Buttons::~Buttons()
{
}

void Gui::Buttons::setPosition(float x, float y)
{
	this->buttonBody.setPosition(Vector2f(x, y));
}
void Gui::Buttons::setSize(float width, float height)
{
	this->buttonBody.setSize(Vector2f(width, height));
}

bool Gui::Buttons::getButtonState()
{
	return this->buttonState == pressed ? true : false;
}

void Gui::Buttons::render(RenderTarget* drawObj)
{
	if(isVisible() == true)
	{
		drawObj->draw(buttonBody);
		drawObj->draw(buttonText);
	}
	
	
	/*drawObj->draw(buttonText);*/

}

bool Gui::Buttons::isPressed() const
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
bool Gui::Buttons::isHover() const
{
	try {
		if (this != nullptr && this->buttonState == hover) {
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
bool Gui::Buttons::isVisible() const
{
	if(visible == true)
	{
		return true;
	}
	else {
		return false;
	}
}
void Gui::Buttons::setVisible(bool visible)
{
	this->visible = visible;
}

void Gui::Buttons::update(const Vector2f& mousePos)
{
	this->buttonState = idle;
	this->buttonBody.setOutlineThickness(3.f);
	this->buttonBody.setOutlineColor(Color::Black);
	if (isVisible() == true) 
	{
		if (this->buttonBody.getGlobalBounds().contains(mousePos))
		{

			this->buttonState = hover;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->buttonState = pressed;
				sleep(milliseconds(50));
			}
		}
	}

	switch (this->buttonState)
	{
	case idle:
		this->buttonBody.setFillColor(Color::Transparent);
		this->buttonText.setFillColor(Color::Yellow);
		/*this->buttonBody.setTexture(&textureIdle);*/
		break;
	case hover:
		this->buttonBody.setFillColor(Color::Transparent);
		this->buttonText.setFillColor(Color::Green);
		/*this->buttonBody.setTexture(&textureHover);*/
		break;
	case pressed:
		this->buttonBody.setFillColor(Color::Transparent);
		this->buttonText.setFillColor(Color::Red);
		/*this->buttonBody.setTexture(&texturePressed);*/
		break;
	default:
		this->buttonBody.setFillColor(Color::Green);
		break;
	}

}


float Gui::Buttons::getButtonWidth()
{
	return this->buttonBody.getSize().x;
}

float Gui::Buttons::getButtonHeight()
{
	return this->buttonBody.getSize().y;
}

Texture Gui::Buttons::getTextureIdle()
{
	return this->textureIdle;
}

Texture Gui::Buttons::getTextureHover()
{
	return this->textureHover;
}
Texture Gui::Buttons::getTexturePressed()
{
	return this->texturePressed;
}

RectangleShape Gui::Buttons::getButtonBody()
{
	return this->buttonBody;
}

Text Gui::Buttons::getBttonText()
{
	return this->buttonText;
}


void Gui::Buttons::centerText()
{
	FloatRect rectBounds = this->buttonBody.getGlobalBounds();
	float rectWidth = rectBounds.width;
	float rectHeight = rectBounds.height;
	FloatRect textBounds = this->buttonText.getLocalBounds();
	float textWidth = textBounds.width;
	float textHeight = textBounds.height;
	float textoX = rectBounds.left + (rectWidth / 2.0f) - (textWidth / 2.0f);
	float textoY = rectBounds.top + (rectHeight / 2.0f) - (textHeight / 2.0f);

	this->buttonText.setPosition(textoX, textoY);

}

void Gui::Buttons::setCharacterSize(int num)
{
	this->buttonText.setCharacterSize(num);
}

//Aqui termina Definiciones de Button

//Empieza Box

Gui::Box::Box(float xPos, float yPos, float width, float height, Font& font, string text) : boxFont(&font)
{
	this->box.setSize(Vector2f(width, height));
	this->box.setFillColor(Color(20, 20, 20, 100));
	this->box.setOutlineColor(Color::Black);
	this->box.setOutlineThickness(3.f);
	this->box.setOrigin(this->box.getGlobalBounds().width / 2.f, this->box.getGlobalBounds().height / 2.f);
	this->box.setPosition(xPos, yPos);
	this->textBox.setFont(font);
	this->textBox.setString(text);
	this->textBox.setCharacterSize(48);
	
	this->visible = true;
	this->boxState = idle;
	centerText();
}

Gui::Box::~Box()
{
}

void Gui::Box::render(RenderTarget* drawObj)
{
	drawObj->draw(box);
	drawObj->draw(textBox);
}

bool Gui::Box::isVisible() const
{
	return true;
}

bool Gui::Box::isPressed() const
{
	if(boxState == pressed)
	{
		return true;
	}
	else {
		return false;
	}
}

void Gui::Box::setVisible(const bool visible)
{
	this->visible = visible;
}

void Gui::Box::update(const Vector2f& mousePos)
{
	this->boxState = idle;
	if (isVisible() == true)
	{
		if (this->textBox.getGlobalBounds().contains(mousePos))
		{

			this->boxState = hover;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				this->boxState = pressed;
			}
		}
	}

	switch (this->boxState)
	{
	case idle:
		this->textBox.setFillColor(Color::Yellow);
		/*this->buttonBody.setTexture(&textureIdle);*/
		break;
	case hover:
		this->textBox.setFillColor(Color::Green);
		/*this->buttonBody.setTexture(&textureHover);*/
		break;
	case pressed:
		this->textBox.setFillColor(Color::Red);
		/*this->buttonBody.setTexture(&texturePressed);*/
		break;
	default:
		break;
	}
}

void Gui::Box::centerText()
{
	FloatRect rectBounds = this->box.getGlobalBounds();
	float rectWidth = rectBounds.width;
	float rectHeight = rectBounds.height;
	FloatRect textBounds = this->textBox.getLocalBounds();
	float textWidth = textBounds.width;
	float textHeight = textBounds.height;
	float textoX = rectBounds.left + (rectWidth / 2.0f) - (textWidth / 2.0f);
	float textoY = rectBounds.top + (rectHeight / 2.0f) - (textHeight / 2.0f);

	this->textBox.setPosition(textoX, textoY);
}

Vector2f Gui::Box::getPosition()
{
	return this->box.getPosition();
}

void Gui::Box::setFont(float size)
{
	this->textBox.setCharacterSize((int)size);
	centerText();
}
