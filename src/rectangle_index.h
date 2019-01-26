#pragma once
#include "core/vector2.h"
#include "core/input.h"

struct RectangleIndex {
	Vector2 *position;
	int *width, *height;

	double *isRooted;
	double *health, *mana;
};

RectangleIndex createRectangleIndex(Vector2* position, int* width, int* height, double* isRooted, double* health, double* mana);
bool checkMouseInRectangleIndex(RectangleIndex rectangleIndex);