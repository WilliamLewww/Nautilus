#pragma once
#include <vector>
#include "core/drawing.h"
#include "core/timer.h"
#include "nautilus.h"
#include "dummy.h"

class World {
private:
	Vector2 position;
	int width, height;

	int baseColor[3] = { 63, 137, 63 };

	Nautilus nautilus;
	std::vector<Dummy> dummyList;

	void updateNautilus();
public:
	void initialize();
	void update();
	void draw();
};