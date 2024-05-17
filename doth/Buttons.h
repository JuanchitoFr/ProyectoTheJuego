#ifndef BUTTONS_H
#define BUTTONS_H

enum btnStates : unsigned short{idle = 0, hover, pressed};

//En esta clase se gestionan los botones, pueden implementar una que gestione en si toda la interfaz ya sea en el menu o ingame.
class Buttons
{
private:
	unsigned short buttonState;
	RectangleShape buttonBody;
	Font* buttonFont;
	Text buttonText;
	Texture textureIdle;
	Texture textureHover;
	Texture texturePressed;
public:
	Buttons(float xPos, float yPos, float width, float heightFont, Font* font, Texture textureIdle,Texture textureHover,Texture texturePressed);
	Buttons();
	virtual ~Buttons();
	void setPosition(float x, float y);
	void setSize(float width, float height);
	void render(RenderTarget* drawObj);
	void update(Vector2f mousePos);
	bool getButtonState();
	const bool isPressed() const;
	float getButtonWidth();
	float getButtonHeight();
	Texture getTextureIdle();
	Texture getTextureHover();
	Texture getTexturePressed();
	RectangleShape getButtonBody();


};

#endif // !BUTTONS_H
