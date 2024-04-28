#include "pch.h"
#include "../doth/ingame.h"


Ingame::Ingame(std::stack<GameStatus*>* Statetype, RenderWindow* ventana) : GameStatus(Statetype,ventana)
{
	initTextures();
	initMap();
	initPlayer();
	this->currentWinSize = Vector2f(800, 800);
	this->sizeChange = false;
}
Ingame::~Ingame()
{
	delete this->playerS;
}

void Ingame::render(RenderTarget* drawObj)
{
	
	try
	{
		if (!drawObj)
		{
			drawObj = this->ventana;
		}
		drawObj->setView(View(winSize));
		drawObj->draw(background[floorC]);
		drawObj->draw(background[wallsC]);
		drawObj->draw(background[decoration2]);
		drawObj->draw(background[decoration1]);
		this->playerS->render(this->ventana);
		
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was: " << p.what() << std::endl;
	}
	
}


void Ingame::checkKeyboardEvents(float deltaT)
{
	this->playerS->setEntityAnimation(0.f, 0.f);
	int y = this->playerS->getCoordinatesY(), x = this->playerS->getCoordinatesX();


	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		this->playerS->entityMovement(deltaT, 0.f, -1.f);
		this->playerS->setIsMoving(true);
		y = 3;
		this->playerS->setCoordinatesY(y);
		/*x++;
		if (x * 64 >= this->playerS->getEntityTexture()->getSize().x) {
			x = 0;
		}
		this->playerS->setCoordinatesX(x);*/
		this->playerS->updateSprite(deltaT, 0.15f);

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		this->playerS->entityMovement(deltaT, 0.f, 1.f);
		this->playerS->setIsMoving(true);
		y = 0;
		this->playerS->setCoordinatesY(y);
		/*x++;
		if (x * 64 >= this->playerS->getEntityTexture()->getSize().x) {
			x = 0;
		}
		this->playerS->setCoordinatesX(x);*/
		this->playerS->updateSprite(deltaT, 0.15f);


	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		this->playerS->entityMovement(deltaT, -1.f, 0.f);
		this->playerS->setIsMoving(true);
		y = 1;
		this->playerS->setCoordinatesY(y);
		/*x++;
		if (x * 64 >= this->playerS->getEntityTexture()->getSize().x) {
			x = 0;
		}
		this->playerS->setCoordinatesX(x);*/
		this->playerS->updateSprite(deltaT, 0.15f);


	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		this->playerS->entityMovement(deltaT, 1.f, 0.f);
		this->playerS->setIsMoving(true);
		y = 2;
		this->playerS->setCoordinatesY(y);
		/*x++;
		if (x * 64 >= this->playerS->getEntityTexture()->getSize().x) {
			x = 0;
		}
		this->playerS->setCoordinatesX(x);*/
		this->playerS->updateSprite(deltaT, 0.15f);

	}
	else if(Keyboard::isKeyPressed(Keyboard::Escape))
	{
		this->endState();
	}

	if (this->playerS->getEntityMovement().x == 0.f && this->playerS->getEntityMovement().y == 0.f) {
		this->playerS->setCoordinatesX(0);
		this->playerS->updateSprite(deltaT, 0.15f);
		this->playerS->setIsMoving(false);
		
	}


}


void Ingame::Update(float deltaT)
{
	checkKeyboardEvents(deltaT);
	updateMap();
	std::cout << playerS->getEntitySprite()->getPosition().x << " " << playerS->getEntitySprite()->getPosition().y << std::endl;
	/*checkSize();*/
}

void Ingame::updateMap()
{
	float windowWidth = static_cast<float>(this->ventana->getSize().x);
	float windowHeight = static_cast<float>(this->ventana->getSize().y);
	Vector2f bgPos(windowWidth/ 7.5, windowHeight / 6.5);
	winSize = FloatRect(0, 0, windowWidth, windowHeight);
	for (auto i = background.begin(); i != background.end(); i++)
	{
		unsigned short num = i->first;
		if (windowWidth > 800 && windowHeight > 800) {
			background[num].setScale(1.5, 1.5);
			background[num].setPosition(bgPos.x / 0.5,bgPos.y);
			this->playerS->getEntitySprite()->setScale(1.3, 1.3);
			
		}
		else {
			background[num].setScale(1, 1);
			background[num].setPosition(bgPos);
			this->playerS->getEntitySprite()->setScale(1, 1);
		}
	}
	Vector2f winSize(windowWidth, windowHeight);

		
}

void Ingame::run()
{
}

void Ingame::initTextures()
{
	Texture texture, background;
	if (!texture.loadFromFile("assets/Spritesheets/Red.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta" ;
		std::cout << "No se pudo cargar" << std::endl;
	}
	texture.setRepeated(true);
	this->textures["Player1"] = texture;

	if(!background.loadFromFile("assets/Spritesheets/piso.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta";
		std::cout << "No se pudo cargar" << std::endl;
	}
	this->textures["floorC"] = background;

	if (!background.loadFromFile("assets/Spritesheets/limitesLobby.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta";
		std::cout << "No se pudo cargar" << std::endl;
	}
	this->textures["wallsC"] = background;

	if (!background.loadFromFile("assets/Spritesheets/decoracion2.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta";
		std::cout << "No se pudo cargar" << std::endl;
	}
	this->textures["decoration2"] = background;


	if (!background.loadFromFile("assets/Spritesheets/decoracion1.png")) {
		throw " No se pudo cargar, tal vez ruta incorrecta";
		std::cout << "No se pudo cargar" << std::endl;
	}
	this->textures["decoration1"] = background;
	
}

void Ingame::initPlayer()
{
	float windowWidth = static_cast<float>(this->ventana->getSize().x);
	float windowHeight = static_cast<float>(this->ventana->getSize().y);
	this->playerS = new Player(64, 64, &this->textures["Player1"],0.f,0,0,1,0);
	this->playerS->setSpeed(100.f);
	this->playerS->getEntitySprite()->setPosition(Vector2f(903, 750));
}

void Ingame::initMap()
{
	this->background[floorC].setTexture(&this->textures["floorC"]);
	this->background[floorC].setSize(Vector2f(576, 480));
	this->background[wallsC].setTexture(&this->textures["wallsC"]);
	this->background[wallsC].setSize(Vector2f(576, 480));
	this->background[decoration1].setTexture(&this->textures["decoration1"]);
	this->background[decoration1].setSize(Vector2f(576, 480));
	this->background[decoration2].setTexture(&this->textures["decoration2"]);
	this->background[decoration2].setSize(Vector2f(576, 480));

}

void Ingame::endState()
{
	this->end = true;
}

void Ingame::parcialEndState()
{
	this->parcialEnd = true;
}

