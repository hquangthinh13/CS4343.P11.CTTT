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
struct queue{
    node* head;
    node* tail;
    int maxNumb; //So luong node toi da trong stack
    int count = 0; //So luong node dang co trong stack o 1 thoi diem
    // 1. Write a function to initialize the queue
    void initializeStack(){
        head = tail = NULL;
        cout<<"Enter the total number of nodes included in the stack: "; cin>>maxNumb;
        int n;
        while (1){
            if (count <= maxNumb){
                cout<<"Enter a value: "; cin>>n;
                if (n==0) break;
                enqueue(n);
                count++;
            }
            else{
                cout<<"The stack has been full.";
                break;
            }
        }
    }
    bool isEmpty(){
        if (head == NULL) return true;
        else return false;
    }
    bool isFull(){
        if (count>=maxNumb) return true;
        else return false;
    }
    //  4. enqueue
    void enqueue(int input){
        node* newTail = new node(input);
        if (head == NULL){
            head = tail = newTail;
        }
        else {
            tail->link = newTail;
            tail = newTail;
        }
    }
    //   5. Write a function to dequeue an element from the queue.
    void dequeue(){
        int result = head->data;
        node* tmp = head;
        head = head->link;
        delete tmp;
        cout<<"The element whose value is "<<result<<" had successfully been dequeued"<<endl;
    }
    void printRearAndFront(){
        cout<<"The rear element has the value of "<<tail->data<<endl;
        cout<<"The front element has the value of "<<head->data<<endl;
    }
};
void MenuList(){
    cout<<"**DSA - LAB 2 - Part 02**"<<endl;
    cout<<"1. Initialize the queue."<<endl;
    cout<<"2. Check if the queue is empty"<<endl;
    cout<<"3. Check if the queue is full "<<endl;
    cout<<"4. Enqueue an element onto the queue."<<endl;
    cout<<"5. Dequeue an element from the queue."<<endl;
    cout<<"6. Print the REAR and FRONT elements of the queue."<<endl;
}
int main(){
    queue A;
    int n;
    MenuList();
    while (cin>>n)
    {
        switch(n){
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
                A.enqueue(k);
                cout<<"The entered value had been pushed into the stack";
                break;
            case 5:
                A.dequeue();
                break;
            case 6:
                A.printRearAndFront();
                break;
            default:
                cout<<"Try again.";
                break;
        }
    }
    return 0;
}




