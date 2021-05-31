#include "Scenes/FarmNo2.hpp"

#include "ExitPoint.hpp"

void FarmNo2::Initialize()
{
	Player* player = new Player(this);
	all_objects.push_back(player);

	ExitPoint* exit = new ExitPoint();
	all_objects.push_back(exit);
	exit->SetPosition({ -200, 0 });
}