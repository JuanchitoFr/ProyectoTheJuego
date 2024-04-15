
#ifndef GAME_H
#define GAME_H

#include "Ingame.h"
#include "menu.h"
#include "entity.h"

class Game
{
	private:
		unsigned int anchoVentana;
		unsigned int altoVentana;
		unsigned int framerate;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		std::stack<GameStatus*> estados;
		double deltaT;

	public:
		Game(unsigned int altoV, unsigned int anchoV, unsigned int framerate, String tituloJ);
		virtual ~Game();
		void render();
		void updateState();
		void run();
		void stateEvents();
		void initStates();
};

#endif // !GAME_H






