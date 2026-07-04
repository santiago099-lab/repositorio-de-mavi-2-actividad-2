#include "raylib.h"
#include "Mundo.h"
#include "Proyectil.h"
#include "Objetivo.h"


enum Estado {WAITING,RUNNING,EVENT_DETECTED,FINISHED};      
         
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Tiro al Objetivo");
    SetTargetFPS(60);

    
    Mundo mundo;
    mundo.Init(screenWidth, screenHeight);

    Proyectil proyectil;
    proyectil.Init(mundo.GetWorld(), screenWidth / 2.0f, 80.0f);

    
    Objetivo objetivo;
    objetivo.Init(mundo.GetWorld(), screenWidth / 2.0f, screenHeight / 2.0f);

    Estado estado = WAITING;
    float  timerMsg = 0.0f;  
    int    aciertos = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

       
        if (estado == WAITING && IsKeyPressed(KEY_SPACE)) {
            
            proyectil.Reset(screenWidth / 2.0f, 80.0f);
            estado = RUNNING;
            mundo.GetListener()->Reset();
        }

        if ((estado == EVENT_DETECTED || estado == FINISHED) && IsKeyPressed(KEY_R)) {
            
            proyectil.Reset(screenWidth / 2.0f, 80.0f);
            mundo.GetListener()->Reset();
            estado = WAITING;
        }

        if (estado == RUNNING) {
            
            if (mundo.GetListener()->EventoDetectado()) {
                estado = EVENT_DETECTED;
                timerMsg = 2.0f;
                aciertos++;
            }

            
            b2Vec2 pos = proyectil.GetBody()->GetPosition();
            if (pos.y > screenHeight - 40) {
                estado = FINISHED;
                timerMsg = 2.0f;
            }
        }

        if (estado == EVENT_DETECTED) {
            timerMsg -= dt;
            if (timerMsg <= 0.0f) estado = WAITING;
        }

        if (estado == FINISHED) {
            timerMsg -= dt;
            if (timerMsg <= 0.0f) estado = WAITING;
        }

        mundo.Step(dt);

        BeginDrawing();

        mundo.Draw();
        objetivo.Draw(estado == EVENT_DETECTED);
        proyectil.Draw();

        
        DrawRectangle(0, 0, 500, 90, Fade(BLACK, 0.5f));
        DrawText("MAVI II - Tiro al Objetivo", 10, 10, 22, RAYWHITE);
        DrawText("b2ContactListener: deteccion de colision", 10, 40, 15, YELLOW);
        DrawText(TextFormat("Aciertos: %d", aciertos), 10, 60, 18, GREEN);

        
        if (estado == WAITING) {
            DrawText("ESPACIO: lanzar proyectil   R: reiniciar", 10, screenHeight - 30, 18, LIGHTGRAY);
                
        }

        
        if (estado == EVENT_DETECTED) {
            int tw = MeasureText("IMPACTO DETECTADO!", 50);
            DrawRectangle(0, screenHeight / 2 - 40, screenWidth, 80, Fade(BLACK, 0.7f));
            DrawText("IMPACTO DETECTADO!", screenWidth / 2 - tw / 2, screenHeight / 2 - 25, 50, GREEN);
        }

        if (estado == FINISHED) {
            int tw = MeasureText("Fallaste! Presiona R para reiniciar", 30);
            DrawRectangle(0, screenHeight / 2 - 30, screenWidth, 60, Fade(BLACK, 0.7f));
            DrawText("Fallaste! Presiona R para reiniciar", screenWidth / 2 - tw / 2, screenHeight / 2 - 15, 30, RED);
        }
                

        
        const char* estadoStr = "";
        switch (estado) {
        case WAITING:        estadoStr = "Estado: WAITING";        break;
        case RUNNING:        estadoStr = "Estado: RUNNING";        break;
        case EVENT_DETECTED: estadoStr = "Estado: EVENT_DETECTED"; break;
        case FINISHED:       estadoStr = "Estado: FINISHED";       break;
        }
        DrawText(estadoStr, screenWidth - 250, 10, 18, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}