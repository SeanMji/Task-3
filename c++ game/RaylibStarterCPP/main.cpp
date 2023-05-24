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

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include <vector>
using namespace std;

struct GameObject
{
    float x;
    float y;
    float dx;
    float dy;
    int nSize;
};

vector <GameObject> vecAsteroids;

bool OnUserCreate()
{
    vecAsteroids.push_back({ 20, 20, 8, -6, (int)16 });

    //update and draw asteroids
    for (auto &a : vecAsteroids)
    {
        a.x += a.dx * GetFrameTime();
        a.y += a.dy * GetFrameTime();

        for (int i = 0; i < a.nSize; i++)
        {
            //yea more test
        }
    }


        return true;
}


int main(int argc, char* argv[])
{
    
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "asteroid");

    SetTargetFPS(60);
    

    
    while (!WindowShouldClose())    
    {
      
        BeginDrawing();

        ClearBackground(RAYWHITE);

        

        EndDrawing();
        
    }

     
    CloseWindow();        
   

    return 0;
}