#include "Level.h"
#include "Player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 432
#define BG_WIDTH 1024
#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 44

Player::Player(SDL_Surface* dest)
{
	screen = dest;

	rightSprite = SDL_LoadBMP("GFX/mario_right.bmp");
	leftSprite = SDL_LoadBMP("GFX/mario_left.bmp");
	rightJumpSprite = SDL_LoadBMP("GFX/mario_right_jump.bmp");
	leftJumpSprite = SDL_LoadBMP("GFX/mario_left_jump.bmp");

	SDL_SetColorKey(rightSprite, SDL_SRCCOLORKEY, SDL_MapRGB(rightSprite->format, 255, 255, 255));
	SDL_SetColorKey(leftSprite, SDL_SRCCOLORKEY, SDL_MapRGB(leftSprite->format, 255, 255, 255));
	SDL_SetColorKey(rightJumpSprite, SDL_SRCCOLORKEY, SDL_MapRGB(rightJumpSprite->format, 255, 255, 255));
	SDL_SetColorKey(leftJumpSprite, SDL_SRCCOLORKEY, SDL_MapRGB(leftJumpSprite->format, 255, 255, 255));

	x = 0;
	y = PLAYER_HEIGHT;
	yVelocity = 0;
	xVelocity = 0;
	frames = 3;
	current = 0;
	right = true;
	jumping = false;
	moveCamera = false;

	playerRight[0].x = 0;
	playerRight[0].y = 0;
	playerRight[0].w = PLAYER_WIDTH;
	playerRight[0].h = PLAYER_HEIGHT;
	
	playerRight[1].x = PLAYER_WIDTH;
	playerRight[1].y = 0;
	playerRight[1].w = PLAYER_WIDTH;
	playerRight[1].h = PLAYER_HEIGHT;

	playerRight[2].x = PLAYER_WIDTH * 2;
	playerRight[2].y = 0;
	playerRight[2].w = PLAYER_WIDTH;
	playerRight[2].h = PLAYER_HEIGHT;

	playerRight[3].x = PLAYER_WIDTH * 3;
	playerRight[3].y = 0;
	playerRight[3].w = PLAYER_WIDTH;
	playerRight[3].h = PLAYER_HEIGHT;

	playerLeft[0].x = 0;
	playerLeft[0].y = 0;
	playerLeft[0].w = PLAYER_WIDTH;
	playerLeft[0].h = PLAYER_HEIGHT;
	
	playerLeft[1].x = PLAYER_WIDTH;
	playerLeft[1].y = 0;
	playerLeft[1].w = PLAYER_WIDTH;
	playerLeft[1].h = PLAYER_HEIGHT;

	playerLeft[2].x = PLAYER_WIDTH * 2;
	playerLeft[2].y = 0;
	playerLeft[2].w = PLAYER_WIDTH;
	playerLeft[2].h = PLAYER_HEIGHT;

	playerLeft[3].x = PLAYER_WIDTH * 3;
	playerLeft[3].y = 0;
	playerLeft[3].w = PLAYER_WIDTH;
	playerLeft[3].h = PLAYER_HEIGHT;
}

void Player::draw()
{
	SDL_Rect pos;

	pos.x = x;
	pos.y = y;
	if(right)
	{
		if(jumping)
		{
			SDL_BlitSurface(rightJumpSprite, &playerRight[0], screen, &pos);
		}
		else
		{
			SDL_BlitSurface(rightSprite, &playerRight[current], screen, &pos);
		}
	}
	else
	{
		if(jumping)
		{
			SDL_BlitSurface(leftJumpSprite, &playerLeft[0], screen, &pos);
		}
		else
		{
			SDL_BlitSurface(leftSprite, &playerLeft[current], screen, &pos);
		}
	}

	SDL_Flip(screen);

	if(current < frames && xVelocity != 0 && !jumping)
	{
		++current;
	}
	else
	{
		current = 0;
	}
}

void Player::moveRight()
{
	right = true;
	xVelocity = 2;
}

void Player::moveLeft()
{
	right = false;
	xVelocity = -2;
}

void Player::handleEvents(SDL_Event e)
{
		switch(e.type)
		{
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						startJump();
						break;

					case SDLK_RIGHT:
						moveRight();
						break;

					case SDLK_LEFT:
						moveLeft();
						break;
				}
				break;
			case SDL_KEYUP:
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
					case SDLK_RIGHT:
						xVelocity = 0;
						break;
				}
		}
}

void Player::startJump()
{
	if(!jumping)
	{
		yVelocity = -5.0;
	}
}

void Player::handle(Level* level)
{
	if(!level->move(x, xVelocity))
	{
		x += xVelocity;
		//Keep player on the screen horizontally
		x = (x < 0) ? 0 : x;
		x = (x > (SCREEN_WIDTH - PLAYER_WIDTH)) ? (SCREEN_WIDTH - PLAYER_WIDTH) : x;
	}

	y += yVelocity;

	if(y < (SCREEN_HEIGHT - PLAYER_HEIGHT) && yVelocity < 5.0) // y is above the bottom of the screen
	{
		yVelocity += 0.1;
		jumping = true;
	}

	bool platform = level->platform(x, y, yVelocity);

	if(y > (SCREEN_HEIGHT - PLAYER_HEIGHT) || platform) // y is below the bottom of the screen or theres a platform
	{
		jumping = false;
		yVelocity = 0;
		y = platform ? y : (SCREEN_HEIGHT - PLAYER_HEIGHT); // reset player to bottom of the screen
	}
}
