#include "world.h"

void World::initialize() {
	position = Vector2(0, 0);
	width = 2000;
	height = 2000;

	dummyList.emplace_back(Vector2(500, 250), 75, 75);
	nautilus.initialize();
}

void World::update() {
	for (Dummy& dummy : dummyList) { dummy.update(timer.getTimeSeconds()); }
	nautilus.update(timer.getTimeSeconds());
	
	if (!nautilus.anchorIsHooked() && nautilus.anchorIsAlive()) {
		for (Dummy& dummy : dummyList) {
			if (nautilus.checkAnchorCollision(dummy.getRectangleIndexAddr())) {
				nautilus.anchorSetHook(dummy.getRectangleIndexAddr());
			}
		}
	}

	if (nautilus.riptideIsAlive()) {
		for (Dummy& dummy : dummyList) {
			if (nautilus.checkRiptideCollision(dummy.getRectangleIndexAddr())) {
				nautilus.handleRiptideCollision(dummy.getRectangleIndexAddr());
			}
		}
	}

	if (input.getRightButtonPress()) {
		bool selectedEntity = false;
		for (Dummy& dummy : dummyList) {
			if (checkMouseInRectangleIndex(dummy.getRectangleIndex())) {
				nautilus.setSelectedEntity(dummy.getRectangleIndexAddr());
				selectedEntity = true;
			}
		}
		if (selectedEntity == false) { nautilus.resetSelectedEntity(); }
	}
}

void World::draw() {
	drawing.drawRect(position, width, height, baseColor);

	for (Dummy dummy : dummyList) { dummy.draw(); }
	nautilus.draw();
}