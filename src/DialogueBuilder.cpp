#include "DialogueBuilder.hpp"  
	
DialogueBuilder::DialogueBuilder()
{
	
}
	
DialogueBuilder::~DialogueBuilder()
{
	
}

DialogueBuilder& DialogueBuilder::start() 
{
    executor = new DialogueExecutor();
    return *this;
}

void DialogueBuilder::identifyLooseEnds(std::vector<int> nodes) {
    if (!nodes.empty()) {
        DialogueNodeType lastNodeType = executor->content[nodes[nodes.size() - 1]].type;
        if (lastNodeType == LINE || lastNodeType == CALL || lastNodeType == MARK || lastNodeType == NOP) {
            looseEnds.push_back(nodes[nodes.size() - 1]);
        }
    }
}

void DialogueBuilder::tieLooseEnds(int target) {
    if (target > 0){
        DialogueNodeType lastType = executor->content[target - 1].type;
        if ((lastType == CHOICE || lastType == CONDITION)) {
            for (int node : looseEnds) {
                executor->content[node].items = 1;
                executor->content[node].next[0] = target;
            }
            looseEnds.clear();
        }
    }
}

int DialogueBuilder::line(bool showPortrait, PortraitDefinition portrait, std::string name, std::string text) {
    executor->content.push_back({LINE, name, text, 0, {}, 0, showPortrait, portrait});

    int newId = executor->content.size() - 1;
    tieLooseEnds(newId);

    return newId;
}

int DialogueBuilder::choice(bool showPortrait, PortraitDefinition portrait, std::string name, std::string choice, std::vector<int> nodes) {
    DialoguePart part = {CHOICE, name, choice, nodes.size(), {}, 0, showPortrait, portrait};
    int index = 0;
    for (int i : nodes){
        if (executor->content[i].type != OPTION) {
            TraceLog(LOG_WARNING, "Choice contains nodes that are not options!");
        }
        part.next[index++] = i;
        DialogueNodeType leafType = executor->content[i-1].type;
        if (leafType == LINE || leafType == CALL || leafType == MARK || leafType == NOP) {
            looseEnds.push_back(i-1);
        }
    }
    executor->content.push_back(part);
    int newId = executor->content.size() - 1;
    return newId;
}

DialogueExecutor* DialogueBuilder::construct(std::vector<int> nodes) {
        for (int i = 0; i < nodes.size(); i++){
            if (i < nodes.size() - 1) {
                if(executor->content[nodes[i]].items == 0){
                    executor->content[nodes[i]].items = 1;
                    executor->content[nodes[i]].next[0] = nodes[i+1];
                }
            }
        }
        return executor;
    }

int DialogueBuilder::line(std::string text) {
    return line(false, {}, "", text);
}

int DialogueBuilder::line(std::string name, std::string text) {
    return line(false, {}, name, text);
}

int DialogueBuilder::line(PortraitDefinition portrait, std::string name, std::string text) {
    return line(true, portrait, name, text);
}

int DialogueBuilder::choice(std::string choice, std::vector<int> nodes) {
    return this->choice(false, {}, "", choice, nodes);
}

int DialogueBuilder::choice(std::string name, std::string choice, std::vector<int> nodes) {
    return this->choice(false, {}, name, choice, nodes);
}

int DialogueBuilder::choice(PortraitDefinition portrait, std::string name, std::string choice, std::vector<int> nodes) {
    return this->choice(true, portrait, name, choice, nodes);
}

int DialogueBuilder::option(std::string option, std::vector<int> nodes) {
    if(nodes.empty()){
        executor->content.push_back({OPTION,"", option, 1, {nop()}});
    }else{
        executor->content.push_back({OPTION,"", option, 1, {nodes[0]}});
    }

    construct(nodes);

    int newId = executor->content.size() - 1;
    return newId;
}

int DialogueBuilder::call(std::function<void(void)> func) {
    executor->functionStack.push_back(func);
    int newFunctionId = executor->functionStack.size() - 1;

    executor->content.push_back({CALL, "", "", 0, {}, newFunctionId});
    int newId = executor->content.size() - 1;

    tieLooseEnds(newId);
    return newId;
}

int DialogueBuilder::condition(std::function<bool(void)> func, std::vector<int> nodes) {
    return condition(func, nodes, {});
}

int DialogueBuilder::condition(std::function<bool(void)> func, std::vector<int> nodes, std::vector<int> elseNodes) {
    executor->conditionStack.push_back(func);
    int newConditionId = executor->conditionStack.size() - 1;

    identifyLooseEnds(nodes);
    identifyLooseEnds(elseNodes);

    if (elseNodes.empty()) {
        executor->content.push_back({CONDITION,"", "", 0, {0, nodes[0]}, newConditionId});
    }else{
        executor->content.push_back({CONDITION,"", "", 1, {elseNodes[0], nodes[0]}, newConditionId});
    }

    int newId = executor->content.size() - 1;

    construct(nodes);
    return newId;
}

int DialogueBuilder::mark(std::string name) {
    executor->content.push_back({MARK, name, "", 0, {}});
    int newId = executor->content.size() - 1;

    executor->jumps.insert({name, newId});
    tieLooseEnds(newId);
    return newId;
}

int DialogueBuilder::jump(std::string name) {
    executor->content.push_back({JUMP, name, "", 0, {-1}});
    int newId = executor->content.size() - 1;
    tieLooseEnds(newId);
    return newId;
}

int DialogueBuilder::nop() {
    executor->content.push_back({NOP, "NOP", "", 0, {}});
    int newId = executor->content.size() - 1;
    tieLooseEnds(newId);
    return newId;
}