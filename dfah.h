#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>


struct State{

    std::string name;
    bool isFinal;
    bool isStart;
    std::vector<int> edges; // -1 neighbor means there is no such edge.
};


class DFA{
    public:
        //std::vector<std::string> codeToName;
        std::vector<State> states;
        void configuration();
        void printStates();
        bool isInLanguage(std::string word);
    private:
        std::string getStartState();
        bool langHelper(std::string currentState, std::string word);
        bool isFinalState(std::string stateName);
        void insertStates(std::vector<std::string> newStates);
        void processStates(std::string inputString, int mode = 0); // mode 0:all states, -1:start states, 1:final states
        void annotateStart(std::string startStateName);
        void annotateFinals(std::vector<std::string> finalStates);
        void processTransition(std::string inputString);
        void insertTransition(std::string pos1, std::string pos2, char weight);
        int nameToCode(std::string stateName);
        std::string codeToName(int code);
};


void DFA::configuration(){
    std::string line;
    std::getline(std::cin, line);
    processStates(line,0);

    std::getline(std::cin, line);
    processStates(line,-1);

    std::getline(std::cin, line);
    processStates(line,1);

    int transitions;
    std::cin >> transitions;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for(int i=0; i<transitions ;i++){
        std::getline(std::cin, line);
        processTransition(line);
    }
}


bool DFA::isInLanguage(std::string word){
    std::string startState = getStartState();
    return langHelper(startState, word);
}



bool DFA::langHelper(std::string currentState, std::string word){
    if(word == ""){
        bool isFinal = isFinalState(currentState);
        return isFinal;
    }
    else{  
        int code = nameToCode(currentState);
        char weight = word[0];
        std::string remaining = word.substr(1);
        int neighborCode = states[code].edges[int(weight)];

        if(neighborCode == -1){
            return false;
        }
        else{
            std::string neighborName = codeToName(neighborCode);
            return langHelper(neighborName,remaining);
        }
    }
}

bool DFA::isFinalState(std::string stateName){
    int code = nameToCode(stateName);
    return (states[code].isFinal);
}

std::string DFA::getStartState(){
    for(State state : states){
        if(state.isStart) return state.name;
    }
}


void DFA::insertStates(std::vector<std::string> newStates){

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

void DFA::processStates(std::string inputString, int mode){

    char seperator = ' ';
    std::vector<std::string> newStates;

    std::string temp = "";
    for(char c : inputString){
        if(c == seperator){
            newStates.push_back(temp);
            temp = "";
        }
        else{
            temp  = temp + c;
        }
    }

    newStates.push_back(temp);
    if(mode == 0) insertStates(newStates);
    else if (mode == -1) annotateStart(newStates[0]);
    else annotateFinals(newStates);

}

void DFA::printStates(){
    
    std::cout << "All States: ";
    for(State state : states){
        std::cout << state.name << " ";
    }

    std::cout << '\n' <<"Start State: ";
    for(State state : states){
        if(state.isStart) std::cout << state.name << " ";
    }

    std::cout << '\n' <<"Final States: ";
    for(State state : states){
        if(state.isFinal) std::cout << state.name << " ";
    }
}


void DFA::annotateStart(std::string startStateName){
    int code = nameToCode(startStateName);
    states[code].isStart = true;
}

void DFA::annotateFinals(std::vector<std::string> finalStates){
    for(std::string stateName : finalStates){
        int code = nameToCode(stateName);
        states[code].isFinal = true;
    }
}

void DFA::processTransition(std::string inputString){


    char seperator = ' ';
    std::vector<std::string> newStates;

    std::string temp = "";

    std::string pos1,pos2;
    char weight;

    int count = 0;
    for(char c : inputString){
        if(c == seperator && count == 0){
            count++;
            pos1 = temp;
            temp = "";
        }
        else if(count == 1){
            weight = c;
            count++;
        }
        else{
            temp  = temp + c;
        }
    }
    pos2 = temp.substr(1);

    insertTransition(pos1,pos2,weight);

}

void DFA::insertTransition(std::string pos1, std::string pos2, char weight){
    int code1 = nameToCode(pos1);
    int code2 = nameToCode(pos2);
    states[code1].edges[int(weight)] = code2;
}

int DFA::nameToCode(std::string stateName){

    for(int i=0;i<states.size();i++){

        if(states[i].name == stateName){
            return i;
        }
    }
    return -1; // not found
}

std::string DFA::codeToName(int code){

    for(int i=0;i<states.size();i++){
        if(i==code){
            return states[i].name;
        }
    }

    return "Not Found"; // not found
}