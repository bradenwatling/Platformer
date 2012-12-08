#pragma once
#include "SDL.h"

class Player
{
public:
	int x;
	int y;

	Player(SDL_Surface* dest);
	void draw();
	void moveRight();
	void moveLeft();
	void handleEvents(SDL_Event e);
	void startJump();
	void handle(Level* level);

private:
	SDL_Surface* screen;
	SDL_Surface* rightSprite;
	SDL_Surface* leftSprite;
	SDL_Surface* rightJumpSprite;
	SDL_Surface* leftJumpSprite;
	SDL_Rect playerRight[4];
	SDL_Rect playerLeft[4];
	int frames;
	int current;
	int xVelocity;
	double yVelocity;
	bool right;
	bool jumping;
	bool moveCamera;
};