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

#include <string>
#include <math.h>
#include <iostream>

using namespace std;


typedef struct Spaceship
{
    Vector2 position;
    Vector2 speed;
    int nSize;
    float rotation;
    Color color;
    bool active;

};



typedef struct Meteor
{
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
    Color color;
};

typedef struct Bullets
{
    Vector2 position;
    Vector2 speed;
    float radius;
    float rotation;
    int lifeSpawn;
    bool active;
    Color color;
};


const int maxShooting = 5;
static Bullets shooting[maxShooting];
static Spaceship player;
static int maxMeteor = 4;
static int maxMedMeteor = 8;
static int maxSmallMeteor = 16;
static Meteor* meteor = new Meteor[maxMeteor];
static Meteor* meteorMed = new Meteor[maxMedMeteor];
static Meteor* meteorSmall = new Meteor[maxSmallMeteor];
static bool victory = false;
float screenWidth = 1280;
float screenHeight = 720;
static float meteorSpeed = 3;
static float shipHeight;
static float playerSize = 20;
static float acceleration = 10;
static int destroyedMeteorsCount;
static int midMeteorsCount;
static int smallMeteorsCount;
static bool restart = false;
static bool nextRound = false;
int lives = 3;




void InitGame()
{
    float posx, posy;
    float velx, vely;
    bool correctRange = false;




    shipHeight = (playerSize / 2) / tanf(20 * DEG2RAD);
    player.position = { screenWidth / 2, screenHeight / 2 - shipHeight / 2 };
    player.speed = { 0, 0 };
    player.rotation = 0;
    player.nSize = 12;
    player.active = true;
    player.color = LIGHTGRAY;

    for (int i = 0; i < maxShooting; i++)
    {
        shooting[i].position = { 0, 0 };
        shooting[i].speed = { 0, 0 };
        shooting[i].radius = 2;
        shooting[i].active = false;
        shooting[i].lifeSpawn = 0;
        shooting[i].color = RED;
    }


    for (int i = 0; i < maxMeteor; i++)
    {
        posx = GetRandomValue(0, screenWidth);

        while (correctRange == false)
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

        while (correctRange == false)
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
        meteor[i].radius = 60;
        meteor[i].active = true;
        meteor[i].color = GRAY;




    }
    for (int i = 0; i < maxMedMeteor; i++)
    {

        meteorMed[i].position = { -100, -100 };
        meteorMed[i].speed = { velx, vely };
        meteorMed[i].radius = 45;
        meteorMed[i].active = false;
        meteorMed[i].color = BLACK;

    }
    for (int j = 0; j < maxSmallMeteor; j++)
    {

        meteorSmall[j].position = { -100, -100 };
        meteorSmall[j].speed = { velx, vely };
        meteorSmall[j].radius = 25;
        meteorSmall[j].active = false;
        meteorSmall[j].color = LIGHTGRAY;

    }


}
void UpdateGame(void)
{



    if (!restart)
    {

        if (IsKeyDown(KEY_LEFT))
        {
            player.rotation -= 5;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            player.rotation += 5;
        }

        if (IsKeyDown(KEY_UP))
        {
            player.speed.x += sin(player.rotation * DEG2RAD) * acceleration * GetFrameTime();
            player.speed.y -= cos(player.rotation * DEG2RAD) * acceleration * GetFrameTime();
        }

        player.position.x += player.speed.x;
        player.position.y += player.speed.y;





        if (player.position.x > screenWidth + shipHeight)
        {
            player.position.x = -(shipHeight);
        }
        else if (player.position.x < -(shipHeight))
        {
            player.position.x = screenWidth + shipHeight;
        }
        if (player.position.y > (screenHeight + shipHeight))
        {
            player.position.y = -(shipHeight);
        }
        else if (player.position.y < -(shipHeight))
        {
            player.position.y = screenHeight + shipHeight;
        }


        if (IsKeyPressed(KEY_SPACE))
        {
            for (int i = 0; i < maxShooting; i++)
            {
                if (shooting[i].active == false)
                {
                    shooting[i].position = { player.position.x , player.position.y };
                    shooting[i].active = true;
                    shooting[i].speed.x = 1.5 * sin(player.rotation * DEG2RAD) * acceleration;
                    shooting[i].speed.y = 1.5 * cos(player.rotation * DEG2RAD) * acceleration;
                    shooting[i].rotation = player.rotation;
                    break;
                }
            }
        }
        for (int i = 0; i < maxShooting; i++)
        {
            if (shooting[i].active) shooting[i].lifeSpawn++;
        }

        for (int i = 0; i < maxShooting; i++)
        {
            if (shooting[i].active)
            {

                shooting[i].position.x += shooting[i].speed.x;
                shooting[i].position.y -= shooting[i].speed.y;


                if (shooting[i].position.x > screenWidth + shooting[i].radius)
                {
                    shooting[i].active = false;
                    shooting[i].lifeSpawn = 0;
                }
                else if (shooting[i].position.x < 0 - shooting[i].radius)
                {
                    shooting[i].active = false;
                    shooting[i].lifeSpawn = 0;
                }
                if (shooting[i].position.y > screenHeight + shooting[i].radius)
                {
                    shooting[i].active = false;
                    shooting[i].lifeSpawn = 0;
                }
                else if (shooting[i].position.y < 0 - shooting[i].radius)
                {
                    shooting[i].active = false;
                    shooting[i].lifeSpawn = 0;
                }

                if (shooting[i].lifeSpawn >= 30)
                {
                    shooting[i].position = { 0, 0 };
                    shooting[i].speed = { 0, 0 };
                    shooting[i].lifeSpawn = 0;
                    shooting[i].active = false;
                }
            }
        }




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


        for (int i = 0; i < maxMedMeteor; i++)
        {
            if (meteorMed[i].active)
            {
                meteorMed[i].position.x += meteorMed[i].speed.x;
                meteorMed[i].position.y += meteorMed[i].speed.y;

                if (meteorMed[i].position.x > screenWidth + meteorMed[i].radius)
                {
                    meteorMed[i].position.x = -(meteorMed[i].radius);
                }
                else if (meteorMed[i].position.x < 0 - meteorMed[i].radius)
                {
                    meteorMed[i].position.x = screenWidth + (meteorMed[i].radius);
                }
                if (meteorMed[i].position.y > screenHeight + meteorMed[i].radius)
                {
                    meteorMed[i].position.y = -(meteorMed[i].radius);
                }
                else if (meteorMed[i].position.y < 0 - meteorMed[i].radius)
                {
                    meteorMed[i].position.y = screenHeight + (meteorMed[i].radius);
                }
            }
        }


        for (int i = 0; i < maxSmallMeteor; i++)
        {
            if (meteorSmall[i].active)
            {
                meteorSmall[i].position.x += meteorSmall[i].speed.x;
                meteorSmall[i].position.y += meteorSmall[i].speed.y;

                if (meteorSmall[i].position.x > screenWidth + meteorSmall[i].radius)
                {
                    meteorSmall[i].position.x = -(meteorSmall[i].radius);
                }
                else if (meteorSmall[i].position.x < 0 - meteorSmall[i].radius)
                {
                    meteorSmall[i].position.x = screenWidth + (meteorSmall[i].radius);
                }
                if (meteorSmall[i].position.y > screenHeight + meteorSmall[i].radius)
                {
                    meteorSmall[i].position.y = -(meteorSmall[i].radius);
                }
                else if (meteorSmall[i].position.y < 0 - meteorSmall[i].radius)
                {
                    meteorSmall[i].position.y = screenHeight + (meteorSmall[i].radius);
                }
            }
        }



        if (player.active)
        {
            for (int i = 0; i < maxMeteor; i++)
            {
                if (player.active && meteor[i].active && CheckCollisionCircles({ player.position.x, player.position.y }, player.nSize, meteor[i].position, meteor[i].radius))
                {
                    player.active = false;
                }
            }
            for (int i = 0; i < maxMedMeteor; i++)
            {
                if (player.active && meteorMed[i].active && CheckCollisionCircles({ player.position.x, player.position.y }, player.nSize, meteorMed[i].position, meteorMed[i].radius))
                {
                    player.active = false;

                }
            }
            for (int i = 0; i < maxSmallMeteor; i++)
            {
                if (player.active && meteorSmall[i].active && CheckCollisionCircles({ player.position.x, player.position.y }, player.nSize, meteorSmall[i].position, meteorSmall[i].radius))
                {
                    player.active = false;
                }
            }

            for (int i = 0; i < maxShooting; i++)
            {
                if (shooting[i].active)
                {
                    for (int j = 0; j < maxMeteor; j++)
                    {
                        if (meteor[j].active && CheckCollisionCircles(shooting[i].position, shooting[i].radius, meteor[j].position, meteor[j].radius))
                        {
                            shooting[i].active = false;
                            shooting[i].lifeSpawn = 0;
                            meteor[j].active = false;
                            destroyedMeteorsCount++;

                            for (int k = 0; k < 2; k++)
                            {
                                if (midMeteorsCount % 2 == 0)
                                {
                                    meteorMed[midMeteorsCount].position = { meteor[j].position.x, meteor[j].position.y };
                                    meteorMed[midMeteorsCount].speed = { cos(shooting[i].rotation * DEG2RAD) * meteorSpeed * -1, sin(shooting[i].rotation * DEG2RAD) * meteorSpeed * -1 };
                                }
                                else
                                {
                                    meteorMed[midMeteorsCount].position = { meteor[j].position.x, meteor[j].position.y };
                                    meteorMed[midMeteorsCount].speed = { cos(shooting[i].rotation * DEG2RAD) * meteorSpeed, sin(shooting[i].rotation * DEG2RAD) * meteorSpeed };
                                }

                                meteorMed[midMeteorsCount].active = true;
                                midMeteorsCount++;



                            }
                            meteor[j].color = WHITE;
                            j = maxMeteor;
                        }
                    }

                    for (int a = 0; a < maxMedMeteor; a++)
                    {
                        if (meteorMed[a].active && CheckCollisionCircles(shooting[i].position, shooting[i].radius, meteorMed[a].position, meteorMed[a].radius))
                        {
                            shooting[i].active = false;
                            shooting[i].lifeSpawn = 0;
                            meteorMed[a].active = false;
                            destroyedMeteorsCount++;

                            for (int l = 0; l < 2; l++)
                            {
                                if (smallMeteorsCount % 2 == 0)
                                {
                                    meteorSmall[smallMeteorsCount].position = { meteorMed[a].position.x, meteorMed[a].position.y };
                                    meteorSmall[smallMeteorsCount].speed = { cos(shooting[i].rotation * DEG2RAD) * meteorSpeed * -1, sin(shooting[i].rotation * DEG2RAD) * meteorSpeed * -1 };
                                }
                                else
                                {
                                    meteorSmall[smallMeteorsCount].position = { meteorMed[a].position.x, meteorMed[a].position.y };
                                    meteorSmall[smallMeteorsCount].speed = { cos(shooting[i].rotation * DEG2RAD) * meteorSpeed, sin(shooting[i].rotation * DEG2RAD) * meteorSpeed };
                                }

                                meteorSmall[smallMeteorsCount].active = true;
                                smallMeteorsCount++;



                            }
                            meteorMed[a].color = WHITE;
                            a = maxMedMeteor;
                        }
                    }

                    for (int b = 0; b < maxSmallMeteor; b++)
                    {
                        if (meteorSmall[b].active && CheckCollisionCircles(shooting[i].position, shooting[i].radius, meteorSmall[b].position, meteorSmall[b].radius))
                        {
                            shooting[i].active = false;
                            shooting[i].lifeSpawn = 0;
                            meteorSmall[b].active = false;
                            destroyedMeteorsCount++;
                            meteorSmall[b].color = WHITE;
                            b = maxSmallMeteor;
                        }
                    }
                }
            }


        }
        else
        {
            restart = true;
            lives -= 1;
            if (lives == 0)
            {
                maxMeteor = 1;
                maxMedMeteor = 2;
                maxSmallMeteor = 4;
                lives = 3;
            }

            midMeteorsCount = 0;
            smallMeteorsCount = 0;
            destroyedMeteorsCount = 0;

        }
        if (destroyedMeteorsCount == maxMeteor + maxMedMeteor + maxSmallMeteor)
        {
            victory = true;
        }
        if (victory == true)
        {

            restart = true;
            delete[] meteor;
            delete[] meteorMed;
            delete[] meteorSmall;

            midMeteorsCount = 0;
            smallMeteorsCount = 0;
            destroyedMeteorsCount = 0;
            maxMeteor += 1;
            maxMedMeteor += 2;
            maxSmallMeteor += 4;


            meteor = new Meteor[maxMeteor];
            meteorMed = new Meteor[maxMedMeteor];
            meteorSmall = new Meteor[maxSmallMeteor];


        }







    }
    else
    {
        if (IsKeyDown(KEY_R))
        {
            InitGame();
            victory = false;
            restart = false;
        }
    }

}

