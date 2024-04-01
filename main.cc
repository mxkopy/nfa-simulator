#include "NFA.hh"

using namespace std;

int main(int argc, char* argv[]){

    vector<string> r = {};
    vector<string> s = {};
    auto R = string(argv[1]);
    auto S = string(argv[2]);
    for(auto i = argv[1]; *i; i++) r.push_back(string(1, *i));
    for(auto i = argv[2]; *i; i++) s.push_back(string(1, *i));

    NFA<string> n = NFA<string>(r);
    cout << n.accepts(s) << endl;

}