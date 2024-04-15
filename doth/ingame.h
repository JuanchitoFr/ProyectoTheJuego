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
		void run() override;
		void initTextures();
		void initPlayer();


};


#endif // !INGAME_H

