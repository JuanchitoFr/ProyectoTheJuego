
#ifndef GAME_H
#define GAME_H

#include "Ingame.h"
#include "menu.h"
#include "entity.h"

class Game
{
	private:
		int anchoVentana;
		int altoVentana;
		short framerate;
		String tituloJuego;
		RenderWindow* ventana;
		Event eventos;
		std::stack<GameStatus*> estados;

	public:
		Game(int altoV, int anchoV, short framerate, String tituloJ);
		virtual ~Game();
		void render();
		void run();
		void checkStop();
		void initStates();
};

#endif // !GAME_H






