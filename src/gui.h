#pragma once
#include <cmath>
#include <string>
#include "core/vector2.h"
#include "core/drawing.h"
#include "core/configuration.h"

class GUI {
private:
	int abilityWidth = 75, abilityHeight = 75;
	int colorAbilityValid[3] = { 0, 255, 0 };
	int colorAbilityInvalid[3] = { 255, 0, 0 };

	double *abilityCooldown[4];
	Vector2 abilityPosition[4];
public:
	void linkAbilities(double* abilityA, double* abilityB, double* abilityC, double* abilityD);
	void initialize();
	void update();
	void draw();
};

extern GUI gui;