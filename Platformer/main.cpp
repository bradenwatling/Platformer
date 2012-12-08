#include "Level.h"
#include "Player.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 432
#define BG_WIDTH 1024
#define PLAYER_WIDTH 30
#define PLAYER_HEIGHT 44

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(1, 20);
	SDL_WM_SetCaption("Platformer", NULL);
}

int main(int argc, char* args[])
{
	bool quit = false;
	SDL_Event e;

	init();
    
	SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

	Level level(screen);

	Player player(screen);

	while(!quit)
	{
		level.update();

		while(SDL_PollEvent(&e))
		{
			player.handleEvents(e);
			quit = (e.type == SDL_QUIT) ? true : false;
		}

		player.handle(&level);
		player.draw();
		SDL_FreeSurface(screen);
	}

    SDL_Quit();
    
    return 0;
}
