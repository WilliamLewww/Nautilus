#pragma once
#include <vector>
#include <cmath>
#include "core/drawing.h"
#include "core/vector2.h"
#include "core/input.h"
#include "stats.h"

class Nautilus {
private:
	Stats stats;
	StatsUpgrade statsUpgrade;

	Vector2 position;
	int width, height;

	int color[3] = { 119, 84, 81 };
	int pathColor[3] = { 92, 185, 196 };

	std::vector<Vector2> pathVertices;

	inline Vector2 center() { return Vector2(position.x + (width / 2), position.y + (height / 2)); };

	void setupStats();

	void createPath(int x, int y);
	void followPath(float elapsedTimeSeconds);
public:
	void initialize();

	void update(float elapsedTimeSeconds);
	void draw();
};