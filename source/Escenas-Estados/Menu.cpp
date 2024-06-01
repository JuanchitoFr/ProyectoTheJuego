#include "pch.h"
#include "GameStatus.h"
#include "../source/Gui/Gui.h"

#include "Menu.h"



Menu::Menu(GameStatus** estados = nullptr, RenderWindow* window = nullptr) : GameStatus(estados,window)
{
	cout << "Soy Menu" << endl;

	this->elapsedT = 0.f, elapsedT2 = 0.f; this->buttonArrSize = 0; this->xPos = 0;
	this->yPos = 0; this->width = 0; this->height = 0; this->buttons = nullptr;
	this->sceneState = Menu_Principal; this->changeScene = false; this->opacidad = 1.f;
	this->currentCharacter = 0;
	initFont();
	initBackground(); 
	
}

Menu::~Menu()
{
	delete[] buttons;
	for (auto&& map: sprites)
	{
		delete map.second;
	}
	for (auto&& map : this->backgroundLayers)
	{
		delete map.second;
	}
	for(auto &&map : this->stateTextures)
	{
		delete map.second;
	}
	
}

void Menu::updateBackgroundTexture(float deltaT, float switchT, float switchT2)
{
	elapsedT += deltaT;
	
		for (auto&& map : backgroundLayers)
		{
			width = static_cast<float>(map.second->getTexture()->getSize().x);
			height = static_cast<float>(map.second->getTexture()->getSize().y);

			float displacement = (elapsedT / switchT) * width;
			xPos = fmod(displacement, width);
			/*if (elapsedT >= switchT) {
				elapsedT -= switchT;
				xPos++;
				if(xPos >= width)
				{
					xPos = 0;
				}
			}*/
			map.second->setTextureRect(IntRect(static_cast<int>(xPos), 0, static_cast<int>(width), static_cast<int>(height)));
		}

		
}

void Menu::render(RenderTarget* drawObj)
{
	if (!drawObj) {
		drawObj = this->ventana;
	}

	
	drawObj->draw(*this->backgroundLayers["Backg_1"]);
	drawObj->draw(*this->backgroundLayers["Backg_3"]);
	
	if (changeScene == true)
	{
		// Si ha pasado suficiente tiempo, establecer pantallaNegra en false
		// Limpiar la ventana de renderizado (pintarla de negro con opacidad)
		blackOverlay.setFillColor(Color(0, 0, 0, static_cast<Uint8>(opacidad * 255)));
		blackOverlay.setSize(Vector2f(static_cast<float>(this->ventana->getSize().x), static_cast<float>(this->ventana->getSize().y)));
		drawObj->draw(blackOverlay);

		// Reducir gradualmente la opacidad
		opacidad -= 0.9f * deltaT; 

		// Si la opacidad es menor o igual a cero, establecer pantallaNegra en false
		if (opacidad <= 0.0f) {
			changeScene = false;
			opacidad = 1.f;
		}
		
	}else
	{
		if (this->sceneState == Seleccion)
		{
		
			this->buttons[Bttn_ShowCharacter1].render(drawObj);
			this->buttons[Bttn_ShowCharacter2].render(drawObj);
			this->buttons[Bttn_ShowCharacter3].render(drawObj);
			this->buttons[Bttn_ShowCharacter4].render(drawObj);
			if(this->buttons[Bttn_ShowCharacter1].isHover() == true && this->sprites["Dragon"] != nullptr)
			{
				
				this->sprites["Dragon"]->render(drawObj);
			}
			else if (this->buttons[Bttn_ShowCharacter2].isHover() == true)
			{

				this->sprites["Sirena"]->render(drawObj);
			}
			else if (this->buttons[Bttn_ShowCharacter3].isHover() == true && this->sprites["Ogro"] != nullptr)
			{

				this->sprites["Ogro"]->render(drawObj);
			}
			else if (this->buttons[Bttn_ShowCharacter4].isHover() == true && this->sprites["Yordle"] != nullptr)
			{

				this->sprites["Yordle"]->render(drawObj);
			}
			this->buttons[readyButton].render(drawObj);
			
			
		}
		else if (this->sceneState == Menu_Principal)
		{
			this->buttons[playButton].render(drawObj);
			for(int i = Bttn_ShowCharacter1; i <= Bttn_ShowCharacter4; i++)
			{
				this->buttons[i].setVisible(false);
			}
			this->buttons[serverButton].setVisible(false);
			this->buttons[clientButton].setVisible(false);
			this->buttons[readyButton].setVisible(false);
			/*this->buttons[serverButton].render(drawObj);
			this->buttons[clientButton].render(drawObj);*/
			
		}
	}
	
	
}

void Menu::checkKeyboardEvents(float deltaT)
{
	if (Keyboard::isKeyPressed(Keyboard::Home))
	{
		this->sceneState = Menu_Principal;
		for (size_t i = Bttn_ShowCharacter1; i < Total_TypeBttons; i++)
		{
			this->buttons[i].setVisible(false);
		}
		for (size_t i = playButton; i < Bttn_ShowCharacter1; i++)
		{
			this->buttons[i].setVisible(true);
		}
		this->changeScene = true;
	}
}



