//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 02 - Homework 02
//Notes or Remarks:

#include <iostream>
using namespace std;

struct node{
    node* link;
    node* prev;
    string url;
    node(string input){
        url = input;
        link = NULL;
        prev = NULL;
    }
};
struct stack{
    node* top;
    node* bottom;
    node* current; 
    stack(){
        top = bottom = current = NULL;
    }
    void back(){
        if (top==NULL){
            cout<<"Can not move backward.";
        }
        else{
            current = current->link;
            cout<<"Current url: "<<current->url;
        }
    }
    void forward(){
        if (top==NULL){
            cout<<"Can not move backward.";
        }
        else{
            current = current->prev;
            cout<<"Current url: "<<current->url;
        }
    }
    void visit(string url){
        node* newUrl = new node(url);
        if (top == NULL) {
            top = newUrl; 
            top->link = top; 
            top->prev = top; 
        } else {
            bottom = top->prev; 
            bottom->link = newUrl;
            newUrl->prev = bottom; 
            newUrl->link = top; 
            top->prev = newUrl; 
        }
        current = top;
    }
};
void MenuList(){
    cout<<"**DSA - LAB 2 - HW02**"<<endl
    <<"1. Visit a new url."<<endl
    <<"2. Go back to the previous URL."<<endl
    <<"3. Go forward to the next URL."<<endl<<"0. Exit."<<endl;
}
int main(){
    stack A;
    int n;
    string url;
    MenuList();
    while (cin>>n)
    {
        switch(n){
            case 0:
                return 0;
            case 1:
                cout<<"Enter an url: "; 
                // getline(cin,url);
                cin>>url;
                A.visit(url);
                cin.ignore();
                break;
            case 2:
                A.back();
                break;
            case 3:
                A.forward();
                break;
            default:
                cout<<"Try again.";
                break;
        }
    }
    return 0;
}




