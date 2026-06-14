#include "raylib.h"
#include "Escena.h"
#include "raylib.h"
#include "Plataforma.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Ascensor con Polea");
    SetTargetFPS(60);

    Escena escena;
    escena.Init(screenWidth, screenHeight);

    Plataforma plataforma;
    plataforma.Init(escena.GetWorld(), screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_UP)) {
            plataforma.Mover(-1);
        }
        else if (IsKeyDown(KEY_DOWN)) {
            plataforma.Mover(1);
        }
        else {
            plataforma.Mover(0);
        }

        escena.Step(dt);

        BeginDrawing();

        escena.Draw();
        plataforma.Draw();

        DrawRectangle(0, 0, 580, 115, Fade(BLACK, 0.5f));
        DrawText("MAVI II - Ascensor con Polea", 10, 10, 22, RAYWHITE);
        DrawText("Prismatic Joint: plataforma restringida al eje Y", 10, 40, 16, GREEN);
        DrawText("Pulley Joint:    polea conecta plataforma y caja", 10, 60, 16, ORANGE);
        DrawText("Flechas arriba/abajo: mover la plataforma", 10, 85, 16, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}