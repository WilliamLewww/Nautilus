#include "stats.h"

int colorStatusBarBackground[3] = { 159, 159, 159 };
int colorStatusBarHealth[3] = { 19, 173, 29 };
int colorStatusBarTick[3] = { 0, 0, 0 };

double getActualSpeed(Stats stats) {
	return stats.movement_speed * 0.5;
}

void upgradeStats(Stats& stats, StatsUpgrade statsUpgrade) {
	stats.health += statsUpgrade.health;
	stats.health_regen += statsUpgrade.health_regen;
	stats.attack_damage += statsUpgrade.attack_damage;
	stats.attack_speed += (statsUpgrade.attack_speed * stats.attack_speed);
	stats.armor += statsUpgrade.armor;
	stats.magic_resist += statsUpgrade.magic_resist;
}

void linkStatusBar(StatusBar& statusBar, double* totalHealth, double* health, double* mana, int* level) {
	statusBar.totalHealth = totalHealth;
	statusBar.health = health;
	statusBar.mana = mana;
	statusBar.level = level;
}

void updateStatusBar(StatusBar& statusBar, Vector2 position, int width) {
	statusBar.position = Vector2(position.x + (width / 2) - (statusBar.width / 2), position.y - 40);
	statusBar.healthWidth = (statusBar.width - 2.0) * (*statusBar.health / *statusBar.totalHealth);
	statusBar.healthLargeTickCount = (*statusBar.totalHealth / 1000);
	statusBar.healthLittleTickCount = (*statusBar.totalHealth / 100);
	statusBar.healthLittleTickRemainder = ((int)*statusBar.totalHealth % 100);
}

void drawStatusBar(StatusBar& statusBar) {
	drawing.drawRect(statusBar.position, statusBar.width, statusBar.height, colorStatusBarBackground);
	drawing.drawRect(statusBar.position + Vector2(1, 1), statusBar.healthWidth, statusBar.height - 2, colorStatusBarHealth);

	for (int x = 0; x < statusBar.healthLittleTickCount; x++) {
		Vector2 tickPosition = statusBar.position + Vector2((x + 1) * ((statusBar.width - 2.0) / (statusBar.healthLittleTickCount + 1.0)), 0);
		drawing.drawLine(tickPosition, tickPosition + Vector2(0, statusBar.height * 0.5), colorStatusBarTick);
	}
}