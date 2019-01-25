#include "rectangle_index.h"

RectangleIndex createRectangleIndex(Vector2* position, int* width, int* height) {
	RectangleIndex index;
	index.position = position;
	index.width = width;
	index.height = height;

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