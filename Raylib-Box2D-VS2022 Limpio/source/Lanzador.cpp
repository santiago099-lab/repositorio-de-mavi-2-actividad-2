#include "Lanzador.h"
#include <cmath>

const int ID_LANZADOR = 1;

Lanzador::Lanzador()
    : mundo(nullptr), body(nullptr), bola(nullptr),
    angulo(45.0f), potencia(500.0f), disparado(false),
    initX(0), initY(0), ancho(30.0f), alto(30.0f)
{
}

void Lanzador::Init(b2World* m, float x, float y) {
    mundo = m;
    initX = x;
    initY = y;
    b2BodyDef def;
    def.type = b2_staticBody; 
    def.position.Set(x, y);
    def.userData.pointer = 0;
    body = mundo->CreateBody(&def);
    b2PolygonShape shape;
    shape.SetAsBox(ancho / 2.0f, alto / 2.0f);
    body->CreateFixture(&shape, 0.0f);
}

void Lanzador::AjustarAngulo(int dir) {
    if (disparado) return;
    angulo += dir * 5.0f;
    if (angulo > 85.0f) angulo = 85.0f;
    if (angulo < -85.0f) angulo = -85.0f;
}

void Lanzador::AjustarPotencia(int dir) {
    if (disparado) return;
    potencia += dir * 50.0f;
    if (potencia < 100.0f)  potencia = 100.0f;
    if (potencia > 2000.0f)  potencia = 2000.0f;
}

void Lanzador::Disparar() {
    if (disparado) return;
    disparado = true;

    b2BodyDef bolaDef;
    bolaDef.type = b2_dynamicBody;
    bolaDef.position.Set(initX, initY);
    bolaDef.bullet = true;
    bolaDef.userData.pointer = (uintptr_t)ID_LANZADOR;
    bola = mundo->CreateBody(&bolaDef);

    b2CircleShape bolaShape;
    bolaShape.m_radius = 15.0f;
    b2FixtureDef bolaFix;
    bolaFix.shape = &bolaShape;
    bolaFix.density = 0.1f;
    bolaFix.friction = 0.3f;
    bolaFix.restitution = 0.3f;
    bola->CreateFixture(&bolaFix);

    float rad = angulo * DEG2RAD;
    b2Vec2 impulso(potencia * 50.0f * cosf(rad), -potencia * 50.0f * sinf(rad));
    bola->SetAwake(true);
    bola->ApplyLinearImpulse(impulso, bola->GetWorldCenter(), true);
}

void Lanzador::Reset(float x, float y) {
    if (bola) {
        mundo->DestroyBody(bola);
        bola = nullptr;
    }
    disparado = false;
    angulo = 45.0f;
    potencia = 500.0f;
}

void Lanzador::Draw() const {
    if (!body) return;
    b2Vec2 pos = body->GetPosition();

    DrawRectangle((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, SKYBLUE);
    DrawRectangleLines((int)(pos.x - ancho / 2), (int)(pos.y - alto / 2), (int)ancho, (int)alto, BLACK);

    if (!disparado) {
        float rad = angulo * DEG2RAD;
        float len = potencia / 10.0f;
        float endX = pos.x + len * cosf(rad);
        float endY = pos.y - len * sinf(rad);
        DrawLineEx({ pos.x, pos.y }, { endX, endY }, 2, YELLOW);
        DrawCircle((int)endX, (int)endY, 5, YELLOW);
    }

    if (disparado && bola) {
        b2Vec2 posBola = bola->GetPosition();
        DrawCircle((int)posBola.x, (int)posBola.y, 15, ORANGE);
        DrawCircleLines((int)posBola.x, (int)posBola.y, 15, RED);
    }
}

float   Lanzador::GetAngulo()    const { return angulo; }
float   Lanzador::GetPotencia()  const { return potencia; }
bool    Lanzador::FueDisparado() const { return disparado; }
b2Body* Lanzador::GetBody()      const { return bola ? bola : body; }