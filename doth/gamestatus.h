#ifndef GAMESTATUS_H
#define GAMESTATUS_H


#include "gamemethods.h"


class GameStatus : public GameMethods
{
	protected:
		std::stack<GameStatus*>* Statetype;
		std::map<std::string, Texture> textures;
		RenderWindow* ventana;
	public:
		GameStatus(std::stack<GameStatus*>* Statetype,
		RenderWindow* ventana);
		virtual ~GameStatus();
		virtual void render(RenderTarget* drawObj) = 0;
		virtual void run() = 0;

};


#endif // !GAMESTATUS_H

