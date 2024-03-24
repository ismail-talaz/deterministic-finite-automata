#include "dfah.h"
#include <string>
#include <vector>

using namespace std;


int main(){

    DFA machine;

    machine.configuration();

    cout << "Result: " << machine.isInLanguage("abc");


    return 0;
}