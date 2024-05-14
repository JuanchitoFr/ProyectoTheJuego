#include "pch.h"
#include "../doth/ingame.h"


Ingame::Ingame(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr) : GameStatus(estados,ventana)
{
	cout << "Soy ingame" << endl;
	this->buttons = nullptr;
	initTextures();
}
Ingame::~Ingame()
{
}

Buttons* Ingame::getButtons()
{
	return nullptr;
}

void Ingame::render(RenderTarget* drawObj)
{
	
	try
	{
		if (!drawObj)
		{
			drawObj = this->ventana;
		}
		/*player[Dragon]->render(drawObj);*/
		
		/*drawObj->setView(View(winSize));*/
		
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	
}


void Ingame::checkKeyboardEvents(float deltaT)
{
	

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		

	}
	else if(Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->estados[0]->findEstado();
	}
	else if(Keyboard::isKeyPressed(Keyboard::Home))
	{
		this->estados[0] = new Menu(this->estados, this->ventana);
		this->estados[0]->setEstadosArrSize(1);
		this->estados[0]->setIsMenu(true);
	}

	/*if (this->player->getEntityMovement().x == 0.f && this->player->getEntityMovement().y == 0.f) {
		this->playerS->setCoordinatesX(0);
		this->playerS->updateSprite(deltaT, 0.15f);
		this->playerS->setIsMoving(false);
		
	}*/


}


void Ingame::Update(float deltaT)
{
	checkKeyboardEvents(deltaT);
}

void Ingame::updateMap()
{
}

void Ingame::updateButtons()
{
}




void Ingame::textureProcessor(String rute, textureType xd)
{
	try
	{
		if (xd >= textureType::Total_TexturesIg || xd < textureType::Dragon_T)
		{
			return;
		}

		if (textureArrSize == 0 || textures == nullptr)
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

void Ingame::initTextures()
{
	textureProcessor("assets/Spritesheets/free-rpg-monster-sprites-pixel-art/PNG/dragon/SpritesDragon.png", Dragon_T);
	textureProcessor("assets/Spritesheets/free-rpg-monster-sprites-pixel-art/PNG/dragon/fireEffect.png", Dragon_FireEffect);
	/*initPlayer(&textures[Dragon_T], Dragon);*/
}

void Ingame::initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, typeBttonIn xd)
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
		float width = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().x);
		float height = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().y);
		float xPos = static_cast<float>(this->ventana->getSize().x) / 2.41f;
		float yPos = static_cast<float>(this->ventana->getSize().y) / 2.5f;
		this->buttons[xd] = Buttons(xPos, yPos, width, height, NULL, *textureIdle, *textureHover, *texturePressed);
		this->buttons[xd].setSize(328, 180);

		/*this->buttonArr[xd].setSize(Vector2f(328, 180));*/
		/*this->buttonArr[xd].setTexture(&texture);*/

	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}


void Ingame::initPlayer(Texture* playerTexture, playerType xd)
{
	try
	{
		/*bool exit = true;
		while(exit)
		{
			Entity* player = new Entity();
			string opc;
			cin >> opc;
			if (opc == "1")
			{
				player->asignarEstadisticas(*player->getStats(), 27, 10, 16, 26, 10, 11);
				cout << "Antes de la variación: " << endl << *player;
				player->variacionStats();
				cout << "Después de la variación: " << endl << *player;

				delete player;
			}
			else if (opc == "e")
			{
				exit = false;
			}
		}*/
		
			
				
			

	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}

void Ingame::initMap()
{


}



