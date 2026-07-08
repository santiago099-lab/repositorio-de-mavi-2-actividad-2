#pragma once
#include "raylib.h"
#include <box2d.h>

const int ID_LANZADOR = 1;
const int ID_SENSOR = 2;
const int ID_SUELO = 3;

class ContactListener : public b2ContactListener {
public:
    ContactListener();
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    bool DentroDelSensor() const;
    void Reset();
private:
    bool dentroDelSensor;
};

class Mundo {
public:
    Mundo();
    ~Mundo();
    void Init(int screenWidth, int screenHeight);
    void Step(float dt);
    void Draw() const;
    b2World* GetWorld();
    ContactListener* GetListener();
    int GetWidth()  const;
    int GetHeight() const;
private:
    b2World* mundo;
    b2Body* suelo;
    ContactListener listener;
    int screenWidth;
    int screenHeight;
};