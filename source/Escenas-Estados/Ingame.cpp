#include "pch.h"
#include "Menu.h"
#include "Ingame.h"




Ingame::Ingame(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr) : GameStatus(estados,ventana), forCorrectPorpouses("nada")
{

	std::cout << "Soy ingame" << endl;
	initPlayer();
	this->buttons = nullptr;
	initBackgroud();
	initFont();
	initUI();
	this->pausaM = new PausaMenu(*ventana, font);
	this->initPauseMenu();
	
	
	
}
Ingame::~Ingame()
{
	delete this->pausaM;
	for (auto&& map : this->players)
	{
		delete map.second;
	}
	for(auto &&map: this->uiBoxes)
	{
		delete map.second;
	}
	for(auto &&map: this->stateTextures)
	{
		delete map.second;
	}

}

Gui::Buttons* Ingame::getButtons()
{
	return nullptr;
}

Mapa<string, Entity*> Ingame::getMapPlayer()
{
	return playersIngame;
}

void Ingame::setActualPlayers(Mapa<string, Entity*> players)
{
	this->playersIngame = players;
	this->players = players;
}

Mapa<string, Gui::Box*> Ingame::getUiBoxes()
{
	return this->uiBoxes;
}

std::pair<bool, string> Ingame::getPlayerAction(const std::string& playerKey)
{
	for(auto&& map: playersIngame)
	{
		if (map.first == this->actions.second)
		{
			return this->actions;
		}
	}
	
}

void Ingame::handleAttack(const string& attackerN, const string& defenderN)
{
	auto attacker = players[attackerN];
	auto defender = players[defenderN];

	if (attacker == nullptr || defender == nullptr) {
		std::cout << "Error: Jugador no encontrado" << std::endl;
		return;
	}

	// Obtener las estad�sticas de ataque del atacante y defensa del defensor
	auto attackerStats = attacker->getStats();
	auto defenderStats = defender->getStats();

	// Calcular el da�o del ataque
	int damage = attackerStats->atkFisico - defenderStats->defFisica;
	// Considerar defensa m�gica si es necesario
	// damage -= defenderStats.defMagica;

	// Asegurarse de que el da�o sea positivo
	damage = std::max(0, damage);

	// Reducir la salud del defensor
	defenderStats->hp -= damage;

	// Manejar otros efectos del ataque, como reducci�n de velocidad, etc.

	std::cout << "Player " << attackerN << " ha infligido " << damage << " de da�o a Player " << defenderN << std::endl;
	std::cout << "Salud restante de Player " << defenderN << ": " << defenderStats->hp << std::endl;
}

int Ingame::calculateDamage(int attackStat, const std::string& defenderKey, bool isDefending)
{
	// Obtener las estad�sticas de defensa del jugador defensor
	auto defenderStats = estados[0]->getMapPlayer()[defenderKey]->getStats(); // Suponiendo que tienes un m�todo para obtener las estad�sticas del jugador en tu estado de juego
	int damage = 0;
	// Calcular el da�o
	if (isDefending) {
		// Si el jugador defensor se est� defendiendo, se reduce el da�o en funci�n de su defensa
		damage = (attackStat > defenderStats->defFisica) ? (attackStat - defenderStats->defFisica) : 0;
	}
	else {
		// Si el jugador defensor no se est� defendiendo, recibe todo el da�o
		damage = attackStat;
	}
	damage = std::max(0, damage);
	return damage;
}
void Ingame::updateHealth(const std::string& playerKey, int damage)
{
	auto playerStats = estados[0]->getMapPlayer()[playerKey]->getStats(); // Suponiendo que tienes un m�todo para obtener las estad�sticas del jugador en tu estado de juego

	// Actualizar la salud
	playerStats->hp -= damage;

	// Si la salud llega a cero o menos, el jugador est� muerto
	if (playerStats->hp <= 0) {
		Clock timer;
		if (timer.getElapsedTime().asSeconds() > 1.f)
		{
			this->players[playerKey]->setCurrentAnimation(typeOfAnimation::Dead_Anim);
		}
		// Implementar la l�gica de muerte del jugador, por ejemplo, eliminarlo del juego
		// Tambi�n puedes enviar un mensaje al cliente indicando que el jugador est� muerto
	}
}

