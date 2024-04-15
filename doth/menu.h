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
		void run() override;



};

#endif // !MENU_H

