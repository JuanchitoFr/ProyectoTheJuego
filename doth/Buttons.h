#ifndef BUTTONS_H
#define BUTTONS_H

enum btnStates : unsigned short{idle = 0, hover, pressed};


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
	void setPosition(float x, float y);
	void setSize(float width, float height);
	void render(RenderTarget* drawObj);
	void update(Vector2f mousePos);
	bool getButtonState();
	bool isPressed();
	float getButtonWidth();
	float getButtonHeight();
	Texture getTextureIdle();
	Texture getTextureHover();
	Texture getTexturePressed();
	RectangleShape getButtonBody();


};

#endif // !BUTTONS_H