void Ingame::determinateTurn()
{
	for(auto&& map: players)
	{
		std::cout << map.first << endl;
	}
	bool isServerTurn, isClientTurn;
	std::cout << "Esto es antes de comparar velocidades" << endl;
	if (this->estados[0]->getMapPlayer()["Player_1"]->getStats()->velocidad >= this->estados[0]->getMapPlayer()["Player_2"]->getStats()->velocidad) {
		std::cout << "Empieza primero el servidor" << endl;
		isServerTurn = true; // Siempre es el turno del servidor
		isClientTurn = false;
	}
	else {
		std::cout << "Empieza primero el cliente" << endl;
		isServerTurn = false; // Siempre es el turno del cliente
		isClientTurn = true;
	}

	Packet packet;
	packet << isServerTurn << isClientTurn;
	if(socket->send(packet) != Socket::Done)
	{
		std::cout << "turns packet from ingame not send" << endl;
	}
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
		drawObj->draw(battleBackground);
		for (auto&& map : playersIngame)
		{
			if (map.second != nullptr)
			{
				if (map.first == "Player_1" || map.first == "Player_2")
				{
					map.second->render(drawObj);
				}
					
			}

		}
		
		
		for(auto&& map : uiBoxes)
		{
			map.second->render(drawObj);
		}
		/*drawObj->setView(View(winSize));*/

		if(this->paused) //Renderizar el menu de pausa
		{
			this->pausaM->render(drawObj);
		}
		
		
	}
	catch (const std::exception& p)
	{
		std::cout << "From render: The problemas was: " << p.what() << std::endl;
		
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
		updateGuiStatus("Player_1", forCorrectPorpouses);
		if(anotherClient == true)
		{
			initPlayer();
			anotherClient = false;
			
		}
		for (auto map : playersIngame)
		{
			map.second->update(deltaT);

			/*cout << *map.second << endl;*/
		}

		
		
	}
	else //Pausa
	{
		pausaM->update(mousePosView);
		updateButtons();
		
		
		
	}
	for (auto&& map : uiBoxes)
	{
		map.second->update(mousePosView);
	}
	if(Keyboard::isKeyPressed(Keyboard::Tab))
	{
		std::cout << mousePosView.x << ":" << mousePosView.y << endl;
	}
	
	
}

void Ingame::updateGuiStatus(const std::string& playerKey, std::string& action)
{
	bool defense = false;
	auto player = playersIngame.get(playerKey);
	if (player == nullptr) {
		std::cout << "Retorne de Gui Status" << endl;
		return;
	}
	if(playerKey == "Player_1")
	{
		forCorrectPorpouses = action;
		for (auto&& map1 : playersIngame)
		{
			for (auto&& map2 : uiBoxes)
			{
				if(map2.second->isPressed())
				{
					if (map1.first == "Player_1")
					{
						if (map2.first == "Attack")
						{
							map1.second->setCurrentAnimation(typeOfAnimation::Attack_Anim);
							action = map2.first;
							/*players["Player_2"]->addDamage(this->players["Player_1"]->getStats()->atkFisico);*/
						}
						else if (map2.first == "Defend")
						{
							map1.second->setCurrentAnimation(typeOfAnimation::Defend_Anim);
							action = map2.first;
							defense = true;
						}
						else if (map2.first == "Dead")
						{
							map1.second->setCurrentAnimation(typeOfAnimation::Dead_Anim);
							action = map2.first;
						}
						else if (map2.first == "Hurt")
						{
							map1.second->setCurrentAnimation(typeOfAnimation::Hurt_Anim);
							action = map2.first;
						}
						else if (map2.first == "Walk")
						{
							map1.second->setCurrentAnimation(typeOfAnimation::Walk_Anim);
							action = map2.first;
						}
						else if (map2.first == "Stats")
						{
							std::cout << map1.first << " Stats despu�s de la variaci�n " << endl << *map1.second << endl;
						}
						Packet packet;
						packet << action << playerKey << defense;
						if (socket->send(packet) != Socket::Done)
						{
							std::cout << "Something went wrong sending the action " << endl;
						}
					}
				}
			}
		}
	}
	else if(playerKey == "Player_2")
	{

		{
			if (action == "Attack")
			{
				player->setCurrentAnimation(typeOfAnimation::Attack_Anim);
			}
			else if (action == "Defend")
			{
				player->setCurrentAnimation(typeOfAnimation::Defend_Anim);
			}
			else if (action == "Dead")
			{
				player->setCurrentAnimation(typeOfAnimation::Dead_Anim);
			}
			else if (action == "Hurt")
			{
				player->setCurrentAnimation(typeOfAnimation::Hurt_Anim);
			}
			else if (action == "Walk")
			{
				player->setCurrentAnimation(typeOfAnimation::Walk_Anim);
			}
			else if (action == "Stats")
			{
				std::cout << playerKey << " Stats despu�s de la variaci�n " << std::endl << *player << std::endl;
			}
		}
	}
	
	
}


