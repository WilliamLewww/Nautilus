#pragma once
#include "core\vector2.h"
#include "core\input.h"

class Camera {
private:
	Vector2 position;
	int speed = 10;
public:
	inline Camera() { position = Vector2(0, 0); };

	inline Vector2 *getPositionAddr() { return &position; };
	inline Vector2 getPosition() { return position; };

	inline void moveCamera() {
		if ((input.checkKeyDown(SDLK_LEFT) && !input.checkKeyDown(SDLK_RIGHT))) {
			position.x -= speed;
		}

		if ((!input.checkKeyDown(SDLK_LEFT) && input.checkKeyDown(SDLK_RIGHT))) {
			position.x += speed;
		}

		if ((input.checkKeyDown(SDLK_UP) && !input.checkKeyDown(SDLK_DOWN))) {
			position.y -= speed;
		}

		if ((!input.checkKeyDown(SDLK_UP) && input.checkKeyDown(SDLK_DOWN))) {
			position.y += speed;
		}
	}
};