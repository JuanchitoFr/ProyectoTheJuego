#ifndef MENU_H
#define MENU_H

#include "gamestatus.h"
#include "ingame.h"
#include "Buttons.h"


enum Textures : unsigned int 
{
	Backg_1, Backg_2, Backg_3, Backg_4, Backg_5, PlayButtonT, 
	PlayBtton_Hover,PlayBtton_Pressed, 
	OtherButton, OtherButton_Hover_Pressed
	, Total_TexturesMn
};

enum typeBtton: unsigned int
{
	playButton, serverButton,clientButton,exitButtonT, Bttn_ShowCharacter1, Bttn_ShowCharacter2, Bttn_ShowCharacter3
	,Bttn_ShowCharacter4
};




class Menu : public GameStatus
{
	private:
		
		Font titleFont, textFont;
		Text text, titleText;
		Sprite titleSprite;
		Vector2u currentWinSize;
		
		
		unsigned short bttnState;
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
		Buttons* getButtons() override;
		
};

#endif // !MENU_H

