#include "Proyectil.h"

const int ID_PROYECTIL = 1;

Proyectil::Proyectil() : body(nullptr), radio(20.0f), activo(false) {}

void Proyectil::Init(b2World* mundo, float x, float y) {
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set(x, y);
	def.bullet = true;
	def.userData.pointer = (uintptr_t)ID_PROYECTIL;
	body = mundo->CreateBody(&def);

	b2CircleShape shape;
	shape.m_radius = radio;

	b2FixtureDef fix;
	fix.shape = &shape;
	fix.density = 3.0f;
	fix.friction = 0.3f;
	fix.restitution = 0.2f;
	body->CreateFixture(&fix);

	activo = true;
}

void Proyectil::Draw() const {
	if (!body || !activo) return;
	b2Vec2 pos = body->GetPosition();
	DrawCircle((int)pos.x, (int)pos.y, radio, RED);
	DrawCircleLines((int)pos.x, (int)pos.y, radio, ORANGE);
}

void Proyectil::Reset(float x, float y) {
	if (!body) return;
	body->SetTransform(b2Vec2(x, y), 0.0f);
	body->SetLinearVelocity(b2Vec2(0, 0));
	body->SetAngularVelocity(0);
	body->SetAwake(true);
	activo = true;
}

bool Proyectil::EstaActivo() const { return activo; }
b2Body* Proyectil::GetBody() const { return body; }