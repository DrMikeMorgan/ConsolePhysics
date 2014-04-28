#include "collisions.h"
#include <cmath>
#include <fstream>

int CollisionDetector::detect(std::vector<Sprite*>& sprites, int spacesPerMetre)
{
	std::vector<collision> collisions;
	size_t n = sprites.size();
	for(size_t i=0; i<n; ++i)
		for(size_t j=i+1; j<n; ++j)
		{
			float dx, dy;
			dx = sprites[i]->getPos().getx() - sprites[j]->getPos().getx();
			dy = sprites[i]->getPos().gety() - sprites[j]->getPos().gety();
			Vector2d normal;
			if(fabs(dx)*spacesPerMetre < (sprites[i]->getWidth() + sprites[j]->getWidth())/2 && fabs(dy)*spacesPerMetre < (sprites[i]->getHeight() + sprites[j]->getHeight())/2)
			{
				normal.setx(dx);
				normal.sety(dy);
				normal.normalise();
				collisions.push_back({i,j,normal});	
			}
		}

	//resolve collisions

	for(size_t i=0; i<collisions.size(); ++i)
	{
		Vector2d relVel = sprites[collisions[i].a]->getVel();
		relVel -= sprites[collisions[i].b]->getVel();
		float sepVel = relVel * collisions[i].normal;
		if(sepVel > 0)
			continue;
		float newSep = -sepVel * (sprites[collisions[i].a]->getBounce()*sprites[collisions[i].b]->getBounce()/2.f);
		float deltaVel = newSep -sepVel;
		float totInvMass = sprites[collisions[i].a]->getInverseMass() + sprites[collisions[i].b]->getInverseMass();		
		float impulse = deltaVel / totInvMass;
		Vector2d impPerIMass = collisions[i].normal * impulse;
		sprites[collisions[i].a]->setVel(sprites[collisions[i].a]->getVel() + impPerIMass * sprites[collisions[i].a]->getInverseMass());
		sprites[collisions[i].b]->setVel(sprites[collisions[i].b]->getVel() + impPerIMass * -sprites[collisions[i].b]->getInverseMass());
	}
	return collisions.size();
}
