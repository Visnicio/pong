#include <iostream>
#include <raylib.h>

using namespace std;

bool CheckCollision(Vector2 object1_position, Vector2 object1_dimentions, Vector2 object2_position, Vector2 object2_dimentions){
    if (object2_position.x < object1_position.x + object1_dimentions.x && 
        object2_position.y < object1_position.y + object1_dimentions.y &&
        object2_position.y + object2_dimentions.y > object1_position.y &&
        object2_position.x + object2_dimentions.x > object1_position.x 
        ){
        return true;
    }
}

void DrawTextPivotCenter(const char *text, int fontSize, Vector2 position){
    // Configurando o texto
    // const char *text = "Hello, World!";
    // int fontSize = 20;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);

    // Calculando a posição para centralizar o texto
    float x = (position.x - textSize.x) / 2;
    float y = (position.y - textSize.y) / 2;

    // Renderizando o texto no meio da tela
    DrawText(text, x, y, fontSize, BLACK);
}

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;

    int p1_score = 0;
    int p2_score = 0;

    int ball_size = 30;
    double ball_speed = 7.f;
    Vector2 ball_position = {200, 200};
    Vector2 ball_velocity = {1, 1};

    int rect_width = 30;
    int rect_height = 200;

    Vector2 player1_pos = {100, 100};
    Vector2 player2_pos = {700, 100};

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

        std::string scoreText =  std::to_string(p1_score) + " : " + std::to_string(p2_score);
        const char* pScoreText = scoreText.c_str();
        DrawTextPivotCenter(pScoreText, 32, {(float)GetScreenWidth(), (float)GetScreenHeight()}); // isso é o equivalente a p1_score + " : " + p2_score
        DrawCircle(ball_position.x, ball_position.y, ball_size, BLACK);
        
        //Debug Ball collision
        // DrawRectangle(ball_position.x - ball_size, ball_position.y - ball_size, ball_size * 2, ball_size * 2, BLUE);

        //Debug Score Rects
        // DrawRectangle(0, 0, 100, GetScreenHeight(), BLUE); //player1_goal
        // DrawRectangle(GetScreenWidth() - 70, 0, 100, GetScreenHeight(), PINK); //player2_goal

        DrawRectangle(player1_pos.x, player1_pos.y, rect_width, rect_height, GREEN);
        DrawRectangle(player2_pos.x, player2_pos.y, rect_width, rect_height, RED);

        if (IsKeyDown(KEY_S) && player1_pos.y + rect_height < GetScreenHeight()) {
            player1_pos.y += 10;
        }else if (IsKeyDown(KEY_W) && player1_pos.y > 0){
            player1_pos.y -= 10;
        }

        if (IsKeyDown(KEY_DOWN) && player2_pos.y + rect_height < GetScreenHeight()) {
            player2_pos.y += 10;
        }else if (IsKeyDown(KEY_UP) && player2_pos.y > 0){
            player2_pos.y -= 10;
        }

        //The flickering glith is caused because of the check every frame
        if(CheckCollision(player1_pos, {(float)rect_width, (float)rect_height}, {ball_position.x - ball_size, ball_position.y - ball_size}, {(float)ball_size * 2, (float)ball_size * 2})){
            ball_velocity.x *= -1;
        }
        if(CheckCollision(player2_pos, {(float)rect_width, (float)rect_height}, {ball_position.x - ball_size, ball_position.y - ball_size}, {(float)ball_size * 2, (float)ball_size * 2})){
            ball_velocity.x *= -1;
        }

        if(CheckCollision({0, 0}, {100.f, (float)GetScreenHeight()}, {ball_position.x - ball_size, ball_position.y - ball_size}, {(float)ball_size * 2, (float)ball_size * 2})){
            ball_position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
            p2_score ++;
            ball_velocity.x = -1;
        }
        if(CheckCollision({(float)GetScreenWidth() - 70, 0}, {100, (float)GetScreenHeight()}, {ball_position.x - ball_size, ball_position.y - ball_size}, {(float)ball_size * 2, (float)ball_size * 2})){
            ball_position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
            p1_score ++;
            ball_velocity.x = 1;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}