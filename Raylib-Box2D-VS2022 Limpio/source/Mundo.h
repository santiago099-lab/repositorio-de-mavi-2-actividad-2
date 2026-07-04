#pragma once
#include "raylib.h"
#include <Box2d.h>


class ContactListener : public b2ContactListener {
public:
	ContactListener();

	void BeginContact(b2Contact* contact) override;

	bool EventoDetectado() const;

	void Reset();

private:
	bool eventoDetectado;
};

class Mundo {
public:
	Mundo();
	 ~Mundo();

	 void Init(int screenWidth, int screenHeiht);
	 void Step(float dt);
	 void Draw() const;

	 b2World* GetWorld();
	 ContactListener* GetListener();
	 int GetWidth() const;
	 int GetHeight() const;

private:
	b2World* mundo;
	b2Body* suelo;
	ContactListener listener;

	int ScreenWidth;
	int ScreenHeight;
};
