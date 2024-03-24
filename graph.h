#include <stdio.h>
#include <string>
#include <vector>


struct State{

    std::string name;
    bool isFinal;
    bool isStart;
    std::vector<int> edges; // -1 neighbor means there is no such edge.
};


class FA{
    public:
        //std::vector<std::string> codeToName;
        std::vector<State> states;
    

    private:


        void insertStates(std::vector<std::string> newStates);
        void annotateStarts(std::vector<std::string> startStates);
        void annotateFinals(std::vector<std::string> finalStates);
        int nameToCode(std::string stateName);
        std::string codeToName(int code);
};



void FA::insertStates(std::vector<std::string> newStates){

    for(std::string stateName : newStates){

        for(State state : states){
            if(state.name == stateName){
                return;
                // exception 
            }
        }

        State newState;
        newState.name = stateName;
        newState.isFinal = false;
        newState.isStart = false;
        newState.edges = std::vector<int>(128,-1);

        states.push_back(newState);
    }
}

void FA::annotateStarts(std::vector<std::string> startStates){
    for(std::string stateName : startStates){
        int code = nameToCode(stateName);
        states[code].isStart = true;
    }
}

void FA::annotateFinals(std::vector<std::string> finalStates){
    for(std::string stateName : finalStates){
        int code = nameToCode(stateName);
        states[code].isFinal = true;
    }
}

int FA::nameToCode(std::string stateName){

    for(int i=0;i<states.size();i++){

        if(states[i].name == stateName){
            return i;
        }
    }
    return -1; // not found
}

std::string FA::codeToName(int code){

    for(int i=0;i<states.size();i++){
        if(i==code){
            return states[i].name;
        }
    }

    return "Not Found"; // not found
}