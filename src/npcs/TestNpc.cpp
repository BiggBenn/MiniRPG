#include "npcs/TestNpc.hpp"  
#include "raylib.h"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "scenes/DialogueScene.hpp"
#include "StoryProgress.hpp"
	
TestNpc::TestNpc()
{
	typeFlags |= TypeFlag::Interactable;
    ChangeTexture("resources/rem_npc.png");

    normal_face = LoadTexture("resources/portrait-1.png");

    db = new DialogueBuilder();
    db->start();

    dialogue_start = db->construct({
        db->line({normal_face}, "Rem", "I seem to have lost all my eggs!"),
        db->choice({normal_face}, "Rem", "Can you please help me collect my eggs?", {
            db->option("Sure!", {
                db->line({normal_face}, "Rem", "Thank you!"),
                db->line({normal_face}, "Rem", "When you see an egg, walk to it, and press SPACE to collect it!"),
                db->call([&](){
                    this->dialogue_current = this->dialogue_in_progress;
                })
            }),
            db->option("No way...", {
                db->line({normal_face}, "Rem", "Oh, that's ok... I'll wait for someone else...")
            })
        }),
        db->nop()
    });

    db->start();
    dialogue_in_progress = db->construct({
        db->nop(),
        db->condition([](){return StoryProgress::eggsCollected == StoryProgress::goalEggCount;}, {
            db->line({normal_face}, "Rem", "Oh lovely! you found all my eggs!"),
            db->line({normal_face}, "Rem", "Thank you sooo much!"),
            db->line({normal_face}, "Rem", "Now I can finally make the biggest omelette possible for my master!"),
            db->call([&](){
                this->dialogue_current = this->dialogue_finished;
            })
        }, {
            db->line({normal_face}, "Rem", "I'm still missing some eggs. Keep it up!")
        }),
        db->nop()
    });

    db->start();
    dialogue_finished = db->construct({
        db->line({normal_face}, "Rem", "Thank you for your help, you're the best!")
    });


    dialogue_current = dialogue_start;
}
	
TestNpc::~TestNpc()
{

}


void TestNpc::interact() 
{
    SceneManager::GetSceneManager()->AddScene(new DialogueScene(dialogue_current));
}