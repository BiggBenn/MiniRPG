#ifndef DIALOGUEBUILDER_H
#define DIALOGUEBUILDER_H
#pragma once

#include "DialogueExecutor.hpp"

/**
 * Aids with construction dialogues using a tree structure
 **/
class DialogueBuilder {
    private:
    DialogueExecutor* executor;
    std::vector<int> looseEnds;

    void identifyLooseEnds(std::vector<int> nodes);
    void tieLooseEnds(int target);
    int line(bool showPortrait, PortraitDefinition portrait, std::string name, std::string text);
    int choice(bool showPortrait, PortraitDefinition portrait, std::string name, std::string choice, std::vector<int> nodes);

    public:

    DialogueBuilder();
    virtual ~DialogueBuilder();

    //Every new construction needs to start with a start() call
    //so DialogueBuilder->start().construct(...)
    DialogueBuilder& start();

    //Main way of constructing a Dialogue with an executor
    DialogueExecutor& construct(std::vector<int> nodes);

    //Show a single line of dialogue with an optional name tag and a portrait
    int line(std::string text);
    int line(std::string name, std::string text);
    int line(PortraitDefinition portrait, std::string name, std::string text);

    //Show several option()s to the player. All supplied nodes have to be option() nodes here
    int choice(std::string choice, std::vector<int> nodes);
    int choice(std::string name, std::string choice, std::vector<int> nodes);
    int choice(PortraitDefinition portrait, std::string name, std::string choice, std::vector<int> nodes);

    //A single option flow, always part of a choice() node tree
    int option(std::string option, std::vector<int> nodes);

    //Performs function when executed
    int call(std::function<void(void)> func);

    //IF branch, if the function func returns TRUE then the flow in nodes is executed, otherwise it continues
    int condition(std::function<bool(void)> func, std::vector<int> nodes);

    //Same as previous, but includes an ELSE branch, if the function func returns TRUE first flow is executed, otherwise the second flow is executed
    //afterwards the current flow continues as normal
    int condition(std::function<bool(void)> func, std::vector<int> nodes, std::vector<int> elseNodes);

    //Mark a position in a flow
    int mark(std::string name);

    //Jump to a marked position
    int jump(std::string name);

    //No Operation. Useful if the flows behave strangely. Usually inserting a line() or a nop() can help tie things together.
    int nop();

};
#endif