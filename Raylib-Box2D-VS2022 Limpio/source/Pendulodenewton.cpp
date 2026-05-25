#include "PendulodeNewton.h"

PendulodeNewton::PendulodeNewton()
    : longitud(0), radio(0), soporteX(0), soporteY(0)
{
    for (int i = 0; i < CANT_BOLAS; i++) {
        bolas[i] = nullptr;
        pivotes[i] = nullptr;
        revoluteJoints[i] = nullptr;
        distanceJoints[i] = nullptr;
    }
}

void PendulodeNewton::Init(b2World* mundo, float pivoteX, float pivoteY,
    float long_, float rad)
{
    longitud = long_;
    radio = rad;
    soporteX = pivoteX;
    soporteY = pivoteY;

    float separacion = radio * 2.0f;

    float totalAncho = separacion * (CANT_BOLAS - 1);
    float startX = pivoteX - totalAncho / 2.0f;

    for (int i = 0; i < CANT_BOLAS; i++) {
        float px = startX + i * separacion;
        float py = pivoteY;

        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set(px, py);
        pivotes[i] = mundo->CreateBody(&pivoteDef);

        b2CircleShape pivoteShape;
        pivoteShape.m_radius = 5.0f;
        pivotes[i]->CreateFixture(&pivoteShape, 0.0f);

        
        b2BodyDef bolaDef;
        bolaDef.type = b2_dynamicBody;
        bolaDef.position.Set(px, py + longitud);
        bolaDef.bullet = true; 
        bolas[i] = mundo->CreateBody(&bolaDef);

        b2CircleShape bolaShape;
        bolaShape.m_radius = radio;

        b2FixtureDef bolaFixture;
        bolaFixture.shape = &bolaShape;
        bolaFixture.density = 5.0f;   
        bolaFixture.friction = 0.0f;   
        bolaFixture.restitution = 1.0f;   
        bolas[i]->CreateFixture(&bolaFixture);

        
        b2RevoluteJointDef revoluteDef;
        revoluteDef.Initialize(pivotes[i], bolas[i], pivotes[i]->GetWorldCenter());
        revoluteDef.enableLimit = false;
        revoluteJoints[i] = (b2RevoluteJoint*)mundo->CreateJoint(&revoluteDef);

        
        b2DistanceJointDef distanceDef;
        distanceDef.Initialize(
            pivotes[i], bolas[i],
            pivotes[i]->GetWorldCenter(),
            bolas[i]->GetWorldCenter()
        );
        distanceDef.length = longitud;
        distanceJoints[i] = (b2DistanceJoint*)mundo->CreateJoint(&distanceDef);
    }
}

void PendulodeNewton::AplicarImpulso() {
    if (!bolas[0]) return;

    bolas[0]->SetAwake(true);
    b2Vec2 impulso(800000.0f, 0.0f);
    bolas[0]->ApplyLinearImpulse(impulso, bolas[0]->GetWorldCenter(), true);
}

void PendulodeNewton::Draw() const {
    
    float separacion = radio * 2.0f;
    float totalAncho = separacion * (CANT_BOLAS - 1);
    float startX = soporteX - totalAncho / 2.0f;
    float endX = soporteX + totalAncho / 2.0f;

    DrawLine((int)startX, (int)soporteY - 60,
        (int)startX, (int)soporteY, GRAY);
    
    DrawLine((int)endX, (int)soporteY - 60,
        (int)endX, (int)soporteY, GRAY);
    
    DrawLine((int)startX - 20, (int)soporteY,
        (int)endX + 20, (int)soporteY, GRAY);
    DrawLine((int)startX - 20, (int)soporteY - 60,
        (int)endX + 20, (int)soporteY - 60, GRAY);

    for (int i = 0; i < CANT_BOLAS; i++) {
        if (!pivotes[i] || !bolas[i]) continue;

        b2Vec2 posPivote = pivotes[i]->GetWorldCenter();
        b2Vec2 posBola = bolas[i]->GetWorldCenter();

        
        DrawLine(
            (int)posPivote.x, (int)posPivote.y,
            (int)posBola.x, (int)posBola.y,
            LIGHTGRAY
        );

        
        DrawCircle((int)posPivote.x, (int)posPivote.y, 6, YELLOW);

       
        DrawCircle((int)posBola.x, (int)posBola.y, (int)radio, ORANGE);
        DrawCircleLines((int)posBola.x, (int)posBola.y, (int)radio, YELLOW);
    }
}