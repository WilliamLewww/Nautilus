#include "nautilus.h"

void Nautilus::anchorSetHook(RectangleIndex* rectangleIndex) { 
	damageDredgeLine(rectangleIndex);
	anchor.rectangleIndex = rectangleIndex;
	anchor.hooked = true; 
};

bool Nautilus::checkAnchorCollision(RectangleIndex* rectangleIndex) {
	if (anchor.position.x + anchor.width >= rectangleIndex->position->x &&
		anchor.position.x <= rectangleIndex->position->x + *rectangleIndex->width &&
		anchor.position.y + anchor.height >= rectangleIndex->position->y &&
		anchor.position.y <= rectangleIndex->position->y + *rectangleIndex->height) {

		return true;
	}
	return false;
}

bool Nautilus::checkRiptideCollision(RectangleIndex* rectangleIndex) {
	for (Vector2 explosionPosition : riptide.explosionPositionList) {
		if (explosionPosition.x + riptide.explosionWidth >= rectangleIndex->position->x &&
			explosionPosition.x <= rectangleIndex->position->x + *rectangleIndex->width &&
			explosionPosition.y + riptide.explosionHeight >= rectangleIndex->position->y &&
			explosionPosition.y <= rectangleIndex->position->y + *rectangleIndex->height) {

			return true;
		}
	}

	return false;
}

void Nautilus::handleRiptideCollision(RectangleIndex* rectangleIndex) {
	if (std::find(riptide.hitRectangleList.begin(), riptide.hitRectangleList.end(), rectangleIndex) == riptide.hitRectangleList.end()) {
		damageRiptide(rectangleIndex, false);
		riptide.hitRectangleList.push_back(rectangleIndex);
		riptide.hitStage.push_back(0);
	}

	if (riptide.stage == 1) {
		for (int x = 0; x < riptide.hitStage.size(); x++) {
			if (rectangleIndex == riptide.hitRectangleList[x]) {
				if (riptide.hitStage[x] < 1) {
					damageRiptide(rectangleIndex, true);
					riptide.hitStage[x] += 1;
				}
			}
		}
	}

	if (riptide.stage == 2) {
		for (int x = 0; x < riptide.hitStage.size(); x++) {
			if (rectangleIndex == riptide.hitRectangleList[x]) {
				if (riptide.hitStage[x] < 2) {
					damageRiptide(rectangleIndex, true);
					riptide.hitStage[x] += 1;
				}
			}
		}
	}
}

void Nautilus::initialize() {
	position = Vector2(250, 250);
	rectangleIndex = createRectangleIndex(&position, &width, &height, &isRooted, &health, &mana);

	setupStats();
	setupCooldowns();
	health = stats.health;
	mana = stats.mana;
	gui.linkAbilities(&cooldowns.dredge_line, &cooldowns.titans_wrath, &cooldowns.riptide, &cooldowns.depth_charge);
	linkStatusBar(statusBar, &stats.health, &health, &mana, &level);
}

void Nautilus::setupStats() {
	stats.health 		 			= 576.48;
	stats.mana						= 200;
	stats.health_regen   			= 8.5;
	stats.mana_regen   				= 7.45;
	stats.attack_damage  			= 61.0;
	stats.attack_speed   			= 0.613;
	stats.ability_power				= 0;
	stats.armor 		 			= 35.46;
	stats.magic_resist   			= 32.1;
	stats.movement_speed 			= 325;

	statsUpgrade.health 			= 86.0;
	statsUpgrade.mana				= 50.0;
	statsUpgrade.health_regen 		= 0.55;
	statsUpgrade.mana_regen   		= 0.7;
	statsUpgrade.attack_damage 		= 3.3;
	statsUpgrade.attack_speed 		= 0.01;
	statsUpgrade.armor 				= 3.75;
	statsUpgrade.magic_resist		= 1.25;
}

void Nautilus::setupCooldowns() {
	cooldowns.auto_attack = 0;
	cooldowns.staggering_blow = 0;

	cooldowns.dredge_line = 0;
	cooldowns.titans_wrath = 0;
	cooldowns.riptide = 0;
	cooldowns.depth_charge = 0;
}

