#include "Objetivo.h"

const int ID_OBJETIVO = 2;
Objetivo::Objetivo() : body(nullptr), ancho(80.0f), alto(20.0f) {}

void Objetivo::Init(b2World* mundo, float x, float y) {
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set(x, y);
	def.userData.pointer = (uintptr_t)ID_OBJETIVO;
	body = mundo->CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(ancho / 2.0f, alto / 2.0f);

	b2FixtureDef fix;
	fix.shape = &shape;
	fix.isSensor = true;
	body->CreateFixture(&fix);
}

void Objetivo::Draw(bool golpeado) const {
	if (!body) return;
	b2Vec2 pos = body->GetPosition();

	Color color = golpeado ? GREEN : YELLOW;

	DrawRectangle((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, color);
	DrawRectangleLines((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, WHITE);
	DrawText("OBJETIVO", (int)(pos.x - 30), (int)(pos.y - 8), 14, BLACK);
}

b2Body* Objetivo::GetBody() const { return body; }