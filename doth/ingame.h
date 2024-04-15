#ifndef INGAME_H
#define INGAME_H

#include "gamestatus.h"
#include "player.h"

class Ingame : public GameStatus
{
	private:
		Player* jugadores;
		
	public:
		Ingame(std::stack<GameStatus*>* Statetype, RenderWindow* ventana);
		virtual ~Ingame();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents() override;
		void Update(const double& deltaT) override;
		void run() override;
		void initTextures();
		void initPlayer();
		void endState() override;


};


#endif // !INGAME_H

