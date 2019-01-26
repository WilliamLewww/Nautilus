#include "dummy.h"

Dummy::Dummy(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;

	rectangleIndex = createRectangleIndex(&this->position, &this->width, &this->height, &this->isRooted, &this->health, &this->mana);
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
	drawing.drawRect(position, width, height, color);
}