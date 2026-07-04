#pragma once
#include "raylib.h"
#include <Box2d.h>

class Objetivo {
public:
	Objetivo();

	void Init(b2World* mundo, float x, float y);
	void Draw(bool golpeado) const;

	b2Body* GetBody() const;

private:
	b2Body* body;
	float ancho;
	float alto;
};
