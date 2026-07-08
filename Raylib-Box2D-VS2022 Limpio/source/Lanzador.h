#pragma once
#include "raylib.h"
#include <box2d.h>

class Lanzador {
public:
    Lanzador();
    void Init(b2World* mundo, float x, float y);
    void AjustarAngulo(int dir);
    void AjustarPotencia(int dir);
    void Disparar();
    void Reset(float x, float y);
    void Draw() const;
    float   GetAngulo()    const;
    float   GetPotencia()  const;
    bool    FueDisparado() const;
    b2Body* GetBody()      const;
private:
    b2World* mundo;
    b2Body* body;
    b2Body* bola;
    float angulo;
    float potencia;
    bool  disparado;
    float initX, initY;
    float ancho, alto;
};