#include "dummy.h"

Dummy::Dummy(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;

	rectangleIndex = createRectangleIndex(&this->position, this->width, this->height);
}

void Dummy::update() {

}

void Dummy::draw() {
	drawing.drawRect(position, width, height, color);
}