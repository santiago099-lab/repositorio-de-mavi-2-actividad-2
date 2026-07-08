#include "raylib.h"
#include "Mundo.h"
#include "Lanzador.h"
#include "ZonaSensor.h"
#include <cmath>

enum Estado { WAITING, RUNNING, EVENT_DETECTED, FINISHED };

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "MAVI II - Sistema de Lanzamiento");
    SetTargetFPS(60);

    Mundo mundo;
    mundo.Init(screenWidth, screenHeight);

    Lanzador lanzador;
    float lanzX = 120.0f;
    float lanzY = screenHeight - 80.0f;
    lanzador.Init(mundo.GetWorld(), lanzX, lanzY);

    ZonaSensor zona;
    zona.Init(mundo.GetWorld(), 750.0f, screenHeight - 120.0f, 150.0f, 160.0f);

    Estado estado = WAITING;
    float  timerMsg = 0.0f;
    int    intentos = 0;
    int    aciertos = 0;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (estado == WAITING) {
            if (IsKeyDown(KEY_W)) lanzador.AjustarAngulo(1);
            if (IsKeyDown(KEY_S)) lanzador.AjustarAngulo(-1);
            if (IsKeyDown(KEY_D)) lanzador.AjustarPotencia(1);
            if (IsKeyDown(KEY_A)) lanzador.AjustarPotencia(-1);
            if (IsKeyPressed(KEY_SPACE)) {
                lanzador.Disparar();
                estado = RUNNING;
                intentos++;
                mundo.GetListener()->Reset();
            }
        }

        if (IsKeyPressed(KEY_R)) {
            lanzador.Reset(lanzX, lanzY);
            mundo.GetListener()->Reset();
            estado = WAITING;
            timerMsg = 0.0f;
        }

        if (estado == RUNNING) {
            if (mundo.GetListener()->DentroDelSensor()) {
                estado = EVENT_DETECTED;
                timerMsg = 3.0f;
                aciertos++;
            }
            b2Vec2 pos = lanzador.GetBody()->GetPosition();
            if (pos.y > screenHeight - 50 && !mundo.GetListener()->DentroDelSensor()) {
                estado = FINISHED;
                timerMsg = 3.0f;
            }
        }

        if (estado == EVENT_DETECTED || estado == FINISHED) {
            timerMsg -= dt;
            if (timerMsg <= 0.0f) {
                lanzador.Reset(lanzX, lanzY);
                mundo.GetListener()->Reset();
                estado = WAITING;
            }
        }

        mundo.Step(dt);

        BeginDrawing();
        mundo.Draw();
        zona.Draw(mundo.GetListener()->DentroDelSensor());
        lanzador.Draw();

        DrawRectangle(0, 0, 360, 140, ColorAlpha(BLACK, 0.55f));
        DrawText("MAVI II - Sistema de Lanzamiento", 10, 8, 18, RAYWHITE);
        DrawText("W/S: ajustar angulo", 10, 35, 15, LIGHTGRAY);
        DrawText("A/D: ajustar potencia", 10, 55, 15, LIGHTGRAY);
        DrawText("ESPACIO: disparar  |  R: reiniciar", 10, 75, 15, LIGHTGRAY);
        DrawText(TextFormat("Angulo:   %.0f grados", lanzador.GetAngulo()), 10, 100, 15, YELLOW);
        DrawText(TextFormat("Potencia: %.0f", lanzador.GetPotencia()), 10, 118, 15, YELLOW);

        DrawRectangle(screenWidth - 200, 0, 200, 60, ColorAlpha(BLACK, 0.55f));
        DrawText(TextFormat("Intentos: %d", intentos), screenWidth - 190, 10, 16, WHITE);
        DrawText(TextFormat("Aciertos: %d", aciertos), screenWidth - 190, 32, 16, GREEN);

        const char* estadoStr = "";
        Color estadoColor = WHITE;
        switch (estado) {
        case WAITING:        estadoStr = "Estado: WAITING";        estadoColor = LIGHTGRAY; break;
        case RUNNING:        estadoStr = "Estado: RUNNING";        estadoColor = YELLOW;    break;
        case EVENT_DETECTED: estadoStr = "Estado: EVENT_DETECTED"; estadoColor = GREEN;     break;
        case FINISHED:       estadoStr = "Estado: FINISHED";       estadoColor = RED;       break;
        }
        DrawText(estadoStr, screenWidth / 2 - MeasureText(estadoStr, 18) / 2,
            screenHeight - 30, 18, estadoColor);

        if (estado == EVENT_DETECTED) {
            DrawRectangle(0, screenHeight / 2 - 50, screenWidth, 100, ColorAlpha(BLACK, 0.7f));
            const char* msg = "OBJETIVO ALCANZADO!";
            DrawText(msg, screenWidth / 2 - MeasureText(msg, 50) / 2, screenHeight / 2 - 25, 50, GREEN);
        }

        if (estado == FINISHED) {
            DrawRectangle(0, screenHeight / 2 - 50, screenWidth, 100, ColorAlpha(BLACK, 0.7f));
            const char* msg = "FALLASTE! Intenta de nuevo...";
            DrawText(msg, screenWidth / 2 - MeasureText(msg, 35) / 2, screenHeight / 2 - 18, 35, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}