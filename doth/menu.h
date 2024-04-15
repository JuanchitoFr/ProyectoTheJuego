#ifndef MENU_H
#define MENU_H

#include "gamestatus.h"

class Menu : public GameStatus
{
	private:

	public:
		Menu(std::stack<GameStatus*>* stateType = nullptr, RenderWindow* window = nullptr);
		virtual ~Menu();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents() override;
		void run() override;
		void initTextures();
		void endState() override;



};

#endif // !MENU_H