void Ingame::updateMap()
{
}

void Ingame::updateButtons()
{
	if(this->pausaM->IsButtonPressed("Resume_Btton"))
	{
		paused = false;
	}
	else if(this->pausaM->IsButtonPressed("Quit_Btton"))
	{
		ventana->close();
	}
}




void Ingame::textureProcessor(const string rute, const string key)
{
	
	Texture* temporalT = new Texture();
	if (!temporalT->loadFromFile(rute))
	{
		cerr << "MENU EXCEPTION: No se pudo cargar la imagen";
	}
	else
	{
		std::cout << "Textura: " << key << " cargada" << endl;
	}
	if(this->stateTextures[key] = temporalT)
	{
		if(this != nullptr)
		{
			std::cout << "Textura: " << key << " cargada al mapa" << endl;
		}
		else
		{
			std::cout << "Textura: " << key << " no cargada al mapa" << endl;
		}
	}
}


void Ingame::initBackgroud()
{
	textureProcessor("assets/ui/background/FondoBatalla/Additions/Forest_01_300%.png", "Battle_Background");
	this->battleBackground.setTexture(stateTextures["Battle_Background"]);
	this->battleBackground.setSize(Vector2f(static_cast<float>(this->ventana->getSize().x), static_cast<float>(this->ventana->getSize().y)));
}

void Ingame::initPlayer()
{
	std::cout << "Personaje elegido: " << this->estados[0]->getChosenCharacter() << endl;
	if (this->estados[0]->getChosenCharacter() == 1)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/dragon/SpritesDragon.png", "Dragon_T");
		createPlayer("Dragon_T", 151, 270);

	}
	else if (this->estados[0]->getChosenCharacter() == 2)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/sirena/sirena.png", "Sirena_T");
		createPlayer("Sirena_T", 251, 329);
	}
	else if (this->estados[0]->getChosenCharacter() == 3)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/ogro/Ogro1.png", "Ogro_T");
		createPlayer("Ogro_T", 151, 429);

	}
	else if (this->estados[0]->getChosenCharacter() == 4)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/yordle/YordleSpriteSheet1.png", "Yordle_T");
		createPlayer("Yordle_T", 151, 429);
	}
	else
	{
		std::cout << "No se devolvio el valor " << endl;
	}
	
}

