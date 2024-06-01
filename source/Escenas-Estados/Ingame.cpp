#include "pch.h"
#include "Menu.h"
#include "Ingame.h"




Ingame::Ingame(GameStatus** estados = nullptr, RenderWindow* ventana = nullptr) : GameStatus(estados,ventana), forCorrectPorpouses("")
{

	std::cout << "Soy ingame" << endl;
	this->buttons = nullptr;
	initBackgroud();
	initFont();
	initUI();
	this->pausaM = new PausaMenu(*ventana, font);
	this->initPauseMenu();
	initPlayer();
	
	
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
	return players;
}

void Ingame::setActualPlayers(Mapa<string, Entity*> players)
{
	this->players = players;
}

Mapa<string, Gui::Box*> Ingame::getUiBoxes()
{
	return this->uiBoxes;
}

std::pair<bool, string> Ingame::getPlayerAction(const std::string& playerKey)
{
	for(auto&& map: players)
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

	// Obtener las estadísticas de ataque del atacante y defensa del defensor
	auto attackerStats = attacker->getStats();
	auto defenderStats = defender->getStats();

	// Calcular el daño del ataque
	int damage = attackerStats->atkFisico - defenderStats->defFisica;
	// Considerar defensa mágica si es necesario
	// damage -= defenderStats.defMagica;

	// Asegurarse de que el daño sea positivo
	damage = std::max(0, damage);

	// Reducir la salud del defensor
	defenderStats->hp -= damage;

	// Manejar otros efectos del ataque, como reducción de velocidad, etc.

	std::cout << "Player " << attackerN << " ha infligido " << damage << " de daño a Player " << defenderN << std::endl;
	std::cout << "Salud restante de Player " << defenderN << ": " << defenderStats->hp << std::endl;
}

