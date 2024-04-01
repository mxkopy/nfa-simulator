# NFA 
Simulates an NFA with epsilon-transitions. A basic regular expression matcher (only supporting . and *) is provided.

To run the code, run `make && ./nfa $regex $input`. 

However, if your regex is .*, make sure you quote it, since bash will instead give you the first item in your directory starting with '.'. 

# Further Reading
I think this code is a pretty good instance of [Savitch's theorem](https://en.wikipedia.org/wiki/Savitch%27s_theorem) for finite automata. 
You'd expect NFAs to have some sort of exponential resource usage, but we can bound it by using the fact that there are a finite number of states and that a state receiving an input on one branch is indistinguishable from a state receiving the same input on another branch.