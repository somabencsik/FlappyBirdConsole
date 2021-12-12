#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>

#include "Bird.h"
#include "Wall.h"
#include "keyboardInput.h"

Bird bird;
struct Wall walls[10];

struct winsize size;

void cls()
{
	printf("\e[1;1H\e[2J");
}

int processInput()
{
	if(u_kbhit())
	{
		return u_getchar();
	}
}

void update()
{
	int key = processInput();
	if (key == 3)
	{
		cls();
		printf("Exiting...\n");
		exit(0);
	}
	if (key == 32)
	{
		bird = bird.jump(bird);
	}
	if (key != 0)
	{
		printf("%d\n", key);
	}
		cls();
	bird = bird.update(bird);
	
	short lastUsed = 0;
	for (short i = 0; i < 10; ++i)
	{
		if (walls[i].x > 0)
		{
			walls[i] = walls[i].update(walls[i]);
			if (i > lastUsed)
			{
				lastUsed = i;
			}
		}
		else if (walls[i].x == 0)
		{
			for (short j = 0; j < 10; ++j)
			{
				if (walls[j].x > walls[lastUsed].x)
				{
					lastUsed = j;
				}
			}
			if (walls[lastUsed].x <= 60)
			{
				walls[i].x = 80;
				walls[i].height = rand() % (size.ws_row - 11);
			}
		}
	}
}

void render()
{
	cls();
	bird.render(bird);
	for (short i = 0; i < 10; ++i)
	{
		if (walls[i].x > 0)
		{
			walls[i].render(walls[i]);
		}
	}
}

void init()
{
	
	bird = createBird(5, 5, "Bird");
	
	walls[0] = createWall(80, rand() % (size.ws_row - 11), size.ws_row);

	for (short i = 1; i < 10; ++i)
	{
		walls[i] = createWall(0, rand() % (size.ws_row - 11), size.ws_row);
	}
	
}

int main()
{
	srand(time(NULL));
	ioctl( 0, TIOCGWINSZ, (char *) &size );

	init();
	
	while (1)
	{
		update();
		render();
		usleep(100 * 1000); 
	}
	return 0;
}
