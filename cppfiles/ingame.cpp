#include "pch.h"
#include "../doth/ingame.h"


Ingame::Ingame(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr) : GameStatus(estados,ventana)
{
	cout << "Soy ingame" << endl;
	initTextures();
}
Ingame::~Ingame()
{
}

void Ingame::render(RenderTarget* drawObj)
{
	
	try
	{
		if (!drawObj)
		{
			drawObj = this->ventana;
		}
		player[Dragon]->render(drawObj);
		
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
	initPlayer(&textures[Dragon_T], Dragon);

}

void Ingame::initPlayer(Texture* playerTexture, playerType xd)
{
	try
	{
			if (xd >= playerArrSize)
			{
				// Crear un nuevo array con el tamaño incrementado
				unsigned int newSize = xd + 1;
				Entity** newArrayB = new Entity*[newSize]();
				// Copiar las texturas del array original al nuevo array
				for (unsigned int i = 0; i < playerArrSize; i++) {
					newArrayB[i] = player[i];
				}
				// Liberar la memoria del array original y asignar el nuevo array
				delete[] player;
				player = newArrayB;
				// Actualizar el tamaño del array
				playerArrSize = newSize;
			}

			Vector2f bgSize(static_cast<float>(this->ventana->getSize().x),
				static_cast<float>(this->ventana->getSize().y));
			std::cout << "Tamaño: " << bgSize.x << " : " << bgSize.y << endl;
			this->player[xd] = new Player(playerTexture, 100.f, playerTexture->getSize().x, playerTexture->getSize().y);


	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}

void Ingame::initMap()
{


}



