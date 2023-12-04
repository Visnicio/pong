#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    int ball_size = 30;
    double ball_speed = 5.f;
    Vector2 ball_position = {200, 200};
    Vector2 ball_velocity = {1, 1};

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(WHITE);

        ball_position.x += ball_velocity.x * ball_speed;
        ball_position.y += ball_velocity.y * ball_speed;

        cout << ball_position.x + ball_size << endl;

        if (ball_position.x + ball_size >= GetScreenWidth()){
            ball_velocity.x *= -1;
        }

        if (ball_position.x - ball_size <= 0){ //is - beacause I need to go up to check;
            ball_velocity.x *= -1;
        }

        if (ball_position.y + ball_size >= GetScreenHeight()){
            ball_velocity.y *= -1;
        }

        if (ball_position.y - ball_size <= 0){ //is - beacause I need to go up to check;
            ball_velocity.y *= -1;
        }

        DrawText("Hello world!", 400, 300, 32, BLACK);
        DrawCircle(ball_position.x, ball_position.y, ball_size, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}