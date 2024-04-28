#ifndef GAMESTATUS_H
#define GAMESTATUS_H


#include "gamemethods.h"


class GameStatus : public GameMethods
{
	protected:
		std::stack<GameStatus*>* Statetype;
		std::map<std::string, Texture> textures;
		RenderWindow* ventana;
		Vector2i mousePosScreen, mousePosWindow;
		Vector2f mousePosView;
		bool end, parcialEnd;
	public:
		GameStatus(std::stack<GameStatus*>* Statetype,
		RenderWindow* ventana);
		virtual ~GameStatus();
		virtual void render(RenderTarget* drawObj) override;
		virtual void run() override;
		virtual void checkKeyboardEvents(float deltaT) override;
		virtual void Update(float deltaTime) override;
		virtual void updateMousePos() override;
		virtual void endState() override;
		virtual void parcialEndState();
		bool getEndState() const;
		bool getParcialEndState() const;
		RenderWindow* getWindow();
};


#endif // !GAMESTATUS_H

