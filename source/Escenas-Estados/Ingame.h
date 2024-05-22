#ifndef INGAME_H
#define INGAME_H

#include "GameStatus.h"
#include "../source/Gui/PausaMenu.h"


enum Keybinds : unsigned short
{
	Down,Left,Right,Up, Total_Keybinds
};

enum mapLayers : unsigned short
{
	decoration1,decoration2,floorC,wallsC, Total_MapLayers
};

enum textureType : unsigned short
{
	Dragon_T, Dragon_FireEffect , Total_TexturesIg
};


enum typeBttonIn : unsigned short
{

};

// Estado ya en el juego
class Ingame : public GameStatus
{
	private:
		Entity player;
		PausaMenu pausaM;
		void textureProcessor(String rute, textureType xd);
		void initTextures();
		void initPlayer(Texture* playerTexture, typeCharacter xd);
		void initMap();
		FloatRect winSize;
		void initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, string text, typeBttonIn xd);
	public:
		Ingame(GameStatus** estados, RenderWindow* ventana);
		virtual ~Ingame();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void checkKeyboardPause(const float& deltaT);
		void Update(float deltaT) override;
		void GUI() override;
		void updateMap();
		void updateButtons();
		Gui::Buttons* getButtons() override;
		


};


#endif // !INGAME_H

