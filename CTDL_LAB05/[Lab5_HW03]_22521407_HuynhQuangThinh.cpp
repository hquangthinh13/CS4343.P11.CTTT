//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 05 - Homework 03
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

// A Huffman tree node
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Compare function for priority queue
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// Build Huffman Tree
HuffmanNode* buildHuffmanTree(const string& text) {
    // Count frequency of each character
    unordered_map<char, int> freqMap;
    for(char ch : text) {
        freqMap[ch]++;
    }
    
    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for(auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    // Iterate until the queue has more than one node
    while(pq.size() != 1) {
        // Remove two nodes with the highest priority (lowest frequency)
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        // Create a new internal node with these two nodes as children
        // and with frequency equal to the sum of the two nodes
        HuffmanNode* top = new HuffmanNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    
    // The remaining node is the root of the Huffman tree
    return pq.top();
}

// Generate Huffman Codes
void generateCodes(HuffmanNode* root, string str, unordered_map<char, string> &huffmanCode) {
    if(!root)
        return;
    
    // If this is a leaf node, it contains one of the input characters
    if(!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }
    
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

string encodeMessage(const string& text, unordered_map<char, string> &huffmanCode) {
    string encodedString = "";
    for(char ch : text) {
        encodedString += huffmanCode[ch];
    }
    return encodedString;
}

string decodeMessage(HuffmanNode* root, const string& encodedStr) {
    string decodedStr = "";
    HuffmanNode* current = root;
    for(char bit : encodedStr) {
        if(bit == '0')
            current = current->left;
        else
            current = current->right;
        
        // If leaf node, append the character and reset to root
        if(!current->left && !current->right) {
            decodedStr += current->data;
            current = root;
        }
    }
    return decodedStr;
}

int main() {
    string text = "hanh trinh tren dat phu sa";
    
    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(text);
    
    // Generate Huffman Codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    
    cout << "Huffman Codes:\n";
    for(auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second<<endl;
    }
    
    // Encode the message
    string encodedStr = encodeMessage(text, huffmanCode);
    cout << "Encoded Message:\n" << encodedStr;
    
    // Decode the message
    string decodedStr = decodeMessage(root, encodedStr);
    cout << "\nDecoded Message:\n" << decodedStr;
    
    return 0;
}