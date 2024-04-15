#ifndef ENTITYMETHODS_H
#define ENTITYMETHODS_H

class EntityMethods
{
public:
	EntityMethods();
	virtual ~EntityMethods();
	virtual void entityMovement(double deltaTime, float x, float y, float speed) = 0;
	virtual void render(RenderTarget* objTarget) = 0;
	virtual void updateTimeInScreen(double deltaT) = 0;
	virtual void setPosition(float xPos, float yPos) = 0;
	virtual Vector2f getPosition() const = 0;
};


#endif // !ENTITYMETHODS_H
