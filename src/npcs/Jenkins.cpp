#include "npcs/Jenkins.hpp"

#include "SceneManager.hpp"
#include "scenes/DialogueScene.hpp"

Jenkins::Jenkins()
{
	//set basic stuff
	typeFlags |= TypeFlag::Interactable;
	SetSize({ 128,128 });

	//load textures
	ChangeTexture("npcs/Jenkins/overworld.png");
	AssetManager* assman = AssetManager::GetAssetManager();
	happy_face = assman->RequestTexture("npcs/Jenkins/portrait_happy.png");
	normal_face = assman->RequestTexture("npcs/Jenkins/portrait_normal.png");


	//set up the dialogueses
	DialogueBuilder* db = new DialogueBuilder();
	
	db->start();
	first_talk = db->construct({
		db->nop(),
		db->choice({normal_face}, "Jenkins", "Oh hey, you're Marvin's boy. Excited for the festival?", {
			db->option("I'm not Marvin's kid...", {
				db->line({normal_face}, "Jenkins", "Right right, Marvin's brother's kid. Same difference."),
				db->line({normal_face}, "Jenkins", "So what did you want? Surely you didn't just want to visit some old guy."),
				db->line("Nathan", "I was supposed to remind you of the festival tonight, but it seems like you haven't forgotten!")
			}),
			db->option("[Remind him about the festival]", {
				db->line("Nathan", "I was supposed to remind you of the festival tonight, but it seems like you haven't forgotten!")
			})
		}),
		db->line({happy_face}, "Jenkins", "Damn Right I haven't. Been excited for it since last week!"),
		db->line("Nathan", "Great! Well, see you there then."),
		db->line({normal_face}, "Jenkins", "Later."),
		db->call([&]() {
					this->talkedTo = true;
		})
	});

	db->start();
	after_talk = db->construct({
		db->line({normal_face}, "Jenkins", "See you later.")
	});
}

Jenkins::~Jenkins()
{
	AssetManager* assman = AssetManager::GetAssetManager();
	assman->UnregisterTexture("npcs/Jenkins/portrait_happy.png");
	assman->UnregisterTexture("npcs/Jenkins/portrait_normal.png");
}

void Jenkins::interact(Player* player)
{
	DialogueExecutor* ex;
	if (!talkedTo)
		ex = first_talk;
	else
		ex = after_talk;

	SceneManager::GetSceneManager()->AddScene(new DialogueScene(ex));
}
