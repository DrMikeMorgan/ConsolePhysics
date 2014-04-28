#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <cmath>

class ForceGenerator;

class Vector2d
{
	float x,y;
public:
	Vector2d():x(0),y(0){}
	Vector2d(float _x, float _y):x(_x),y(_y){}	
	Vector2d operator + (const Vector2d& v){return Vector2d(x+v.x, y+v.y);}
	void operator += (const Vector2d& v){x+=v.x; y+=v.y;}
	Vector2d operator - (const Vector2d& v){return Vector2d(x-v.x, y-v.y);}
	void operator -= (const Vector2d& v){x-=v.x; y-= v.y;}
	Vector2d operator * (const float& s){return Vector2d(x*s, y*s);}
	void operator *= (const float& v){x*=v; y*=v;}
	float operator * (const Vector2d& v){return x*v.x + y*v.y;}
	void operator = (const Vector2d& rhs){x=rhs.x, y=rhs.y;}
	float getx(){return x;}
	float gety(){return y;}
	void setx(float _x){x = _x;}
	void sety(float _y){y = _y;}
	float magnitude(){return sqrt(x*x+y*y);}
	void normalise(){if(!magnitude()) return; x /= magnitude(); y /= magnitude();}
	void clear(){x=y=0.f;}	
};

class Particle
{
protected:
	Vector2d pos, vel, acc, forceAccum;		//position, velocity, acceleration, total force acting on particle, acceleration due to gravity
	float damping, inverseMass, bounciness;
	std::vector<ForceGenerator*> forces; 
public:
	Particle():pos(),vel(),acc(0,15.0),forceAccum(),damping(0.98), bounciness(0.8){}
	Particle(const float& x, const float& y, const float& mass):pos(x,y),vel(),acc(0,15.0),forceAccum(),damping(0.98), bounciness(0.8){setMass(mass);}
	Vector2d& getPos(){return pos;}
	void setPos(float x, float y){pos = Vector2d(x,y);}
	void setPos(Vector2d v){pos = v;}
	Vector2d& getVel(){return vel;}
	void setVel(float x, float y){vel = Vector2d(x,y);}
	void setVel(Vector2d v){vel = v;}
	void addForceGenerator(ForceGenerator& fg){forces.push_back(&fg);}
	void removeForceGenerator(ForceGenerator& fg);
	void addForce(const Vector2d& force){forceAccum += force;}
	void setMass(float mass, bool infinite = false){if(infinite) inverseMass = 0; else inverseMass = 1.f/mass;}
	float getInverseMass(){return inverseMass;}
	float getBounce(){return bounciness;}
	void setBounce(float b){bounciness = b;} 
	void integrate(float time, float impulse_frame=0.033);
};

class ForceGenerator
{
public:
	virtual void updateForce(Particle *particle, float duration) = 0;
};

class AnchoredSpring : public ForceGenerator
{
	Vector2d anchor;
	float springConstant, restLength;
public:
	AnchoredSpring(float x, float y, float springConst, float restLen):anchor(x,y), springConstant(springConst), restLength(restLen){}
	virtual void updateForce(Particle * p, float duration);
};

class AnchoredBungee : public ForceGenerator
{
	Vector2d anchor;
	float springConstant, restLength;
public:
	AnchoredBungee(float x, float y, float springConst, float restLen):anchor(x,y), springConstant(springConst), restLength(restLen){}
	virtual void updateForce(Particle * p, float duration);
};

#endif

