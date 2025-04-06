#include <iostream>
#include <fstream> 

using namespace std;

#define MAX_SIZE 100
#define INPUT_SIZE 20000

bool isDigit(char a);

struct ListNode {
    char value;
    ListNode* prev;
    ListNode* next;

    ListNode(char val) : value(val), prev(nullptr), next(nullptr) {}
};


class List {
public:
    ListNode* head;
    ListNode* tail;

    List() : head(nullptr), tail(nullptr) {}

    List(const List& other) : head(nullptr), tail(nullptr) {
        if (other.head) {
            head = new ListNode(other.head->value);
            copyNodes(head, other.head->next);
        }
    }
    
    void copyNodes(ListNode* current, ListNode* otherNode) {
        if (!otherNode) {
            tail = current;
            return;
        }
    
        current->next = new ListNode(otherNode->value);
        current->next->prev = current;
        copyNodes(current->next, otherNode->next);
    }

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
        ListNode* temp = head;
        char value = temp->value;
        head = head->next;

        if (head) {
            head->prev = nullptr; 
        } else {
            tail = nullptr; 
        }

        delete temp; 
        return value;
    }

    char popTail() {
        if(!tail) return '0';
        ListNode* temp = tail;
        char value = temp->value;
        tail = tail->prev;

        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }

        delete temp;
        return value;
    }

    int toIntHelper(ListNode* node, int mult, int* value) {
        if (!node) return *value; 
        if (node->value == '-') {
            *value *= -1;
            return *value;
        }
        if (isDigit(node->value)) {
            *value += (node->value - '0') * mult;
        }
        return toIntHelper(node->next, mult * 10, value);
    }

    int toInt() {
        if (!head) return 0;
        int value = 0;
        return toIntHelper(head, 1, &value);
    }

    void printHelper(ListNode* node) {
        if (!node) {
            return;
        }
        cout << node->value;
        printHelper(node->next);
    }

    void print() {
        if (!head) {
            cout << endl;
            return;
        }
        printHelper(head);
        cout << endl;
    }

    void cutZerosHelper() {
        if (!tail) {
            return;
        }
        if (tail->value == '0') {
            popTail();
            cutZerosHelper();
        }
    }
    void cutZeros() {
        if(!tail) return;
        bool neg = false;
        if(tail->value == '-') {
            popTail();
            neg = true;
        }
        if(tail) cutZerosHelper();
        if (!head) {
            push_back('0');
            neg = false;
        }
        if(neg) {

            List* temp = new List;
            temp->push_back('-');
            append(temp);
            delete temp;
        }
    }

    bool isEqual(List* other) {
        if (!other) return false;
        cutZeros();
        other->cutZeros();
        if(length() < 10 && other->length() < 10) {
            return toInt() == other->toInt();
        }
        else {
        //print();
        //other->print();
        return isEqualHelper(head, other->head);
        }
    }

    bool isEqualHelper(ListNode* a, ListNode* b) {
        if (!a && !b) {
            return true;
        }
        if(!a || !b) {
            return false;
        }
        if (a->value != b->value) {
            return false;
        }
        return isEqualHelper(a->next, b->next);
    }

    bool isSmaller(List* other) {
        if (!other) return false;
        cutZeros();
        other->cutZeros();
        if(length() < 10 && other->length() < 10) {
            //cout << toInt() << endl << other->toInt() << endl;
            return toInt() < other->toInt();
        }
        else {
        ListNode* a = tail;
        ListNode* b = other->tail;
        if(a->value == '-' && b->value == '-') return isBiggerHelper(a->prev, b->prev);
        if(a->value == '-') return true;
        if(b->value == '-') return false;
        if(length() < other->length()) return true;
        if(length() > other->length()) return false;
        return isSmallerHelper(a, b);
        }
    }

    bool isSmallerHelper(ListNode* a, ListNode* b) {
        if (!a && !b) return false;
        if(a->value > b->value) return false;
        if (a->value < b->value) return true;
        return isSmallerHelper(a->prev, b->prev);
    }

    bool isBiggerHelper(ListNode* a, ListNode* b) {
        if (!a && !b) {
            return true;
        }
        if(b->value > a->value) return false;
        return isBiggerHelper(a->prev, b->prev);
    }

    int getLength(ListNode* node) {
        if (!node) return 0;
        return 1 + getLength(node->next);
    }
    
    int length() {
        return getLength(head);
    }

    bool isEmpty() {
        if(head == nullptr) return true;
        else return false;
    }

    void append(List* other) {
        if (!other || !other->head) {
            return;
        }
    
        if (!head) {
            head = other->head;
            tail = other->tail;
            return;
        }
    
        tail->next = other->head;
        other->head->prev = tail;
    
        tail = other->tail;
    }
};


struct StackNode {
    List* list;
    StackNode* prev;
    StackNode* next;

