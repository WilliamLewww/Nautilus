#pragma once

struct Stats {
	double health, health_regen;
	double attack_damage, attack_speed;
	double armor, magic_resist;
	double movement_speed;
};

struct StatsUpgrade {
	double health, health_regen;
	double attack_damage, attack_speed;
	double armor, magic_resist;
};

double getActualSpeed(Stats stats);
void upgradeStats(Stats& stats, StatsUpgrade statsUpgrade);