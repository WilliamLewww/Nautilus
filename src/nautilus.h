#pragma once
#include <vector>
#include "core/drawing.h"
#include "core/vector2.h"
#include "core/input.h"

class Nautilus {
private:
	Vector2 position;
	int width, height;

	std::vector<Vector2> pathVertices;
public:
	void initialize();

	void createPath(int x, int y);
	void update();
	void draw();
};