void DrawGame()
{




    ClearBackground(RAYWHITE);


    if (lives > 0)
    {
        DrawText(to_string(lives).c_str(), screenWidth / 15, screenHeight / 10, 25, RED);
        DrawText("lives: ", screenWidth / 120, screenHeight / 10, 25, RED);
    }
    if (player.active)
    {
        Vector2 v1 = { player.position.x + sinf(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cosf(player.rotation * DEG2RAD) * (shipHeight) };
        Vector2 v2 = { player.position.x - cosf(player.rotation * DEG2RAD) * (playerSize / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (playerSize / 2) };
        Vector2 v3 = { player.position.x + cosf(player.rotation * DEG2RAD) * (playerSize / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (playerSize / 2) };
        DrawTriangle(v1, v2, v3, RED);
    }
    else
    {
        Vector2 v1 = { player.position.x + sinf(player.rotation * DEG2RAD) * (shipHeight), player.position.y - cosf(player.rotation * DEG2RAD) * (shipHeight) };
        Vector2 v2 = { player.position.x - cosf(player.rotation * DEG2RAD) * (playerSize / 2), player.position.y - sinf(player.rotation * DEG2RAD) * (playerSize / 2) };
        Vector2 v3 = { player.position.x + cosf(player.rotation * DEG2RAD) * (playerSize / 2), player.position.y + sinf(player.rotation * DEG2RAD) * (playerSize / 2) };
        DrawTriangle(v1, v2, v3, Fade(RAYWHITE, 0.1));
        shooting->active = false;
        DrawText("YOU LOSE!!", screenWidth / 2 - 250, screenHeight / 2, 100, RED);
        DrawText("Press r to restart", screenWidth / 2 - 250, screenHeight / 1.25f, 50, RED);
    }


    for (int i = 0; i < maxMeteor; i++)
    {
        if (meteor[i].active)
        {
            DrawCircleV(meteor[i].position, meteor[i].radius, BLACK);
        }
        else
        {
            DrawCircleV(meteor[i].position, meteor[i].radius, Fade(RAYWHITE, 0.1));
        }
    }
    for (int i = 0; i < maxMedMeteor; i++)
    {
        if (meteorMed[i].active)
        {
            DrawCircleV(meteorMed[i].position, meteorMed[i].radius, DARKGRAY);
        }
        else
        {
            DrawCircleV(meteorMed[i].position, meteorMed[i].radius, Fade(RAYWHITE, 0.1));
        }
    }
    for (int i = 0; i < maxSmallMeteor; i++)
    {
        if (meteorSmall[i].active)
        {
            DrawCircleV(meteorSmall[i].position, meteorSmall[i].radius, DARKGRAY);
        }
        else
        {
            DrawCircleV(meteorSmall[i].position, meteorSmall[i].radius, Fade(RAYWHITE, 0.1));
        }
    }

    for (int i = 0; i < maxShooting; i++)
    {
        if (shooting[i].active) DrawCircleV(shooting[i].position, shooting[i].radius, RED);
    }

    if (victory == true)
    {
        DrawText("YOU WIN!!", screenWidth / 2 - 250, screenHeight / 2, 100, RED);
        DrawText("Press r to for next round", screenWidth / 2 - 250, screenHeight / 1.25f, 50, RED);
    }
    else
    {
        DrawText("", screenWidth / 2 - 450, screenHeight / 2, 100, RED);
    }


}

void UpdateDrawFrame()
{
    UpdateGame();
    DrawGame();
}



int main(int argc, char* argv[])
{



    InitWindow(screenWidth, screenHeight, "asteroid");

    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();


        UpdateDrawFrame();


        EndDrawing();
    }


    CloseWindow();


    return 0;
}