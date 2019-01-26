#include "rectangle_index.h"

RectangleIndex createRectangleIndex(Vector2* position, int* width, int* height, double* isRooted, double* health, double* mana) {
	RectangleIndex index;
	index.position = position;
	index.width = width;
	index.height = height;
	index.isRooted = isRooted;
	index.health = health;
	index.mana = mana;

	return index;
}

bool checkMouseInRectangleIndex(RectangleIndex rectangleIndex) {
	if (input.getMouseXCamera() > rectangleIndex.position->x &&
		input.getMouseXCamera() < rectangleIndex.position->x + *rectangleIndex.width &&
		input.getMouseYCamera() > rectangleIndex.position->y &&
		input.getMouseYCamera() < rectangleIndex.position->y + *rectangleIndex.height) {

		return true;
	}

	return false;
}