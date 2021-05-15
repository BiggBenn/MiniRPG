//system libs

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "DialogueBuilder.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MiniRPG");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    SceneManager* scenes = SceneManager::GetSceneManager();
    scenes->AddScene( new Scene());

    Texture2D REM = LoadTexture("resources/portrait-1.png");
    Texture2D RAM = LoadTexture("resources/portrait-2.png");

    DialogueBuilder* db = new DialogueBuilder();
    DialogueExecutor executor = db->start().construct({
        db->line("You wake up, and see two colorful figures...")
    });

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float delta = GetFrameTime();

        if (IsKeyPressed(KEY_ENTER)) {
            executor.next();
        }

        executor.update();
        scenes->update(delta);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        scenes->draw();
        executor.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete AssetManager::GetAssetManager(); //get rid of all loaded textures
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}