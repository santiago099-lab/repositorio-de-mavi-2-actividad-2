#include "Mundo.h"
#include <string>

const int ID_PROYECTIL = 1;
const int ID_OBJETIVO = 2;
const int ID_SUELO = 3;

ContactListener::ContactListener() : eventoDetectado(false) {}

void ContactListener::BeginContact(b2Contact* contact) {

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	int idA = (int)(intptr_t)bodyA->GetUserData().pointer;
	int idB = (int)(intptr_t)bodyB->GetUserData().pointer;

	bool proyectilVsObjetivo = (idA == ID_PROYECTIL && idB == ID_OBJETIVO) || (idA == ID_OBJETIVO && idB == ID_PROYECTIL);

	if (proyectilVsObjetivo) {
		eventoDetectado = true;
	}
}

bool ContactListener::EventoDetectado() const { return eventoDetectado; }
void ContactListener::Reset() { eventoDetectado = false; }

Mundo::Mundo() : mundo(nullptr), suelo(nullptr), ScreenWidth(0), ScreenHeight(0) {}

Mundo::~Mundo() {
	delete mundo;
}

void Mundo::Init(int w, int h) {
	ScreenWidth = w;
	ScreenHeight = h;

	b2Vec2 gravedad(0.0f, 980.0f);
	mundo = new b2World(gravedad);

	mundo->SetContactListener(&listener);

	b2BodyDef sueloDef;
	sueloDef.type = b2_staticBody;
	sueloDef.position.Set(w / 2.0f, h - 20.0f);

	sueloDef.userData.pointer = (uintptr_t)ID_SUELO;
	suelo = mundo->CreateBody(&sueloDef);

	b2PolygonShape sueloShape;
	sueloShape.SetAsBox(w / 2.0f, 20.0f);
	suelo->CreateFixture(&sueloShape, 0.0f);
}

void Mundo::Step(float dt) {
	mundo->Step(dt, 8, 3);
}

void Mundo::Draw() const {
	ClearBackground({ 20, 20, 40, 255 });
	DrawRectangle(0, ScreenHeight - 40, ScreenWidth, 40, DARKBROWN); 
	DrawLine(0, ScreenHeight - 40, ScreenWidth, ScreenHeight - 40, BROWN);
}

b2World* Mundo::GetWorld() { return mundo; }
ContactListener* Mundo::GetListener() { return &listener; }
int Mundo::GetWidth() const { return ScreenWidth; }
int Mundo::GetHeight() const { return ScreenHeight; }