#pragma once
#include "raylib.h"
#include <box2d.h>

const int CANT_BOLAS = 5;

class PendulodeNewton {
public:
    PendulodeNewton();

    void Init(b2World* mundo, float pivoteX, float pivoteY,float longitud, float radio);
    
    void Draw() const;

   
    void AplicarImpulso();

private:
    
    b2Body* bolas[CANT_BOLAS];

    
    b2Body* pivotes[CANT_BOLAS];

    b2RevoluteJoint* revoluteJoints[CANT_BOLAS]; 
    b2DistanceJoint* distanceJoints[CANT_BOLAS]; 

    float longitud;
    float radio;

    
    float soporteX;
    float soporteY;
};

