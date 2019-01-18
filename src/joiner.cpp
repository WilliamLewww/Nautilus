#include "joiner.h"

Joiner joiner;

void Joiner::initialize() {
	world.initialize();
}

void Joiner::update() {
	world.update();
}

void Joiner::draw() {
	world.draw();
}