#pragma once
#include "raylib.h"
#include <Box2d.h>

class Proyectil {
public:
	Proyectil();
	void Init(b2World* mundo, float x, float y);

	void Draw() const;

	void Reset(float x, float y);

	bool EstaActivo() const;

	b2Body* GetBody() const;

private:
	b2Body* body;
	float radio;
	bool activo;
};
