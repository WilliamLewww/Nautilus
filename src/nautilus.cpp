#include "nautilus.h"

void Nautilus::initialize() {
	position = Vector2(250, 250);
	setupStats();
}

void Nautilus::setupStats() {
	stats.health 		 			= 576.48;
	stats.mana						= 200;
	stats.health_regen   			= 8.5;
	stats.mana_regen   				= 7.45;
	stats.attack_damage  			= 61.0;
	stats.attack_speed   			= 0.613;
	stats.armor 		 			= 35.46;
	stats.magic_resist   			= 32.1;
	stats.movement_speed 			= 325;

	statsUpgrade.health 			= 86.0;
	statsUpgrade.mana				= 50.0;
	statsUpgrade.health_regen 		= 0.55;
	statsUpgrade.mana_regen   		= 0.7;
	statsUpgrade.attack_damage 		= 3.3;
	statsUpgrade.attack_speed 		= 0.01;
	statsUpgrade.armor 				= 3.75;
	statsUpgrade.magic_resist		= 1.25;
}

void Nautilus::update(float elapsedTimeSeconds) {
	if (input.getRightButtonPress()) {
		if (abs(center().x - input.getMouseXCamera()) > 3 || abs(center().y - input.getMouseYCamera()) > 3) {
			createPath(input.getMouseXCamera(), input.getMouseYCamera());

			clickPosition = Vector2(input.getMouseXCamera(), input.getMouseYCamera());
			clickAlpha = 255;
		}
	}

	if (clickAlpha > 0) {
		if (clickAlpha - 25 < 0) { clickAlpha = 0; }
		else { clickAlpha -= 25; }
	}

	if (input.checkKeyDown(SDLK_q)) { 
		if (input.getRightButtonPress()) {
			queueDredgeLine = false;
			cancelDredgeLine = true;
			anchor.hint = false;
		}
		if (!cancelDredgeLine) {
			queueDredgeLine = true;

			anchor.hint = true;
			Vector2 difference = Vector2(input.getMouseXCamera(), input.getMouseYCamera()) - center();
			anchor.hintPosition = center() + Vector2((difference.x / (abs(difference.x) + abs(difference.y))), (difference.y / (abs(difference.x) + abs(difference.y)))) * 325;
		}
	}
	else { anchor.hint = false; cancelDredgeLine = false; }
	if (!anchor.alive && queueDredgeLine && !input.checkKeyDown(SDLK_q)) { anchor.alive = true; queueDredgeLine = false; initializeDredgeLine(input.getMouseXCamera(), input.getMouseYCamera()); }
	if (anchor.alive) {	castDredgeLine(elapsedTimeSeconds); }

	if (!isRooted) { followPath(elapsedTimeSeconds); }
}

void Nautilus::initializeDredgeLine(int x, int y) {
	isRooted = true;
	anchor.anchorPosition = Vector2(center().x - (anchor.anchorWidth / 2), center().y - (anchor.anchorHeight / 2));
	anchor.anchorDirection = Vector2(x, y) - center();
	anchor.distance = 0;
}

void Nautilus::castDredgeLine(float elapsedTimeSeconds) {
	float movementX = (anchor.anchorDirection.x / (abs(anchor.anchorDirection.x) + abs(anchor.anchorDirection.y))) * (getActualSpeed(stats) * 2.8) * elapsedTimeSeconds;
	float movementY = (anchor.anchorDirection.y / (abs(anchor.anchorDirection.x) + abs(anchor.anchorDirection.y))) * (getActualSpeed(stats) * 2.8) * elapsedTimeSeconds;

	anchor.anchorPosition.x += movementX;
	anchor.anchorPosition.y += movementY;

	anchor.distance += abs(movementX) + abs(movementY);

	if (anchor.distance > 325) {
		anchor.alive = false;
		isRooted = false;
	}
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
	drawDebug();

	drawing.drawCircleFill(clickPosition, 12, clickColor, clickAlpha);
	drawing.drawRect(position, width, height);

	if (anchor.hint) {
		drawing.drawLine(center(), anchor.hintPosition, anchor.chainColor);
	}

	if (anchor.alive) {
		drawing.drawLine(center(), anchor.anchorPosition + Vector2(anchor.anchorWidth / 2, anchor.anchorHeight / 2), anchor.chainColor);
		drawing.drawRect(anchor.anchorPosition, anchor.anchorWidth, anchor.anchorHeight, anchor.anchorColor);
	}
}

void Nautilus::drawDebug() {
	if (pathVertices.size() == 2) {
		drawing.drawLine(center(), pathVertices[1], pathColor);
	}
}