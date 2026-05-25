#pragma once
#include "raylib.h"
#include <box2d.h>


class Escena {
public:
    Escena();
    ~Escena();

    void Init(int screenWidth, int screenHeight);
    void Step(float dt);
    void Draw() const;

    b2World* GetWorld();
    int GetWidth()  const;
    int GetHeight() const;

private:
    b2World* mundo;
    b2Body* suelo;
    int screenWidth;
    int screenHeight;
};
