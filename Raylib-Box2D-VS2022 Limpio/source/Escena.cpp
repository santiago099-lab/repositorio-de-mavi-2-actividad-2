#include "Escena.h"

Escena::Escena() : mundo(nullptr), suelo(nullptr), screenWidth(0), screenHeight(0) {}

Escena::~Escena() {
    delete mundo;
}

void Escena::Init(int w, int h) {
    screenWidth = w;
    screenHeight = h;

    b2Vec2 gravedad(0.0f, 980.0f);
    mundo = new b2World(gravedad);

    
    b2BodyDef sueloDef;
    sueloDef.type = b2_staticBody;
    sueloDef.position.Set(w / 2.0f, h - 20.0f);
    suelo = mundo->CreateBody(&sueloDef);

    b2PolygonShape sueloShape;
    sueloShape.SetAsBox(w / 2.0f, 20.0f);
    suelo->CreateFixture(&sueloShape, 0.0f);
}

void Escena::Step(float dt) {
    mundo->Step(dt, 8, 3);
}

void Escena::Draw() const {
    ClearBackground({ 30, 30, 60, 255 });
    DrawRectangle(0, screenHeight - 40, screenWidth, 40, DARKGREEN);
    DrawLine(0, screenHeight - 40, screenWidth, screenHeight - 40, GREEN);
}

b2World* Escena::GetWorld() { return mundo; }
int      Escena::GetWidth()  const { return screenWidth; }
int      Escena::GetHeight() const { return screenHeight; }