#ifndef DIALOGUE_H
#define DIALOGUE_H
#pragma once

#include "raylib.h"
#include "string"
#include "vector"

enum DgState {
	OPENING,
	CLOSING,
	OPEN,
	CLOSED
};

class Dialogue  
{
	private:
		Texture2D	nPatchTexture;				//NPatch texture
		NPatchInfo	nPatchInfo;					//the NPatch info structure holding details about the NPatch texture loaded
		Rectangle 	destRectangle;				//the dialogue rectangle, specifying the position and size of the dialogue window on the screen
		Rectangle	destTextRectangle;			//the rectangle for the text content (there's a margin added so it's inset into the dialogue rectangle)
		Color		windowDrawColorFilter;		//the color filter, mostly used to control the transparency of the window, but can also be used to change color

		Texture2D	nPatchTextureNametag;		//NPatch texture for the speaker name tag
		NPatchInfo	nPatchInfoNametag;			//NPatch Info structure for the speaker name tag
		Rectangle	nametagRectangle;			//Rectangle for drawing the speaker name tag
		Rectangle	nametagTextRectangle;		//Rectangle for drawing the text in the speaker name tag
		float		nametagTextInset	= 8.0f;	//Margin applied to all the sides of the rectangle to get the text rectangle

		int			contentFontSize	= 24;		//the font size used for the content text
		int			speakerFontSize	= 18;		//the font size used for the speaker name text
		Font		contentFont;				//the font used for writting to the dialogue box
		Font		speakerNameFont;			//the font used for the speaker name;
		std::string	targetText;					//the final string to write to the dialogue box
		std::string	speakerName;				//name of the speaker, if left empty, the character name is not displayed
		int 		textPosition 	= 0;		//current position in the targetText
		double		lastCharTime	= 0;		//last time a char was added
		double 		charDelay		= 0.025;	//Delay in seconds

		DgState		state			= CLOSED;	//Dialogue state
		DgState		nextState		= OPEN;		//Dialogue state after transition
		float		openPercentage	= 0.0f;		//Animation control
		float		animationSpeed	= 0.1f;		//how much the animation proceeds every *frame*

		bool		optionsShown	= false;	//Whether dialogue is in options mode
		std::vector<std::string> options;		//Options rendered
		int*		optionDest		= nullptr;	//Where to store the answer

	public:

		//The height is given in percentage from 0 to 1, this allows us to have consistent results across resolutions, margin is in pixels
		Dialogue(float height = 0.3f, float margin = 5.0f);
		~Dialogue();

		//Draws the dialogue, depending on it's current animation state
		void draw();

		//Update dialogue, mainly animation
		void update();

		void typeText(std::string content, std::string name = "");
		void showOptions(std::string content, std::vector<std::string> options, int* destination, std::string name = "");

		void hide();
		void show();

		bool isShown();

};
#endif