void Nautilus::checkCooldowns(float elapsedTimeSeconds) {
	if (cooldowns.auto_attack <= 0) { cooldowns.can_auto_attack = true; }
	else { cooldowns.auto_attack -= elapsedTimeSeconds; }

	if (cooldowns.staggering_blow <= 0) { cooldowns.can_staggering_blow = true; }
	else { cooldowns.staggering_blow -= elapsedTimeSeconds; }
	
	if (cooldowns.dredge_line <= 0) { cooldowns.can_dredge_line = true; }
	else { cooldowns.dredge_line -= elapsedTimeSeconds; }
	
	if (cooldowns.titans_wrath <= 0) { cooldowns.can_titans_wrath = true; }
	else { cooldowns.titans_wrath -= elapsedTimeSeconds; }
	
	if (cooldowns.riptide <= 0) { cooldowns.can_riptide = true; }
	else { cooldowns.riptide -= elapsedTimeSeconds; }
	
	if (cooldowns.depth_charge <= 0) { cooldowns.can_depth_charge = true; }
	else { cooldowns.depth_charge -= elapsedTimeSeconds; }
}

void Nautilus::update(float elapsedTimeSeconds) {
	checkCooldowns(elapsedTimeSeconds);

	if (input.getRightButtonPress()) {
		if (abs(center().x - input.getMouseXCamera()) > 3 || abs(center().y - input.getMouseYCamera()) > 3) {
			createPath(input.getMouseXCamera(), input.getMouseYCamera());

			clickPosition = Vector2(input.getMouseXCamera(), input.getMouseYCamera());
			clickAlpha = 255;
		}
	}

	if (clickAlpha > 0) {
		if (clickAlpha - 25 < 0) { clickAlpha = 0; }
		else { clickAlpha -= 25; }
	}

	if (input.checkKeyDown(SDLK_q) && cooldowns.can_dredge_line && isRooted == 0) { 
		if (input.getRightButtonPress()) {
			queueDredgeLine = false;
			cancelDredgeLine = true;
			anchor.hint = false;
		}
		if (!cancelDredgeLine) {
			queueDredgeLine = true;

			anchor.hint = true;
			Vector2 difference = Vector2(input.getMouseXCamera(), input.getMouseYCamera()) - center();
			double degree;
			if (difference.x > 0) { degree = atan(difference.y / difference.x); }
			else { degree = atan(difference.y / difference.x) + drawing.PI; }
			anchor.hintPosition = Vector2((cos(degree) * 325) + center().x, (sin(degree) * 325) + center().y);
		}
	}
	else { anchor.hint = false; cancelDredgeLine = false; }
	if (!anchor.alive && queueDredgeLine && !input.checkKeyDown(SDLK_q)) { anchor.alive = true; queueDredgeLine = false; initializeDredgeLine(input.getMouseXCamera(), input.getMouseYCamera()); }
	if (anchor.alive) {	anchor.hint = false; castDredgeLine(elapsedTimeSeconds); }

	if (input.checkKeyDown(SDLK_w) && cooldowns.can_titans_wrath && isRooted == 0) { initializeTitansWrath(); }
	castTitansWrath(elapsedTimeSeconds);

	if (input.checkKeyDown(SDLK_e) && cooldowns.can_riptide && isRooted == 0) { initializeRiptide(); }
	castRiptide(elapsedTimeSeconds);

	if (isRooted == 0) { 
		followPath(elapsedTimeSeconds);
		autoAttack(elapsedTimeSeconds);
	}
	else {
		if (isRooted > 0) {
			if (isRooted - elapsedTimeSeconds <= 0) { isRooted = 0; }
			else { isRooted -= elapsedTimeSeconds; }
		}
	}
	updateTimer(elapsedTimeSeconds);
	updateDamageDisplay(elapsedTimeSeconds);
}

void Nautilus::updateTimer(float elapsedTimeSeconds) {
	if (timer <= 1) {
		timer += elapsedTimeSeconds;
	}
	else {
		if (health < stats.health) {
			if (health + stats.health_regen > stats.health) { health = stats.health; }
			else { health += stats.health_regen; }
		}

		if (mana < stats.mana) {
			if (mana + stats.mana_regen > stats.mana) { mana = stats.mana; }
			else { mana += stats.mana_regen; }
		}
		timer = 0.0;
	}
}

