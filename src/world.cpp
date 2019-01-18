#include "world.h"

void World::initialize() {
	position = Vector2(0, 0);
	width = 2000;
	height = 2000;

	nautilus.initialize();
}

void World::update() {
	nautilus.update();
}

void World::draw() {
	drawing.drawRect(position, width, height, baseColor);

	nautilus.draw();
}