#include <stdio.h>

#include "Bird.h"
#include "Wall.h"
#include "keyboardInput.h"

Bird bird;
Wall wall;

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
	wall = wall.update(wall);
}

void render()
{
	cls();
	bird.render(bird);
	wall.render(wall);
}

int main()
{
	bird = createBird(5, 5, "Bird");
	wall = createWall(50, 10);
	while (1)
	{
		update();
		render();
		usleep(100 * 1000); 
	}
	return 0;
}
