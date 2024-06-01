#include "Entity.h"

#ifndef OGRO_H
#define OGRO_H

class Ogro : public Entity
{
private:
	
public:
	Ogro(Texture& texture, float xPos, float yPos);
	~Ogro();
	void update(const float& deltaT) override;
	void setNextAnimation(typeOfAnimation xd) override;
	void setCurrentAnimation(typeOfAnimation xd) override;
	void setTypeAnim(unsigned int typeAnim) override;
	unsigned int getTypeAnim() override;



};


#endif // !OGRO_H


