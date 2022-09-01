/*******************************************************************************************
*
*   
*
*
*   Copyright (c) 2022 ==Maria Cristina== @maricristinai
*
********************************************************************************************/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>




#include "raylib.h"
int randomtime(int max)
{
    return rand() % max;

}


void DrawBike(int x, int y) {
    x += -150;
    y += -300;
    DrawCircleLines(100 + x, 340 + y, 40, BLACK);
    DrawCircleLines(250 + x, 340 + y, 40, BLACK);
    DrawTriangleLines((Vector2) { 150 + x, 340 + y },
        (Vector2) {
        240 + x, 290 + y
    },
        (Vector2) {
        140 + x, 290 + y
    }, BLUE);
    DrawTriangleLines((Vector2) { 150 + x, 340 + y },
        (Vector2) {
        100 + x, 340 + y
    },
        (Vector2) {
        140 + x, 290 + y
    }, BLUE);
    DrawLine(250 + x, 340 + y, 240 + x, 290 + y, RED);
    DrawLine(240 + x, 290 + y, 240 + x, 275 + y, RED);
    DrawLine(225 + x, 275 + y, 240 + x, 275 + y, RED);
    DrawLine(140 + x, 290 + y, 140 + x, 275 + y, RED);
    DrawLine(130 + x, 275 + y, 150 + x, 275 + y, BLACK);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    srand(time(NULL)); 
    const int screenWidth = 800;
    const int screenHeight = 697;
    int jump_frame_count = 0;
    int obstacle_x_i = -900;
    int obstacle_x;
    int obstacle_x_xspeed = 10;
    int points = 0;
    char points_str[50];
    bool game_over = false;
    int obstacle_x_iwine = -600;
    int obstacle_xwine = 90;
    int obstacle_x_xspeedwine = 10;

    Vector2 bike_position = { 200, screenHeight - 80 };

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

    Texture2D background = LoadTexture("img/bg.png");
    Texture2D rock = LoadTexture("img/rock.png");
    Texture2D wine = LoadTexture("img/wine.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose() && !game_over)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) jump_frame_count = 100;
        if (jump_frame_count > 1) jump_frame_count-=2;
        if ((obstacle_x_i + obstacle_x_xspeed) > screenWidth)
            obstacle_x_i = -randomtime(4000);
        else 
            obstacle_x_i = obstacle_x_i + obstacle_x_xspeed;
        obstacle_x = screenWidth - obstacle_x_i;
        points++;
        sprintf(points_str, "Points: %d", points);
        if ((obstacle_x_iwine + obstacle_x_xspeedwine) > screenWidth)
            obstacle_x_iwine = -randomtime(40000);
        else
            obstacle_x_iwine = obstacle_x_iwine  + obstacle_x_xspeedwine;
        obstacle_xwine = screenWidth - obstacle_x_iwine;



        if (bike_position.x - 100 < obstacle_x
            && bike_position.x + 100 > obstacle_x
            && jump_frame_count < 50)
            game_over = true;

        if (bike_position.x - 100 < obstacle_xwine
            && bike_position.x + 100 > obstacle_xwine
            && jump_frame_count < 50)
            game_over = true;

        if (points % 50 == 0)
            obstacle_x_xspeed = obstacle_x_xspeed + 1;
        if (points % 50 == 0)
            obstacle_x_xspeedwine = obstacle_x_xspeedwine + 1;
       



        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        DrawTexture(background, 0, 0, WHITE);

        DrawText("My bike", 20, 20, 20, DARKGRAY);
        DrawText(points_str, 200, 20, 20, DARKGRAY);

        DrawBike(bike_position.x, bike_position.y - jump_frame_count);

        DrawTexture(rock, obstacle_x, screenHeight - 60, WHITE);
        DrawTexture(wine, obstacle_xwine, screenHeight - 90, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    if(game_over)
    {
        BeginDrawing();
        DrawText("GAME OVER ", 100, 100,100,WHITE);
    
        EndDrawing();
        WaitTime(3);
       }
     
 
    UnloadTexture(background);
    UnloadTexture(rock);
    UnloadTexture(wine);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

