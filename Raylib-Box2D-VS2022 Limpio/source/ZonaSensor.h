#pragma once
#include "raylib.h"
#include <box2d.h>

class ZonaSensor {
public:
    ZonaSensor();
    void Init(b2World* mundo, float x, float y, float ancho, float alto);
    void Draw(bool activa) const;
    b2Body* GetBody() const;
private:
    b2Body* body;
    float   ancho;
    float   alto;
};