void Menu::Update(float deltaT)
{
	/*cout << "Estoy en update de menu" << endl;*/
	checkKeyboardEvents(deltaT);
	this->deltaT = deltaT;
	this->updateMousePos();
	this->buttons[playButton].setPosition(270, 400);

	for (size_t i = playButton; i < Total_TypeBttons; i++)
	{
		this->buttons[i].setCharacterSize(64);
	}
	this->updateButtons();
	this->updateBackgroundTexture(deltaT, 32.f, 0.4f);

	for (auto &&map : sprites)
	{
		if (map.second != nullptr)
		{
			map.second->update(deltaT);
		}
		
	}
	
	if(Keyboard::isKeyPressed(Keyboard::Tab))
	{
		std::cout << "X pos: " << mousePosView.x << " " << "Y pos: " << mousePosView.y << std::endl;
	}
	
}

void Menu::updateButtons()
{

	try
	{
		
		if (this->buttons != nullptr)
		{
			for (unsigned int i = 0; i < buttonArrSize; i++)
			{
				this->buttons[i].update(mousePosView);
			}
			for (unsigned int i = playButton; i < Total_TypeBttons; i++)
			{
				this->buttons[i].centerText();
			}

			if (this->buttons[playButton].isPressed() == true && this != nullptr)
			{
				cout << "Presione play" << endl;
				for (size_t i = playButton; i <= clientButton; i++)
				{
					this->buttons[i].setVisible(false);
				}
				for (size_t i = Bttn_ShowCharacter1; i < Total_TypeBttons; i++)
				{
					this->buttons[i].setVisible(true);
				}
				this->sceneState = Seleccion;
				this->changeScene = true;
				/*this->estados[0] = new Ingame(this->estados, this->ventana);
				this->estados[0]->setIsMenu(false);
				this->estados[0]->setEstadosArrSize(1);*/
			}
			else if(this->buttons[Bttn_ShowCharacter1].isPressed() == true && this != nullptr)
			{
				this->currentCharacter = 1;
			}
			else if (this->buttons[Bttn_ShowCharacter2].isPressed() == true && this != nullptr)
			{
				this->currentCharacter = 2;
			}
			else if (this->buttons[Bttn_ShowCharacter3].isPressed() == true && this != nullptr)
			{
				this->currentCharacter = 3;
				
			}
			else if (this->buttons[Bttn_ShowCharacter4].isPressed() == true && this != nullptr)
			{
				this->currentCharacter = 4;
			}

			if (this->currentCharacter > 0)
			{

				cout << "Current character para pasar a ingame" << currentCharacter << endl;

				this->estados[0]->setChosenCharacter(currentCharacter);


			}

			

		}
	}
	catch (const std::exception& p)
	{
		cout << p.what() << endl;
	}
	
}



Gui::Buttons* Menu::getButtons()
{
	return this->buttons;
}

Entity* Menu::getPlayer()
{
	return nullptr;
}

Mapa<string, Entity*> Menu::getMapPlayer()
{
	return sprites;
}

Mapa<string, Gui::Box*> Menu::getUiBoxes()
{
	return Mapa<string, Gui::Box*>();
}




void Menu::initFont()
{
	if (!this->titleFont.loadFromFile("assets/ui/Fuente/pricedown/pricedown_bl.otf"))
	{
		cerr << "ERROR::MENU::INITFONT: No se pudo cargar la fuente" << endl;
	}
}

