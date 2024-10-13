//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 02 - Homework 03
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
    bool isEmpty(){
        if (top == NULL) return true;
        else return false;
    }
    int topValue(){
        return top->value;
    }
};
void visiblePeople(int heights[], int n) {
    int* answer = new int[n];
    for (int i = 0; i < n; i++) {
        answer[i] = 0; 
    }
    stack A;  
    for (int i = n - 1; i >= 0; i--) {
        int visibleCount = 0; //Bien dem so luong nguoi visible cua nguoi thu i
        while (!A.isEmpty() && heights[i] > A.topValue()) {
            A.pop(); 
            visibleCount++; 
        }
        if (!A.isEmpty()) {
            visibleCount++; 
        }
        answer[i] = visibleCount; 
        A.push(heights[i]);
    }
    for (int i = 0; i < n; i++) {
        cout << answer[i] << " ";
    }
    delete[] answer; 
}
int main() {
    int n;
    cout << "Enter the number of people: ";
    cin >> n;
    int* heights = new int[n];
    for (int i = 0; i < n; i++) {
        cout<<"Enter person "<<i+1<<" height: ";
        cin >> heights[i];
    }
    visiblePeople(heights, n);
    delete[] heights; 
    return 0;
}




