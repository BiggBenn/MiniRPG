#include "Dialogue.hpp"  

#include "raymath.h"
#include "AssetManager.hpp"
	
Dialogue::Dialogue(float height, float margin)
{
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();

    contentFont = LoadFontEx("resources/font.ttf", contentFontSize, 0, 0);
    speakerNameFont = LoadFontEx("resources/font.ttf", speakerFontSize, 0, 0);

    //semi transparent window with the original texture color
    windowDrawColorFilter = ColorAlpha(WHITE, 0.8f);

    float realHeight = (float)sHeight * height;
	nPatchTexture = AssetManager::GetAssetManager()->RequestTexture("resources/dialogue_blue.png");
    nPatchInfo = { (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f }, 16, 16, 16, 16, NPATCH_NINE_PATCH };
    destRectangle = {   margin,
                        sHeight - realHeight - margin,
                        sWidth - (2 * margin),
                        realHeight};

    float inset = 16.0f;
    destTextRectangle = {   margin + inset,
                            sHeight - realHeight - margin + inset,
                            sWidth - (2 * (margin + inset)),
                            realHeight - (2*inset)};

    nPatchTextureNametag = AssetManager::GetAssetManager()->RequestTexture("resources/dialogue_blue.png");
    nPatchInfoNametag = { (Rectangle){ 0.0f, 0.0f, 64.0f, 64.0f }, 8, 8, 8, 8, NPATCH_NINE_PATCH };
    nametagRectangle = destRectangle;

    inset = nametagTextInset;
    float nametagHeight = speakerFontSize + 2 * inset;
    nametagRectangle = {margin + (nametagHeight/2),
                        sHeight - realHeight - margin - (nametagHeight / 2),
                        100,
                        nametagHeight};

    nametagTextRectangle = {nametagRectangle.x + inset,
                            nametagRectangle.y + inset,
                            100 - inset,
                            nametagRectangle.height - inset};

    float portraitSize = 192;
    portraitSourceRectangle = {0, 0, 0, 0};
    portraitRectangle = {destRectangle.x, destRectangle.y - portraitSize, portraitSize, portraitSize};

    targetText = "";
    lastCharTime = 0;
    charDelay = 0.025;
}
	
Dialogue::~Dialogue()
{
	AssetManager::GetAssetManager()->UnregisterTexture("resources/dialogue_blue.png");
    UnloadFont(contentFont);
}

void Dialogue::draw() 
{
    if (state == OPEN) {

        if (showPortrait) {
            DrawTexturePro(portrait, portraitSourceRectangle, portraitRectangle, {0, 0},0, WHITE);
        }

        DrawTextureNPatch(nPatchTexture, nPatchInfo, destRectangle, Vector2Zero(), 0.0f, windowDrawColorFilter);
        if  (!speakerName.empty())  {
            DrawTextureNPatch(nPatchTextureNametag, nPatchInfoNametag, nametagRectangle, Vector2Zero(), 0.0f, WHITE);
            DrawTextRec(speakerNameFont, speakerName.c_str(), nametagTextRectangle, speakerFontSize, 4, false, WHITE);
        }
        DrawTextRec(contentFont, targetText.substr(0, textPosition).c_str(), destTextRectangle, contentFontSize, 4, true, WHITE);

        if (optionsShown && textPosition >= targetText.size()){
            for (int i = 0; i < options.size(); i++) {
                int offset = options.size() * contentFontSize;
                Rectangle test = {destTextRectangle.x, destTextRectangle.y + destTextRectangle.height - offset + (float)i * (float)contentFontSize, destTextRectangle.width, (float)contentFontSize};
                if(i == *optionDest) DrawTextRec(contentFont, (">" + options[i]).c_str(), test, contentFontSize, 4, false, YELLOW);
                else DrawTextRec(contentFont, options[i].c_str(), test, contentFontSize, 4, false, WHITE);
            }
        }
    }

    if (state == OPENING || state == CLOSING) {
        Rectangle animRectangle = destRectangle;
        animRectangle.height = destRectangle.height * openPercentage;
        animRectangle.y += destRectangle.height - animRectangle.height;
        if (showPortrait) {
            Rectangle portraitAnimRectangle = portraitRectangle;
            portraitAnimRectangle.y = animRectangle.y - portraitRectangle.height;
            DrawTexturePro(portrait, portraitSourceRectangle, portraitAnimRectangle, {0, 0}, 0, ColorAlpha(WHITE, openPercentage));
        }
        DrawTextureNPatch(nPatchTexture, nPatchInfo, animRectangle, Vector2Zero(), 0.0f, windowDrawColorFilter);
    }
}

void Dialogue::update() 
{
    if (state == OPEN) {
        //run text typing animation
        if (textPosition < targetText.length()) {

            double currentTime = GetTime();

            if (currentTime > (lastCharTime + charDelay)) {
                textPosition++;
                lastCharTime = currentTime;
            }
        }
    }

    if (optionsShown) {
        if(optionDest != nullptr){
            if (IsKeyPressed(KEY_DOWN)) *optionDest = std::min(*optionDest + 1, (int)options.size() - 1);
            else if (IsKeyPressed(KEY_UP)) *optionDest = std::max(*optionDest - 1, 0);
        }
    }

    if (state == OPENING) {
        openPercentage = std::min(openPercentage + animationSpeed, 1.0f);
        if (openPercentage >= 1.0f) state = OPEN;
    }

    if (state == CLOSING) {
        openPercentage = std::max(openPercentage - animationSpeed, 0.0f);
        if (openPercentage <= 0.0f) state = CLOSED;
    }
}

void Dialogue::typeText(std::string content, std::string name) 
{
    targetText = content;
    speakerName = name;
    textPosition = 0;
    lastCharTime = GetTime();

    if (!speakerName.empty()) {
        nametagRectangle.width = MeasureTextEx(contentFont, speakerName.c_str(), speakerFontSize, 4).x + nametagTextInset*2;
    }

    optionsShown = false;
}

void Dialogue::showOptions(std::string content, std::vector<std::string> options, int* destination, std::string name) 
{
    typeText(content, name);
    this->options = options;
    optionsShown = true;
    optionDest = destination;
    *optionDest = 0;
}

void Dialogue::setPortrait(Texture2D texture, bool flipped) 
{
    portrait = texture;
    portraitSourceRectangle.width = flipped ? -texture.width : texture.width;
    portraitSourceRectangle.height = texture.height;
    showPortrait = true;

    portraitRectangle.x = destTextRectangle.x + (destTextRectangle.width - portraitRectangle.width ) * flipped;
}

void Dialogue::unsetPortrait() 
{
    showPortrait = false;
}

void Dialogue::skipText() 
{
    textPosition = targetText.length();
}

void Dialogue::hide() 
{
    state = CLOSING;
}

void Dialogue::show() 
{
    textPosition = 0;
    lastCharTime = GetTime();
    state = OPENING;
}

bool Dialogue::isShown() 
{
    return state == OPEN;
}

bool Dialogue::isFinished() 
{
    return textPosition >= targetText.length();
}