//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 02 - Homework 04
//Notes or Remarks:

#include <iostream>
#include <vector>
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
struct queue{
    int count = 0;
    node* head;
    node* tail;
    queue(){
        head = NULL;
    }
    void enqueue(int input){
        node* newTail = new node(input);
        if (head == NULL){
            head = tail = newTail;
        }
        else {
            tail->link = newTail;
            tail = newTail;
        }
        count++;
    }
    void dequeue(){
        if (head == NULL) return;
        node* tmp = head;
        head = head->link;
        delete tmp;
        count--;
    }
    bool isEmpty(){
        if (head == NULL) return true;
        else return false;
    }
    int topValue(){
        return head->value;
    }
    int sum(){
        int sum = 0;
        node* tmp = head;
        while (tmp!=NULL){
            sum = sum + tmp->value;
            tmp = tmp->link;
        }
        return sum;
    }
};
int minCoins(vector<int>& prices) {
    int totalCost = 0;
    queue freeFruits;
    for (int i = 0; i < prices.size(); ++i) {
        //TH1: fruit tại index thử i có giá khác i
        if (prices[i] != i+1){
            totalCost = totalCost + prices[i];
        }
        //TH2: fruit tại index thứ i có giá = i & fruit thứ i+1 có giá khác i+1
        else if (prices[i] == i+1 && prices[i+1] != i+2) {
            totalCost = totalCost + prices[i];
            //Bỏ qua fruit thứ i+1 vì đã được free (+1 ở vòng lặp for và +1 ở câu lệnh dưới đây)
            i++;
        }
        //TH3: có nhiều fruit có giá = với index đứng kề nhau
        else {
            int added = 0; //đếm số lượng đã thêm vào queue
            while (prices[i] == i+1){
                freeFruits.enqueue(prices[i]);
                added++;
                i++;
            }
            //Nếu số lượng vừa thêm vào queue là chẵn, vd: 2 3 4 5 -> Mua 2, 3 lấy 4, 5 sẽ rẻ hơn
            if (added %2 == 0){
                while (!freeFruits.isEmpty()){
                    totalCost = totalCost + freeFruits.topValue();
                    freeFruits.dequeue();
                    freeFruits.dequeue();
                }
            }
            //Nếu số lượng = 3, vd: 1 2 3 -> Mua 1, 2 sẽ rẻ hơn 1, 3
            else if (added == 3){
                totalCost = totalCost + freeFruits.topValue();
                freeFruits.dequeue();
                totalCost = totalCost + freeFruits.topValue();
                freeFruits.dequeue();
                freeFruits.dequeue();
            }
            //Nếu số lượng lẻ >3, vd: 1 2 3 4 5 -> Mua 2, 4 sẽ rẻ hơn 1, 3, 5
            else{
                node *tmp = freeFruits.head;
                while (tmp->link != NULL){
                    totalCost = totalCost + tmp->link->value;
                    tmp = tmp->link->link;
                }
            }
        }
    }
    return totalCost;
};
int main() {
    vector<int> prices;
    int price;
    cout << "Enter the prices of the fruits:" << endl;
    while (true) {
        cin >> price;
        if (price == 0) {
            break;
        }
        prices.push_back(price);
    }
    int result = minCoins(prices);
    cout << "Minimum number of coins necessary to obtain all the fruits: " << result;
    return 0;
}