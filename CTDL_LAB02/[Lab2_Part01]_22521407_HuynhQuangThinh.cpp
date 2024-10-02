//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 02 - Exercise - Part 01
//Notes or Remarks:

#include <iostream>
using namespace std;

struct node{
    node* link;
    int data;
    node(int input){
        data = input;
        link = NULL;
    }
};
struct stack{
    node* top;
    int maxNumb; //So luong node toi da trong stack
    int count = 0; //So luong node dang co trong stack o 1 thoi diem
    // 1. Write a function to initialize the stack
    void initializeStack(){
        top = NULL;
        cout<<"Enter the total number of nodes included in the stack: "; cin>>maxNumb;
        int n;
        while (1){
            if (count <= maxNumb){
                cout<<"Enter a value: "; cin>>n;
                if (n==0) break;
                push(n);
                count++;
            }
            else{
                cout<<"The stack has been full.";
                break;
            }
        }
    }
    //  4. Write a function to push an element onto the stack.
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
    //  5. Write a function to pop an element from the stack.
    void pop(){
        int result = top->data;
        node* tmp = top;
        top = top->link;
        delete tmp;
        cout<<"The element whose value is "<<result<<" had successfully been poped from the stack"<<endl;
    }
    // 2. Write a function to check if the stack is empty. If empty, return true, otherwise return false
    bool isEmpty(){
        if (top == NULL) return true;
        else return false;
    }
    //3. Write a function to check if the stack is full (if applicable). If full, return true, otherwise return false.
    bool isFull(){
        if (count>=maxNumb) return true;
        else return false;
    }
    //  6. Print the TOP element of the stack.
    void printTop(){
        cout<<"The top element of the stack has the value of "<<top->data;
    }
};
void MenuList(){
    cout<<"**DSA - LAB 2 - Part 01**"<<endl;
    cout<<"1. Initialize the stack."<<endl;
    cout<<"2. Check if the stack is empty"<<endl;
    cout<<"3. Check if the stack is full "<<endl;
    cout<<"4. Push an element onto the stack."<<endl;
    cout<<"5. Pop an element from the stack."<<endl;
    cout<<"6. Print the TOP element of the stack."<<endl;
}
int main(){
    stack A;
    int n;
    MenuList();
    while (cin>>n)
    {
        switch(n){
            case 0:
                return;
            case 1:
                A.initializeStack();
                break;
            case 2:
                if (A.isEmpty()) cout<<"The stack is empty";
                else cout<<"The stack is not empty";
                break;
            case 3:
                if (A.isFull()) cout<<"The stack has been full";
                else cout<<"There are still empty slots in the stack";
                break;
            case 4:
                int k;
                cout<<"Enter a value to push into the stack: "; cin>>k;
                A.push(k);
                cout<<"The entered value had been pushed into the stack";
                break;
            case 5:
                A.pop();
                break;
            case 6:
                A.printTop();
                break;
            default:
                cout<<"Try again.";
                break;
        }
    }
    return 0;
}




