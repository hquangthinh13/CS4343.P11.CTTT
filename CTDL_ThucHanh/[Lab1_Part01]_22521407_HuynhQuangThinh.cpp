//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 01 - Exercise - Part 01
//Notes or Remarks:

#include <iostream>
using namespace std;

void MenuList(){
    cout<<"**DSA - LAB 1**"<<endl;
    cout<<"1. Find the Middle Node of a Linked List"<<endl;
    cout<<"2. Detect a Cycle in a Linked List"<<endl;
    cout<<"3. Combine Two Sorted Linked Lists"<<endl;
    cout<<"4. Find the Intersection of Two Linked Lists"<<endl;
    cout<<"5. Reverse a Linked List"<<endl;
    cout<<"6. Eliminate Duplicates from a Sorted Linked List"<<endl;
    cout<<"7. Check if a Linked List is a Palindrome"<<endl;
    cout<<"8. Search for nodes with the value X in the list."<<endl;

}
struct Node{
    int value;
    Node* link;
};
Node* createNode(int value){
    Node* A=new Node();
    A->value=value;
    A->link=NULL;
    return A;
}
struct List{
    Node* head;
    Node* tail;
    List(){
        head=NULL;
        tail=NULL;
    }
    void AddTail(int value){
        Node*A=createNode(value);
        if(head==NULL){
            head=A;
            tail=A;
        }
        else{
            tail->link=A;
            tail=A;
        }
    }
    void AddHead(int value){
        Node*A=createNode(value);
        if(head==NULL){
            head=A;
            tail=A;
        }
        else{
            A->link=head;
            head=A;
        }
    }
    void printList(){
        if (head == NULL){
            cout<<"List is empty.";
            return;
        }
        else{
            Node* tmp = head;
            while(tmp != NULL){
                cout<<tmp->value<<" ";
                tmp = tmp->link;
            }
        }
    }
};
void findMiddleNode(List A){   
    //return nếu list trống
    if (A.head == NULL) return;
    //Tạo 1 node tạm để duyệt hết list, mỗi lần duyệt +1 cho biến count -> Tổng node trong list
    Node* tmp = A.head;
    int count = 0;
    while (tmp != NULL)
    {   
        count = count + 1;
        tmp = tmp->link;
    }
    if (count == 0){
        cout<<"The list is empty"<<endl;
    }
    Node* tmp1 = A.head;
    int middle = count/2;
    if (middle == 0) return;
    //Nếu tổng node trong list là số lẻ
    if (count%2!=0)
    {
        while (middle!=0)
        {
            tmp1 = tmp1->link;
            middle--;
        }
        cout<<"The middle node has the value of "<<tmp1->value<<" at the index of "<<count/2<<endl;
        return;
    }
    //Nếu tổng node trong list là số chẵn
    else
    {
        while (middle!=0)
        {
            tmp1 = tmp1->link;
            middle--;
        }
        cout<<"We found 2 nodes at the center of the list."<<endl;
        cout<<"The first node has the value of "<<tmp1->value<<" at the index of "<<count/2<<endl;
        cout<<"The second one has the value of "<<tmp1->link->value<<" at the index of "<<count/2+1<<endl;
    }
}
bool hasCycle(List A){
    if (A.head == NULL || A.head->link == NULL) return false;
    Node* prev_tmp = A.head;
    Node* tmp = A.head;
    while (tmp->link != NULL && tmp != NULL){
        if (prev_tmp == tmp) return true;
        prev_tmp = prev_tmp->link;
        tmp = tmp->link->link;
    }
    return false;
}
void combineTwoList(List& A, List B){
    Node* tmp = B.head;
    while (tmp != 0){
        A.AddTail(tmp->value);
        tmp = tmp->link;
    }
}
void reverseList(List A, List& reversedA){
    Node* tmp = A.head;
    while (tmp != NULL){
        reversedA.AddHead(tmp->value);
        tmp = tmp->link;
    }
}
bool isPalindrome(List A, List B){
    Node* tmpA = A.head;
    Node* tmpB = B.head;
    while (tmpA != NULL){
        if (tmpA->value != tmpB->value) return false;
        tmpA = tmpA->link;
        tmpB = tmpB->link;
    }
    return true;
}
void findX(int X, List A){
    Node* tmp = A.head;
    int index = 0;
    int foundNumber = 0;
    while(tmp!=NULL){
        if(tmp->value==X){
            cout<<endl<<"Address: "<<&tmp;
            foundNumber++;
        }
        index++;
        tmp = tmp->link;
    }
    if (foundNumber == 0) cout<<"NULL";
}
Node* intersectionOf2List(List A, List B){
    if (A.head == NULL || B.head == NULL) return nullptr;
    Node* tmpA = A.head;
    Node* tmpB = B.head;
    while (tmpA != NULL && tmpB != NULL){
        if (tmpA == tmpB) return tmpA;
        tmpA = tmpA->link;
        tmpB = tmpB->link;
    }
    return nullptr;
}
void deleteDuplicates(List& A){
    if (A.head == NULL) return;
    Node* tmp = A.head;
    while (tmp->link != NULL){
        if (tmp->value == tmp->link->value){
            Node* tmp0 =tmp->link;
            tmp->link = tmp->link->link;
            delete tmp0;
        }
        else tmp=tmp->link;
    }
}
void Prob1(){
    List A;
    int n;
    cout<<"Enter the values in the list: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl;
    findMiddleNode(A);
}
void Prob2(){
    List A;
    int n;
    cout<<"Enter the values in the list: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl;
    if (hasCycle(A)) cout <<"The list has a cycle.";
    else cout<<"No cycle was detected in the list.";
    cout<<endl;
}
void Prob3(){
    List A, B;
    int n;
    cout<<"List 1: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    cout<<endl<<"List 2: ";
    while(1){
        cin>>n;
        if (n==0) break;
        B.AddTail(n);
    }
    A.printList();
    combineTwoList(A,B);
    cout<<endl;
    A.printList();
}
void Prob4(){
    List A, B;
    int n;
    cout<<"List 1: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    cout<<endl<<"List 2: ";
    while(1){
        cin>>n;
        if (n==0) break;
        B.AddTail(n);
    }
    A.printList();
    cout<<endl;
    B.printList();
    Node* intersection = intersectionOf2List(A,B);
    if (intersection == nullptr) cout<<"These 2 lists have no common nodes.";
    else cout<<"The intersection of 2 entered lists is the node with the value "<<intersection->value<<"at the address of "<<intersection;
}
void Prob5(){
    List A, B;
    int n;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    reverseList(A,B);
    cout<<endl;
    B.printList();
}
void Prob6(){
    List A;
    int n;
    cout<<"Enter the values in the list: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    deleteDuplicates(A);
    cout<<endl<<"Duplicates-removed list: ";
    A.printList();
    cout<<endl;
}
void Prob7(){
    List A, B;
    int n;
    cout<<"Enter the values in the list: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl;
    reverseList(A,B);
    if (isPalindrome(A,B)) cout<<"The entered list is a Palindrome.";
    else cout<<endl<<"The entered list is not a Palindrome."<<endl;
}
void Prob8(){
    List A;
    int n;
    cout<<"Enter the values in the list: ";
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl<<"Enter the number you wish to find in the list: ";
    cin>>n;
    findX(n,A);
    cout<<endl;
}


int main(){
    while(1){
        MenuList();
        int n;
        cin>>n;
        switch (n){
            case 0:
                return 0;
            case 1:
                Prob1();
                break;
            case 2:
                Prob2();
                break;
            case 3:
                Prob3();
                break;
            case 4:
                Prob4();
                break;
            case 5:
                Prob5();
                break;
            case 6:
                Prob6();
                break;
            case 7:
                Prob7();
                break;
            case 8:
                Prob8();
                break;
            default:
                cout<<"Retry.";
                break;
        }
    }
    return 0;
}