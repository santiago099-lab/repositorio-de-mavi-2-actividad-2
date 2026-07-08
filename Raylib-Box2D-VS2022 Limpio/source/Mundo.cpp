#include "Mundo.h"

ContactListener::ContactListener() : dentroDelSensor(false) {}

void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    int idA = (int)(intptr_t)bodyA->GetUserData().pointer;
    int idB = (int)(intptr_t)bodyB->GetUserData().pointer;
    bool lanzadorVsSensor =
        (idA == ID_LANZADOR && idB == ID_SENSOR) ||
        (idA == ID_SENSOR && idB == ID_LANZADOR);
    if (lanzadorVsSensor) dentroDelSensor = true;
}

void ContactListener::EndContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    int idA = (int)(intptr_t)bodyA->GetUserData().pointer;
    int idB = (int)(intptr_t)bodyB->GetUserData().pointer;
    bool lanzadorVsSensor =
        (idA == ID_LANZADOR && idB == ID_SENSOR) ||
        (idA == ID_SENSOR && idB == ID_LANZADOR);
    if (lanzadorVsSensor) dentroDelSensor = false;
}

bool ContactListener::DentroDelSensor() const { return dentroDelSensor; }
void ContactListener::Reset() { dentroDelSensor = false; }

Mundo::Mundo() : mundo(nullptr), suelo(nullptr), screenWidth(0), screenHeight(0) {}
Mundo::~Mundo() { delete mundo; }

void Mundo::Init(int w, int h) {
    screenWidth = w;
    screenHeight = h;
    b2Vec2 gravedad(0.0f, 20.0f);
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

void Mundo::Step(float dt) { mundo->Step(dt, 8, 3); }

void Mundo::Draw() const {
    ClearBackground({ 15, 15, 35, 255 });
    DrawRectangle(0, screenHeight - 40, screenWidth, 40, DARKBROWN);
    DrawLine(0, screenHeight - 40, screenWidth, screenHeight - 40, BROWN);
}

b2World* Mundo::GetWorld() { return mundo; }
ContactListener* Mundo::GetListener() { return &listener; }
int Mundo::GetWidth()  const { return screenWidth; }
int Mundo::GetHeight() const { return screenHeight; }