//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 01 - Homework 03
//Notes or Remarks:

#include <iostream>
#include <string>
using namespace std;

struct node{
    node* link;
    string tokenID;
    int expiredTime;

    node(string ID, int time){
        tokenID = ID;
        expiredTime = time;
        link = NULL;
    }
};

struct AuthenticationManager{
    node* head;
    int ttl;
    AuthenticationManager(int timeToLive) {
        ttl = timeToLive;
        head = NULL;
    }
    void generate(string tokenID, int currentTime) {
        node* newToken = new node(tokenID, currentTime + ttl);
        newToken->link = head;
        head = newToken;	
    }
    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        node* tmp = head;
        node* prev = NULL;
        while (tmp != NULL) {
            if (tmp->expiredTime > currentTime) {
                count++; 
                prev = tmp; 
            } else {
                if (prev == NULL) {
                    head = tmp->link;
                } else {
                    prev->link = tmp->link; 
                }
                node* tmp0 = tmp; 
                delete tmp0; 
            }
            tmp = tmp->link;
        }
        return count; 
    }
    void renew(string tokenID, int currentTime) {
        node* tmp = head;
        while (tmp != NULL) {
            if (tmp->tokenID == tokenID && tmp->expiredTime > currentTime) {
                tmp->expiredTime = currentTime + ttl;
                return; 
            }
            tmp = tmp->link;
        }
    }
};

int main() {
    cout<<"Enter a time to live value to initialize the Authentication Manager: ";
    int timeToLive;
    cin >> timeToLive; 
    AuthenticationManager* authManager = new AuthenticationManager(timeToLive);
    string command;
    while (cin >> command) {
        if (command == "generate") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->generate(tokenId, currentTime);
        } else if (command == "renew") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->renew(tokenId, currentTime);
        } else if (command == "countUnexpiredTokens") {
            int currentTime;
            cin >> currentTime; 
            cout << authManager->countUnexpiredTokens(currentTime) << endl; 
        }
    }
    return 0;
}

