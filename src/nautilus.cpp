#include "nautilus.h"

void Nautilus::initialize() {
	position = Vector2(250, 250);
	width = 60;
	height = 75;

	setupStats();
}

void Nautilus::setupStats() {
	stats.health 		 			= 576.48;
	stats.health_regen   			= 8.5;
	stats.attack_damage  			= 61.0;
	stats.attack_speed   			= 0.613;
	stats.armor 		 			= 35.46;
	stats.magic_resist   			= 32.1;
	stats.movement_speed 			= 325;

	statsUpgrade.health 			= 86.0;
	statsUpgrade.health_regen 		= 0.55;
	statsUpgrade.attack_damage 		= 3.3;
	statsUpgrade.attack_speed 		= 0.01;
	statsUpgrade.armor 				= 3.75;
	statsUpgrade.magic_resist		= 1.25;
}

void Nautilus::update(float elapsedTimeSeconds) {
	if (input.getRightButtonPress()) {
		if (abs(center().x - input.getMouseXCamera()) > 3 && abs(center().y - input.getMouseYCamera()) > 3) {
			createPath(input.getMouseXCamera(), input.getMouseYCamera());
		}
	}

	followPath(elapsedTimeSeconds);
}

void Nautilus::createPath(int x, int y) {
	pathVertices.clear();

	pathVertices.push_back(center());
	pathVertices.push_back(Vector2(x, y));
}

void Nautilus::followPath(float elapsedTimeSeconds) {
	if (pathVertices.size() > 1) {
		Vector2 difference = pathVertices[1] - pathVertices[0];

		position.x += (difference.x / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;
		position.y += (difference.y / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;

		bool nextNode = false;

		if (!nextNode && difference.x > 0 && difference.y > 0) { if (center().x > pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x > 0 && difference.y < 0) { if (center().x > pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x < 0 && difference.y > 0) { if (center().x < pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x < 0 && difference.y < 0) { if (center().x < pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
	
		if (!nextNode && difference.x == 0 && difference.y > 0) { if (center().x == pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x == 0 && difference.y < 0) { if (center().x == pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x > 0 && difference.y == 0) { if (center().x > pathVertices[1].x && center().y == pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		if (!nextNode && difference.x < 0 && difference.y == 0) { if (center().x < pathVertices[1].x && center().y == pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
	}
}

void Nautilus::draw() {
	drawing.drawRect(position, width, height);

	if (pathVertices.size() > 1) {
		drawing.drawLineStrip(pathVertices, pathColor);
	}
}