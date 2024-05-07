#include "pch.h"
#include "../doth/menu.h"

Menu::Menu(GameStatus** estados = nullptr, RenderWindow* window = nullptr) : GameStatus(estados,window)
{
	cout << "Soy Menu" << endl;

	this->elapsedT = 0.f, elapsedT2 = 0.f; this->backLayersArr = 0; this->buttonArrSize = 0; this->xPos = 0;
	this->yPos = 0; this->width = 0; this->height = 0;
	initBackground();
	
}

Menu::~Menu()
{
	delete[] backLayersArr, textures, buttonArrSize;
}

void Menu::updateBackgroundTexture(float deltaT, float switchT, float switchT2)
{
	
	for (unsigned int i = 0; i < backLayersArrSize; i++)
	{
		textures[i].setRepeated(true);
		width = (float)textures[i].getSize().x;
		height = (float)textures[i].getSize().y;

		elapsedT += deltaT;

		if (elapsedT >= switchT) {
			elapsedT -= switchT;
			xPos++;
			if(xPos >= width)
			{
				xPos = 0;
			}
		}
		switch (i)
		{
		case Backg_1:
			this->backLayersArr[i].setTextureRect(IntRect((int)xPos, (int)yPos, (int)width, (int)height));
			break;
		case Backg_2:
			this->backLayersArr[i].setTextureRect(IntRect((int)xPos, (int)yPos, (int)width, (int)height));
			this->backLayersArr[i].setPosition(this->backLayersArr[i].getPosition().x, 250);
			break;
		case Backg_3:
			this->backLayersArr[i].setTextureRect(IntRect((int)xPos, (int)yPos, (int)width, (int)height));
			this->backLayersArr[i].setPosition(this->backLayersArr[i].getPosition().x, 250);
			break;
		case Backg_4:
			this->backLayersArr[i].setTextureRect(IntRect((int)xPos, (int)yPos, (int)width, (int)height));
			break;
		case Backg_5:
			this->backLayersArr[i].setTextureRect(IntRect((int)xPos, (int)yPos, (int)width, (int)height));
			break;
		default:
			break;
		}
		
		
	}
}

void Menu::render(RenderTarget* drawObj)
{
	if (!drawObj) {
		drawObj = this->ventana;
	}
	drawObj->draw(this->backLayersArr[Backg_1]);
	drawObj->draw(this->backLayersArr[Backg_3]);
	this->buttons[playButtonT].render(drawObj);
	
}

void Menu::checkKeyboardEvents(float deltaT)
{
	
}



void Menu::Update(float deltaT)
{
	/*cout << "Estoy en update de menu" << endl;*/
	this->updateMousePos();
	this->updateButtons();
	this->updateBackgroundTexture(deltaT, 0.3f, 0.4f);
	std::cout << "X pos: " << mousePosView.x << " " << "Y pos: " << mousePosView.y << std::endl;
}

void Menu::updateButtons()
{
	if(this->buttons != nullptr)
	{
		for (unsigned int i = 0; i < buttonArrSize; i++)
		{
			this->buttons[i].update(mousePosView);
		}
	}

	if(this->buttons[playButtonT].isPressed())
	{
		cout << "Presione play" << endl;
		cout << this->estados[0]->getEstadosArrSize() << endl;
		this->estados[0] = new Ingame(this->estados, this->ventana);
		this->estados[0]->setEstadosArrSize(1);
	}
}


void Menu::initFont()
{
	if (!this->titleFont.loadFromFile("assets/ui/pricedown/pricedown_bl.otf"))
	{
		cerr << "ERROR::MENU::INITFONT: No se pudo cargar la fuente" << endl;
	}
}

void Menu::initBackground()
{
	textureProcessor("assets/ui/background/FondoMenu/1.png", Backg_1);
	textureProcessor("assets/ui/background/FondoMenu/2.png", Backg_2);
	textureProcessor("assets/ui/background/FondoMenu/3.png", Backg_3);
	textureProcessor("assets/ui/background/FondoMenu/4.png", Backg_4);
	textureProcessor("assets/ui/background/FondoMenu/5.png", Backg_5);
	textureProcessor("assets/ui/Uibasic/Sprite_sheets/button1.png", PlayButton);
	textureProcessor("assets/ui/Uibasic/Sprite_sheets/button1-1.png", PlayBtton_Hover);
	textureProcessor("assets/ui/Uibasic/Sprite_sheets/button0-1.png", PlayBtton_Pressed);
	initLayers(textures[Backg_1], Backg_1);
	initLayers(textures[Backg_2], Backg_2);
	initLayers(textures[Backg_3], Backg_3);
	initLayers(textures[Backg_4], Backg_4);
	initLayers(textures[Backg_5], Backg_5);
	initBtton(&textures[PlayButton], &textures[PlayBtton_Hover], &textures[PlayBtton_Pressed],playButtonT);
	/*this->buttonArr[playButton].setPosition(static_cast<float>(this->ventana->getSize().x) / 2.35f,static_cast<float>(this->ventana->getSize().y) / 2.22f);*/

}