void Ingame::createPlayer(const string& key, float xPos, float yPos)
{
	if(clientNumber < 3)
	{
		string namePlayer = "Player_" + to_string(clientNumber);
		cout << namePlayer << "Nombre del jugador" << endl;
		clientNumber++;
		if (this->estados[0]->getChosenCharacter() == 1)
		{

			playersIngame[namePlayer] = new Dragon(*stateTextures[key], xPos, yPos);
			playersIngame[namePlayer]->getEntitySprite()->setScale(1.5f, 1.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 2)
		{
			playersIngame[namePlayer] = new Sirena(*stateTextures[key], xPos, yPos);
			playersIngame[namePlayer]->getEntitySprite()->setScale(-1.5f, 1.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 3)
		{
			playersIngame[namePlayer] = new Ogro(*stateTextures[key], xPos, yPos);
			playersIngame[namePlayer]->getEntitySprite()->setScale(2.5f, 2.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 4)
		{
			playersIngame[namePlayer] = new Yordle(*stateTextures[key], xPos, yPos);
			playersIngame[namePlayer]->getEntitySprite()->setScale(2.5f, 2.5f);
		}
		else
		{
			std::cout << "No se devolvio el valor " << endl;
		}
		
		
		if(this->playersIngame.contains("Player_2"))
		{
			if(this->playersIngame["Player_2"] != nullptr)
			{
				
				this->playersIngame["Player_2"]->getEntitySprite()->setOrigin(this->playersIngame["Player_2"]->getEntitySprite()->getGlobalBounds().width / 2.f,
					this->playersIngame["Player_2"]->getEntitySprite()->getGlobalBounds().height / 2.f);
					
					if (this->estados[0]->getChosenCharacter() == 1)
					{

						playersIngame[namePlayer]->getEntitySprite()->setScale(-1.5f, 1.5f);
						this->playersIngame["Player_2"]->getEntitySprite()->setPosition(1580, 620);
					}
					else if (this->estados[0]->getChosenCharacter() == 2)
					{
						playersIngame[namePlayer]->getEntitySprite()->setScale(1.5f, 1.5f);
						this->playersIngame["Player_2"]->getEntitySprite()->setPosition(1580, 590);
					}
					else if (this->estados[0]->getChosenCharacter() == 3)
					{
						playersIngame[namePlayer]->getEntitySprite()->setScale(-2.5f, 2.5f);
						this->playersIngame["Player_2"]->getEntitySprite()->setPosition(1580, 620);
					}
					else if (this->estados[0]->getChosenCharacter() == 4)
					{
						playersIngame[namePlayer]->getEntitySprite()->setScale(-2.5f, 2.5f);
						this->playersIngame["Player_2"]->getEntitySprite()->setPosition(1580, 620);
					}
					else
					{
						std::cout << "No se devolvio el valor " << endl;
					}
			}
			
		}
		for(auto map : playersIngame)
		{
			std::cout << "Jugador: " << map.first << "Estadisticas: " << *map.second << endl;
		}
	}
}

void Ingame::initUI()
{
	this->uiBoxes["Actions_Box"] = new Gui::Box(960, 1020,
		(float)this->ventana->getSize().x, (float)this->ventana->getSize().y / (7.f/4.f),font,"");
	this->uiBoxes["Attack"] = new Gui::Box(160.f, 820.f,200.f, 35.f, font, "Atacar");
	this->uiBoxes["Defend"] = new Gui::Box(this->uiBoxes["Attack"]->getPosition().x, 
		this->uiBoxes["Attack"]->getPosition().y + 100.f, 200.f, 35.f, font, "Defenderse");

	this->uiBoxes["Dead"] = new Gui::Box(this->uiBoxes["Attack"]->getPosition().x + 250.f,
		this->uiBoxes["Attack"]->getPosition().y, 200.f, 35.f, font, "Morir");
	this->uiBoxes["Hurt"] = new Gui::Box(this->uiBoxes["Dead"]->getPosition().x,
		this->uiBoxes["Dead"]->getPosition().y + 100.f, 200.f, 35.f, font, "Herido");

	this->uiBoxes["Walk"] = new Gui::Box(this->uiBoxes["Dead"]->getPosition().x + 250.f,
		this->uiBoxes["Dead"]->getPosition().y, 200.f, 35.f, font, "Caminar");
	this->uiBoxes["Stats"] = new Gui::Box(this->uiBoxes["Walk"]->getPosition().x,
		this->uiBoxes["Walk"]->getPosition().y + 100.f, 200.f, 35.f, font, "Estadisticas");

	for (auto && map: uiBoxes)
	{
		map.second->setFont(36);
	}
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
	this->pausaM->createNewButton(830.f, 200.f,"Resume_Btton","Resume");
	this->pausaM->createNewButton(830.f, 400.f, "Quit_Btton", "Quit");
	
	
}



