#ifndef MENU_H
#define MENU_H

#include "gamestatus.h"


enum typeButton
{
	playB, exitB
};

enum btnStates
{
	idle,hover,pressed
};

enum TexturesBackg {
	cloudFront, cloudMidlle, hill, mountain, backmountain, backgroundSky
};

class Menu : public GameStatus
{
	private:
		std::map<unsigned short, RectangleShape> layers;
		std::map<unsigned short, RectangleShape> buttonArr;
		Font title, font;
		Text text;
		Sprite titleSprite;
		Vector2u currentWinSize;
		
		int xRow, yColumn, xRow2;
		unsigned short bttnState;
		float elapsedT, elapsedT2;
		void initBackground();
		void initButtons();
		void initTextures();
		
		

	public:
		Menu(std::stack<GameStatus*>* stateType = nullptr, RenderWindow* window = nullptr);
		virtual ~Menu();
		
		void updateBackgroundTexture(float deltaT, float switchT, float switchT2);
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void run() override;
		void Update(float deltaT) override;
		void updateBttn(Vector2f mousePos);
		void endState() override;
		void parcialEndState() override;
		unsigned short getBttnState();
		int getYcolumn();
		int getXrow();
		void setYcolumn(int y);
		void setXrow(int x);
};

#endif // !MENU_H

