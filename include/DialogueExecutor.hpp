#ifndef DIALOGUEEXECUTOR_H
#define DIALOGUEEXECUTOR_H
#pragma once

#include "DialogueIncludes.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
#include "Dialogue.hpp"
	
class DialogueExecutor {
    private:
        Dialogue* dialogue;
        std::vector<DialoguePart> content;
        std::vector<std::function<void(void)>> functionStack;
        std::vector<std::function<bool(void)>> conditionStack;
        std::unordered_map<std::string, int> jumps;
        int     index = 0;
        int     lastIndex = 0;
        int     option = 0;
        bool    finished = false;

    public:
        friend class DialogueBuilder;

		DialogueExecutor();
		virtual ~DialogueExecutor();

        void next();
        void draw();
        void update();
        bool isFinished();
};
#endif