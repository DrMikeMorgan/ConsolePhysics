#include "graphics.h"
#include <fstream>
#include <sstream>
#include <ncurses.h>


void Sprite::readFromFile(std::string fileName)
{
	if(strings.size() != 0)
		strings.resize(0);
	std::ifstream is;
  	is.open(fileName.c_str(), std::ios::binary);

	width = 0;
	while(is)
	{
		int first, last;
		bool wMeasure = false;
		char reddit = ' ';
		std::ostringstream str;
		for(int i=0; is ; ++i)
		{
			is.get(reddit);
			if(reddit == '\n')
				break;
			str << reddit;
			if(reddit != ' ')
			{
				if(!wMeasure)
				{
					first = i;
					wMeasure = true;
				}
				last = i;
			}
		}
		std::string stringy = str.str();
		if(last < stringy.length()-1)
			stringy.erase(last+1);
		strings.push_back(stringy);
		if((last-first)>width)
			width = last;
	}
	height = strings.size();
}

void Scene::runPhysics(float time)
{
	for(int i=0; i<sprites.size(); ++i)
	{
		sprites[i]->integrate(time);
	}
}

void Scene::render()
{
	clear();
	for(int i=0; i<sprites.size(); ++i)
	{
		for(int j=0; j<sprites[i]->strings.size(); ++j)
		{
			float height = sprites[i]->getPos().gety()*spacesPerMetre - sprites[i]->height/2 + j;
			if(height < 0 || height > limy * spacesPerMetre)
				continue;
			for(int k=0; k<sprites[i]->strings[j].size(); ++k)
			{
				if(sprites[i]->strings[j][k] == ' ')
					continue;
				float width = sprites[i]->getPos().getx()*spacesPerMetre - sprites[i]->width/2 + k;
				if(width < 0 || width > limx * spacesPerMetre)
					continue;				
				move(height, width);		
				waddch(stdscr, sprites[i]->strings[j][k]);
			}		
		}
		mvprintw(1,1,"%f",sprites[0]->getPos().getx());
		mvprintw(2,1,"%f",sprites[0]->getPos().gety());
	}
}
