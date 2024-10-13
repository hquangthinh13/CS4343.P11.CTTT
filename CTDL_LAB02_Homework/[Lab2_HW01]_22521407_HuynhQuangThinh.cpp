//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 02 - Homework 01
//Notes or Remarks:

#include <iostream>
using namespace std;

struct node{
    node* link;
    node* prev;
    int value;
    node(int data){
        value = data;
        link = NULL;
        prev = NULL;
    }
};
struct stack{
    node* top;
    stack(){
        top = NULL;
    }
    void push(int input){
        node* newTop = new node(input);
        if (top == NULL){
            top = newTop;
        }
        else {
            newTop->link = top;
            top = newTop;
        }
    }
    void pop(){
        node* tmp = top;
        top = top->link;
        delete tmp;
    }
    int topValue(){
        return top->value;
    }
    bool isEmpty(){
        if (top == NULL) return true;
        else return false;
    }
    void display() {
        node* current = top;
        cout << "STACK = < ";
        while (current != nullptr) {   
            cout << current->value << " ";
            current = current->link;
        }
        cout << ">" << endl;
    }
};
void displayTowers(stack& towerA, stack& towerB, stack& towerC){
    cout << "A Tower\n";
    towerA.display();
    cout << "B Tower\n";
    towerB.display();
    cout << "C Tower\n";
    towerC.display();
    cout << "===================\n";
}

bool isValidMove(stack& source, stack& destination) {
    if (source.isEmpty()) {
        cerr << "Error: Cannot move from an empty source stack." << endl;
        return false;
    }
    if (destination.isEmpty()) {
        return true;
    }
    return source.topValue() < destination.topValue();
}

void moveDisk(stack& source, stack& destination) {
    if (isValidMove(source, destination)) {
        int disk = source.topValue();
        source.pop();
        if (disk != -1) { 
            destination.push(disk);
        }
    } else {
        cerr << "Invalid move. Please try again." << endl;
    }
}
bool isGameWon(stack& towerC) {
    if (towerC.isEmpty()) {
        return false;
    }
    node* current = towerC.top;
    int expectedDisk = 1; 
    while (current != nullptr) {
        if (current->value != expectedDisk) {
            return false; 
        }
        current = current->link;
        expectedDisk++; 
    }
    return expectedDisk - 1 == 3;
}
int main() {
    stack towerA, towerB, towerC;
    for (int i = 0; i < 5; i++) {
        towerA.push(i);
    }
    cout << "=========== Demo Stack ===========\n"
    << "0. Exit.\n"
    << "1. A -> B.\n"
    << "2. B -> A.\n"
    << "3. B -> C.\n"
    << "4. C -> B.\n"
    << "5. C -> A.\n"
    << "6. A -> C.\n"
    << "===================================\n";
    displayTowers(towerA, towerB, towerC);
    int move;
    while (!isGameWon(towerC)) {
        cout << "Please input a move (1-6): ";
        cin >> move;
        switch (move) {
            case 0:
                return 0;
            case 1:
                moveDisk(towerA, towerB); // A -> B
                break;
            case 2:
                moveDisk(towerB, towerA); // B -> A
                break;
            case 3:
                moveDisk(towerB, towerC); // B -> C
                break;
            case 4:
                moveDisk(towerC, towerB); // C -> B
                break;
            case 5:
                moveDisk(towerC, towerA); // C -> A
                break;
            case 6:
                moveDisk(towerA, towerC); // A -> C
                break;
            default:
                cerr << "Invalid move. Please enter a number between 1 and 6." << endl;
                continue;
        }
        displayTowers(towerA, towerB, towerC);
    }
    cout << "Congratulations! You won the Tower of Hanoi puzzle." << endl;
    return 0;
}
