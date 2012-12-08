#include "Level.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 432
#define BG_WIDTH 1024
#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 44

Level::Level(SDL_Surface* scr)
{
	screen = scr;

	camera.x = 0;
	camera.y = 0;
	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;

	objects[0].x = 0;
	objects[0].y = SCREEN_HEIGHT - 10;
	objects[0].h = 10;
	objects[0].w = BG_WIDTH;

	objects[1].x = 400;
	objects[1].y = SCREEN_HEIGHT - 100;
	objects[1].h = 10;
	objects[1].w = 100;

	objects[2].x = 600;
	objects[2].y = SCREEN_HEIGHT - 150;
	objects[2].h = 10;
	objects[2].w = 100;

	objects[3].x = 800;
	objects[3].y = SCREEN_HEIGHT - 200;
	objects[3].h = 10;
	objects[3].w = 100;

	numObjects = 4;

	bg = SDL_LoadBMP("GFX/bg.bmp");
}

void Level::update()
{
	SDL_BlitSurface(bg, &camera, screen, NULL);

	for(int i = 0; i < numObjects; ++i)
	{
		SDL_Rect rect;
		rect.x = objects[i].x;
		rect.y = objects[i].y;
		rect.w = objects[i].w;
		rect.h = objects[i].h;
		SDL_FillRect(screen, &rect, 100);
	}
}

bool Level::move(int playerX, int xVelocity)
{
	if(/*Move right*/(xVelocity > 0 && camera.x < (BG_WIDTH - SCREEN_WIDTH) && playerX >= (SCREEN_WIDTH *  2 / 3)) ||
		/*Move left*/ (xVelocity < 0 && camera.x > 0 && playerX <= (SCREEN_WIDTH * 1 / 3)))
	{
		camera.x += xVelocity;
		for(int i = 0; i < numObjects; ++i)
		{
			objects[i].x -= xVelocity;
		}
		return true;
	}
	return false;
}

int Level::platform(int playerX, int& playerY, double yVelocity)
{
	if(yVelocity <= 0)
	{
		return false;
	}

	for(int i = 0; i < numObjects; ++i)
	{
		if(/*Vertically*/(playerY + PLAYER_HEIGHT) >= objects[i].y && (playerY + PLAYER_HEIGHT) <= (objects[i].y + objects[i].h) &&
			/*Horizontally*/(playerX + PLAYER_WIDTH) >= objects[i].x && playerX <= (objects[i].x + objects[i].w)) 
		{
			//Reset player to top of platform
			playerY = objects[i].y - PLAYER_HEIGHT;
			return true;
		}
	}

	return false;
}