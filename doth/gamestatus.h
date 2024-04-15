#ifndef GAMESTATUS_H
#define GAMESTATUS_H


#include "gamemethods.h"


class GameStatus : public GameMethods
{
	protected:
		std::stack<GameStatus*>* Statetype;
		std::map<std::string, Texture> textures;
		RenderWindow* ventana;
		bool end;
	public:
		GameStatus(std::stack<GameStatus*>* Statetype,
		RenderWindow* ventana);
		virtual ~GameStatus();
		virtual void render(RenderTarget* drawObj) override;
		virtual void run() override;
		virtual void checkKeyboardEvents() override;
		virtual void Update(const double& deltaTime) override;
		void endState() override;
		bool getEndState() const;

};


#endif // !GAMESTATUS_H

