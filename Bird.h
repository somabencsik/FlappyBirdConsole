#ifndef BIRD_H
#define BIRD_H

typedef struct Bird Bird;
struct Bird
{
	short x;
	short y;
	char* birdChar;
	short jumpTime;

	Bird (*update)(Bird);
	void (*render)(Bird);
	Bird (*jump)(Bird);
};

Bird UpdateBird(Bird bird)
{
	if (bird.jumpTime > 0)
	{
		bird.y = bird.y - 1;
		bird.jumpTime = bird.jumpTime - 1;
	}
	else
	{
		bird.y = bird.y + 1;
	}
	return bird;
}

void RenderBird(Bird bird)
{
	for (short i = 0; i < bird.y; ++i)
	{
		printf("\n");
	}
	for (short i = 0; i < bird.x; ++i)
	{
		printf(" ");
	}
	printf("%s\n", bird.birdChar);
}

Bird jumpBird(Bird bird)
{
	bird.jumpTime = 5;
	return bird;
}

Bird createBird(int x, int y, char* birdChar)
{
	Bird result = {x, y, birdChar, 0};

	result.update = UpdateBird;
	result.render = RenderBird;
	result.jump = jumpBird;

	return result;
}

#endif
