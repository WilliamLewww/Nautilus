#include "nautilus.h"

void Nautilus::initialize() {
	position = Vector2(250, 250);
	width = 50;
	height = 75;
}

void Nautilus::createPath(int x, int y) {
	position = Vector2(x - (width / 2), y - (height / 2));
}

void Nautilus::update() {
	if (input.getRightButtonPress()) {
		createPath(input.getMouseX(), input.getMouseY());
	}
}

void Nautilus::draw() {
	drawing.drawRect(position, width, height);
}