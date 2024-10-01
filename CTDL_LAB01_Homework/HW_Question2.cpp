//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 01 - Homework 02
//Notes or Remarks:

#include <iostream>
#include <string>

using namespace std;

struct node {
    string url;
    node* prev;
    node* link;
    node(string input){
        url = input;
        prev = NULL;
        link = NULL;
    }
};

struct BrowserHistory {
    node* head;   
    node* current; 
    BrowserHistory(string homepage) {
        head = new node(homepage); 
        current = head;             
    }
    //Method vist ~ them 1 node chua url vao list
    void visit(string url) {
        node* newNode = new node(url);
        current->link = newNode;   
        newNode->prev = current;   
        current = newNode;         
    }
    //Di chuyen toi n lan
    string forward(int steps) {
        while (steps > 0 && current->link != NULL) {
            current = current->link; 
            steps--;
        }
        return current->url; // Tra ve string url cua node hien tai
    }
    //Di chuyen nguoc ve n lan
    string back(int steps) {
        while (steps > 0 && current->prev != NULL) {
            //Neu node o truoc node hien tai la node head
            if (current->prev == head) {
                current = head; 
                break; 
            }
            current = current->prev; 
            steps--;
        }
        return current->url; // Tra ve string url cua node hien tai
    }
    //Method nay dung node tam travel het list de xuat url o tung node
    void display() {
        if (head == NULL){
            cout << "NULL" << endl;
            return;
        }
        node* tmp = head;
        while (tmp != NULL) {
            cout << tmp->url << " -> ";
            tmp = tmp->link;
        }
    }

    ~BrowserHistory() {
        node* tmp;
        while (head) { // Cleanup all nodes starting from head
            tmp = head;
            head = head->link;
            delete tmp;
        }
    }
    
};

int main() {
    string homepage;
    cout<<"Enter your homepage URL: ";
    cin >> homepage;
    BrowserHistory* browserHistory = new BrowserHistory(homepage); 
    string command;
    while (cin >> command) {
        if (command == "visit") {
            string url;
            cin >> url;  
            browserHistory->visit(url);
        } else if (command == "back") {
            int steps;
            cin >> steps;  
            cout << browserHistory->back(steps) << endl;
        } else if (command == "forward") {
            int steps;
            cin >> steps; 
            cout << browserHistory->forward(steps) << endl;  
        }
    }
	browserHistory->display();
    return 0;
}

