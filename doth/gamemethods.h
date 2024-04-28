
#ifndef STATUSOFGAME_H
#define STATUSOFGAME_H


class GameMethods
{
	private:
	public:
		GameMethods();
		virtual ~GameMethods();
		virtual void run() = 0;
		virtual void render(RenderTarget* drawObj) = 0;
		virtual void endState() = 0;
		virtual void checkKeyboardEvents(float deltaT) = 0;
		virtual void Update(float deltaT) = 0;
		virtual void updateMousePos() = 0;

};

#endif // !STATUSOFGAME_H

