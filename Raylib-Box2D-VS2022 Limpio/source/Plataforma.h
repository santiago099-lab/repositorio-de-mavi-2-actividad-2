#pragma once
#include "raylib.h"
#include <box2d.h>

class Plataforma {
public:
    Plataforma();

    void Init(b2World* mundo, int screenWidth, int screenHeight);

    void Mover(int direccion);

    void Draw() const;

private:
    
    b2Body* ancla;       
    b2Body* plataforma;  
    b2Body* caja;        

    b2PrismaticJoint* prismaticJoint; 
    b2PulleyJoint* pulleyJoint;   

    int screenWidth;
    int screenHeight;

    float polea1X, polea1Y;
    float polea2X, polea2Y;
};