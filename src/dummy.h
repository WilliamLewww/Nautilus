#pragma once
#include "core/drawing.h"
#include "rectangle_index.h"

class Dummy {
private:
	RectangleIndex rectangleIndex;

	Vector2 position;
	int width, height;

	int color[3] = { 140, 87, 37 };
public:
	Dummy(Vector2 position, int width, int height);

	inline RectangleIndex* getRectangleIndexAddr() { return &rectangleIndex; };
	inline RectangleIndex getRectangleIndex() { return rectangleIndex; };

	inline Vector2 getPosition() { return position; };
	inline int getWidth() { return width; };
	inline int getHeight() { return height; };

	void update();
	void draw();
};