int Ingame::calculateDamage(int attackStat, const std::string& defenderKey, bool isDefending)
{
	// Obtener las estadísticas de defensa del jugador defensor
	auto defenderStats = estados[0]->getMapPlayer()[defenderKey]->getStats(); // Suponiendo que tienes un método para obtener las estadísticas del jugador en tu estado de juego
	int damage = 0;
	// Calcular el daño
	if (isDefending) {
		// Si el jugador defensor se está defendiendo, se reduce el daño en función de su defensa
		damage = (attackStat > defenderStats->defFisica) ? (attackStat - defenderStats->defFisica) : 0;
	}
	else {
		// Si el jugador defensor no se está defendiendo, recibe todo el daño
		damage = attackStat;
	}
	damage = std::max(0, damage);
	return damage;
}
void Ingame::updateHealth(const std::string& playerKey, int damage)
{
	auto playerStats = estados[0]->getMapPlayer()[playerKey]->getStats(); // Suponiendo que tienes un método para obtener las estadísticas del jugador en tu estado de juego

	// Actualizar la salud
	playerStats->hp -= damage;

	// Si la salud llega a cero o menos, el jugador está muerto
	if (playerStats->hp <= 0) {
		Clock timer;
		if (timer.getElapsedTime().asSeconds() > 1.f)
		{
			this->players[playerKey]->setCurrentAnimation(typeOfAnimation::Dead_Anim);
		}
		// Implementar la lógica de muerte del jugador, por ejemplo, eliminarlo del juego
		// También puedes enviar un mensaje al cliente indicando que el jugador está muerto
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
		for(auto&& map : players)
		{
			map.second->render(drawObj);
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
	
	for(auto&& map : uiBoxes)
	{
		map.second->update(mousePosView);
	}
	if (!paused) //Cuando no esta en pausa
	{
		checkKeyboardEvents(deltaT);
		for(auto&& map: players)
		{
			map.second->update(deltaT);
		}
		if(anotherClient == true)
		{
			initPlayer();
			anotherClient = false;
		}
		updateGuiStatus("Player_1", forCorrectPorpouses);
		
	}
	else //Pausa
	{
		pausaM->update(mousePosView);
		updateButtons();
		
		
		
	}
	if(Keyboard::isKeyPressed(Keyboard::Tab))
	{
		std::cout << mousePosView.x << ":" << mousePosView.y << endl;
	}
	
	
}

void Ingame::updateGuiStatus(const std::string& playerKey, std::string& action)
{
	bool defense = false;
	std::cout << "Entering to updateGuiStatus" << endl;
	auto player = players.get(playerKey);
	if (player == nullptr) {
		std::cout << "Retorne de Gui Status" << endl;
		return;
	}
	if(playerKey == "Player_1")
	{
		for (auto&& map1 : players)
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
							std::cout << map1.first << " Stats después de la variación " << endl << *map1.second << endl;
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
				std::cout << playerKey << " Stats después de la variación " << std::endl << *player << std::endl;
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
		createPlayer("Dragon_T", 151, 429);

	}
	else if (this->estados[0]->getChosenCharacter() == 2)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/sirena/sirena.png", "Sirena_T");
		createPlayer("Sirena_T", 151, 429);
	}
	else if (this->estados[0]->getChosenCharacter() == 3)
	{
		textureProcessor("assets/Spritesheets/Pjs/Sprites/ogro/Ogro1.png", "Ogro_T");
		createPlayer("Ogro_T", 151, 429);
		this->players["Player_1"]->getEntitySprite()->setScale(3.f, 3.f);

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
		clientNumber++;
		if (this->estados[0]->getChosenCharacter() == 1)
		{

			players[namePlayer] = new Dragon(*stateTextures[key], xPos, yPos);
			players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 2)
		{
			players[namePlayer] = new Sirena(*stateTextures[key], xPos, yPos);
			players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 3)
		{
			players[namePlayer] = new Ogro(*stateTextures[key], xPos, yPos);
			players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
		}
		else if (this->estados[0]->getChosenCharacter() == 4)
		{
			players[namePlayer] = new Yordle(*stateTextures[key], xPos, yPos);
			players[namePlayer]->getEntitySprite()->setScale(2.f, 2.f);
		}
		else
		{
			std::cout << "No se devolvio el valor " << endl;
		}
		
		
		if(this->players.contains("Player_2"))
		{
			if(this->players["Player_2"] != nullptr)
			{
				
				this->players["Player_2"]->getEntitySprite()->setOrigin(this->players["Player_2"]->getEntitySprite()->getGlobalBounds().width / 2.f,
					this->players["Player_2"]->getEntitySprite()->getGlobalBounds().height / 2.f);
					this->players["Player_2"]->setPosition(1580, 500);
					if (this->estados[0]->getChosenCharacter() == 1)
					{

						players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
					}
					else if (this->estados[0]->getChosenCharacter() == 2)
					{
						players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
					}
					else if (this->estados[0]->getChosenCharacter() == 3)
					{
						players[namePlayer]->getEntitySprite()->setScale(0.5f, 0.5f);
					}
					else if (this->estados[0]->getChosenCharacter() == 4)
					{
						players[namePlayer]->getEntitySprite()->setScale(2.f, 2.f);
					}
					else
					{
						std::cout << "No se devolvio el valor " << endl;
					}
				/*if (this->players["Player_2"]->getEntitySprite()->getTexture()->getSize().x == stateTextures["Dragon_T"]->getSize().x && this->stateTextures["Dragon_T"] != nullptr)
				{
					std::cout << "Entre a resize y pos 1" << endl;
					this->players["Player_2"]->setPosition(1580, 485);
					this->players["Player_2"]->getEntitySprite()->setScale(-1.f, 1.f);

				}
				else if (this->players["Player_2"]->getEntitySprite()->getTexture()->getSize().x == stateTextures["Ogro_T"]->getSize().x && this->stateTextures["Ogro_T"] != nullptr)
				{
					std::cout << "Entre a resize y pos 2" << endl;
					this->players["Player_2"]->getEntitySprite()->setScale(-3.f, 3.f);
					this->players["Player_2"]->setPosition(1580, 500);
				}
				else if (this->players["Player_2"]->getEntitySprite()->getTexture()->getSize().x == stateTextures["Sirena_T"]->getSize().x && this->stateTextures["Sirena_T"] != nullptr)
				{
					std::cout << "Entre a resize y pos 3" << endl;
					this->players["Player_2"]->getEntitySprite()->setScale(-0.5f, 0.5f);
					this->players["Player_2"]->setPosition(1580, 578);
				}
				else if (this->players["Player_2"]->getEntitySprite()->getTexture()->getSize().x == stateTextures["Yordle_T"]->getSize().x && this->stateTextures["Yordle_T"] != nullptr)
				{
					std::cout << "Entre a resize y pos 4" << endl;
					this->players["Player_2"]->getEntitySprite()->setScale(-2.f, 2.f);
				}*/
			}
			
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



