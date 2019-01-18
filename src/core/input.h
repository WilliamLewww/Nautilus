#pragma once
#include <vector>
#include <algorithm>
#include <SDL2\SDL.h>
#include "vector2.h"
#include "configuration.h"

class Input {
private:
	std::vector<SDL_Keycode> keyList;
	std::vector<SDL_Keycode> pressKeyList;

	bool leftButtonDown, leftButtonPress;
	bool rightButtonDown, rightButtonPress;
	bool middleMouseDown, middleMousePress;
	bool scrollUp, scrollDown;
	int mouseX, mouseY;

	int controllerPad;
	std::vector<int> controllerList;
	std::vector<int> controllerPressList;

public:
	std::vector<SDL_Keycode> returnKeyList();

	inline int getMouseX() { return mouseX; };
	inline int getMouseY() { return mouseY; };
	
	inline bool getLeftButtonPress() { return leftButtonPress; };
	inline bool getRightButtonPress() { return rightButtonPress; };

	inline bool getScrollUp() { return scrollUp; };
	inline bool getScrollDown() { return scrollDown; };
	
	bool checkKeyDown(SDL_Keycode Keycode);
	bool checkButtonDown(int buttonCode);
	int getControllerPadInput();
	int getKeyListSize();

	void getKeyTrigger(SDL_Event event);
	void clearExpiredInput();
	void getMouseTrigger(SDL_Event event);
	void setupController();
	bool checkMouseOnEntity(Vector2 entityPosition, int entityWidth, int entityHeight);
};

extern Input input;