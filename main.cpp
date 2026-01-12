#include <iostream>
#include "raylib/include/raylib.h"
#include "PerlinNoise.hpp"

int main()
{
    InitWindow(800, 500, "Mineacraft alpha 0.0.0");
    SetTargetFPS(60);
    
    const siv::PerlinNoise::seed_type seed = 124324342u;
    const siv::PerlinNoise perlin{ seed };

    Camera3D cam = { 0 };
    cam.position = (Vector3) {10,0,0};
    cam.up = (Vector3) {0,1,0};
    cam.target = (Vector3) {0,0,0};
    cam.projection = CAMERA_PERSPECTIVE;
    cam.fovy = 90;

    const int worldSize = 64;
    int worldMap[worldSize][worldSize];
    bool hidden = 1;
    DisableCursor();

    for (int x = 0; x < worldSize; x++)
    {
        for (int z = 0; z < worldSize; z++) 
        {
            double n = perlin.octave2D_01(x * 0.05, z * 0.05, 4);
            worldMap[x][z] = static_cast<int>(n * 15); // Высота от 0 до 15
        }
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(30, 30); 
        ClearBackground(SKYBLUE);
            UpdateCamera(&cam, CAMERA_FREE);
                BeginMode3D(cam);
                    for (int x = 0; x < worldSize; x++)
                    {
                        for (int z = 0; z < worldSize; z++) 
                        {
                            int currentHeight = worldMap[x][z];

                            for (int y = 0; y <= currentHeight; y++)
                            {
                                bool isVisible = false;

                                if (y == currentHeight) isVisible = true;
                                else
                                {
                                    if (x > 0 && worldMap[x - 1][z] < y) isVisible = true;
                                    else if (x < worldSize - 1 && worldMap[x + 1][z] < y) isVisible = true;
                                    else if (z > 0 && worldMap[x][z - 1] < y) isVisible = true;
                                    else if (z < worldSize - 1 && worldMap[x][z + 1] < y) isVisible = true;
                                }

                                if (isVisible) 
                                {
                                    Vector3 pos = {(float)x, (float)y, (float)z};
                                    Color col = (y == currentHeight) ? LIME : BROWN;
                                    if (y < currentHeight - 3) col = GRAY;

                                    DrawCube(pos, 1.0f, 1.0f, 1.0f, col);
                                    if(y == currentHeight) DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, DARKGREEN);
                                }
                            }   
                        }
                    }      
                EndMode3D(); 
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
