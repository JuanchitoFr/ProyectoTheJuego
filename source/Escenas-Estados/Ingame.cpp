#include "pch.h"
#include "Ingame.h"
#include "Menu.h"




Ingame::Ingame(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr) : GameStatus(estados,ventana)
{
	cout << "Soy ingame" << endl;
	this->buttons = nullptr;
	initTextures();
	initFont();
	this->pausaM = new PausaMenu(*ventana, font);
	this->initPauseMenu();
	
}
Ingame::~Ingame()
{
	delete this->pausaM;
	delete[] this->entities;
}

Gui::Buttons* Ingame::getButtons()
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
		entities[Player_1]->render(drawObj);
		/*drawObj->setView(View(winSize));*/

		if(this->paused) //Renderizar el menu de pausa
		{
			this->pausaM->render(drawObj);
		}
		
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

void Ingame::checkKeyboardPause(const float& deltaT)
{
	
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		if (!this->paused)
			this->pausarEstado();
		else
			this->unpauseEstado();
	}
	sleep(milliseconds(90));
}


void Ingame::Update(float deltaT)
{
	checkKeyboardPause(deltaT);
	updateMousePos();
	
	if (!paused) //Cuando no esta en pausa
	{
		checkKeyboardEvents(deltaT);
		this->entities[Player_1]->updateSprite(deltaT, 0.2f);
	}
	else //Pausa
	{
		pausaM->update(mousePosView);
		pausaM->IsButtonPressed();
	}
	if(Keyboard::isKeyPressed(Keyboard::Tab))
	{
		cout << mousePosView.x << ":" << mousePosView.y << endl;
	}
	
	
}

void Ingame::GUI()
{
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
				for (unsigned int i = 0; i < textureArrSize; i++) {
					newArray[i] = textures[i];
				}
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
	textureProcessor("assets/Spritesheets/Pjs/Sprites/dragon/SpritesDragon.png", Dragon_T);
	textureProcessor("assets/Spritesheets/Pjs/Sprites/ogro/ogro.png", Ogro_T);
	textureProcessor("assets/Spritesheets/Pjs/Sprites/sirena/Walk-izq.png", Sirena_T);
	textureProcessor("assets/Spritesheets/Pjs/Sprites/yordle/caminar.png", Yordle_T);
	textureProcessor("assets/Spritesheets/free-rpg-monster-sprites-pixel-art/PNG/dragon/fireEffect.png", Dragon_FireEffect);
	cout << "Personaje elegido: " << this->estados[0]->getChosenCharacter() << endl;
	if (this->estados[0]->getChosenCharacter() == 1)
	{
		initPlayer(&textures[Dragon_T], 5, 4, Player_1);
		this->entities[Player_1]->setTextureRect(0, 1, 5, 4);
		this->entities[Player_1]->asignarEstadisticas(*this->entities[Player_1]->getStats(), 27, 10, 16, 26, 10, 11);

	}
	else if (this->estados[0]->getChosenCharacter() == 2)
	{
		initPlayer(&textures[Sirena_T], 5, 4, Player_1);
		this->entities[Player_1]->setTextureRect(0, 0, 5, 1);
		this->entities[Player_1]->asignarEstadisticas(*this->entities[Player_1]->getStats(), 10, 16, 10, 11, 27, 26);
	}
	else if (this->estados[0]->getChosenCharacter() == 3)
	{
		std::cout << "El valor si es el del ogro" << endl;
		initPlayer(&textures[Ogro_T], 5, 4, Player_1);
		this->entities[Player_1]->setTextureRect(0, 0, 15, 19);
		this->entities[Player_1]->getEntitySprite()->setScale(3.f, 3.f);
		this->entities[Player_1]->asignarEstadisticas(*this->entities[Player_1]->getStats(), 27, 26, 16, 11, 10, 10);
		
	}
	else if (this->estados[0]->getChosenCharacter() == 4)
	{
		initPlayer(&textures[Yordle_T], 5, 4, Player_1);
		this->entities[Player_1]->setTextureRect(0, 3, 9, 4);
		this->entities[Player_1]->getEntitySprite()->setScale(2.f, 2.f);
		this->entities[Player_1]->asignarEstadisticas(*this->entities[Player_1]->getStats(), 10, 10, 11, 26, 16, 27);
	}
	else
	{
		std::cout << "No se devolvio el valor " << endl;
	}
	cout << "Antes de la variacion: " << endl << *entities[Player_1] << endl;
	this->entities[Player_1]->variacionStats();
	cout << "Después de la variacion: " << endl << *entities[Player_1] << endl;
	this->entities[Player_1]->getEntitySprite()->setOrigin(this->entities[Player_1]->getEntitySprite()->getGlobalBounds().width / 2.f, this->entities[Player_1]->getEntitySprite()->getGlobalBounds().height / 2.f);
	this->entities[Player_1]->setPosition(this->ventana->getSize().x / 4.f, this->ventana->getSize().y / 1.8f);
	
	/*initPlayer(&textures[Dragon_T], Dragon);*/
}

void Ingame::initPlayer(Texture* playerTexture, unsigned int xRows, unsigned int yColumns, Players player)
{
	this->entities[player] = new Player(playerTexture,0.f,xRows,yColumns);
}

void Ingame::initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, string text, typeBttonIn xd)
{
	try
	{
		if (this->buttonArrSize == 0 || this->buttons == nullptr)
		{

			buttonArrSize++;
			buttons = new Gui::Buttons[buttonArrSize]();
			/*buttonArr = new RectangleShape[buttonArrSize]();*/
		}
		else
		{
			if (xd >= buttonArrSize)
			{
				// Crear un nuevo array con el tamaño incrementado
				unsigned int newSize = xd + 1;
				Gui::Buttons* newArrayB = new Gui::Buttons[newSize]();
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
		this->buttons[xd] = Gui::Buttons(xPos, yPos, width, height, NULL, text, *textureIdle, *textureHover, *texturePressed);
		this->buttons[xd].setSize(328, 180);

		/*this->buttonArr[xd].setSize(Vector2f(328, 180));*/
		/*this->buttonArr[xd].setTexture(&texture);*/

	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}


void Ingame::initMap()
{


}

void Ingame::initFont()
{
	if(!font.loadFromFile("assets/ui/Fuente/pricedown/pricedown_bl.otf"))
	{
		cerr << "INGAME:: No se pudo leer la fuente" << endl;
	}
}

void Ingame::initPauseMenu()
{
	this->pausaM->createNewButton(830.f, 200.f);
	
	
}



