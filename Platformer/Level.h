#pragma once
#include "SDL.h"
#include <map>

struct rect
{
	int x;
	int y;
	int w;
	int h;
};

class Level
{
public:
	Level(SDL_Surface* scr);
	void update();
	bool move(int playerX, int xVelocity);
	int platform(int playerX, int& playerY, double yVelocity);

private:
	SDL_Surface* screen;
	SDL_Surface* bg;
	SDL_Rect camera;
	rect objects[1024];
	int numObjects;
};