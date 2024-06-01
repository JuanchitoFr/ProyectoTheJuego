#include "Entity.h"

#ifndef DRAGOM_H
#define DRAGON_H

class Dragon : public Entity
{
private:
public:
	Dragon(Texture& texture, float xPos, float yPos);
	virtual ~Dragon();
	void update(const float& deltaT) override;
	void setNextAnimation(typeOfAnimation xd) override;
	void setCurrentAnimation(typeOfAnimation xd) override;
	void setTypeAnim(unsigned int typeAnim) override;
	unsigned int getTypeAnim() override;



};

#endif // !DRAGOM_H



