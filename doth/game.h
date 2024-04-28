
#ifndef GAME_H
#define GAME_H

#include "Ingame.h"
#include "menu.h"

enum States {
	menu,game
};

class Game
{
	private:
		unsigned int anchoVentana;
		unsigned int altoVentana;
		unsigned int framerate;
		ContextSettings settings;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		std::stack<GameStatus*> estados;
		float deltaT;
		Clock deltaTclock;

	public:
		Game(unsigned int altoV, unsigned int anchoV, unsigned int framerate, String tituloJ);
		virtual ~Game();
		void render();
		void updateState();
		void updateDeltaT();
		void run();
		void stateEvents();
		void initStates();
};

#endif // !GAME_H






