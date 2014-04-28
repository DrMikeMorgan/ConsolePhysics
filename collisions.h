#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include "physics.h"
#include "graphics.h"

class CollisionDetector 	//and resolver...
{
	struct collision
	{
		size_t a,b;	//indices of two objects colliding
		Vector2d normal;	 
	};

public:
	CollisionDetector(){}
	int detect(std::vector<Sprite*>&, int);	
};

#endif
