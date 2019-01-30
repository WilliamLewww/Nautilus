#pragma once
#include "core/drawing.h"
#include "rectangle_index.h"
#include "stats.h"

class Dummy {
private:
	RectangleIndex rectangleIndex;
	StatusBar statusBar;

	Vector2 position;
	int width, height;

	double isRooted;
	int level = 1;
	double totalHealth = 1200;
	double health, mana;

	bool regenerate = false;
	double regenerateTimer = 0;

	int color[3] = { 140, 87, 37 };
	int colorRoot[3] = { 110, 57, 7 };
public:
	Dummy(Vector2 position, int width, int height);

	inline RectangleIndex* getRectangleIndexAddr() { return &rectangleIndex; };
	inline RectangleIndex getRectangleIndex() { return rectangleIndex; };

	inline Vector2 getPosition() { return position; };
	inline int getWidth() { return width; };
	inline int getHeight() { return height; };

	void update(float elapsedTimeSeconds);
	void draw();
};