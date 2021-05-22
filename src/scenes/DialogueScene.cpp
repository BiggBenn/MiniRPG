#include "scenes/DialogueScene.hpp"
#include "raylib.h"

#define DIALOGUE_NEXT_KEY KEY_SPACE
	
DialogueScene::DialogueScene(DialogueExecutor* executor) 
{
    this->executor = executor;
}
	
DialogueScene::~DialogueScene()
{
	
}

void DialogueScene::Initialize() 
{
    this->executor->next();
}

void DialogueScene::update(float delta) 
{
    if(IsKeyPressed(DIALOGUE_NEXT_KEY)) {
        executor->next();
    }

    executor->update();

    if (executor->isFinished()){
        SceneManager::GetSceneManager()->PopScene();
    }
}

void DialogueScene::draw() 
{
    executor->draw();
}
