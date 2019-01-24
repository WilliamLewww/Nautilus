#include "rectangle_index.h"

RectangleIndex createRectangleIndex(Vector2* position, int width, int height) {
	RectangleIndex index;
	index.position = position;
	index.width = width;
	index.height = height;

	return index;
}