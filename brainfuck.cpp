#include <bits/stdc++.h>
using namespace std;

// C++14 doesn't support byte , so using char
typedef char byte;

// strings to output errors occured while interpreting
#define NO_MATCH_PARAN "Syntax error: No match found for paranthesis."
#define SEG_FAULT "Segmentation fault: negative memory address requested."
#define UNEXPECTED_UNMATCH "Unexpected error: Matching paranthesis not found."

/*
 * The main purpose of this function is to get pairs (left, right)
 * (well, in a map, and not *exactly* as pairs) so that whenever we encounter
 * a left or right bracket, we don't need to iterate over the string to find the
 * corresponding matching bracket -- we can simply do a map lookup --
 * much more efficient
 */
map<int, int> get_matching_paran(string s){
    stack<int> st;
    map<int, int> mp;
    for(int i=0; i<s.length(); i++){
        if(s[i] == '[')
            st.push(i);
        else if(s[i] == ']'){
            // stack is empty, there's no [ paran to match to current ]
            if(st.empty()){
                cout<<NO_MATCH_PARAN<<endl;
                exit(1);
            }
            // this gives us the position of matching [ paran
            int position = st.top();
            st.pop();
            mp[position] = i;
            mp[i] = position;
        }
        // else, we have other string characters that 
        // we dont need to worry about for this part of the code
    }
    // if the stack isn't empty, there's at least one [ which wasn't matched
    if(!st.empty()){
        cout<<NO_MATCH_PARAN<<endl;
        exit(1);
    }
    // if stack is empty, we're good to go
    return mp;
}

int main(int argc, char **argv) {
    string code, l;
    // read code from the command line
    while(getline(cin, l))
        code += l;
    
    // data pointer -- current position in memory
    int current_position = 0;
    // the main memory, created using a vector
    vector<byte> memory(1, 0);
    // get (L, R) pairs for paranthesis
    // (again, in the form of a map, and not exactly pairs)
    map<int, int> match = get_matching_paran(code);
    // start iterating over the instruction buffer until we have reached end of buffer
    for(int i=0; i<code.length(); i++){
        if(code[i] == '['){
            if(match.find(i) == match.end()){
                // this should never happen since we matched parans in earlier step
                cout<<UNEXPECTED_UNMATCH<<endl;
                return(1);
            }
            // go to the matching R paran if current memory location is zero
            if(memory[current_position] == 0)
                i = match[i];
        }
        else if(code[i] == ']'){
            if(match.find(i) == match.end()){
                // this should never happen since we matched parans in earlier step
                cout<<UNEXPECTED_UNMATCH<<endl;
                return(1);
            }
            // go to the matching L paran if current memory location is non zero
            if(memory[current_position] != 0)
                i = match[i];
        }
        else if(code[i] == '>'){
            // add more "space" to "memory" if needed
            // need to do this because we aren't allocating a huge memory in one go in the beginning
            if(current_position == memory.size()-1){
                memory.push_back(0);
            }
            current_position++;
        }
        else if(code[i] == '<'){
            // if data pointer is at position zero, 
            // it will point to memory[-1] after one left shift -- invalid address
            if(current_position == 0){
                cout<<SEG_FAULT<<endl;
                exit(1);
            }
            current_position--;
        }
        else if(code[i] == '+'){
            // increase the byte at data pointer
            memory[current_position]++;
        }
        else if(code[i] == '-'){
            // decrease the byte at data pointer
            memory[current_position]--;
        }
        else if(code[i] == '.'){
            // output the byte at data pointer
            cout<<memory[current_position];
        }
        else if(code[i] == ','){
            // read byte from standard input to current memory location
            // TODO
        }
        // else, we just have comments, so ignore
    }
    cout<<endl;
    return 0;
}

