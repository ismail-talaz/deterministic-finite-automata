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


std::string DFA::getStartState(){
    for(State state : states){
        if(state.isStart) return state.name;
    }
}