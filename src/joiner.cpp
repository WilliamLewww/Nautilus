#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	camera = Camera();
	input.linkCamera(camera.getPositionAddr());
	world.initialize();
}

void Joiner::update() {
	camera.moveCamera();
	world.update();
}

void Joiner::draw() {
	glPushMatrix();
	glTranslatef(-camera.getPosition().x, -camera.getPosition().y, 0);
	world.draw();
	glPopMatrix();
}