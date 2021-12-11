#ifndef WALL_H
#define WALL_H

typedef struct Wall Wall;
struct Wall
{
	int x;
	int height;

	Wall (*update)(Wall);
	void (*render)(Wall);
};

void WallRender(Wall wall)
{
	for (short y = 0; y < wall.height; ++y)
	{
		printf("\033[%d;%dH", (y), (wall.x-10));
		printf("P\n");
	}
}

Wall WallUpdate(Wall wall)
{
	wall.x = wall.x - 1;
	return wall;
}

Wall createWall(int x, int height)
{
	Wall result = {x, height};

	result.update = WallUpdate;
	result.render = WallRender;

	return result;
}
#endif
