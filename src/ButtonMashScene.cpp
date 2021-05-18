#include "ButtonMashScene.hpp"


ButtonMashScene::ButtonMashScene(std::function<void(void)> success_callback, std::function<void(void)> failure_callback, float Difficulty) : MiniGameScene(success_callback, failure_callback)
{
	difficulty = Difficulty;
}

void ButtonMashScene::Initialize()
{
	//set up the bar objects
	barShape = new GameObject();
	all_objects.push_back(barShape);
	barShape->SetPosition({ 0,-100 });
	barShape->SetSize({ 200, 40 });

	barFilling = new GameObject();
	all_objects.push_back(barFilling);
	barFilling->SetPosition({ 0,-100 });
	barFilling->SetSize({ 0, 40 });
}

void ButtonMashScene::update(float delta)
{
	MiniGameScene::update(delta);

	//Every press of the space bar increases the value by a certain amount, but the harder the difficulty, the faster progress decays
	if (IsKeyPressed(KEY_SPACE))
	{
		mashValue += 0.2;
	}
	//Higher difficulty means higher decay, default is 0.8 decay (out of 1.0 total and 0.2 added per mash) per second
	mashValue -= difficulty * 0.8 * delta;
	mashValue = Clamp(mashValue, 0, 1);
	//If the player succeeds the mash game, call success
	if (mashValue == 1)
	{
		success();
	}
	//if the player isnt mashing, progress towards timeout
	else if (mashValue == 0)
	{
		failTimer += delta;
		if (failTimer > timeout)
			failure();
	}
	else
	{
		//reset the failtime if the player is still trying
		failTimer = 0;
	}
	
	//Modify the visual size of the filling of the bar. The closer the player gets to completing it, the more filled it is.
	Vector2 visualSize = barShape->GetSize();
	visualSize.x *= mashValue * 0.98;
	visualSize.y *= 0.9;
	barFilling->SetSize(visualSize);
}

void ButtonMashScene::draw()
{
	MiniGameScene::draw();

}