
//system libs

//other libs
#include "raylib.h"
#include "raymath.h"

//project includes
#include "Scene.hpp"
#include "SceneManager.hpp"

#include "Dialogue.hpp"
#include <functional>
#include <unordered_map>

enum DialogueNodeType {
    LINE, CHOICE, CALL, OPTION, CONDITION, MARK, JUMP, NOP
};

struct DialoguePart {
    DialogueNodeType type = LINE;
    std::string name;
    std::string content;
    size_t items = 0;
    int next[5];    //max number of options supported
    int function = -1;
};

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

    public:
        friend class DialogueBuilder;

        DialogueExecutor() {
            dialogue = new Dialogue();
        }

        void next() {
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

        void draw() {
            dialogue->draw();
        }

        void update() {
            dialogue->update();
        }
};

class DialogueBuilder {
    private:
    DialogueExecutor executor;
    std::vector<int> looseEnds;

    void identifyLooseEnds(std::vector<int> nodes) {
        if (!nodes.empty()) {
            DialogueNodeType lastNodeType = executor.content[nodes[nodes.size() - 1]].type;
            if (lastNodeType == LINE || lastNodeType == CALL || lastNodeType == MARK || lastNodeType == NOP) {
                looseEnds.push_back(nodes[nodes.size() - 1]);
            }
        }
    }

    void tieLooseEnds(int target) {
        if (target > 0){
            DialogueNodeType lastType = executor.content[target - 1].type;
            if ((lastType == CHOICE || lastType == CONDITION)) {
                for (int node : looseEnds) {
                    executor.content[node].items = 1;
                    executor.content[node].next[0] = target;
                }
                looseEnds.clear();
            }
        }
    }

    public:

    DialogueExecutor& construct(std::vector<int> nodes) {
        for (int i = 0; i < nodes.size(); i++){
            if (i < nodes.size() - 1) {
                if(executor.content[nodes[i]].items == 0){
                    executor.content[nodes[i]].items = 1;
                    executor.content[nodes[i]].next[0] = nodes[i+1];
                }
            }
        }
        return executor;
    }

    int line(std::string text) {return line("", text);}
    int line(std::string name, std::string text) {
        executor.content.push_back({LINE, name, text, 0});

        int newId = executor.content.size() - 1;
        tieLooseEnds(newId);
        return newId;
    }

    int choice(std::string choice, std::vector<int> nodes) {return this->choice("", choice, nodes);}
    int choice(std::string name, std::string choice, std::vector<int> nodes) {
        DialoguePart part = {CHOICE, name, choice, nodes.size()};
        int index = 0;
        for (int i : nodes){
            if (executor.content[i].type != OPTION) {
                TraceLog(LOG_WARNING, "Choice contains nodes that are not options!");
            }
            part.next[index++] = i;
            DialogueNodeType leafType = executor.content[i-1].type;
            if (leafType == LINE || leafType == CALL || leafType == MARK || leafType == NOP) {
                looseEnds.push_back(i-1);
            }
        }
        executor.content.push_back(part);
        int newId = executor.content.size() - 1;
        return newId;
    }

    int option(std::string option, std::vector<int> nodes) {
        executor.content.push_back({OPTION,"", option, 1, {nodes[0]}});

        construct(nodes);

        int newId = executor.content.size() - 1;
        return newId;
    }

    int call(std::function<void(void)> func) {
        executor.functionStack.push_back(func);
        int newFunctionId = executor.functionStack.size() - 1;

        executor.content.push_back({CALL, "", "", 0, {}, newFunctionId});
        int newId = executor.content.size() - 1;

        tieLooseEnds(newId);
        return newId;
    }

    int condition(std::function<bool(void)> func, std::vector<int> nodes) {
        return condition(func, nodes, {});
    }

    int condition(std::function<bool(void)> func, std::vector<int> nodes, std::vector<int> elseNodes) {
        executor.conditionStack.push_back(func);
        int newConditionId = executor.conditionStack.size() - 1;

        identifyLooseEnds(nodes);
        identifyLooseEnds(elseNodes);

        if (elseNodes.empty()) {
            executor.content.push_back({CONDITION,"", "", 0, {0, nodes[0]}, newConditionId});
        }else{
            executor.content.push_back({CONDITION,"", "", 1, {elseNodes[0], nodes[0]}, newConditionId});
        }

        int newId = executor.content.size() - 1;

        construct(nodes);
        return newId;
    }

    int mark(std::string name) {
        executor.content.push_back({MARK, name, "", 0, {}});
        int newId = executor.content.size() - 1;

        executor.jumps.insert({name, newId});
        tieLooseEnds(newId);
        return newId;
    }

    int jump(std::string name) {
        executor.content.push_back({JUMP, name, "", 0, {-1}});
        int newId = executor.content.size() - 1;
        tieLooseEnds(newId);
        return newId;
    }

    int nop() {
        executor.content.push_back({NOP, "NOP", "", 0, {}});
        int newId = executor.content.size() - 1;
        tieLooseEnds(newId);
        return newId;
    }

};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MiniRPG");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    SceneManager* scenes = SceneManager::GetSceneManager();
    scenes->AddScene( new Scene());

    DialogueBuilder* db = new DialogueBuilder();

    int inventory[3] = {0, 0, 0};

    DialogueExecutor executor = db->construct({
        db->nop(),
        db->mark("Shop"),
        db->choice("Shop keeper", "What do you want to buy?", {
            db->option("Sword", {
                db->call([&inventory](){
                    inventory[0]++;
                }),
                db->jump("Shop")
            }),
            db->option("Potion", {
                db->call([&inventory](){
                    inventory[1]++;
                }),
                db->jump("Shop")
            }),
            db->option("Apple", {
                db->call([&inventory](){
                    inventory[2]++;
                }),
                db->jump("Shop")
            }),
            db->option("Exit", {
                db->nop()
            })
        }),
        db->line("Shop keeper", "I hope to see you again soon!")
    });

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float delta = GetFrameTime();

        if (IsKeyPressed(KEY_ENTER)) {
            executor.next();
        }

        executor.update();
        scenes->update(delta);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        scenes->draw();

        executor.draw();

        
        DrawText("Inventory:", 10, 10, 20, BLUE);
        if(inventory[0] > 0) DrawText(FormatText("Swords: %d", inventory[0]), 10, 40, 20, BLUE);
        if(inventory[1] > 0) DrawText(FormatText("Potions: %d", inventory[1]), 10, 60, 20, BLUE);
        if(inventory[2] > 0) DrawText(FormatText("Apples: %d", inventory[2]), 10, 80, 20, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete AssetManager::GetAssetManager(); //get rid of all loaded textures
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}