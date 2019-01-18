#pragma once
#include "core/drawing.h"
#include "nautilus.h"

class World {
private:
	Vector2 position;
	int width, height;

	int baseColor[3] = { 63, 137, 63 };

	Nautilus nautilus;
public:
	void initialize();
	void update();
	void draw();
};