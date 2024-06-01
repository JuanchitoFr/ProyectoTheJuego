#ifndef MENU_H
#define MENU_H

class GameStatus;
#include "GameStatus.h"
#include "Ingame.h"

enum TexturesM : unsigned int 
{
	Backg_1, Backg_2, Backg_3, Backg_4, Backg_5, PlayButtonT, 
	PlayBtton_Hover,PlayBtton_Pressed, 
	OtherButton, OtherButton_Hover_Pressed, CursorTexture, Dragon_Texture, Ogro_Texture, Sirena_Texture, 
	Yordle_Texture,Total_TexturesMn
};

enum typeBtton: unsigned int
{
	playButton, serverButton,clientButton,exitButtonT, Bttn_ShowCharacter1, Bttn_ShowCharacter2, Bttn_ShowCharacter3
	,Bttn_ShowCharacter4, readyButton, Total_TypeBttons
};

enum escenas
{
	Menu_Principal, Conexion , Seleccion ,Total_Escenas
}; 


//Menu principal

class Menu : public GameStatus
{
	private:
		Mapa<string, Entity*> sprites;
		Mapa<string, RectangleShape*> backgroundLayers;
		Sprite cursor;
		Font titleFont, textFont;
		Text titleText;
		Text* text;
		Clock clock;
		bool changeScene;
		Vector2u currentWinSize;
		unsigned short bttnState, sceneState;
		int currentCharacter;
		float elapsedT, elapsedT2, xPos,yPos, width, height, opacidad, deltaT;
		RectangleShape blackOverlay;
		void initFont();
		void initBackground();
		void initLayers(Texture& texture, const string key);
		void initBtton(Texture* textureIdle, Texture* textureHover, Texture* texturePressed, string text, typeBtton xd);
		void textureProcessor(const string rute, const string key);
		
		
		

	public:
		Menu(GameStatus** estados, RenderWindow* window);
		virtual ~Menu();
		void updateBackgroundTexture(float deltaT, float switchT, float switchT2);
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void Update(float deltaT) override;
		void updateButtons();
		Gui::Buttons* getButtons() override;
		Mapa<string, Entity*> getMapPlayer() override;
		Mapa<string, Gui::Box*> getUiBoxes() override;
		
};

#endif // !MENU_H

