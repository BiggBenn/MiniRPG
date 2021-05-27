#include "Scenes/FarmNo1.hpp"


void FarmNo1::Initialize()
{
	//spawn jenkins somewhere
	Jenkins* jenkins = new Jenkins();
	all_objects.push_back(jenkins);
}
