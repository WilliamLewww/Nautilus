#pragma once
#include <ctime>
#include "core\drawing.h"
#include "core\configuration.h"
#include "core\file.h"
#include "core\timer.h"
#include "world.h"

class Joiner {
private:
	World world;
public:
	int seed;

	void initialize();
	void draw();
	void update();
};

extern Joiner joiner;