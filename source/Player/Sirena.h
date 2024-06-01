#include "Entity.h"

#ifndef SIRENA_H
#define SIRENA_H

class Sirena : public Entity
{
private:
public:
	Sirena(Texture& texture, float xPos, float yPos);
	virtual ~Sirena();
	void update(const float& deltaT) override;
	void setNextAnimation(typeOfAnimation xd) override;
	void setCurrentAnimation(typeOfAnimation xd) override;
	void setTypeAnim(unsigned int typeAnim) override;
	unsigned int getTypeAnim() override;



};




#endif // !SIRENA_H



