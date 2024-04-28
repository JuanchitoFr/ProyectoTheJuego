#include "pch.h"
#include "../doth/menu.h"

Menu::Menu(std::stack<GameStatus*>* stateType, RenderWindow* window) : GameStatus(stateType,window)
{
	this->elapsedT = 0.f, xRow = 0, xRow2 = 0, elapsedT2 = 0.f;
	initTextures();
	initButtons();
	initBackground();
}

Menu::~Menu()
{
	if (!this->ventana->isOpen()) {
			layers.clear();
	}
}

void Menu::updateBackgroundTexture(float deltaT, float switchT, float switchT2)
{
	float windowWidth = static_cast<float>(this->ventana->getSize().x);
	float windowHeight = static_cast<float>(this->ventana->getSize().y);
	Vector2f midBgSize(windowWidth / 2, windowHeight / 4);
	Vector2f bgSize(windowWidth, windowHeight);

	buttonArr[playB].setSize(midBgSize);
	buttonArr[playB].setScale(0.5, 0.5);
	buttonArr[playB].setPosition(midBgSize.x * 0.75, midBgSize.y * 1.25);
	layers[cloudFront].setSize(bgSize);
	layers[hill].setSize(bgSize);
	layers[cloudMidlle].setSize(bgSize);
	layers[mountain].setSize(bgSize);
	layers[backmountain].setSize(bgSize);
	layers[backgroundSky].setSize(bgSize);


	for (auto i = layers.begin(); i != layers.end(); i++)
	{
		unsigned short num = i->first;
		elapsedT += deltaT;
		elapsedT2 += deltaT;

		if (elapsedT >= switchT) {
			elapsedT -= switchT;
			xRow++;
		}

		if (elapsedT2 >= switchT2) 
		{
			elapsedT2 -= switchT2;
			xRow2++;
		}
			
		if (i->first == cloudMidlle) {
			this->layers[num].setTextureRect(IntRect(xRow2 * this->layers[num].getTexture()->getSize().x / 96,
				yColumn * this->layers[num].getTexture()->getSize().y, this->layers[num].getTexture()->getSize().x,
				this->layers[num].getTexture()->getSize().y));
		}
		else if(i->first == cloudFront) 
		{
			this->layers[num].setTextureRect(IntRect(xRow * this->layers[num].getTexture()->getSize().x / 96,
				yColumn * this->layers[num].getTexture()->getSize().y, this->layers[num].getTexture()->getSize().x,
				this->layers[num].getTexture()->getSize().y));
		}
		else {
			continue;
		}
	}
}

void Menu::render(RenderTarget* drawObj)
{
	if (!drawObj) {
		drawObj = this->ventana;
	}
	drawObj->draw(layers[backgroundSky]);
	drawObj->draw(layers[backmountain]);
	drawObj->draw(layers[mountain]);
	drawObj->draw(layers[cloudMidlle]);
	drawObj->draw(layers[hill]);
	drawObj->draw(layers[cloudFront]);
	drawObj->draw(buttonArr[playB]);
}

void Menu::checkKeyboardEvents(float deltaT)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
		endState();
	}
}

void Menu::run()
{
}

void Menu::Update(float deltaT)
{
	this->updateMousePos();
	this->updateBttn(this->mousePosView);
	this->checkKeyboardEvents(deltaT);
	this->updateBackgroundTexture(deltaT, 0.3f, 0.4f);
	/*std::cout << "X pos: " << mousePosView.x << " " << "Y pos: " << mousePosView.y << std::endl;*/
}

void Menu::updateBttn(Vector2f mousePos)
{
	this->bttnState = idle;
	for (auto i = buttonArr.begin(); i != buttonArr.end(); i++) 
	{
		unsigned short num = i->first;
		if (this->buttonArr[num].getGlobalBounds().contains(mousePos)) 
		{

			this->bttnState = hover;

			if (Mouse::isButtonPressed(Mouse::Left)) 
			{
				this->bttnState = pressed;
			}
		}

		switch (bttnState)
		{
		case idle:
			this->buttonArr[num].setTextureRect(IntRect(1, 1 * 32, 96, 32));
			break;
		case hover:
			this->buttonArr[num].setTextureRect(IntRect(1 * 96, 1 * 32, 96, 32));
			break;
		case pressed:
			this->buttonArr[num].setTextureRect(IntRect(1 * 96, 1 * 32, 96, 32));
			break;
		default:
			break;
		}
		
		if (num == playB && this->getBttnState()) 
		{
			this->parcialEndState();
		}
	}

	
}

void Menu::endState()
{
	this->end = true;
}

void Menu::parcialEndState()
{
	this->parcialEnd = true;
}

unsigned short Menu::getBttnState()
{
	if (bttnState == pressed) {
		return true;
	}
	else {
		return false;
	}
	return 0;
}

int Menu::getYcolumn()
{
	return this->yColumn;
}

int Menu::getXrow()
{
	return this->xRow;
}

void Menu::setYcolumn(int y)
{
	this->yColumn = y;
}

void Menu::setXrow(int x)
{
	this->xRow = x;
}

void Menu::initBackground()
{
	/*int winUpWidth = this->ventana->getSize().x;
	int winUpHeight = this->ventana->getSize().y;
	currentWinSize.x = winUpWidth;
	currentWinSize.y = winUpHeight;
	float windowWidth = static_cast<float>(this->ventana->getSize().x);
	float windowHeight = static_cast<float>(this->ventana->getSize().y);
	Vector2f bgSize(windowWidth, windowHeight);
	Vector2f midBgSize(windowWidth / 2, windowHeight / 4);*/
	layers[cloudFront].setTexture(&this->textures["cloudFront"]);
	layers[hill].setTexture(&this->textures["Hill"]);
	layers[cloudMidlle].setTexture(&this->textures["cloudMidlle"]);
	layers[mountain].setTexture(&this->textures["mountain"]);
	layers[backmountain].setTexture(&this->textures["backmountain"]);
	layers[backgroundSky].setTexture(&this->textures["backgroundSky"]);
	buttonArr[playB].setTexture(&this->textures["playB"]);
	buttonArr[playB].setTextureRect(IntRect(1,1 * 32,96,32));
	
}

void Menu::initButtons()
{
}


void Menu::initTextures()
{
	Texture backgTexture, bttn;
	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/hill.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["Hill"] = backgTexture;

	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/clouds_front_t.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["cloudFront"] = backgTexture;

	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/clouds_mid.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["cloudMidlle"] = backgTexture;

	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/grassy_mountains.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["mountain"] = backgTexture;

	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/far_mountains.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["backmountain"] = backgTexture;

	if (!backgTexture.loadFromFile("assets/ui/background/bgMParallax/BgMParallax/layers/sky.png"))
	{
		throw "ERROR:MENU";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	backgTexture.setRepeated(true);
	this->textures["backgroundSky"] = backgTexture;

	if (!bttn.loadFromFile("assets/ui/Uibasic/Sprite_sheets/UI_Big_Play_Button.png")) {
		throw "ERROR:MENU::BUTTONS";
		std::cout << "No se pudo cargar la textura #1" << std::endl;
	}
	this->textures["playB"] = bttn;
	
}

