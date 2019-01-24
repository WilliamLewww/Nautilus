#include "world.h"

void World::initialize() {
	position = Vector2(0, 0);
	width = 2000;
	height = 2000;

	dummyList.emplace_back(Vector2(500, 250), 75, 75);
	nautilus.initialize();
}

void World::update() {
	for (Dummy dummy : dummyList) { dummy.update(); }
	nautilus.update(timer.getTimeSeconds());

	for (Dummy& dummy : dummyList) {
		if (nautilus.anchorIsAlive()) {
			if (nautilus.checkAnchorCollision(dummy.getPosition(), dummy.getWidth(), dummy.getHeight())) {
				nautilus.anchorSetHook(dummy.getRectangleIndexAddr());
			}
		}
	}
}

void World::draw() {
	drawing.drawRect(position, width, height, baseColor);

	for (Dummy dummy : dummyList) { dummy.draw(); }
	nautilus.draw();
}