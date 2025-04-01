#include <iostream>
#include <fstream> 

using namespace std;

#define MAX_SIZE 100
#define INPUT_SIZE 20000

bool isDigit(char a);
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

    int toIntHelper(ListNode* node, int mult, int* value) {
        if (!node) return 0; // Base case: if node is null, return 0
        if (isDigit(node->value)) {
            *value += (node->value - '0') * mult; // Convert char to int
        }
        if (node->value == '-') {
            *value *= -1;
        }
        toIntHelper(node -> next, mult * 10, value);
        return *value;
    }

    int toInt() {
        if (!head) return 0; // Handle empty list case
        int value = 0;
        return toIntHelper(head, 1, &value); // Start recursion from the head with multiplier 1
    }

    void print() {
        ListNode* current = tail; // Start from the tail
        while (current) {
            cout << current->value; // Print the value of the current node
            current = current->prev; // Move to the previous node
        }
        cout << endl; // End the line after printing all nodes
    }

    void append(List* other) {
        if (!other || !other->head) {
            return; // If the other list is empty, do nothing
        }
    
        if (!head) {
            // If the current list is empty, copy the other list
            head = other->head;
            tail = other->tail;
            return;
        }
    
        // Connect the tail of the current list to the head of the other list
        tail->next = other->head;
        other->head->prev = tail;
    
        // Update the tail of the current list
        tail = other->tail;
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

    List* listAtPositionHelper(StackNode* node, int position, int currentIndex) {
        if (!node) {
            cout << "Error: Position " << position << " is out of bounds!" << endl;
            return nullptr; // Base case: if the node is null, return nullptr
        }
        if (currentIndex == position) {
            return node->list; // Base case: if the current index matches the position, return the list
        }
        return listAtPositionHelper(node->prev, position, currentIndex + 1); // Recursive call to the previous node
    }

    List* listAtPosition(int position) {
        return listAtPositionHelper(top, position, 0);
    }

    void append(List* list) {
        top->list->append(list);
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
// to fix
void toListHelper(int val, List* list) {
    
    return toListHelper(val/10, list);
    list->push_back((val%10) + '0');
    if(val == 0) return;
}

List* toList(int val) {
    List* list = new List;
    toListHelper(val, list);
    return list;

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
            //done
            case '\'':
            stack->push();
            break;
            //done
            case ',':
            stack->pop();
            break;
            //done
            case ':':
            stack->push(stack->getTop()->list);
            break;
            //done
            case ';': 
            stack->swapTop();
            break;
            //done
            case '@':{
                int position = stack->pop()->toInt();
                List * list = stack->listAtPosition(position);
                stack->push(list);
                break;
            }
            //done
            case '.':
            cin>>a;
            stack->addToList(a);
            break;
            //done
            case '>':
            cout << stack->pop()->head->value << endl;
            break;
            //done
            case '!': 
            stack->negate();
            break;
            //done
            case '<': {
                int a = stack->pop()->toInt();
                int b = stack->pop()->toInt();
                stack->push();
                if(b<a) stack->addToList('1');
                else stack->addToList('0');
                break;
            } 
            //done
            case '=': {
                int a = stack->pop()->toInt();
                int b = stack->pop()->toInt();
                stack->push();
                if(b==a) stack->addToList('1');
                else stack->addToList('0');
                break;
            }  
            //done
            case '~':
            stack->push();
            stack->addToList(*(instr_count) + '0');
            break;
            //not
            case '?':

            break;
            //done
            case '-':
            if(isDigit(*(input + 1))) stack->addToList(*input);
            break;
            //done
            case '^':
            if(stack->getTop()->list->tail->value == '-') { // change for '-'
                stack->getTop()->list->popTail();
            }
            break;
            //done
            case '$':
            a = stack->getTop()->list->pop();
            stack->push();
            stack->addToList(a);
            break;
            //done
            case '#': {
                List* list = stack->pop();
                stack->append(list);
            }
            break;
            //to fix
            case '+': {
                int a = stack->pop()->toInt();
                int b = stack->pop()->toInt();
                stack->push(toList(a+b));
                break;
            }
            //done
            case '&':
            stack->print();
            break;
            //not
            case ']':

            break;
            //not
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
    cout << stack->getTop()->list->toInt();
    

    return 0;
}