void Menu::initLayers(Texture& texture, Textures xd)
{
	try
	{
		if (this->backLayersArrSize == 0 || this->backLayersArr == nullptr)
		{
			backLayersArrSize++;
			backLayersArr = new RectangleShape[backLayersArrSize]();
		}
		else
		{

			if (xd >= backLayersArrSize)
			{
				// Crear un nuevo array con el tamaño incrementado
				unsigned int newSize = xd + 1;
				RectangleShape* newArrayT = new RectangleShape[newSize]();
				// Copiar las texturas del array original al nuevo array
				for (unsigned int i = 0; i < backLayersArrSize; i++) {
					newArrayT[i] = backLayersArr[i];
				}
				// Liberar la memoria del array original y asignar el nuevo array
				delete[] backLayersArr;
				backLayersArr = newArrayT;
				// Actualizar el tamaño del array
				backLayersArrSize = newSize;
			}
		}
		Vector2f bgSize(static_cast<float>(this->ventana->getSize().x),
			static_cast<float>(this->ventana->getSize().y));
		std::cout << "Tamaño: " << bgSize.x << " : " << bgSize.y << endl;
		std::cout << texture.getSize().x << endl;
		this->backLayersArr[xd].setSize(bgSize);
		this->backLayersArr[xd].setTexture(&texture);
	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}

void Menu::initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, typeBtton xd)
{
	try
	{
		if (this->buttonArrSize == 0 || this->buttons == nullptr)
		{
			
			buttonArrSize++;
			buttons = new Buttons[buttonArrSize]();
			/*buttonArr = new RectangleShape[buttonArrSize]();*/
		}
		else
		{
			if (xd >= buttonArrSize)
			{
				// Crear un nuevo array con el tamaño incrementado
				unsigned int newSize = xd + 1;
				Buttons* newArrayB = new Buttons[newSize]();
				// Copiar las texturas del array original al nuevo array
				for (unsigned int i = 0; i < buttonArrSize; i++) {
					newArrayB[i] = buttons[i];
				}
				// Liberar la memoria del array original y asignar el nuevo array
				delete[] buttons;
				buttons = newArrayB;
				// Actualizar el tamaño del array
				buttonArrSize = newSize;
			}
		}
		Vector2f bgSize(static_cast<float>(this->ventana->getSize().x),
			static_cast<float>(this->ventana->getSize().y));
		std::cout << "Tamaño: " << bgSize.x << " : " << bgSize.y << endl;
		cout << textureIdle->getSize().x << " : " << textureHover->getSize().x << " : " << texturePressed->getSize().x << endl;
		this->width = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().x);
		this->height = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().y);
		this->xPos = static_cast<float>(this->ventana->getSize().x) / 2.35f;
		this->yPos = static_cast<float>(this->ventana->getSize().y) / 2.22f;
		this->buttons[xd] = Buttons(xPos,yPos,width,height,&titleFont, *textureIdle, *textureHover, *texturePressed);
		this->buttons[xd].setSize(328, 180);
		
		/*this->buttonArr[xd].setSize(Vector2f(328, 180));*/
		/*this->buttonArr[xd].setTexture(&texture);*/
		
	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}



void Menu::textureProcessor(String rute, Textures xd)
{
	try
	{
		if (xd >= Textures::Total_TexturesMn || xd < Textures::Backg_1)
		{
			return;
		}

		if(textureArrSize == 0 || textures == nullptr)
		{
			textureArrSize++;
			textures = new Texture[textureArrSize]();
		}
		else
		{
			

			if (xd >= textureArrSize)
			{
				std::cout << "Entre al resize del arr de texturas" << endl;
				// Crear un nuevo array con el tamaño incrementado
				unsigned int newSize = xd + 1;
				Texture* newArray = new Texture[newSize]();
				// Copiar las texturas del array original al nuevo array
				for (unsigned int i = 0; i < textureArrSize; i++) {
					newArray[i] = textures[i];
				}
				// Liberar la memoria del array original y asignar el nuevo array
				delete[] textures;
				textures = newArray;
				// Actualizar el tamaño del array
				textureArrSize = newSize;
				cout << "Mew tewturARrsize" << textureArrSize << endl;
			}
		}



		
		
		std::cout << "index texture" << textureArrSize - 1 << endl;
		if (!this->textures[xd].loadFromFile(rute))
		{
			cerr << "MENU EXCEPTION: No se pudo cargar la imagen";
		}
		else
		{
			std::cout << "Texturas: " << xd << " cargada" << endl;
		}
		

	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::TEXTUREPROCESSOR: " << p.what() << std::endl;
	}
		
	
}



