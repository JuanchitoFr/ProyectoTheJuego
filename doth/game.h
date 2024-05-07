
#ifndef GAME_H
#define GAME_H

#include "Ingame.h"
#include "menu.h"
enum stateName
{
	menu, ingame
};
class Game
{
	private:
		unsigned int anchoVentana, altoVentana, framerate;
		int currentEstadoIndex;
		ContextSettings settings;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		GameStatus* estados;
		GameStatus* currentState;
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






