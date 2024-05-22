#ifndef PAUSAMENU_H
#define PAUSAMENU_H
#include "../Funciones/Map.h"
class PausaMenu
{
private:
	RectangleShape background;
	RectangleShape container;
	mapas::ButtonsMap *buttons;
public:
	PausaMenu(RenderWindow& ventana);
	virtual ~PausaMenu();
	void update();
	bool checkIsUnPause();
	void render(RenderTarget* objTarget);



};

#endif // !PAUSAMENU_H

