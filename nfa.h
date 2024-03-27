#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>


struct State{

    std::string name;
    bool isFinal;
    bool isStart;
    std::vector<std::vector<int>> edges; // empty vector means that there is no neighbor related to the character. 
};



class NFA{
    public:
        //std::vector<std::string> codeToName;
        
        /*void configuration();
        void printStates();
        bool isInLanguage(std::string word);*/
    private:
        /*std::vector<State> states;
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
        std::string codeToName(int code); */
};


void NFA::configuration(){
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


bool NFA::isInLanguage(std::string word){
    std::string startState = getStartState();
    return langHelper(startState, word);
}



bool NFA::langHelper(std::string currentState, std::string word){
    if(word == ""){
        bool isFinal = isFinalState(currentState);
        return isFinal;
    }
    else{  
        int code = nameToCode(currentState);
        char utilized = word[0];
        std::vector<int> neighbors = states[code].edges[int(weight)];
        std::vector<int> emptyneighbors = states[code].edges[int('e')];

        bool key = false;

        for(int neighborCode : neighbors){
            std::string neighborName = codeToName(neighborCode);
            key = (key || langHelper(neighborName, word.substr(1)));
        }

        for(int int neighborCode : emptyneighbors){
            std::string neighborName = codeToName(neighborCode);
            key = (key || langHelper(neighborName, word));
        }

        return key;
    }
}

bool NFA::isFinalState(std::string stateName){
    int code = nameToCode(stateName);
    return (states[code].isFinal);
}

std::string NFA::getStartState(){
    for(State state : states){
        if(state.isStart) return state.name;
    }
}


void NFA::insertStates(std::vector<std::string> newStates){

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

void NFA::processStates(std::string inputString, int mode){

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

void NFA::printStates(){
    
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


void NFA::annotateStart(std::string startStateName){
    int code = nameToCode(startStateName);
    states[code].isStart = true;
}

void NFA::annotateFinals(std::vector<std::string> finalStates){
    for(std::string stateName : finalStates){
        int code = nameToCode(stateName);
        states[code].isFinal = true;
    }
}

void NFA::processTransition(std::string inputString){


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

void NFA::insertTransition(std::string pos1, std::string pos2, char weight){
    int code1 = nameToCode(pos1);
    int code2 = nameToCode(pos2);
    states[code1].edges[int(weight)] = code2;
}

int NFA::nameToCode(std::string stateName){

    for(int i=0;i<states.size();i++){

        if(states[i].name == stateName){
            return i;
        }
    }
    return -1; // not found
}

std::string NFA::codeToName(int code){

    for(int i=0;i<states.size();i++){
        if(i==code){
            return states[i].name;
        }
    }

    return "Not Found"; // not found
}