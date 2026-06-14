#include "Plataforma.h"
#include <cmath>
#include "Escena.h"

Plataforma::Plataforma() : ancla(nullptr), plataforma(nullptr), caja(nullptr), prismaticJoint(nullptr), pulleyJoint(nullptr), screenWidth(0), screenHeight(0), polea1X(0), polea1Y(0), polea2X(0), polea2Y(0){}
    
void Plataforma::Init(b2World* mundo, int w, int h) {
    screenWidth = w;
    screenHeight = h;

    polea1X = w * 0.35f;
    polea1Y = 50.0f;
    polea2X = w * 0.65f;
    polea2Y = 50.0f;

    
    b2BodyDef ancladef;
    ancladef.type = b2_staticBody;
    ancladef.position.Set(polea1X, polea1Y);
    ancla = mundo->CreateBody(&ancladef);
    b2CircleShape anclaShape;
    anclaShape.m_radius = 5.0f;
    ancla->CreateFixture(&anclaShape, 0.0f);

    
    b2BodyDef platDef;
    platDef.type = b2_dynamicBody;
    platDef.position.Set(polea1X, h - 120.0f);
    platDef.fixedRotation = true;
    plataforma = mundo->CreateBody(&platDef);

    b2PolygonShape platShape;
    platShape.SetAsBox(70.0f, 10.0f);
    b2FixtureDef platFix;
    platFix.shape = &platShape;
    platFix.density = 2.0f;
    platFix.friction = 0.5f;
    platFix.restitution = 0.0f;
    plataforma->CreateFixture(&platFix);

    
    b2BodyDef cajaDef;
    cajaDef.type = b2_dynamicBody;
    cajaDef.position.Set(polea2X, 150.0f);
    cajaDef.fixedRotation = true;
    caja = mundo->CreateBody(&cajaDef);

    b2PolygonShape cajaShape;
    cajaShape.SetAsBox(30.0f, 30.0f);
    b2FixtureDef cajaFix;
    cajaFix.shape = &cajaShape;
    cajaFix.density = 2.0f;
    cajaFix.friction = 0.3f;
    cajaFix.restitution = 0.1f;
    caja->CreateFixture(&cajaFix);

    
    b2PrismaticJointDef prisDef;
    b2Vec2 ejeVertical(0.0f, 1.0f);
    prisDef.Initialize(ancla, plataforma, plataforma->GetWorldCenter(), ejeVertical);
    prisDef.enableLimit = true;
    prisDef.lowerTranslation = -500.0f;
    prisDef.upperTranslation = 300.0f;
    prisDef.enableMotor = false; 
    prismaticJoint = (b2PrismaticJoint*)mundo->CreateJoint(&prisDef);

    
    b2PulleyJointDef pulleyDef;
    b2Vec2 anclaPolea1(polea1X, polea1Y);
    b2Vec2 anclaPolea2(polea2X, polea2Y);
    b2Vec2 anclaPlat = plataforma->GetWorldCenter();
    b2Vec2 anclaCaja = caja->GetWorldCenter();

    pulleyDef.Initialize(plataforma, caja,
        anclaPolea1, anclaPolea2,
        anclaPlat, anclaCaja,
        1.0f);
    pulleyJoint = (b2PulleyJoint*)mundo->CreateJoint(&pulleyDef);
}

void Plataforma::Mover(int direccion) {
    if (!plataforma || !caja) return;
    plataforma->SetAwake(true);
    caja->SetAwake(true);

    if (direccion == 0) {
        b2Vec2 vel = plataforma->GetLinearVelocity();
        b2Vec2 frenada(0.0f, -vel.y * plataforma->GetMass() * 10.0f);
        plataforma->ApplyForceToCenter(frenada, true);
    }
    else if (direccion == -1) {
        b2Vec2 fuerzaPlat(0.0f, -800000.0f);
        b2Vec2 fuerzaCaja(0.0f, 800000.0f);
        plataforma->ApplyForceToCenter(fuerzaPlat, true);
        caja->ApplyForceToCenter(fuerzaCaja, true);
    }
    else {
        b2Vec2 fuerzaPlat(0.0f, 800000.0f);
        b2Vec2 fuerzaCaja(0.0f, -800000.0f);
        plataforma->ApplyForceToCenter(fuerzaPlat, true);
        caja->ApplyForceToCenter(fuerzaCaja, true);
    }
}

void Plataforma::Draw() const {
    if (!plataforma || !caja) return;

    b2Vec2 posPlat = plataforma->GetWorldCenter();
    b2Vec2 posCaja = caja->GetWorldCenter();

    DrawLine((int)polea1X, (int)polea1Y, (int)polea1X, screenHeight - 40, DARKGRAY);
    DrawLine((int)polea2X, (int)polea2Y, (int)polea2X, screenHeight - 40, DARKGRAY);

    DrawLine((int)polea1X, (int)polea1Y, (int)posPlat.x, (int)posPlat.y, WHITE);
    DrawLine((int)polea2X, (int)polea2Y, (int)posCaja.x, (int)posCaja.y, WHITE);
    DrawLine((int)polea1X, (int)polea1Y, (int)polea2X, (int)polea2Y, WHITE);

    DrawCircle((int)polea1X, (int)polea1Y, 10, YELLOW);
    DrawCircleLines((int)polea1X, (int)polea1Y, 10, ORANGE);
    DrawCircle((int)polea2X, (int)polea2Y, 10, YELLOW);
    DrawCircleLines((int)polea2X, (int)polea2Y, 10, ORANGE);

    DrawRectangle((int)(posPlat.x - 70), (int)(posPlat.y - 10), 140, 20, SKYBLUE);
    DrawRectangleLines((int)(posPlat.x - 70), (int)(posPlat.y - 10), 140, 20, BLUE);
    DrawText("PLATAFORMA", (int)(posPlat.x - 40), (int)(posPlat.y - 8), 12, WHITE);

    DrawRectangle((int)(posCaja.x - 30), (int)(posCaja.y - 30), 60, 60, ORANGE);
    DrawRectangleLines((int)(posCaja.x - 30), (int)(posCaja.y - 30), 60, 60, DARKBROWN);
    DrawText("CAJA", (int)(posCaja.x - 15), (int)(posCaja.y - 8), 12, WHITE);

    DrawText("Pulley Joint", (int)polea1X + 15, (int)polea1Y - 5, 14, ORANGE);
    DrawText("Prismatic Joint", (int)(posPlat.x + 75), (int)(posPlat.y - 8), 14, GREEN);
}