
#include "ZonaSensor.h"

const int ID_SENSOR = 2;

ZonaSensor::ZonaSensor() : body(nullptr), ancho(0), alto(0) {}

void ZonaSensor::Init(b2World* mundo, float x, float y, float ancho, float alto) {
    this->ancho = ancho;
    this->alto = alto;
    b2BodyDef def;
    def.type = b2_staticBody;
    def.position.Set(x, y);
    def.userData.pointer = (uintptr_t)ID_SENSOR;
    body = mundo->CreateBody(&def);
    b2PolygonShape shape;
    shape.SetAsBox(ancho / 2.0f, alto / 2.0f);
    b2FixtureDef fix;
    fix.shape = &shape;
    fix.isSensor = true;
    body->CreateFixture(&fix);
}

void ZonaSensor::Draw(bool activa) const {
    if (!body) return;
    b2Vec2 pos = body->GetPosition();
    Color colorFondo = activa ? ColorAlpha(GREEN, 0.3f) : ColorAlpha(YELLOW, 0.15f);
    Color colorBorde = activa ? GREEN : YELLOW;
    DrawRectangle((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, colorFondo);
    DrawRectangleLines((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, colorBorde);
    DrawText("ZONA OBJETIVO", (int)(pos.x - ancho / 2 + 5), (int)(pos.y - alto / 2 + 5), 16, colorBorde);
}

b2Body* ZonaSensor::GetBody() const { return body; }