void Nautilus::initializeDredgeLine(int x, int y) {
	isRooted = -1;
	resetPath();
	autoReset();
	cooldowns.can_dredge_line = false;
	cooldowns.dredge_line = cooldownsParent.staggering_blow[cooldowns.dredge_line_level];

	anchor.position = Vector2(center().x - (anchor.width / 2), center().y - (anchor.height / 2));
	anchor.direction = Vector2(x, y) - center();
	if (anchor.direction.x > 0) { anchor.angle = atan(anchor.direction.y / anchor.direction.x); }
	else { anchor.angle = atan(anchor.direction.y / anchor.direction.x) + drawing.PI; }
	anchor.magnitude = 0;
}

void Nautilus::castDredgeLine(float elapsedTimeSeconds) {
	if (anchor.hooked) {
		Vector2 difference = Vector2(anchor.rectangleIndex->position->x + (*anchor.rectangleIndex->width / 2), anchor.rectangleIndex->position->y + (*anchor.rectangleIndex->height / 2)) - center();
		if (*anchor.rectangleIndex->isRooted == 0) { *anchor.rectangleIndex->isRooted = -1; }

		if (!anchor.bounce) {
			position.x += (difference.x / (abs(difference.x) + abs(difference.y))) * 682.5 * elapsedTimeSeconds;
			position.y += (difference.y / (abs(difference.x) + abs(difference.y))) * 682.5 * elapsedTimeSeconds;
			anchor.rectangleIndex->position->x -= (difference.x / (abs(difference.x) + abs(difference.y))) * 682.5 * elapsedTimeSeconds;
			anchor.rectangleIndex->position->y -= (difference.y / (abs(difference.x) + abs(difference.y))) * 682.5 * elapsedTimeSeconds;
			anchor.position.x = anchor.rectangleIndex->position->x + (*anchor.rectangleIndex->width / 2) - (anchor.width / 2);
			anchor.position.y = anchor.rectangleIndex->position->y + (*anchor.rectangleIndex->height / 2) - (anchor.height / 2);
		
			if (abs(difference.x) + abs(difference.y) < 50) { anchor.bounce = true; }
		}
		else {
			if (abs(difference.x) + abs(difference.y) > 75) {
				anchor.bounce = false;
				anchor.alive = false;
				anchor.hooked = false;
				resetRoot();
				if (*anchor.rectangleIndex->isRooted == -1) { *anchor.rectangleIndex->isRooted = 0; }
			}
			else {
				position.x -= (difference.x / (abs(difference.x) + abs(difference.y))) * 227.5 * elapsedTimeSeconds;
				position.y -= (difference.y / (abs(difference.x) + abs(difference.y))) * 227.5 * elapsedTimeSeconds;
				anchor.rectangleIndex->position->x += (difference.x / (abs(difference.x) + abs(difference.y))) * 227.5 * elapsedTimeSeconds;
				anchor.rectangleIndex->position->y += (difference.y / (abs(difference.x) + abs(difference.y))) * 227.5 * elapsedTimeSeconds;
				anchor.position.x = anchor.rectangleIndex->position->x + (*anchor.rectangleIndex->width / 2) - (anchor.width / 2);
				anchor.position.y = anchor.rectangleIndex->position->y + (*anchor.rectangleIndex->height / 2) - (anchor.height / 2);
			}
		}
	}
	else {
		if (anchor.magnitude < anchor.chainLength) {
			if (anchor.magnitude + (anchor.hookSpeed * elapsedTimeSeconds) >= anchor.chainLength) {
				anchor.magnitude = anchor.chainLength;
			}
			else { anchor.magnitude += anchor.hookSpeed * elapsedTimeSeconds; }
			anchor.position = Vector2(cos(anchor.angle) * anchor.magnitude, sin(anchor.angle) * anchor.magnitude) + center() - Vector2(anchor.width / 2, anchor.height / 2);
		}
		else {
			anchor.alive = false;
			resetRoot();
		}
	}
}

