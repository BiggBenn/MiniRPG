#pragma once

#ifndef STORYPROGRESS_HPP
#define STORYPROGRESS_HPP

namespace StoryProgress
{
	/*
	*	General story guide:
	*		-Player is tasked to check on 10 farmers to see if they are coming to the festival
	*		-Player has time to visit all 10 farms, but 4 need help, and helping them takes time away to visit a different farm
	* 
	*		-Farmer list: (name -- condition -- location -- what they bring to the festival if they come)
	*			#1 Jenkins -- Will come either way -- Farm -- provides seating
	*			#2 Ol' Rick -- Forgot about festival and will only come if the player visited -- Homestead -- provides music (Banjo, harmonica)
	*			#3 Billy Bob -- requires help collecting eggs before he can go to the festival -- Ranch -- provides a big cake
	*			#4 Miller -- will come either way -- Flour Mill -- provides bread
	*			#5 Francine -- Needs help pulling weeds from her field -- Farm -- provides vegetable stew
	*			#6 Alexander -- will come either way -- Homestead -- provides lighting
	*			#7 Theodore Richards -- forgot about the festival -- Flower garden -- provides decorative flowers and banners
	*			#8 Shepherd Christian -- Needs player to find his sheepdog -- Pasture -- provides cheese 
	*			#9 Natalie -- needs player to chop wood, so she can fire her pottery for the festival -- Workshop -- provides plates and art
	*			#10 O'Malley -- Will come either way -- Brewery -- provides drinks
	* 
	*/

	
	//how much time the player has left, in general they have time to visit 10 farms
	//taking time to help someone costs time as well, so if you help everyone, you can only visit 6 farms
	inline int timeLeft = 10;

	///
	///Farmer sections
	/// 
	
	//#1 Jenkins
	//he is coming either way, even if the player does not visit him


	//#2 Ol' Rick
	inline bool isComingOlRick = false;

	//#3 Billy Bob / BB
	inline bool isComingBB = false;
	inline bool wasHelpedBB = false;
	//egg collection progress, 12 eggs needed to fulfill the task
	inline int eggsCollected = 0;
	inline const int goalEggCount = 12;


	//#4 Miller


	//#5 Francine
	inline bool wasHelped = false;
	//amount of weeds plucked, 9 is the goal
	inline int weedsPlucked = 0;
	inline const int goalWeedCount = 9;

	//#6 Alexander
	

	//#7 Theodore Richards -- forgot about the festival -- Flower garden -- provides decorative flowers and banners
	inline bool isComingTed = false;
	

	//#8 Shepherd Christian -- Needs player to find his sheepdog -- Pasture -- provides cheese
	inline bool isComingShep = false;
	//Whether or not the player has found the lost dog
	inline bool dogFound = false;
	

	//#9 Natalie

	//amount of wood chopped, 6 is the goal
	inline int woodChopped = 0;
	inline const int goalWoodCount = 6;


	//#10 O'Malley

};

#endif