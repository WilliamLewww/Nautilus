#include "gui.h"

GUI gui;

void GUI::linkAbilities(double* abilityA, double* abilityB, double* abilityC, double* abilityD) {
	abilityCooldown[0] = abilityA;
	abilityCooldown[1] = abilityB;
	abilityCooldown[2] = abilityC;
	abilityCooldown[3] = abilityD;
}

void GUI::initialize() {
	for (int x = 0; x < 4; x++) {
		abilityPosition[x] = Vector2((x * abilityWidth * 2.0) + (configuration.getScreenWidth() / 2.0) - (525.0 / 2.0), configuration.getScreenHeight() * 0.87);
	}
}

void GUI::update() {

}

void GUI::draw() {
	for (int x = 0; x < 4; x++) {
		std::string cooldown = std::to_string((int)ceil(*abilityCooldown[x]));
		if ((int)ceil(*abilityCooldown[x]) == 0) {
			drawing.drawRect(abilityPosition[x], abilityWidth, abilityHeight, colorAbilityValid);
		}
		else {
			drawing.drawRect(abilityPosition[x], abilityWidth, abilityHeight, colorAbilityInvalid);
		}
		drawing.drawText(cooldown.c_str(), abilityPosition[x] + Vector2(abilityWidth / 2, abilityHeight / 2), 4);
	}
}