#pragma once
#include "core/drawing.h"

class Dummy {
private:
	Vector2 position;
	int width, height;

	int color[3] = { 140, 87, 37 };
public:
	Dummy(Vector2 position, int width, int height);

	inline Vector2* getPositionAddr() { return &position; };
	inline Vector2 getPosition() { return position; };
	inline int getWidth() { return width; };
	inline int getHeight() { return height; };

	void update();
	void draw();
};