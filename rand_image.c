/* cc rand_image.c -Wall -ansi -pedantic -Wextra -o rand_image && ./rand_image*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IMAGE_WIDTH 500
#define IMAGE_HEIGHT 500
#define STROKE 2
#define MAX_SHAPES 16
#define OPACITY 1.0

#define MIN(a,b) ((a) < (b) ? (a) : (b))

static int randrange(int max)
{
	return rand() % (max + 1);
}

static char *rand_color()
{
	const char *letters = "0123456789ABCDEF";
	char *color = malloc(8);
	int i;
	color[0] = '#';
	for (i = 1; i < 6; i++) {
		color[i] = letters[randrange(16)];
	}
	return color;
}

#define BACKGROUND (rand_color())
static void rand_shape(FILE *fp)
{
	int shape;
	int i;

	shape = randrange(4);
	if (!shape) {
		fprintf(fp,
			"<rect x='%d' y='%d' width='%d' height='%d'",
			randrange(IMAGE_WIDTH),
			randrange(IMAGE_HEIGHT),
			randrange(IMAGE_WIDTH / 2), randrange(IMAGE_WIDTH / 2));
	} else if (shape == 1) {
		fprintf(fp, "<circle cx='%d' cy='%d' r='%d'",
			randrange(IMAGE_WIDTH),
			randrange(IMAGE_HEIGHT),
			randrange(MIN(IMAGE_WIDTH, IMAGE_HEIGHT) / 4));
	} else if (shape == 2) {
		fprintf(fp, "<ellipse cx='%d' cy='%d' rx='%d' ry='%d'",
			randrange(IMAGE_WIDTH),
			randrange(IMAGE_HEIGHT),
			randrange(IMAGE_WIDTH / 2), randrange(IMAGE_WIDTH / 2));
	} else {
		fprintf(fp, "<polyline points='");

		for (i = 0; i < randrange(6) + 3; i++) {
			fprintf(fp, "%d %d, ", randrange(IMAGE_WIDTH),
				randrange(IMAGE_WIDTH));
		}
		fprintf(fp, "'");
	}

	if (!randrange(2) && shape != 3) {
		fprintf(fp, " fill='%s' fill-opacity='%g'/>", rand_color(),
			OPACITY);
	} else {
		fprintf(fp, " fill='none' stroke-width='%d'", STROKE);
		fprintf(fp, " stroke='%s' stroke-opacity='%g'/>", rand_color(),
			OPACITY);
	}
}

static void write(const char *filename)
{
	FILE *fp = fopen(filename, "w");
	int i;
	fprintf(fp,"<?xml version='1.0'?><svg width='%d' height='%d'>\
		<rect height='%d' width='%d' fill='%s'/>",
		IMAGE_WIDTH,IMAGE_HEIGHT, IMAGE_HEIGHT, IMAGE_WIDTH, BACKGROUND);

	for (i = 0; i < MAX_SHAPES; ++i) {
		rand_shape(fp);
	}

	fprintf(fp,"</svg>");
	fclose(fp);
}

int main()
{
    time_t seconds;
    const char *filename = "test.svg";
    time(&seconds);
    srand((unsigned int)seconds);
    write(filename);
    return 0;
}
