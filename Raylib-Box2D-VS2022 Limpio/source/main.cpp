#include "raylib.h"
#include "Escena.h"
#include "PendulodeNewton.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Pendulo de Newton");
    SetTargetFPS(60);

    Escena escena;
    escena.Init(screenWidth, screenHeight);

    PendulodeNewton pendulo;
    pendulo.Init(escena.GetWorld(), screenWidth / 2.0f, 150.0f, 200.0f, 20.0f);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE)) {
            pendulo.AplicarImpulso();
        }

        escena.Step(dt);

        BeginDrawing();

        escena.Draw();
        pendulo.Draw();

        DrawText("MAVI II - Pendulo de Newton", 10, 10, 22, RAYWHITE);
        DrawText("Revolute Joint: pivote de rotacion de cada bola", 10, 40, 16, YELLOW);
        DrawText("Distance Joint: longitud fija de cada cuerda", 10, 60, 16, YELLOW);
        DrawText("ESPACIO: aplicar impulso a la primera bola", 10, 90, 16, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}