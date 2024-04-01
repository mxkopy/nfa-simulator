#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

template <typename T>
struct State {

    multimap<T, State*> transitions = {};

    auto operator[](T c){
        return transitions.equal_range(c);
    }

    void set_transition(T input, State* output){
        transitions.insert({input, output});
    }

};

template <typename T>
struct NFA {

    State<T>* initial;
    set<State<T>*> states;
    set<State<T>*> accept_states;

    // Constructs an NFA from a regular expression. 
    // Currently only supports the . and * operations. 
    NFA(vector<T> input){
        int i = 0;
        initial = new State<T>;
        states.insert(initial);
        State<T>* current = initial;
        while( i < input.size() ){
            auto next = new State<T>;
            if(input[i] == T(".")){
                current -> set_transition(T("ANY"), next);
            }
            else {
                current -> set_transition(input[i], next);
            }
            if(i+1 < input.size() && input[i+1] == T("*")){
                vector<pair<T, State<T>*>> current_transitions(current -> transitions.begin(), current -> transitions.end());
                for(auto n : current_transitions)
                    current -> set_transition(n.first, current);
                current -> set_transition(T(""), next);
                i++;
            }
            current = next;
            states.insert(current);
            i++;
        }
        accept_states.insert(current);
    }

    // Adds the set of states reachable by some transition from the set of current states
    // to the set of next states
    void add_symbol_reachable(set<State<T>*>& current, set<State<T>*>& next, T c){
        for(auto state : current)
            for(auto i = state -> transitions.begin(); i != state -> transitions.end(); i++)
                if(i -> first == c || i -> first == T("ANY"))
                    next.insert(i -> second);        
    }

    // The idea here is that once the set of states reachable by e-transitions is equal
    // to the set of states that we're currently at, we've reached them all
    void add_epsilon_reachable(set<State<T>*>& current){
        int s = 0;
        while(s != current.size()){
            set<State<T>*> reachable = current;
            add_symbol_reachable(current, reachable, T(""));
            current.insert(reachable.begin(), reachable.end());
            s = reachable.size();
        }
    }

    void add_reachable(set<State<T>*>& current, set<State<T>*>& next, T c){
        add_epsilon_reachable(current);
        add_symbol_reachable(current, next, c);
    }

    // Returns the set of states the NFA is in after reading some input.
    set<State<T>*> run(vector<T> input){
        set<State<T>*> current = {initial};
        for(auto c : input){
            set<State<T>*> next = {};
            add_reachable(current, next, c);
            current = next;
        }
        return current;
    }

    // If the NFA has an accept state after reading some input, it accepts. Otherwise it rejects.
    bool accepts(vector<T> input){
        auto end_states = run(input);
        for(State<T>* state : end_states)
            if(accept_states.count(state)) 
                return true;
        return false;
    }

};