#pragma once
#include "core/vector2.h"
#include "core/drawing.h"

struct Stats {
	double health, health_regen;
	double mana, mana_regen;
	double attack_damage, attack_speed;
	double ability_power;
	double armor, magic_resist;
	double movement_speed;
};

struct StatsUpgrade {
	double health, health_regen;
	double mana, mana_regen;
	double attack_damage, attack_speed;
	double armor, magic_resist;
};

struct StatusBar {
	double *totalHealth;
	double *health, *mana;
	int* level;

	int width = 80, height = 20;
	Vector2 position;
	double healthWidth;

	int healthLittleTickCount;
	double healthLittleTickRemainder;
	int healthLargeTickCount;
};

double getActualSpeed(Stats stats);
void upgradeStats(Stats& stats, StatsUpgrade statsUpgrade);

void linkStatusBar(StatusBar& statusBar, double* totalHealth, double* health, double* mana, int* level);
void updateStatusBar(StatusBar& statusBar, Vector2 position, int width);
void drawStatusBar(StatusBar& statusBar);