void Nautilus::initializeTitansWrath() {
	helmet.alive = true;
	helmet.timeLeft = durationsParent.titans_wrath;
	shield += damageAbilities.titans_wrath_shield[cooldowns.titans_wrath_level] + (damageAbilities.titans_wrath_shield_scale[cooldowns.titans_wrath_level] * stats.health);

	autoReset();
	cooldowns.can_titans_wrath = false;
	cooldowns.titans_wrath = cooldownsParent.titans_wrath[cooldowns.titans_wrath_level];
}

void Nautilus::addTitansWrathEffect(RectangleIndex* rectangleIndex) {
	if (std::find(helmet.hitRectangleList.begin(), helmet.hitRectangleList.end(), rectangleIndex) == helmet.hitRectangleList.end()) {
		*rectangleIndex->health -= damageAbilities.titans_wrath[cooldowns.titans_wrath_level] + (0.4 * stats.ability_power);
		generateDamageDisplay(*rectangleIndex->position, damageAbilities.titans_wrath[cooldowns.titans_wrath_level] + (0.4 * stats.ability_power), 1);

		helmet.hitRectangleList.push_back(rectangleIndex);
		helmet.tickList.push_back(Vector2(0.0, 0.0));
	}
}

void Nautilus::castTitansWrath(float elapsedTimeSeconds) {
	if (helmet.alive == true) { 
		if (helmet.timeLeft > 0) {
			helmet.timeLeft -= elapsedTimeSeconds;
		}
		else {
			helmet.alive = false;
			if (shield > 0) {
				if (shield - damageAbilities.titans_wrath_shield[cooldowns.titans_wrath_level] + (damageAbilities.titans_wrath_shield_scale[cooldowns.titans_wrath_level] * stats.health) < 0) {
					shield = 0;
				}
				else {
					shield -= damageAbilities.titans_wrath_shield[cooldowns.titans_wrath_level] + (damageAbilities.titans_wrath_shield_scale[cooldowns.titans_wrath_level] * stats.health);
				}
			}
		}
	}

	for (int x = 0; x < helmet.hitRectangleList.size(); x++) {
		if (helmet.tickList[x].x < durationsParent.titans_wrath_effect) {
			if (helmet.tickList[x].y < 1.0) {
				helmet.tickList[x].y += elapsedTimeSeconds;
			}
			else {
				*helmet.hitRectangleList[x]->health -= damageAbilities.titans_wrath[cooldowns.titans_wrath_level] + (0.4 * stats.ability_power);
				generateDamageDisplay(*helmet.hitRectangleList[x]->position, damageAbilities.titans_wrath[cooldowns.titans_wrath_level] + (0.4 * stats.ability_power), 1);
				helmet.tickList[x].x += 1;
				helmet.tickList[x].y = 0.0;
			}
		}
		else {
			helmet.hitRectangleList.erase(helmet.hitRectangleList.begin() + x);
			helmet.tickList.erase(helmet.tickList.begin() + x);
			x -= 1;
		}
	}
}

void Nautilus::initializeRiptide() {
	isRooted = -1;
	resetPath();
	autoReset();

	cooldowns.can_riptide = false;
	cooldowns.riptide = cooldownsParent.riptide[cooldowns.riptide_level];
	riptide.alive = true;
	riptide.stage = 0;
	riptide.timer = 0;
	riptide.explosionPositionList.clear();
	riptide.hitRectangleList.clear();
	riptide.hitStage.clear();
}

void Nautilus::castRiptide(float elapsedTimeSeconds) {
	if (riptide.alive) {
		if (riptide.stage < 3) {
			if (riptide.explosionPositionList.size() == 0) {
				int distance = riptide.distances[riptide.stage];
				int count = riptide.explosionCounts[riptide.stage];

				for (int x = 0; x < count; x++) {
					riptide.explosionPositionList.push_back(Vector2((cos(drawing.degreeToRadians(x * 360 / count)) * distance) + center().x - (riptide.explosionWidth / 2), (sin(drawing.degreeToRadians(x * 360 / count)) * distance) + center().y - (riptide.explosionHeight / 2)));
				}
			}
		}
		else {
			if (isRooted == -1) { isRooted = 0; }
			riptide.alive = false;
		}
	}

	if (riptide.timer >= 0.18) { 
		riptide.stage += 1;
		riptide.explosionPositionList.clear();
		riptide.timer = 0.0;
	}
	else { riptide.timer += elapsedTimeSeconds; }
}

