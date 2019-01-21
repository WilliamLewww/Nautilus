#pragma once
#include "core/drawing.h"

class Dummy {
private:
	Vector2 position;
	int width, height;

	int color[3] = { 140, 87, 37 };
public:
	Dummy(Vector2 position, int width, int height);

	void update();
	void draw();
};