#include "scenes/ListScene.hpp"

#include "StoryProgress.hpp"
#include "DialogueBuilder.hpp"

#include "scenes/FarmNo1.hpp"
#include "scenes/FarmNo2.hpp"

void ListScene::Initialize()
{
	//set up the small dialogue 
	DialogueBuilder* db = new DialogueBuilder();
	db->start();
	beenThere = db->construct({
		db->line("Nathan", "I've already been there.")
	});

	db->start();
	notYet = db->construct({
		db->line("Nathan", "It's still too early to go to Zeek's for the festival."),
		db->line("Nathan", "I should finish visiting all the people Uncle Marv told me to, first.")
	});

	db->start();
	notImplementedYet = db->construct({
		db->line("Dev", "I'm sorry, this area has not been implemented yet :(")
	});

	db->start();
	jenkinsFirst = db->construct({
		db->line("Nathan", "I should go to Jenkins first.")
		});

	selector = new GameObject();
	selector->ChangeTexture("resources/list/selector.png");
	selector->SetZ(25);
	selector->SetSize({ 200,40 });
	all_objects.push_back(selector);

	Vector2 origin = { 0, -200 };
	for (int i = 0; i < 11; i++)
	{
		GameObject* obj = new GameObject();
		std::string path = "resources/list/name_" + std::to_string(i) + ".png";
		//path = "resources/list/writing.png";
		obj->ChangeTexture(path);

		Vector2 position = origin;
		position.y += i * 40;
		obj->SetPosition(position);

		obj->SetSize({ 240, 40 });

		obj->SetZ(15);

		names[i] = obj;
		all_objects.push_back(obj);

		//check if the farm was already visited, if so display it crossed
		if (i != 10 && StoryProgress::farmsVisited[i])
		{
			GameObject* strikeThrough = new GameObject();
			strikeThrough->ChangeTexture("resources/list/strikethrough.png");
			strikeThrough->SetPosition(position);
			strikeThrough->SetSize({ 240, 40 });
			strikeThrough->SetZ(50);
			all_objects.push_back(strikeThrough);
		}
	}

	//add background paper graphic
	GameObject* paper = new GameObject();
	paper->ChangeTexture("resources/list/background.png");
	paper->SetSize({ 400, 550 });
	paper->SetZ(0);
	all_objects.push_back(paper);

	//make sure the selector is in the right place
	adjustSelector();

	sortZ();
}


void ListScene::update(float delta)
{
	Scene::update(delta);

	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
	{
		selected--;
		if (selected < 0)
			selected = 10;
		adjustSelector();
	}
	
	if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
	{
		selected++;
		if (selected > 10)
			selected = 0;
		adjustSelector();
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		if (selected == 10)
		{
			if (StoryProgress::timeLeft > 0)
			{
				SceneManager::GetSceneManager()->AddScene(new DialogueScene(notYet));
			}
			else
			{
				//go to the party at the end of the game!
			}
		}
		else if (StoryProgress::farmsVisited[selected])
		{
			SceneManager::GetSceneManager()->AddScene(new DialogueScene(beenThere));
		}
		else if (selected != 0 && !StoryProgress::farmsVisited[0])
		{
			//player is trying to visit anything else without visiting jenkins first
			SceneManager::GetSceneManager()->AddScene(new DialogueScene(jenkinsFirst));
		}
		else
		{
			//load up the corresponding scene
			Scene* toLoad = nullptr;
			switch (selected)
			{
			case 0:
				toLoad = new FarmNo1();
				break;
			case 1:
				toLoad = new FarmNo2();
				break;
			default:
				SceneManager::GetSceneManager()->AddScene(new DialogueScene(notImplementedYet));
			}

			if (toLoad != nullptr)
			{
				SceneManager* man = SceneManager::GetSceneManager();
				//pop this scene, and the scene underlying the list scene, i.e. the farm the player was previously on
				man->PopScene();
				man->PopScene();
				//load up the new farm
				man->AddScene(toLoad);
			}
		}
	}
}

void ListScene::adjustSelector()
{
	Vector2 selectPos = names[selected]->GetPosition();
	selectPos.y += 0;
	selector->SetPosition(selectPos);
}