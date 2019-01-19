#include "stats.h"

void upgradeStats(Stats& stats, StatsUpgrade statsUpgrade) {
	stats.health += statsUpgrade.health;
	stats.health_regen += statsUpgrade.health_regen;
	stats.attack_damage += statsUpgrade.attack_damage;
	stats.attack_speed += (statsUpgrade.attack_speed * stats.attack_speed);
	stats.armor += statsUpgrade.armor;
	stats.magic_resist += statsUpgrade.magic_resist;
}