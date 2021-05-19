#include "LogChopSpot.hpp"


LogChopSpot::LogChopSpot()
{
	ChangeTexture("resources/ChoppingLog.png");
	typeFlags |= TypeFlag::Interactable;
	logsLeft = StoryProgress::goalWoodCount;
	SetSize({ 50,50 });

	unchoppedLogs = new GameObject();
	unchoppedLogs->SetSize({ 10,10 });

	choppedLogs = new GameObject();
	choppedLogs->SetSize({ 10,10 });


}

LogChopSpot::~LogChopSpot()
{
	delete unchoppedLogs;
	delete choppedLogs;
}

void LogChopSpot::interact(Player* player)
{
	//only do the chopping minigame if anything is left to chop
	if (logsLeft > 0)
	{
		//set player to chop prep drawing
		//player->changeTexture("resources/player/axe_prep.png");

		//set up callbacks
		std::function<void(void)> success = std::bind(&LogChopSpot::chop, this);
		std::function<void(void)> failure = std::bind(&LogChopSpot::miss, this);

		//set up the minigame scene with a difficulty random between 0.85 and 1.15
		Scene* minigame = new TimingGameScene(success, failure, GetRandomValue(85, 115) / 100.0f);
		SceneManager::GetSceneManager()->AddScene(minigame);
	}
}

void LogChopSpot::chop()
{
	//return players texture to normal
	//player->changeTexture("resources/player/default.png")

	//maybe play a sound? chop crunch?

	logsChopped++;
	logsLeft--;

	StoryProgress::woodChopped++;
}

void LogChopSpot::miss()
{
	//return players texture to normal
	//player->changeTexture("resources/player/default.png")

	//maybe play a sound? chop without crunch as its a miss
}

void LogChopSpot::draw()
{
	//First draw this object as normal
	GameObject::draw();

	//draw the unchopped log holding cage
	//logStorage->draw();

	//draw the log at however many logs are left positions
	for (int i = 0; i < logsLeft; i++)
	{
		Vector2 adjustment = { 0,0 };
		if (i == 0)
		{
			adjustment.x = -10;
		}
		else if (i == 1)
		{
			adjustment.x = 0;
		}
		else if (i == 2)
		{
			adjustment.x = 10;
		}
		else if (i == 3)
		{
			adjustment.x = -5;
			adjustment.y = -10;
		}
		else if (i == 4)
		{
			adjustment.x = 5;
			adjustment.y = -10;
		}
		else if (i == 5)
		{
			adjustment.x = 0;
			adjustment.y = -20;
		}

		unchoppedLogs->SetPosition(position + unchoppedOffset + adjustment);
		unchoppedLogs->draw();
	}

	//draw the pallet the firewood is stored on
	//fireWoodStorage->draw();

	for (int j = 0; j < logsChopped; j++)
	{
		Vector2 adjustment = { 0,0 };
		if (j == 0)
		{
			adjustment.x = -10;
		}
		else if (j == 1)
		{
			adjustment.x = 0;
		}
		else if (j == 2)
		{
			adjustment.x = 10;
		}
		else if (j == 3)
		{
			adjustment.x = -5;
			adjustment.y = -10;
		}
		else if (j == 4)
		{
			adjustment.x = 5;
			adjustment.y = -10;
		}
		else if (j == 5)
		{
			adjustment.x = 0;
			adjustment.y = -20;
		}

		choppedLogs->SetPosition(position + choppedOffset + adjustment);
		choppedLogs->draw();
	}
}