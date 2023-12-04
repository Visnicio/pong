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

    int rect_width = 30;
    int rect_height = 200;

    Vector2 player1_pos = {100, 100};
    Vector2 player2_pos = {GetScreenWidth() - 100.f, GetScreenHeight() + 100.f};

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(WHITE);

        ball_position.x += ball_velocity.x * ball_speed;
        ball_position.y += ball_velocity.y * ball_speed;

        if (ball_position.x + ball_size >= GetScreenWidth() || ball_position.x - ball_size <= 0){
            ball_velocity.x *= -1;
        }

        if (ball_position.y + ball_size >= GetScreenHeight() || ball_position.y - ball_size <= 0){
            ball_velocity.y *= -1;
        }

        DrawText("Hello world!", GetScreenWidth() / 2, GetScreenHeight() / 2, 32, BLACK);
        DrawCircle(ball_position.x, ball_position.y, ball_size, BLACK);

        DrawRectangle(player1_pos.x, player1_pos.y, rect_width, rect_height, GREEN);
        DrawRectangle(player2_pos.x, player2_pos.y, rect_width, rect_height, RED);

        if (IsKeyDown(KEY_S) && player1_pos.y + rect_height < GetScreenHeight()) {
            player1_pos.y += 10;
        }else if (IsKeyDown(KEY_W) && player1_pos.y > 0){
            player1_pos.y -= 10;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}