#include "DialogueExecutor.hpp"  
	
DialogueExecutor::DialogueExecutor()
{
	dialogue = new Dialogue();
}
	
DialogueExecutor::~DialogueExecutor()
{
	
}


void DialogueExecutor::next() 
{
    DialoguePart* lastRef = &content[lastIndex];

    if(!dialogue->isShown()){
        dialogue->show();
    }

    if(lastRef->next[0] == 0){
        dialogue->hide();
        index = 0;
        lastIndex = 0;
        return;
    }

    if (lastRef->type == CHOICE) {
        // since last was CHOICE, this one must be an OPTION, so we check what the user picked and run that
        index = content[lastRef->next[option]].next[0];
    }
    
    DialoguePart* ref = &content[index];

    if(ref->hasPortrait) {
        dialogue->setPortrait(ref->portrait.Texture, ref->portrait.flipped);
    }else{
        dialogue->unsetPortrait();
    }

    if (ref->type == CHOICE ) {
        //if the current one is CHOICE, we draw options
        std::vector<std::string> options;
        for (int i = 0; i < ref->items; i++) {
            options.push_back(content[ref->next[i]].content);
        }
        dialogue->showOptions(ref->content, options, &option, ref->name);
    }else if (ref->type == LINE) {
        //if the current one is LINE we draw a text
        dialogue->typeText(ref->content, ref->name);
    }

    lastIndex = index;
    index = ref->next[0];

    if(ref->type == MARK || ref->type == NOP) {
        next();
    }

    if(ref->type == JUMP) {
        index = jumps[ref->name];
        next();
    }

    if (ref->type == CALL) {
        functionStack[ref->function]();
        next();
    }

    if (ref->type == CONDITION) {
        if (conditionStack[ref->function]()) {
            index = ref->next[1];
            next();
        } else{
            index = ref->next[0];
            next();
        }
    }
}

void DialogueExecutor::draw() 
{
    dialogue->draw();
}

void DialogueExecutor::update() 
{
    dialogue->update();
}