    StackNode() : list(new List()), prev(nullptr), next(nullptr) {}
};

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
        StackNode* temp = top;
        List* list = temp->list;
        top = top->prev;
        if (top) {
            top->next = nullptr;
        }
        delete temp;
        return list;
    }

    void addToList(char val) {
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

    bool isTopNegative() {
        if(!top->list->tail) return false;
        return top->list->tail->value == '-';
    }
    
    void printHelper(StackNode* node, int* count) {
        if (!node) {
            return;
        }
        (*count)++;
        printHelper(node->prev, count);
        
        cout << (*count)-- << ": ";
        node->list->print();
    }

    void print() {
        int count = -1;
        printHelper(top, &count);
    }

    char listTop() {
        return top->list->tail->value;
    }
    bool isTopEmpty() {
        if (getTop()->list->head == nullptr) return true;
        else return false;
    }
    void negate() {
        if (isTopEmpty()) {
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
            cerr << "Error: Position " << position << " is out of bounds!" << endl;
            return nullptr;
        }
        if (currentIndex == position) {
            return node->list;
        }
        return listAtPositionHelper(node->prev, position, currentIndex + 1);
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
        cerr << "Error: Could not open input file: " << filename << endl;
        return false; // Return false if the file could not be opened
    }

    inputFile.getline(input, INPUT_SIZE); // Read the input from the file
    if (inputFile.fail()) {
        cerr << "Error: Failed to read input from file: " << filename << endl;
        inputFile.close();
        return false;
    }

    inputFile.close(); // Close the file
    return true; // Return true if the input was successfully read
}

void toListHelper(int val, List* list) {
    if (val == 0) return;
    toListHelper(val / 10, list); 
    list->push_back((val % 10) + '0');
}

List* toList(int val) {
    List* list = new List;

    if (val == 0) {
        list->push_back('0');
        return list;
    }

    if (val < 0) {
        list->push_back('-');
        val = -val;
        toListHelper(val, list);
    } else {
        toListHelper(val, list);
    }

    return list;
}

bool isDigit(char a) {
    if (a >= '0' && a <= '9') return true;
    else return false;
}


void process(char* input, Stack* stack, int* instr_count) {
    char current = *(input + *instr_count);
    if(current == '\0') {
        return;
    }
    
    switch (current) {
        case '\'':
            stack->push();
            break;
        case ',': {
            stack->pop();
            break;
        }
        case ':': {
            List* list = new List(*(stack->getTop()->list));
            stack->push(list);
            break;
        }
        case ';':
            stack->swapTop();
            break;
        case '@': {
            int position = stack->pop()->toInt();
            List* list = stack->listAtPosition(position);
            stack->push(list);
            break;
        }
        case '.': {
            char a;
            cin >> a;
            stack->addToList(a);
            break;
        }
        case '>':
            cout << stack->pop()->pop();
            break;
        case '!':
            stack->negate();
            break;
        case '<': {
            List* a = stack->pop();
            List* b = stack->pop();
            
            stack->push();
            stack->addToList(b->isSmaller(a) ? '1' : '0');
            delete a;
            delete b;
            break;
        }
        case '=': {
            List* a = stack->pop();
            List* b = stack->pop();
            
            stack->push();
            stack->addToList(a->isEqual(b) ? '1' : '0');
            delete a;
            delete b;
            break;
        }
        case '~':
            stack->push(toList(*(instr_count)));
            break;
        case '?': {
            int t = stack->pop()->toInt();
            List* w = stack->pop();
            if(!w->isEmpty() && !(w && w->length() == 1 && w->head->value == '0')) {
                *instr_count = t-1;
            }
            break;
        }
        case '-':
            if (isDigit(*(input + *instr_count + 1))) {
                stack->addToList(current);
            } else {
                if (stack->isTopNegative()) {
                    stack->getTop()->list->popTail();
                } else {
                    List* list = new List;
                    list->push_back('-');
                    stack->append(list);
                }
            }
            break;
        case '^':
        if (stack->isTopNegative()) {
            stack->getTop()->list->popTail();
        }
            break;
        case '$': {
            char a = stack->getTop()->list->pop();
            stack->push();
            stack->addToList(a);
            break;
        }
        case '#': {
            List* list = stack->pop();
            stack->append(list);
            break;
        }
        case '+': {
            int a = stack->pop()->toInt();
            int b = stack->pop()->toInt();
            stack->push(toList(a + b));
            break;
        }
        case '&':
            stack->print();
            break;
        case ']': {
            int ascii = stack->pop()->toInt();
            stack->push();
            stack->addToList(ascii);
            break;
        }
        case '[': {
            List* list = stack->pop();
            List* ascii = toList(list->head->value);
            stack->push(ascii);
            break;
        }
        default:
            stack->addToList(current);
            break;
        
    }
    
    cout << *instr_count << ": " << *(input + *instr_count) << endl;
    (*instr_count)++;

    
    process(input, stack, instr_count);
    
}

int main() {
    char input[INPUT_SIZE];
    Stack* stack = new Stack;
    int instr_count = 0;
    // cin>>input;
    if (!readInputFromFile("input.txt", input)) return 1;
    process(input, stack, &instr_count);

    return 0;
}
