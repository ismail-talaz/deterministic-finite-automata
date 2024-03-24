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

``` q0 qf   // All states
q0          // Start state
qf          // Final state
4           // Number of transitions
q0 a q0     // Transitions
q0 a qf  
qf a qf  
qf b qf
```

- It creates this deterministic finite automata :


![img](https://miro.medium.com/v2/resize:fit:514/1*Q35rZMtMP4MF8TiOoDZLmw.jpeg)
