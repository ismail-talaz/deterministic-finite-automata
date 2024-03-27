//#include "dfah.h"
#include "nfa.h"
#include <string>
#include <vector>

using namespace std;


int main(){

    NFA machine;

    machine.configuration();

    cout << "Result: " << machine.isInLanguage("");


    return 0;
}