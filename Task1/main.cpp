#include <iostream>
#include <fstream> 

using namespace std;

#define MAX_SIZE 100
#define INPUT_SIZE 20000
// Node for the doubly linked list
struct ListNode {
    char value;
    ListNode* prev;
    ListNode* next;

    ListNode(char val) : value(val), prev(nullptr), next(nullptr) {}
};

// Doubly linked list class
class List {
public:
    ListNode* head;
    ListNode* tail;

    List() : head(nullptr), tail(nullptr) {}

    void push_back(char val) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    char pop() {
        if (!head) {
            cout << "List is empty!" << endl;
            return '\0'; // Return a null character if the list is empty
        }

        ListNode* temp = head; // Save the current head
        char value = temp->value; // Save the value of the head node
        head = head->next; // Move the head pointer to the next node

        if (head) {
            head->prev = nullptr; // Disconnect the new head from the old head
        } else {
            tail = nullptr; // If the list becomes empty, set tail to nullptr
        }

        delete temp; // Delete the old head node
        return value; // Return the value of the removed node
    }

    char popTail() {
        if (!tail) {
            cout << "List is empty!" << endl;
            return '\0'; // Return a null character if the list is empty
        }

        ListNode* temp = tail; // Save the current tail
        char value = temp->value; // Save the value of the tail node
        tail = tail->prev; // Move the tail pointer to the previous node

        if (tail) {
            tail->next = nullptr; // Disconnect the new tail from the old tail
        } else {
            head = nullptr; // If the list becomes empty, set head to nullptr
        }

        delete temp; // Delete the old tail node
        return value; // Return the value of the removed node
    }

    void print() {
        ListNode* current = head;
        while (current) {
            cout << current->value << " "; // Print the value of the current node
            current = current->next;      // Move to the next node
        }
        cout << endl; // End the line after printing all nodes
    }
};

// Node for the stack of doubly linked lists
struct StackNode {
    List* list;
    StackNode* prev;
    StackNode* next;

    StackNode() : list(new List()), prev(nullptr), next(nullptr) {}
};

// Stack of doubly linked lists class
class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}

    void push() {
        StackNode* newNode = new StackNode();
        if (!top) {
            top = newNode;
        } else {
            newNode->prev = top;
            top->next = newNode;
            top = newNode;
        }
    }

    void push(List* list) {
        StackNode* newNode = new StackNode();
        if (!top) {
            top = newNode;
            top->list = list;
        } else {
            newNode->prev = top;
            top->next = newNode;
            top = newNode;
            top->list = list;
        }
    }

    List* pop() {
        if (!top) {
            cout << "Stack is empty!" << endl;
            return nullptr; // Return nullptr if the stack is empty
        }
    
        StackNode* temp = top;
        List* poppedList = temp->list; // Save the list to return later
        top = top->prev;
        if (top) {
            top->next = nullptr;
        }
        delete temp; // Delete the StackNode, but not the list
        return poppedList; // Return the popped list
    }

    void addToList(char val) {
        if (!top) {
            cout << "Stack is empty! Push a list first." << endl;
            return;
        }
        top->list->push_back(val);
    }

    StackNode* getTop() {
        return top;
    }

    void swapTop() {
        List* list1 = this->pop();
        List* list2 = this->pop();
        if (list1 && list2) {
            this->push(list1);
            this->push(list2);
        }
    }

    

    void printRecursion(StackNode* node, int* count) {
        if (!node) {
            return; // Base case: stop when the node is null
        }
        // Recursive call to the previous node
        (*count)++;
        printRecursion(node->prev, count);
        
        // Print the current list after recursion unwinds
        ListNode* listCurrent = node->list->head;
        cout << (*count)-- << ": ";
        while (listCurrent) {
            cout << listCurrent->value;
            listCurrent = listCurrent->next;
        }
        cout << endl;
    }

    void print() {
        int count = -1;
        printRecursion(top, &count);
    }

    char listTop() {
        return top->list->head->value;
    }
    bool isTopEmpty(){
        if(getTop()->list->head == nullptr) return true;
        else return false;
    }
    void negate() {
        if (isTopEmpty()) { //change for isEmpty()
            pop();
            push();
            addToList('1');
        } else if (listTop() == '0') {
            pop();
            push();
            addToList('1');
        } else {
            pop();
            push();
            addToList('0');
        }
    }
};

bool readInputFromFile(const string& filename, char* input) {
    ifstream inputFile(filename); // Open the file
    if (!inputFile) {
        cout << "Error: Could not open input file!" << endl;
        return false; // Return false if the file could not be opened
    }

    inputFile.getline(input, INPUT_SIZE); // Read the input from the file
    inputFile.close(); // Close the file
    return true; // Return true if the input was successfully read
}


bool isDigit(char a) {
    if(a >= '0' && a <='9') return true;
    else return false;
}

void process(char *input, Stack* stack, int* instr_count) {
    if (*input == '\0') { 

        return;
    }
    if(isDigit(*input)) {
        stack->addToList(*input);
    }
    else {
        (*instr_count)++;
        char a;
        switch(*input) {
            case '\'':
            stack->push();
            break;
            case ',':
            stack->pop();
            break;
            case ':':
            stack->push(stack->getTop()->list);
            break;
            case ';': 
            stack->swapTop();
            break;
            case '@':

            break;
            case '.':
            cin>>a;
            stack->addToList(a);
            break;
            case '>':
            cout << stack->pop()->head->value << endl;
            break;
            case '!': 
            stack->negate();
            break;
            case '<':

            break;
            case '=':

            break;
            case '~':
            stack->push();
            stack->addToList(*(instr_count) + '0');
            break;
            case '?':

            break;
            case '-':

            break;
            case '^':
            if(stack->getTop()->list->tail->value == '6') { // change for '-'
                stack->getTop()->list->popTail();
            }
            break;
            case '$':
            a = stack->getTop()->list->pop();
            stack->push();
            stack->addToList(a);

            break;
            case '#':

            break;
            case '+':

            break;
            case '&':
            stack->print();
            break;
            case ']':

            break;
            case '[':

            break;
            
        }
        
    }
    process(input + 1, stack, instr_count);
    
}


int main() {
    char input[INPUT_SIZE];
    Stack* stack = new Stack;
    int instr_count = 0;
    if(!readInputFromFile("input.txt", input)) return 1;
    //cout << input;
    process(input, stack, &instr_count);
    stack->print();
    

    return 0;
}