#include "scenes/IntroScene.hpp"

#include "DialogueBuilder.hpp"

IntroScene::~IntroScene()
{
	AssetManager* manager = AssetManager::GetAssetManager();
	manager->UnregisterTexture("resources/npcs/marvin/portrait_normal.png");
	manager->UnregisterTexture("resources / npcs / marvin / portrait_happy.png");
}

void IntroScene::Initialize()
{
	//prepare the background image
	GameObject* background = new GameObject();
	background->ChangeTexture("resources/images/intro_background_1");
	background->SetSize({(float) GetScreenWidth(), (float) GetScreenHeight() });
	background->SetZ(-500);

	AssetManager* manager = AssetManager::GetAssetManager();
	//load up the images for marvin
	marv_normal = manager->RequestTexture("resources/npcs/marvin/portrait_normal.png");
	marv_happy = manager->RequestTexture("resources/npcs/marvin/portrait_happy.png");
	


	//set up the dialogue
	DialogueBuilder* db = new DialogueBuilder();

	db->start();
	dialogue = db->construct({
		db->nop(),
		db->choice({marv_normal}, "Uncle", "Good morning Nathan! Are you excited for the festival tonight?", {
			db->option("Hell yeah!", {
				db->line({marv_happy}, "Uncle", "Nice! That's the spirit. But keep it down with the H-Word. Your dad would be mad at me if I influenced you to swear.")
			}),
			db->option("Not really...", {
				db->line({marv_normal}, "Uncle", "Oh come on, you loved it last year! You'll be in a better mood after breakfast.")
			})
		}),
		db->line({marv_normal}, "Uncle", "Right, let's get ready for the day. I have some errands for you to run later, but first, pancakes!"),
		db->line("*You have a nice, pancakey breakfast*"),
		db->choice({marv_normal}, "Uncle", "Now that we're energized, about those errands...", {
			db->option("*Groan*", {
				db->line({marv_normal}, "Uncle", "It'll be fun! Like a field trip!")
			}),
			db->option("What do you need me to do?", {
				db->line({marv_happy}, "Uncle", "Good boy, always eager to help.")
			})
		}),
		db->line({marv_normal}, "Uncle", "I'll be working on preparations for the harvest festival tonight, as you know, but there are some of our neighbors who I think could use a reminder that the festival is *today*."),
		db->line({marv_normal}, "Uncle", "They might have forgotten. So you will be visiting all of them!"),
		db->line("Nathan", "..."),
		db->line({marv_normal}, "Uncle", "Yes, I know the people of this village are spread out pretty far. But you have time, and won't starve! I've packed your little backpack with some pop and a sandwich. Don't tell your dad."),
		db->line({marv_normal}, "Uncle", "Here's a list of the neighbors I'm worried about."),
		db->line("*Uncle hands you a piece of paper*"),
		db->line({marv_happy}, "Uncle", "Alright! I'll leave you to it, and I will do my very best to prepare a great party for tonight. I'm sure you'll have fun!"),
		db->line({marv_normal}, "Uncle", "See you tonight! I'll be waiting for you at Zeek's barn."),
		db->line("*Uncle pushes you out of the door in front of him, and then leaves you while walking to his tractor*"),
		db->call([&]() {
			this->introDialogueDone = true;
		})
	});

	SceneManager::GetSceneManager()->AddScene(new DialogueScene(dialogue));

}


void IntroScene::update(float delta)
{
	Scene::update(delta);

	//check 
}
