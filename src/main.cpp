#include "raylib.h"

int main(){
    InitWindow(1360, 760, "Geometry Dash: Star Wars Edition");
    InitAudioDevice();
    Texture2D Darth_vader = LoadTexture("../assets/Darth_Vader.png");
    Texture2D Falcon = LoadTexture("../assets/Falcon.png");
    Texture2D Falcon1 = LoadTexture("../assets/Falcon1.png");
    Sound vaderJump = LoadSound("../assets/vader.wav");
    Sound theme1 = LoadSound("../assets/Vadertheme.mp3");
    Sound vaderDie = LoadSound("../assets/Seismic.wav");
    SetTargetFPS(144);
    

    Rectangle rec2;
    rec2.height = Darth_vader.height * 0.2f;
    rec2.width = Darth_vader.width * 0.2f;
    rec2.x = 100.0f;
    
    Rectangle rec1;
    rec1.height = 40.0f;
    rec1.width = 40.0f;
    rec1.y = 700.0f;

    float bgX = 0.0f;
    float bgX1 = Falcon.width;
    float bgX2 = 1800.0f;
    float bgSpeed = 400.0f;


    Vector2 VaderPos = { 100.0f, 670.0f }; 
    float velocityY = 0.0f;
    float gravity = 2500.0f;     
    float jumpForce = -1000.0f; 
    float floorY = 670.0f;


    bool isGameOver = false;

    PlaySound(theme1);

    while(!WindowShouldClose()){
    
        rec2.y = VaderPos.y;
        rec1.x = bgX2;


        if(!isGameOver && CheckCollisionRecs(rec1, rec2)){
            PlaySound(vaderDie);
            isGameOver = true; 
        }
        if(IsKeyPressed(KEY_ENTER)){
            bgX2=-500.0f;
            VaderPos.y= 670.0f;
            isGameOver= false;
        }

    
        if (!isGameOver) {
           
            bgX -= bgSpeed * GetFrameTime();
            bgX1 -= bgSpeed * GetFrameTime();
            bgX2 -= bgSpeed * GetFrameTime();

            if(bgX <= -Falcon.width) bgX = bgX1 + Falcon1.width;
            if(bgX1 <= -Falcon1.width) bgX1 = bgX + Falcon.width;

            if(bgX2 <= -40) bgX2 = 1400;

            
            if(IsKeyPressed(KEY_SPACE) && VaderPos.y >= floorY){
                PlaySound(vaderJump);
                velocityY = jumpForce; 
            }

            
            velocityY += gravity * GetFrameTime();
            VaderPos.y += velocityY * GetFrameTime();

            
            if(VaderPos.y >= floorY){
                VaderPos.y = floorY;
                velocityY = 0.0f; 
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(Falcon, bgX, 0, WHITE);
            DrawTexture(Falcon1, bgX1, 0, WHITE);
            DrawRectangle(bgX2, rec1.y, rec1.width, rec1.height, GRAY);
            DrawTextureEx(Darth_vader, VaderPos, 0.0f, 0.2f, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(Darth_vader);
    UnloadTexture(Falcon1);
    UnloadTexture(Falcon);
    CloseWindow();
    
    return 0;
}
