#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fstream>

#include "graphics.h"
#include "collisions.h"

int main()
{
	const float PHYS_TIMER = 0.002;
	const float FRAME_LENGTH = 0.04;
	Sprite cartman(7,0.6,2), kyle(14,0.6,1);
	Sprite ledge(8, 4, 1);
	ledge.setMass(0,true);
	cartman.readFromFile("Cartman.txt");
	kyle.readFromFile("Kyle.txt");
	ledge.readFromFile("basket.txt");
	ledge.setBounce(0);
	Scene myScene;
	myScene.add(cartman);
	myScene.add(kyle);
	//myScene.add(ledge);
	myScene.setLimits(30,5.5);

	AnchoredBungee spr(9,0.5,25.0,1.0);
	AnchoredBungee spr2(12,0.5,15.0,1.0);
	cartman.addForceGenerator(spr);
	kyle.addForceGenerator(spr2);

	

	timeval a;
	double t1,t2, t3;
	gettimeofday(&a, NULL);
	t1=t2=t3=a.tv_sec+(a.tv_usec/1000000.0);
			
	initscr();
	raw();
	noecho();
	timeout(1);

	//nodelay(stdscr, TRUE);
	
	for(char ch = '#'; ch != 'x';)
	{
		gettimeofday(&a, NULL);
		t2=a.tv_sec+(a.tv_usec/1000000.0);
		if(t2>=t3 + PHYS_TIMER)
		{
			t3=t2;
			myScene.runPhysics(PHYS_TIMER);	
			CollisionDetector cd;
			cd.detect(myScene.getSprites(), 10);		
		}
		if(t2>=t1 + FRAME_LENGTH)
		{	
			t1=t2;
			myScene.render();
		}	
		ch = getch();
		switch(ch)
		{
			case ERR: break;
			case 'w': cartman.addForce(Vector2d(0,-20/PHYS_TIMER));break;
			case 'a': cartman.addForce(Vector2d(-20/PHYS_TIMER,0));break;
			case 'd': cartman.addForce(Vector2d(20/PHYS_TIMER,0));break;	
			case ' ': cartman.removeForceGenerator(spr); break;			
		}	
	}
	endwin();
	return 0;
}


