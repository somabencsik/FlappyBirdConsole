#ifndef WALL_H
#define WALL_H

typedef struct Wall Wall;
struct Wall
{
	short x;
	short height;
	short maxHeight;

	Wall (*update)(Wall);
	void (*render)(Wall);
};

void WallRender(Wall wall)
{
	for (short y = 0; y < wall.height; ++y)
	{
		printf("\033[%d;%dH", (y), (wall.x));
		printf("X\n");
	}
	for (short y = wall.height + 10; y < wall.maxHeight; ++y)
	{
		printf("\033[%d;%dH", (y), (wall.x));
   		printf("X\n");
	}
}

Wall WallUpdate(Wall wall)
{
	wall.x = wall.x - 1;
	return wall;
}

Wall createWall(short x, short height, short terminalSize)
{
	Wall result = {x, height, terminalSize};

	result.update = WallUpdate;
	result.render = WallRender;

	return result;
}
#endif
