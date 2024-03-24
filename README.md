## Deterministic Finite Automata

- You can create a deterministic finite automata by giving configuration.

### How can I create DFA with configuration?

- After creating an instance of DFA class, use instance.configuration() function. It takes configuration from input stream.
- In the first line, give state names which are seperated by blank (' ').
- Second line consists of start state.
- Third line consists of final states which are seperated by blank again.
- Then, give the n = number of transitions in the forth.
- In the next n lines, give transitions in this format : s1 character s2
- Here is the one sample:

`q0 qf '\'
q0  \
qf  \
4  \
q0 a q0  
q0 a qf  
qf a qf  
qf b qf`
