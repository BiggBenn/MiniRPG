#ifndef DIALOGUEINCLUDES_H
#define DIALOGUEINCLUDES_H
#pragma once

#include <string>
#include "raylib.h"

enum DialogueNodeType {
    LINE, CHOICE, CALL, OPTION, CONDITION, MARK, JUMP, NOP
};

struct PortraitDefinition {
    Texture2D Texture;
    bool flipped = false;
};

struct DialoguePart {
    DialogueNodeType type = LINE;
    std::string name;
    std::string content;
    size_t items = 0;
    int next[5];    //max number of options supported
    int function = -1;
    bool hasPortrait = false;
    PortraitDefinition portrait;
};

#endif