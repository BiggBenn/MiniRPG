#include "ExitPoint.hpp"

#include "DialogueBuilder.hpp"
#include "scenes/DialogueScene.hpp"
#include "scenes/ListScene.hpp"


ExitPoint::ExitPoint() 
{
	typeFlags |= TypeFlag::Interactable;

	ChangeTexture("resources/images/exit.png");
	SetSize({ 100,100 });

	DialogueBuilder* db = new DialogueBuilder();
	
	db->start();
	confirmationDialogue = db->construct({
		db->nop(),
		db->choice("Do you really want to leave this area? You won't be able to come back!", {
			db->option("Yes", {
				db->call([&]() {
					this->reallyLeave = true;
				})
			}),
			db->option("No", {
				db->call([&]() {
					this->reallyLeave = false;
				})
			})
		})
	});
}

ExitPoint::~ExitPoint()
{

}


void ExitPoint::update(float delta)
{
	GameObject::update(delta);

	if (reallyLeave)
	{
		//set up the list scene
		Scene* List = new ListScene();
		SceneManager::GetSceneManager()->AddScene(List);
	}
}

void ExitPoint::interact(Player* player)
{
	//Create the confirmation dialogue
	SceneManager::GetSceneManager()->AddScene(new DialogueScene(confirmationDialogue));
}