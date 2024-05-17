#ifndef INGAME_H
#define INGAME_H

#include "gamestatus.h"
#include "player.h"
#include "entity.h"
#include "menu.h"
//Animation player
enum Keybinds
{
	Down,Left,Right,Up
};

enum mapLayers
{
	decoration1,decoration2,floorC,wallsC
};

enum playerType : unsigned short
{
	Dragon, Ogro, Sirena, Yordle, Total_Characters
};
enum textureType : unsigned short
{
	Dragon_T, Dragon_FireEffect , Total_TexturesIg
};

struct backgroud
{
	RectangleShape layer;
	float x, y;
};

enum typeBttonIn
{

};

// Estado ya en el juego
class Ingame : public GameStatus
{
	private:
		void textureProcessor(String rute, textureType xd);
		void initTextures();
		void initPlayer(Texture* playerTexture, playerType xd);
		void initMap();
		FloatRect winSize;
		void initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, typeBttonIn xd);
	public:
		Ingame(GameStatus** estados, RenderWindow* ventana);
		virtual ~Ingame();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void Update(float deltaT) override;
		void updateMap();
		void updateButtons();
		Buttons* getButtons() override;
		


};


#endif // !INGAME_H

