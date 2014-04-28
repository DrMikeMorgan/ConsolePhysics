#include "physics.h"
#include <vector>
#include <string>

class Sprite : public Particle
{
	std::vector<std::string> strings;
	int height, width;	//max height, width in char spaces
public:
	Sprite(float x, float y, float mass): Particle(x,y,mass){}
	void readFromFile(std::string fileName);
	friend class Scene;
};

class Scene
{
	std::vector<Sprite*> sprites;
	float spacesPerMetre;
	float limy, limx;
public:
	void runPhysics(float time);
	Scene():spacesPerMetre(10){}
	void add(Sprite& s){sprites.push_back(&s);}
	void setLimits(float x, float y){limx = x, limy = y;}	
	void render();
};
