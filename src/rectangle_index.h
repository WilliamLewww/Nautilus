#pragma once
#include "core/vector2.h"

struct RectangleIndex {
	Vector2* position;
	int width, height;
};

RectangleIndex createRectangleIndex(Vector2* position, int width, int height);