void Menu::initBackground()
{
	textureProcessor("assets/ui/background/FondoMenu/1.png", "Backg_1");
	textureProcessor("assets/ui/background/FondoMenu/3.png", "Backg_3");
	textureProcessor("assets/Spritesheets/Pjs/Sprites/dragon/SpritesDragon.png", "Dragon_Texture");
	textureProcessor("assets/Spritesheets/Pjs/Sprites/sirena/sirena.png", "Sirena_Texture");
	textureProcessor("assets/Spritesheets/Pjs/Sprites/ogro/Ogro1.png", "Ogro_Texture");
	textureProcessor("assets/Spritesheets/Pjs/Sprites/yordle/YordleSpriteSheet1.png", "Yordle_Texture");
	textureProcessor("assets/ui/Gui/Mouse/mouse.png", "CursorTexture");


	//Capas de fondo

	initLayers(*stateTextures["Backg_1"], "Backg_1");
	initLayers(*stateTextures["Backg_3"], "Backg_3");

	//Botones

	initBtton(NULL, NULL, NULL, "Jugar", playButton);
	initBtton(NULL, NULL, NULL, "Conectarse como servidor" ,serverButton);
	initBtton(NULL, NULL, NULL, "Conectarse como cliente",clientButton);
	initBtton(NULL, NULL, NULL, "Dragon",Bttn_ShowCharacter1);
	initBtton(NULL, NULL, NULL, "Sirena",Bttn_ShowCharacter2);
	initBtton(NULL, NULL, NULL, "Ogro",Bttn_ShowCharacter3);
	initBtton(NULL, NULL, NULL, "Yordle", Bttn_ShowCharacter4);
	initBtton(NULL, NULL, NULL, "Listo", readyButton);
	
	
	for (unsigned int i = Bttn_ShowCharacter1; i <= Bttn_ShowCharacter4; i++)
	{
		unsigned int j = i - 3;
		this->buttons[i].setSize(328, 180);
		this->buttons[i].setPosition((float)this->ventana->getSize().x / 6.25f  * (float)j
			, (float)this->ventana->getSize().y / 12);
	}

		
	this->sprites["Dragon"] = new Dragon(*stateTextures["Dragon_Texture"],0.f,0.f);
	this->sprites["Dragon"]->getEntitySprite()->setPosition((float)this->buttons[Bttn_ShowCharacter1].getButtonBody().getPosition().x * 1.05f,
		(float)this->buttons[Bttn_ShowCharacter1].getButtonBody().getPosition().y / 1.28f);
	this->sprites["Dragon"]->setTextureRect(0, 1, 5, 4);
	this->sprites["Sirena"] = new Sirena(*stateTextures["Sirena_Texture"], 0.f, 0.f);
	this->sprites["Sirena"]->getEntitySprite()->setPosition((float)this->buttons[Bttn_ShowCharacter2].getButtonBody().getPosition().x * 1.05f,
		(float)this->buttons[Bttn_ShowCharacter2].getButtonBody().getPosition().y / 1.28f);
	this->sprites["Sirena"]->setTextureRect(0, 1, 5, 4);
	this->sprites["Yordle"] = new Yordle(*stateTextures["Yordle_Texture"], 0.f,0.f);
	this->sprites["Yordle"]->getEntitySprite()->setPosition((float)this->buttons[Bttn_ShowCharacter4].getButtonBody().getPosition().x * 1.05f,
		(float)this->buttons[Bttn_ShowCharacter4].getButtonBody().getPosition().y / 1.28f);
	this->sprites["Yordle"]->setTextureRect(0, 1, 7, 2);
	this->sprites["Ogro"] = new Ogro(*stateTextures["Ogro_Texture"], 0.f, 0.f);
	this->sprites["Ogro"]->getEntitySprite()->setPosition((float)this->buttons[Bttn_ShowCharacter3].getButtonBody().getPosition().x * 1.05f,
		(float)this->buttons[Bttn_ShowCharacter3].getButtonBody().getPosition().y / 1.28f);

	for (auto &&map: sprites)
	{
		if(map.second == this->sprites["Yordle"])
		{
			map.second->getEntitySprite()->setScale(2.5f, 2.5f);
		}
		else if(map.second == this->sprites["Ogro"])
		{
			map.second->getEntitySprite()->setScale(4.f, 4.f);
		}
		else if(map.second == this->sprites["Dragon"])
		{
			map.second->getEntitySprite()->setScale(1.5f, 1.5f);
		}
	}
	
	


}

void Menu::initLayers(Texture& texture, const string key)
{
	this->backgroundLayers[key] = new RectangleShape();
	this->backgroundLayers[key]->setSize(Vector2f(static_cast<float>(this->ventana->getSize().x), static_cast<float>(this->ventana->getSize().y)));
	this->backgroundLayers[key]->setTexture(&texture);
}


void Menu::initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, string text, typeBtton xd)
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
		this->xPos = static_cast<float>(this->ventana->getSize().x) / 2.41f;
		this->yPos = static_cast<float>(this->ventana->getSize().y) / 2.5f;
		if(textureIdle != nullptr && textureHover != nullptr && texturePressed != nullptr)
		{
			this->width = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().x);
			this->height = static_cast<float>(this->buttons[xd].getTextureIdle().getSize().y);
			this->buttons[xd] = Gui::Buttons(xPos, yPos, width, height, &titleFont, text, *textureIdle, *textureHover, *texturePressed);
		}
		else
		{
			this->buttons[xd] = Gui::Buttons(xPos, yPos, width, height, &titleFont, text, Texture(), Texture(), Texture());
		}
		
		
		this->buttons[xd].setSize(140, 45);
		
		/*this->buttonArr[xd].setSize(Vector2f(328, 180));*/
		/*this->buttonArr[xd].setTexture(&texture);*/
		
	}
	catch (const std::exception& p)
	{
		cerr << "ERROR::FROM::INITLAYERS: " << p.what() << std::endl;
	}
}

void Menu::textureProcessor(const string rute, const string key)
{
	Texture* temporalT = new Texture();

	if(!temporalT->loadFromFile(rute))
	{
		cerr << "INGAME::TextureProcessor: No se pudo cargar la textura de la ruta: " << rute << endl;
	}
	else
	{
		std::cout << "Textura: " << key << " Cargada" << endl;
	}
	temporalT->setRepeated(true);
	if(stateTextures[key] = temporalT)
	{
		if(this != nullptr)
		{
			std::cout << "Textura: " << key << " Cargada al mapa" << endl;
		}
		else
		{
			cerr << "INGAME::TextureProcessor: No se pudo cargar la textura: " << key << " al mapa" << endl;
		}
	}

}




