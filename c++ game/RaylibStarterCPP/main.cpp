/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <math.h>
using namespace std;

typedef struct Meteor
{
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
};


const int maxMeteor = 4;
static Meteor meteor[maxMeteor];
static bool victory = false;
int screenWidth = 1280;
int screenHeight = 720;
static float shipHeight = 0;
static float meteorSpeed = 2;















void DrawGame(void)
{
    BeginDrawing();

    

    ClearBackground(RAYWHITE);

    for (int i = 0; i < maxMeteor; i++)
    {
        if (meteor[i].active) DrawCircleV(meteor[i].position, meteor[i].radius, DARKGRAY);
        else DrawCircleV(meteor[i].position, meteor[i].radius, Fade(LIGHTGRAY, 0.3f));
    }

    EndDrawing();
}

void UpdateGame(void)
{
    for (int i = 0; i < maxMeteor; i++)
    {
        if (meteor[i].active)
        {
            meteor[i].position.x += meteor[i].speed.x;
            meteor[i].position.y += meteor[i].speed.y;

            if (meteor[i].position.x > screenWidth + meteor[i].radius)
            {
                meteor[i].position.x = -(meteor[i].radius);
            }
            else if (meteor[i].position.x < 0 - meteor[i].radius)
            {
                meteor[i].position.x = screenWidth + (meteor[i].radius);
            }
            if (meteor[i].position.y > screenHeight + meteor[i].radius)
            {
                meteor[i].position.y = -(meteor[i].radius);
            }
            else if (meteor[i].position.y < 0 - meteor[i].radius)
            {
                meteor[i].position.y = screenHeight + (meteor[i].radius);
            }
        }
    }
}

void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

void InitGame(void)
{
    float posx, posy;
    float velx, vely;
    bool correctRange = false;
    victory = false;

    shipHeight = (20.0f / 2) / tanf(20 * DEG2RAD);


    for (int i = 0; i < maxMeteor; i++)
    {
        posx = GetRandomValue(0, screenWidth);

        while (!correctRange)
        {
            if (posx > screenWidth / 2 - 150 && posx < screenWidth / 2 + 150)
            {
                posx = GetRandomValue(0, screenWidth);

            }
            else
            {
                correctRange = true;
            }
        }
        correctRange = false;

        posy = GetRandomValue(0, screenHeight);

        while (!correctRange)
        {
            if (posy > screenHeight / 2 - 150 && posy < screenHeight / 2 + 150)  posy = GetRandomValue(0, screenHeight);
            else correctRange = true;
        }

        meteor[i].position = { posx, posy };

        correctRange = false;

        velx = GetRandomValue(-meteorSpeed, meteorSpeed);
        vely = GetRandomValue(-meteorSpeed, meteorSpeed);

        while (!correctRange)
        {
            if (velx == 0 && vely == 0)
            {

                velx = GetRandomValue(-meteorSpeed, meteorSpeed);
                vely = GetRandomValue(-meteorSpeed, meteorSpeed);
            }
            else correctRange = true;
        }

        meteor[i].speed = { velx, vely };
        meteor[i].radius = 40;
        meteor[i].active = true;
        meteor[i].color = GRAY;
        
    }
}

int main(int argc, char* argv[])
{



    InitWindow(screenWidth, screenHeight, "asteroid");

    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose())
    {

       

              

        UpdateDrawFrame();
        

    }


    CloseWindow();


    return 0;
}