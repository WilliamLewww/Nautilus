#include "dummy.h"

Dummy::Dummy(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;

	rectangleIndex = createRectangleIndex(&this->position, &this->width, &this->height, &this->isRooted, &this->health, &this->mana);
	health = totalHealth;
	mana = 100;

	linkStatusBar(statusBar, &totalHealth, &health, &mana, &shield, &level);
}

bool Dummy::checkCollision(Vector2 position) {
	if (this->position.x + width >= position.x &&
		this->position.x <= position.x &&
		this->position.y + height >= position.y &&
		this->position.y <= position.y) {

		return true;
	}
	
	return false;
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

	if (health < 0) { regenerate = true; }
	if (regenerate) {
		if (regenerateTimer >= 0.25) {
			if (health + 100 >= totalHealth) {
				health = totalHealth;
				regenerate = false;
			}
			else {
				health += 100;
			}
			regenerateTimer = 0.0;
		}
		else {
			regenerateTimer += elapsedTimeSeconds;
		}
	}
}

void Dummy::draw() {
	if (isRooted == 0) { drawing.drawRect(position, width, height, color); }
	else { drawing.drawRect(position, width, height, colorRoot); }

	updateStatusBar(statusBar, position, width);
	drawStatusBar(statusBar);
}