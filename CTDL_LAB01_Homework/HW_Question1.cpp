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
};
node* createNode(string name){
    node* A = new node();
    A->songName = name;
    A->link = NULL;
    A->prev = NULL;
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
        if (head == NULL){
            head = newSong;
            tail = head;
            return;
        }
        newSong->prev = tail;
        tail->link = head;
        newSong = tail;
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
    }
    void removeNodeBySongName(string songName) {
        node* temp = head;
        while (temp != NULL) {
            if (temp->songName == songName) {
                // Neu la node head
                if (temp == head) {
                    head = temp->link;
                    if (head != NULL) {
                        head->prev = NULL;
                    }
                }
                // Neu la node tail
                else if (temp == tail) {
                    tail = temp->prev;
                    tail->link = NULL;
                }
                // Neu la node giua
                else {
                    temp->prev->link = temp->link;
                    temp->link->prev = temp->prev;
                }
                delete temp;
                return;
            }
            temp = temp->link;
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
        node* tmp = head;
        int index = 0;
        while (tmp!=NULL){
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
    for (int i = 0; i < n; i++) {
        cout << "CHOOSE AN OPERATION BELOW BY ENTER THE COMMAND:" << endl
             << "ADD <song name> to add a song." << endl
             << "NEXT to play the next song." << endl
             << "PREV to play the previous song." << endl
             << "REMOVE <song name> to remove a song." << endl
             << "DISPLAY to display the current playlist." << endl;
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