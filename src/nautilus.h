#pragma once
#include <vector>
#include <cmath>
#include "core/drawing.h"
#include "core/vector2.h"
#include "core/input.h"
#include "stats.h"

struct Anchor {
	Vector2 position, direction, hintPosition;
	int width = 40, height = 40;
	float distance = 0;

	bool alive = false;
	bool hint = false;

	bool hooked = false;
	bool bounce = false;
	Vector2* hookedPosition;
	int hookedWidth, hookedHeight;

	int anchorColor[3] = { 99, 64, 61 };
	int chainColor[3] = { 102, 94, 90 };
};

class Nautilus {
private:
	Stats stats;
	StatsUpgrade statsUpgrade;

	Vector2 position;
	int width = 60, height = 75;

	Vector2 clickPosition;
	int clickAlpha = 0;

	bool isRooted = false;

	int color[3] = { 119, 84, 81 };
	int pathColor[3] = { 92, 185, 196 };
	int clickColor[3] = { 0, 0, 0 };

	std::vector<Vector2> pathVertices;

	bool queueDredgeLine = false, cancelDredgeLine = false;
	Anchor anchor;

	inline Vector2 center() { return Vector2(position.x + (width / 2), position.y + (height / 2)); };

	void setupStats();

	void createPath(int x, int y);
	void followPath(float elapsedTimeSeconds);

	void initializeDredgeLine(int x, int y);
	void castDredgeLine(float elapsedTimeSeconds);

	void initializeTitansWrath();
	void castTitansWrath();

	void initializeRiptide();
	void castRiptide();

	void initializeDepthCharge(Vector2* position);
	void castDepthCharge();
public:
	inline bool anchorIsAlive() { return anchor.alive; };
	inline void anchorSetHook(Vector2* hookedPosition, int hookedWidth, int hookedHeight) { 
		anchor.hookedPosition = hookedPosition; 
		anchor.hookedWidth = hookedWidth;
		anchor.hookedHeight = hookedHeight;

		anchor.hooked = true; 
	};
	bool checkAnchorCollision(Vector2 position, int width, int height);

	void initialize();
	void resetPath();

	void update(float elapsedTimeSeconds);

	void draw();
	void drawDebug();
};