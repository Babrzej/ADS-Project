#include <iostream>

using namespace std;

#define MAX_SIZE 100

class Stack {
private:
    string arr[MAX_SIZE];
    int top;

public:
    Stack() : top(-1) {}

    void push(string list) {

    }
};
//works :)
string readProgram(string input) {
    string program = "";
    for(int i = 0; i < input.size(); i++) {
        if(!isalpha(input[i]) && !isdigit(input[i])) {
            program += input[i];
        }
    }
    return program;
}

void Process(string* input, string program, string number) {
    if(program.find(input[0]) == false || input[0] == "-") {
        if(input->size() > 1 && input) {
            
        }
    }
}

int main() {
    string input;
    string program;
    int instructions = program.size();
    int instrCount = 0;
    cin >> input;
    program = readProgram(input);


    return 0;
}