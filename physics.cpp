#include "physics.h"
#include <cmath>
#include <fstream>
void Particle::integrate(float time, float impulse_frame)
{
	if(inverseMass == 0)
		return;

	//update forces
	for(int i=0; i<forces.size(); ++i)
		forces[i]->updateForce(this, time);

	//update positions and velocities
	Vector2d tempAcc = acc;
	tempAcc += forceAccum*inverseMass;
	
	pos += (vel*time);
	vel += (tempAcc*time);
		
	vel *= (float) pow(damping,time);
	forceAccum.clear();
}

void Particle::removeForceGenerator(ForceGenerator &fg)
{
	for(int i=0; i<forces.size(); ++i) 
		if(&fg == forces[i])
		{
			forces[i] = forces[forces.size()-1];
			forces.resize(forces.size()-1);	
			break;
		}
}

void AnchoredSpring::updateForce(Particle * p, float duration)
{
	Vector2d force;
	force.setx(p->getPos().getx());
	force.sety(p->getPos().gety());
	force -= anchor;
	float magnitude = force.magnitude();
	magnitude = (restLength-magnitude) * springConstant;
	
	force.normalise();
	force *= magnitude;
	p->addForce(force);
}

void AnchoredBungee::updateForce(Particle * p, float duration)
{
	Vector2d force;
	force.setx(p->getPos().getx());
	force.sety(p->getPos().gety());
	force -= anchor;
	float magnitude = force.magnitude();
	if(magnitude < restLength)
		return;
	magnitude -= restLength;
	magnitude *= springConstant;
	force.normalise();
	force *= -magnitude;
	p->addForce(force);
}