void Nautilus::createPath(int x, int y) {
	pathVertices.clear();

	pathVertices.push_back(center());
	pathVertices.push_back(Vector2(x, y));
}

void Nautilus::followPath(float elapsedTimeSeconds) {
	if (selectedRectangleIndex == nullptr) {
		if (pathVertices.size() > 1) {
			Vector2 difference = pathVertices[1] - pathVertices[0];

			position.x += (difference.x / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;
			position.y += (difference.y / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;

			bool nextNode = false;

			if (!nextNode && difference.x > 0 && difference.y > 0) { if (center().x > pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x > 0 && difference.y < 0) { if (center().x > pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x < 0 && difference.y > 0) { if (center().x < pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x < 0 && difference.y < 0) { if (center().x < pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		
			if (!nextNode && difference.x == 0 && difference.y > 0) { if (center().x == pathVertices[1].x && center().y > pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x == 0 && difference.y < 0) { if (center().x == pathVertices[1].x && center().y < pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x > 0 && difference.y == 0) { if (center().x > pathVertices[1].x && center().y == pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
			if (!nextNode && difference.x < 0 && difference.y == 0) { if (center().x < pathVertices[1].x && center().y == pathVertices[1].y) { nextNode = true; pathVertices.clear(); }}
		}
	}
	else {
		Vector2 difference = Vector2(selectedRectangleIndex->position->x + (*selectedRectangleIndex->width / 2), selectedRectangleIndex->position->y + (*selectedRectangleIndex->height / 2)) - center();
		
		if (abs(difference.x) + abs(difference.y) >= 100) {
			durationsParent.auto_attack_current_frame = 0.0;

			position.x += (difference.x / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;
			position.y += (difference.y / (abs(difference.x) + abs(difference.y))) * getActualSpeed(stats) * elapsedTimeSeconds;
		}
	}
}

void Nautilus::autoAttack(float elapsedTimeSeconds) {
	if (selectedRectangleIndex != nullptr && cooldowns.can_auto_attack) {
		Vector2 difference = Vector2(selectedRectangleIndex->position->x + (*selectedRectangleIndex->width / 2), selectedRectangleIndex->position->y + (*selectedRectangleIndex->height / 2)) - center();
		
		if (durationsParent.auto_attack_current_frame < stats.attack_speed * 0.37) {
			durationsParent.auto_attack_current_frame += elapsedTimeSeconds;
		}
		else {
			durationsParent.auto_attack_current_frame = 0.0;

			if (abs(difference.x) + abs(difference.y) < 100) {
				if (cooldowns.can_staggering_blow) {
					cooldowns.can_staggering_blow = false;
					cooldowns.staggering_blow = cooldownsParent.staggering_blow[cooldowns.staggering_blow_level];
					*selectedRectangleIndex->isRooted = durationsParent.staggering_blow[cooldowns.staggering_blow_level];
					damageAuto(selectedRectangleIndex, true);
				}
				else { damageAuto(selectedRectangleIndex, false); }

				cooldowns.can_auto_attack = false;
				cooldowns.auto_attack = (1.0 / stats.attack_speed);
			}
		}
	}
}

void Nautilus::damageAuto(RectangleIndex* rectangleIndex, bool empowered) {
	*rectangleIndex->health -= stats.attack_damage;
	if (helmet.alive) { addTitansWrathEffect(rectangleIndex); }

	if (!empowered) {
		generateDamageDisplay(*rectangleIndex->position, stats.attack_damage, 0);
	}
	else {
		*rectangleIndex->health -= (2.0 + (6 * level));
		generateDamageDisplay(*rectangleIndex->position, stats.attack_damage + (2.0 + (6 * level)), 0);
	}
}

void Nautilus::damageDredgeLine(RectangleIndex* rectangleIndex) {
	*rectangleIndex->health -= damageAbilities.dredge_line[cooldowns.dredge_line_level] + (0.75 * stats.ability_power);
	generateDamageDisplay(*rectangleIndex->position, damageAbilities.dredge_line[cooldowns.dredge_line_level] + (0.75 * stats.ability_power), 1);
}

void Nautilus::damageRiptide(RectangleIndex* rectangleIndex, bool additional) {
	if (!additional) {
		*rectangleIndex->health -= damageAbilities.riptide[cooldowns.riptide_level] + (0.3 * stats.ability_power);
		generateDamageDisplay(*rectangleIndex->position, damageAbilities.riptide[cooldowns.riptide_level] + (0.3 * stats.ability_power), 1);
	}
	else {
		*rectangleIndex->health -= (damageAbilities.riptide[cooldowns.riptide_level] + (0.3 * stats.ability_power)) * 0.5;
		generateDamageDisplay(*rectangleIndex->position, (damageAbilities.riptide[cooldowns.riptide_level] + (0.3 * stats.ability_power)) * 0.5, 1);
	}
}

void Nautilus::generateDamageDisplay(Vector2 position, double damage, int type) {
	damageDisplayMap.emplace(position, Vector3(damage, 0.0, type));
}

void Nautilus::updateDamageDisplay(float elapsedTimeSeconds) {
	std::vector<Vector2> tempList;
	for (auto& pair : damageDisplayMap) {
		pair.second.y += elapsedTimeSeconds;
		if (pair.second.y > 0.43) {
			tempList.push_back(pair.first);
		}
	}

	for (Vector2 position : tempList) {
		std::multimap<Vector2,Vector3>::iterator it = damageDisplayMap.find(position);
		damageDisplayMap.erase(it);
	}
	tempList.clear();
}

void Nautilus::draw() {
	//drawDebug();

	if (riptide.alive) {
		for (Vector2 explosionPosition : riptide.explosionPositionList) {
			drawing.drawRect(explosionPosition, riptide.explosionWidth, riptide.explosionHeight, riptide.explosionColor);
		}
	}

	drawing.drawCircleFill(clickPosition, 12, colorClick, clickAlpha);
	if (isRooted == 0) { drawing.drawRect(position, width, height, color); }
	else { drawing.drawRect(position, width, height, colorRoot); }

	if (helmet.alive) { drawing.drawRect(position, width, height / 3, colorHelmet); }

	if (anchor.hint) {
		drawing.drawLine(center(), anchor.hintPosition, anchor.colorChain, 100);
		drawing.drawLine(center(), anchor.hintPosition - Vector2( anchor.width / 2,  anchor.height / 2), anchor.colorChain, 100);
		drawing.drawLine(center(), anchor.hintPosition - Vector2(-anchor.width / 2,  anchor.height / 2), anchor.colorChain, 100);
		drawing.drawLine(center(), anchor.hintPosition - Vector2( anchor.width / 2, -anchor.height / 2), anchor.colorChain, 100);
		drawing.drawLine(center(), anchor.hintPosition - Vector2(-anchor.width / 2, -anchor.height / 2), anchor.colorChain, 100);

		drawing.drawRect(anchor.hintPosition - Vector2(anchor.width / 2, anchor.height / 2), anchor.width, anchor.height, anchor.colorAnchor, 100);
	}

	if (anchor.alive) {
		drawing.drawLine(center(), anchor.position + Vector2(anchor.width / 2, anchor.height / 2), anchor.colorChain);
		drawing.drawRect(anchor.position, anchor.width, anchor.height, anchor.colorAnchor);
	}

	for (auto& pair : damageDisplayMap) {
		std::string damage = std::to_string((int)ceil(pair.second.x));
		if (pair.second.z == 0) {
			drawing.drawText(damage.c_str(), Vector2(pair.first) + Vector2(25, - 40.0 - (pair.second.y * 25.0)), 2, colorDamagePhysical);
		}
		if (pair.second.z == 1) {
			drawing.drawText(damage.c_str(), Vector2(pair.first) + Vector2(25, - 15.0 - (pair.second.y * 25.0)), 2, colorDamageMagic);
		}
	}

	drawStatus();
}

void Nautilus::drawStatus() {
	updateStatusBar(statusBar, position, width);
	drawStatusBar(statusBar);
}

void Nautilus::drawDebug() {
	if (pathVertices.size() == 2) {
		drawing.drawLine(center(), pathVertices[1], colorPath);
	}
}