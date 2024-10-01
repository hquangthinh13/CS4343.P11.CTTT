//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 01 - Homework 01
//Notes or Remarks:

#include <iostream>
#include <string.h>
using namespace std;

struct node{
    string songName;
    node* prev;
    node* link;
    node(){
        prev = link = NULL;
    }
};
node* createNode(string name){
    node* A = new node();
    A->songName = name;
}
struct songList{
    node* head;
    node* tail;
    node* current;
    songList(){
        head = NULL;
        tail = NULL;
        current = NULL;
    }
    void addSong(string name){
        node* newSong = createNode(name);
        if (head == NULL) {
            head = newSong; 
            head->link = head; 
            head->prev = head; 
            current = head; 
        } else {
            node* tail = head->prev; 
            tail->link = newSong;
            newSong->prev = tail; 
            newSong->link = head; 
            head->prev = newSong; 
        }
    }
    void playNext(){
        if (head == NULL){
            cout<<"There's no songs in your playlist.";
            return;
        }
        if (current == NULL){
            current = head->link;
        }
        else{
            current = current->link;
        }
        if (current != NULL) cout<<"Playing: "<<current->songName<<endl;
    }
    void playPrev(){
        if (head == NULL){
            cout<<"There's no song in your playlist.";
            return;
        }
        if (current == NULL){
            current = head->prev;
        }
        else{
            current = current->prev;
        }
        if (current != NULL) cout<<"Playing: "<<current->songName<<endl;
    }
    void removeNodeBySongName(string songName) {
        node* tmp = head;
        while (tmp != NULL) {
            if (tmp->songName == songName) {
                //Neu list co 1 node duy nhat
                if (tmp->link == tmp) {
                    delete tmp;
                    head = NULL;
                    current = NULL;
                    return;
                }
                //Neu la node head
                if (tmp == head) {
                    head->prev->link = head->link; 
                    head->link->prev = head->prev; 
                    head = head->link; 
                } else {
                    // Link the previous node to the next node
                    tmp->prev->link = tmp->link;
                    tmp->link->prev = tmp->prev;
                }
                if (current == tmp) {
                    current = tmp->link;
                }
                delete tmp;
                return;
            }
            tmp = tmp->link;
        }
        cout << "Song not found." << endl;
    }
    //Method nay dung node tam travel het list de xuat thong tin cua tung node trong list 
    void display(){
        if (head == NULL){
            cout<<"There's no song in your playlist.";
            return;
        }
        cout<<"--YOUR CURRENT PLAYLIST--"<<endl;
        node* tmp = head->link;
        int index = 1;
        cout<<index<<". "<<tmp->prev->songName<<" ";
        while (tmp != head){
            index++;
            cout<<index<<". "<<tmp->songName<<" ";
            tmp = tmp->link;
        }
    }
};

int main(){
    cout << "--WELCOME TO HQUANGTHINH'S MUSIC PLAYER--"<< endl;
    cout << "Enter the number of operations you wish to execute: ";
    int n;
    cin >> n;
    string operation, name;
    songList A;
    cout << "CHOOSE AN OPERATION BELOW BY ENTER THE COMMAND:" << endl
        << "ADD <song name> to add a song." << endl
        << "NEXT to play the next song." << endl
        << "PREV to play the previous song." << endl
        << "REMOVE <song name> to remove a song." << endl
        << "DISPLAY to display the current playlist." << endl;
    for (int i = 0; i < n; i++) {
        cin>>operation;
        if (operation=="ADD") {
            cin>>name;
            A.addSong(name);
        } else if (operation == "NEXT") {
            A.playNext();
        } else if (operation == "PREV") {
            A.playPrev();
        } else if (operation == "REMOVE"){
            cin>>name;
            A.removeNodeBySongName(name);
        } else if (operation == "DISPLAY") {
            A.display();
            cout<<endl;
        } else {
            cout << "Invalid" << endl;
        }
    }
    return 0;
}