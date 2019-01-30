#include "dummy.h"

Dummy::Dummy(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;

	rectangleIndex = createRectangleIndex(&this->position, &this->width, &this->height, &this->isRooted, &this->health, &this->mana);
	health = totalHealth;
	mana = 100;

	linkStatusBar(statusBar, &totalHealth, &health, &mana, &level);
}

void Dummy::update(float elapsedTimeSeconds) {
	if (isRooted == 0) { 

	}
	else {
		if (isRooted > 0) {
			if (isRooted - elapsedTimeSeconds <= 0) { isRooted = 0; }
			else { isRooted -= elapsedTimeSeconds; }
		}
	}
}

void Dummy::draw() {
	if (isRooted == 0) { drawing.drawRect(position, width, height, color); }
	else { drawing.drawRect(position, width, height, colorRoot); }

	updateStatusBar(statusBar, position, width);
	drawStatusBar(statusBar);
}