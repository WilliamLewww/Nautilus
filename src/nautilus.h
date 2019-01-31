#pragma once
#include <map>
#include <cmath>
#include <vector>
#include "core/drawing.h"
#include "core/vector2.h"
#include "core/vector3.h"
#include "core/input.h"
#include "rectangle_index.h"
#include "stats.h"
#include "gui.h"

struct NautilusDurationsParent {
	double auto_attack_current_frame = 0.0;
	double staggering_blow[5] = { 0.5, 0.75, 1, 1.25, 1.5 };
	double titans_wrath = 6.0;
	double titans_wrath_effect = 1.0;
	double depth_charge[3] = { 1, 1.5, 2 };
};

struct NautilusCooldownsParent {
	double staggering_blow[4] = { 9, 8, 7, 6 };
	double dredge_line[5] = { 14, 13, 12, 11, 10 };
	double titans_wrath[1] = { 12 };
	double riptide[5] = { 7, 6.5, 6, 5.5, 5 };
	double depth_charge[3] = { 120, 100, 80 };
};

struct NautilusDamageAbilities {
	double dredge_line[5] = { 80, 120, 160, 200, 240 };
	double titans_wrath[5] = { 30, 40, 50, 60, 70 };
	double titans_wrath_shield[5] = { 60, 70, 80, 90, 100 };
	double titans_wrath_shield_scale[5] = { 9, 10, 11, 12, 13 };
	double riptide[5] = { 55, 85, 115, 145, 175 };
	double depth_charge_trail[3] = { 125, 175, 225 };
	double depth_charge[3] = { 200, 325, 450 };
};

struct NautilusCooldowns {
	double auto_attack;
	bool can_auto_attack;

	double staggering_blow;
	bool can_staggering_blow;
	int staggering_blow_level = 0;

	double dredge_line;
	bool can_dredge_line;
	int dredge_line_level = 0;

	double titans_wrath;
	bool can_titans_wrath;
	int titans_wrath_level = 0;

	double riptide;
	bool can_riptide;
	int riptide_level = 0;

	double depth_charge;
	bool can_depth_charge;
	int depth_charge_level = 0;
};

struct Anchor {
	Vector2 position, direction, hintPosition;
	double magnitude, chainLength = 325;
	double angle;
	int hookSpeed = 100;

	int width = 50, height = 50;

	bool alive = false;
	bool hint = false;

	bool hooked = false;
	bool bounce = false;
	RectangleIndex* rectangleIndex;

	int colorAnchor[3] = { 99, 64, 61 };
	int colorChain[3] = { 102, 94, 90 };
};

struct Helmet {
	bool alive = false;
	double timeLeft = 0.0;

	std::vector<RectangleIndex*> hitRectangleList;
	std::vector<Vector2> tickList;
};

struct Riptide {
	bool alive = false;
	int stage;
	double timer;

	int distances[3] = { 100, 150, 200 };

	std::vector<RectangleIndex*> hitRectangleList;

	std::vector<Vector2> explosionPositionList;
	int explosionWidth = 30, explosionHeight = 30;
};

class Nautilus {
private:
	int level = 1;
	double health, mana;
	double shield;

	StatusBar statusBar;

	NautilusDurationsParent durationsParent;

	NautilusCooldowns cooldowns;
	NautilusCooldownsParent cooldownsParent;

	NautilusDamageAbilities damageAbilities;

	Stats stats;
	StatsUpgrade statsUpgrade;

	RectangleIndex rectangleIndex;

	Vector2 position;
	int width = 60, height = 75;

	Vector2 clickPosition;
	int clickAlpha = 0;

	double isRooted = 0;

	int color[3] = { 119, 84, 81 };
	int colorRoot[3] = { 89, 54, 51 };
	int colorHelmet[3] = { 0, 0, 255 };
	int colorPath[3] = { 92, 185, 196 };
	int colorClick[3] = { 0, 0, 0 };

	int colorDamagePhysical[3] = { 255, 48, 55 };
	int colorDamageMagic[3] = { 198, 160, 255 };

	std::vector<Vector2> pathVertices;

	double timer = 0;
	double dredgeLineTimer = 0;

	RectangleIndex* selectedRectangleIndex;

	bool queueDredgeLine = false, cancelDredgeLine = false;

	Anchor anchor;
	Helmet helmet;
	Riptide riptide;

	std::multimap<Vector2,Vector3> damageDisplayMap;

	inline Vector2 center() { return Vector2(position.x + (width / 2), position.y + (height / 2)); };
	inline void resetPath() { pathVertices.clear(); };
	inline void resetRoot() { isRooted = 0; };
	inline void autoReset() { cooldowns.auto_attack = 0; cooldowns.can_auto_attack = true; };

	void setupStats();
	void setupCooldowns();
	void checkCooldowns(float elapsedTimeSeconds);

	void createPath(int x, int y);
	void followPath(float elapsedTimeSeconds);
	void autoAttack(float elapsedTimeSeconds);

	void damageAuto(RectangleIndex* rectangleIndex, bool empowered);
	void damageDredgeLine(RectangleIndex* rectangleIndex);

	void generateDamageDisplay(Vector2 position, double damage, int type);
	void updateDamageDisplay(float elapsedTimeSeconds);

	void initializeDredgeLine(int x, int y);
	void castDredgeLine(float elapsedTimeSeconds);

	void initializeTitansWrath();
	void castTitansWrath(float elapsedTimeSeconds);
	void addTitansWrathEffect(RectangleIndex* rectangleIndex);

	void initializeRiptide();
	void castRiptide(float elapsedTimeSeconds);

	void initializeDepthCharge(Vector2* position);
	void castDepthCharge();

	void updateTimer(float elapsedTimeSeconds);

	void drawStatus();
	void drawDebug();
public:
	inline void setSelectedEntity(RectangleIndex* selectedRectangleIndex) {  this->selectedRectangleIndex = selectedRectangleIndex; };
	inline void resetSelectedEntity() { this->selectedRectangleIndex = nullptr; }

	inline bool anchorIsAlive() { return anchor.alive; };
	inline bool anchorIsHooked() { return anchor.hooked; };
	void anchorSetHook(RectangleIndex* rectangleIndex);
	bool checkAnchorCollision(Vector2 position, int width, int height);

	void initialize();

	void update(float elapsedTimeSeconds);

	void draw();
};