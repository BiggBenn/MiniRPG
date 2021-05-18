#include "TimingGameScene.hpp"


TimingGameScene::TimingGameScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback, float Difficulty) : MiniGameScene(success_callback, failure_callback)
{
	difficulty = Difficulty;
	targetSize = defaultTargetSize / difficulty;
	targetSizeHalf = targetSize / 2;
	markerSpeed = defaultMarkerSpeed * difficulty;
	markerPos = (float)GetRandomValue(-10, 10) / 10.0f;
}

void TimingGameScene::Initialize()
{
	bar = new GameObject();
	all_objects.push_back(bar);
	bar->SetPosition({ 0,-100 });
	bar->SetSize({ 200, 40 });

	target = new GameObject();
	all_objects.push_back(target);
	target->SetPosition(bar->GetPosition());
	Vector2 modifier = { 0,0 };
	modifier.x = targetSize;
	modifier.y = 0.95;
	target->SetSize(bar->GetSize() * modifier);

	marker = new GameObject();
	all_objects.push_back(marker);
	marker->SetPosition(bar->GetPosition());
	modifier.x = 0.02;
	marker->SetSize(bar->GetSize() * modifier);
}

void TimingGameScene::update(float delta)
{
	MiniGameScene::update(delta);

	//Move the marker either left or right
	if (goingRight)
	{
		markerPos += markerSpeed * delta;
		if (markerPos >= 1)
		{
			markerPos = 1;
			goingRight = false;
		}
	}
	else
	{
		markerPos -= markerSpeed * delta;
		if (markerPos <= -1)
		{
			markerPos = -1;
			goingRight = true;
		}
	}

	//update the visual position of the marker
	Vector2 position = bar->GetPosition();
	position.x += (bar->GetSize().x / 2) * markerPos;
	marker->SetPosition(position);

	//on key press, check if the player hit the target
	if (IsKeyPressed(KEY_SPACE))
	{
		//check if the marker is where it should be
		if (abs(markerPos) <= targetSizeHalf + graceValue)
		{
			success();
		}
		else
			failure();
	}
}

void TimingGameScene::draw()
{
	MiniGameScene::draw();
}
