#ifndef ENTITYMETHODS_H
#define ENTITYMETHODS_H

class EntityMethods
{
public:
	EntityMethods();
	virtual ~EntityMethods();
	virtual void render(RenderTarget* objTarget) = 0;
	virtual void entityMovement(float deltaTime, float x, float y) = 0;
	virtual void updateSprite(float deltaT, float switchT) = 0;
	virtual void setPosition(float xPos, float yPos) = 0;
	virtual Vector2f getPosition() = 0;

};


#endif // !ENTITYMETHODS_H
