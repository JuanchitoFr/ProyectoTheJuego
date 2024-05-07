#ifndef MENU_H
#define MENU_H

#include "gamestatus.h"
#include "ingame.h"
#include "Buttons.h"


enum Textures : unsigned int 
{
	Backg_1, Backg_2, Backg_3, Backg_4, Backg_5, PlayButton, PlayBtton_Hover,PlayBtton_Pressed, Total_TexturesMn
};

enum typeBtton: unsigned int
{
	playButtonT, exitButtonT
};




class Menu : public GameStatus
{
	private:
		RectangleShape* backLayersArr;
		Buttons* buttons;
		RectangleShape* buttonArr;
		Font titleFont, textFont;
		Text text, titleText;
		Sprite titleSprite;
		Vector2u currentWinSize;
		
		
		unsigned short bttnState, backLayersArrSize, buttonArrSize;
		float elapsedT, elapsedT2, xPos,yPos, width, height;
		void initFont();
		void initBackground();
		void initLayers(Texture& texture, Textures xd);
		void initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, typeBtton xd);
		void textureProcessor(String rute, Textures xd);
		
		
		

	public:
		Menu(GameStatus** estados, RenderWindow* window);
		virtual ~Menu();
		
		void updateBackgroundTexture(float deltaT, float switchT, float switchT2);
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void Update(float deltaT) override;
		void updateButtons();
};

#endif // !MENU_H

