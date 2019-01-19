#pragma once
#include "core\vector2.h"
#include "core\input.h"
#include "core\configuration.h"

class Camera {
private:
	Vector2 position;
	int speed = 10, screenRatio = 12;
public:
	inline Camera() { position = Vector2(0, 0); };

	inline Vector2 *getPositionAddr() { return &position; };
	inline Vector2 getPosition() { return position; };

	inline void moveCamera() {
		if ((input.checkKeyDown(SDLK_LEFT) && !input.checkKeyDown(SDLK_RIGHT))) { position.x -= speed; }
		if ((!input.checkKeyDown(SDLK_LEFT) && input.checkKeyDown(SDLK_RIGHT))) { position.x += speed; }
		if ((input.checkKeyDown(SDLK_UP) && !input.checkKeyDown(SDLK_DOWN))) { position.y -= speed; }
		if ((!input.checkKeyDown(SDLK_UP) && input.checkKeyDown(SDLK_DOWN))) { position.y += speed; }

		if (input.getMouseX() >= 0 && input.getMouseX() < configuration.getScreenWidth() / screenRatio) { position.x -= speed; }
		if (input.getMouseX() <= configuration.getScreenWidth() && input.getMouseX() > configuration.getScreenWidth() - (configuration.getScreenWidth() / screenRatio)) { position.x += speed; }
		if (input.getMouseY() >= 0 && input.getMouseY() < configuration.getScreenHeight() / screenRatio) { position.y -= speed; }
		if (input.getMouseY() <= configuration.getScreenHeight() && input.getMouseY() > configuration.getScreenHeight() - (configuration.getScreenHeight() / screenRatio)) { position.y += speed; }
	}
};