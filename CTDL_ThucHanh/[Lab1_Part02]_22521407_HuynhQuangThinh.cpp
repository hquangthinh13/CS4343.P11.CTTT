//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 01 - Exercise - Part 02
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <cstdlib> //Su dung cho ham rand()

using namespace std;

void MenuList(){
    cout<<"**DSA - LAB 1**"<<endl;
    cout<<"1. Add Two Numbers"<<endl;
    cout<<"2. Copy List with Random Pointers"<<endl;
    cout<<"3. Swap Nodes in a Linked List"<<endl;
    cout<<"4. Remove the N-th Node from the End of a List"<<endl;
    cout<<"5. Separate Odd and Even Nodes in a Linked List"<<endl;
    cout<<"6. Divide a Linked List into Parts"<<endl;
    cout<<"7. Remove Zero-Sum Consecutive Nodes from a Linked List"<<endl;
    cout<<"8. Randomly generate a list."<<endl;
    cout<<"0. Exit."<<endl;
}
struct Node{
    int value;
    Node* link;
    Node* random;
};
Node* createNode(int value){
    Node* A=new Node();
    A->value=value;
    A->link=NULL;
    A->random = NULL;
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
int countNodes(List A){
    if (A.head == NULL) return 0;
    int count = 1;
    Node* tmp = A.head;
    while (tmp != NULL){
        count++;
        tmp=tmp->link;
    }
    return count;
}
void deleteTheNthNode(List& A, int N){
    if (countNodes(A)<N || A.head == NULL){
        cout<<endl<<"The entered list does not have any node at the index of "<<N;
        return;
    }
    Node* tmp = A.head;
    //Neu xoa node head (index = 1)
    if (N == 1){
        A.head = A.head->link;
        if (A.head->link == NULL){
            A.tail = A.head;
        }
        delete tmp;
        return;
    }
    Node* prev_tmp = A.head;
    //Duyet den node thu n
    for (int i = 1; i < N-1; i++) {
        prev_tmp = prev_tmp->link;
    }
    if (prev_tmp == NULL) return;
    Node* toBeDeletedNode = prev_tmp->link;
    prev_tmp->link = toBeDeletedNode->link;
    delete toBeDeletedNode;
    return;
}
void deleteNthNodeFromTheEnd(List& A, int N){
    //Vi tri node tinh tu dau list = Tong node - vi tri tu cuoi list
    int M = countNodes(A) - N;
    deleteTheNthNode(A,M);
}
bool isOdd(int value){
    if (value%2==0) return false;
    else return true;
}
List sortedOddAndEvenList(List&A){
    //Tao 1 list moi, duyet qua tung node, kiem tra chan le -> them vao dau hoac duoi cua list moi 
    List SortedA;
    Node* tmp = A.head;
    while (tmp != NULL){
        if (isOdd(tmp->value)){
            SortedA.AddTail(tmp->value);
        }
        else SortedA.AddHead(tmp->value);
        tmp = tmp->link;
    }
    return SortedA;
}
void swapNodes(List& A){
    if (A.head == NULL) return;
    cout<<"Enter the first position: "; 
    int pos1; cin>>pos1;
    cout<<"Enter the second position: ";
    int pos2; cin>>pos2;

    //Neu la 2 node o dau list
    if ((pos1 == 1 && pos2 == 2) || (pos1 == 2 && pos2 == 1)){
        Node* tmp = A.head->link;
        A.head->link = tmp->link;
        tmp->link = A.head;
        return;
    }
    //Tim 2 nodes o 2 vi tri input
    Node* first_tmp0 = NULL;
    Node* first_tmp1 = A.head;
    for (int i = 1; i < pos1 && first_tmp1 != NULL; i++) {
        first_tmp0 = first_tmp1;
        first_tmp1 = first_tmp1->link;
    }
    Node* sec_tmp0 = NULL;
    Node* sec_tmp1 = A.head;
    for (int i = 1; i < pos2 && sec_tmp1 != nullptr; i++) {
        sec_tmp0 = sec_tmp1;
        sec_tmp1 = sec_tmp1->link;
    }
    //Neu 1 trong 2 node = NULL
    if (first_tmp1 == NULL || sec_tmp1 == NULL) return;
    //Doi vi tri 2 nodes
    if (first_tmp0 != NULL) {
        first_tmp0->link = sec_tmp1;
    } else {
        A.head = sec_tmp1;
    }
    if (sec_tmp0 != NULL) {
        sec_tmp0->link = first_tmp1;
    } else {
        A.head = first_tmp1;
    }
    Node* tmp = first_tmp1->link;
    first_tmp1->link = sec_tmp1->link;
    sec_tmp1->link = tmp; 
}
void removeZeroSumNodes(List& A) {
    if (A.head == NULL) {
        return; 
    }
    Node* tmp = new Node();
    tmp->link = A.head;
    Node* prev = tmp;
    int sum = 0;
    while (prev->link != NULL) {
        sum += prev->link->value;
        if (sum == 0) {
            prev->link = prev->link->link;
        } else {
            prev = prev->link;
        }
    }
    delete tmp;
    if (tmp->link != A.head) {
        A.head = tmp->link;
    }
}
void divideList(List& A, int k) {
    //Chia list thanh k phan
    if (A.head == NULL || k <= 0) return; 
    // Tinh tong so node trong list
    int size = countNodes(A);
    // So node cua moi phan va phan node con du
    int partSize = size / k;
    int remainder = size % k;
    Node* current = A.head;
    //vector nay dung de chua cac node head cua cac list sau khi duoc divided
    vector<Node*> parts(k);
    for (int i = 0; i < k; i++) {
        parts[i] = current;
        for (int j = 0; j < partSize + (i < remainder ? 1 : 0); j++) {
            if (current != NULL) {
                current = current->link;
            }
        }
    }

    if (parts[k - 1] != NULL) {
        parts[k - 1]->link = NULL;
    }

    A.head = parts[0];
    for (int i = 0; i < k; i++){
        Node* tmp = parts[i];
        cout<<"Part "<<i+1<<": ";
        while (tmp != NULL && tmp != parts[i+1]){
            cout<<tmp->value<<" ";
            tmp = tmp->link;
        }
        cout<<endl;
    }
}
Node* copyListWithRandomPointers(Node* head) {
    if (head == NULL) return NULL;
    //Tao cac node moi sau nhung node ban dau
    for (Node* current = head; current != NULL; ) {
        Node* newNode = createNode(current->value);
        newNode->link = current->link;
        current->link = newNode;
        current = newNode->link;
    }
    //Gan vi tri pointer->random voi cac node vua tao o tren
    for (Node* current = head; current != NULL; current = current->link->link) {
        if (current->random != NULL) {
            current->link->random = current->random->link;
        }
    }

    //Tach list vua copy khoi list ban dau
    Node* newHead = head->link;
    for (Node* current = head; current != NULL; ) {
        Node* newCurrent = current->link;
        current->link = newCurrent->link;
        if (newCurrent->link != NULL) {
            newCurrent->link = newCurrent->link->link;
        }
        current = current->link;
    }
    return newHead;
}
void Prob1(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl<<"You're about to add 2 numbers to the list above.";
    cout<<endl<<"Enter the 1st number: "; cin>>n;
    A.AddTail(n);
    cout<<"Enter the 2nd number: "; cin>>n;
    A.AddTail(n);
    cout<<endl<<"Your final list: ";
    A.printList(); cout<<endl;
}
void Prob2(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    List B;
    Node* randomHeadNode = copyListWithRandomPointers(A.head);
    B.head = randomHeadNode;
    cout<<endl;
    B.printList();
    cout<<endl;
}
void Prob3(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl;
    swapNodes(A);
    A.printList();
    cout<<endl;
}
void Prob4(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl<<"Enter the position of the node you wish to delete: "; 
    cin>>n;
    deleteNthNodeFromTheEnd(A,n);
    A.printList();
    cout<<endl;
}
void Prob5(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    List B = sortedOddAndEvenList(A);
    cout<<endl;
    B.printList();
    cout<<endl;
}
void Prob6(){
    List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    cout<<endl<<"How many parts do you want to divide into?"; 
    cout<<endl;
    cin>>n;
    divideList(A,n);
}
void Prob7(){
   List A;
    cout<<"Initialize your list."<<endl;
    int n;
    cout<<"Enter the values: "<<endl;
    while(1){
        cin>>n;
        if (n==0) break;
        A.AddTail(n);
    }
    A.printList();
    removeZeroSumNodes(A);
    cout<<endl;
    A.printList();
    cout<<endl;
}
void Prob8(){
    //Su dung ham rand() tu thu vien cstdlib de lay random gia tri
    //So luong node/entry
    int numbOfEntries = rand() % 21 + 39; //lay random trong khoang 39-59
    List A;
    //Loop n lan de them tung node vao, voi moi node assign random value trong khoang -99 den 99
    int value;
    for (int i = 1; i < numbOfEntries; i++){
        value = rand() % 199 - 99;
        A.AddTail(value);
    }
    A.printList();
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