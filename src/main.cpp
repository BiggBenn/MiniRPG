
//system libs

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes
#include "Scene.hpp"
#include "SceneManager.hpp"

#include "Dialogue.hpp"

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

    Dialogue* dialogue = new Dialogue();

    int textCount = 4;
    std::string texts[] = {
        "Hello hero!",
        "What a lovely day you have chosen to visit me.",
        "I shall give you the legendary Hoe of pig smiting for your efforts.",
        "Use it only for good and never for that stupid evil!"
    };

    dialogue->typeText(texts[0], "Clarissa");

    int dialogueCounter = 0;

    bool dShow = false;
    dialogue->hide();

    int answer = -1;


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float delta = GetFrameTime();
        
        if (IsKeyPressed(KEY_K)) {
            dShow = !dShow;
            if(dShow) dialogue->show();
            else {
                dialogue->hide();
                dialogueCounter = 0;
                dialogue->typeText(texts[dialogueCounter], "Clarissa");
            }
        }

        if (IsKeyPressed(KEY_L)) {
            dialogue->show();
            dialogue->showOptions("What do you want?", {"Nothing", "Something", "Something Else"}, &answer, "Clarissa");
            dShow = true;
        }

        if (dShow && IsKeyPressed(KEY_M)) {
            if(answer == 0) {
                dialogue->typeText("Fine, as you wish...", "Clarissa");
                answer = -2;
            }else if (answer == 1) {
                dialogue->typeText("I don't have this 'Something' you speak of", "Clarissa");
                answer = -2;
            }else if (answer == 2) {
                dialogue->typeText("Don't we all?", "Clarissa");
                answer = -2;
            }else if (answer == -2) {
                answer = -1;
                dShow = false;
                dialogue->hide();
                dialogueCounter = 0;
                dialogue->typeText(texts[dialogueCounter], "Clarissa");
            }else{
                dialogueCounter = (dialogueCounter + 1) % textCount;
                dialogue->typeText(texts[dialogueCounter], "Clarissa");
            }
        }

        dialogue->update();
        scenes->update(delta);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        scenes->draw();

        dialogue->draw();

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