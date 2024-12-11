//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 05 - Classwork
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value){
        val = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    TreeNode* root;
    
    BinaryTree(){
        root = nullptr;
    }

    // Insertion
    TreeNode* insertRec(TreeNode* node, int val){
    if(!node){
        return new TreeNode(val);
    }
    if(val < node->val){
        node->left = insertRec(node->left, val);
    }
    else{
        node->right = insertRec(node->right, val);
    }
    return node;   
    }

    void insert(int val) {
        root = insertRec(root, val);
        cout<<"Inserted "<<val<<" to the tree."<<endl;
    }

    // Deletion
    TreeNode* deleteNode(TreeNode* root, int key){
        if(!root) return root;
        if(key < root->val){
            root->left = deleteNode(root->left, key);
        }
        else if(key > root->val){
            root->right = deleteNode(root->right, key);
        }
        else{
            if(!root->left){
                TreeNode* temp = root->right;
                delete root;
                cout<<"Deleted"<<endl;
                return temp;
            }
            else if(!root->right){
                TreeNode* temp = root->left;
                delete root;
                cout<<"Deleted"<<endl;
                return temp;
            }
            TreeNode* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }

    TreeNode* minValueNode(TreeNode* node){
        TreeNode* current = node;
        while(current && current->left)
            current = current->left;
        return current;
    }

    // Searching for value
    TreeNode* searchRec(TreeNode* node, int val){
        if(!node || node->val == val){
            return node;
        }
        if(val < node->val){
            return searchRec(node->left, val);
        }
        else{
            return searchRec(node->right, val);
        }
    }   

    TreeNode* search(int val){
        return searchRec(root, val);
    }

    // Pre-order traversal
    void preorder(TreeNode* node, vector<int>& res){
        if(node){
            res.push_back(node->val);
            preorder(node->left, res);
            preorder(node->right, res);
        }
    }

    // In-order traversal
    void inorder(TreeNode* node, vector<int>& res){
        if(node){
            inorder(node->left, res);
            res.push_back(node->val);
            inorder(node->right, res);
        }
    }

    // Post-order traversal
    void postorder(TreeNode* node, vector<int>& res){
        if(node){
            postorder(node->left, res);
            postorder(node->right, res);
            res.push_back(node->val);
        }
    }

    // Level-order traversal
    vector<vector<int>> levelOrder(){
        vector<vector<int>> levels;
        if(!root) return levels;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            vector<int> level;
            for(int i=0;i<size;i++){
                TreeNode* node = q.front(); q.pop();
                level.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            levels.push_back(level);
        }
        return levels;
    }

    // Calculate height
    int height(TreeNode* node){
        if(!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    // Check if balanced
    bool isBalanced(TreeNode* node){
        if(!node) return true;
        int lh = height(node->left);
        int rh = height(node->right);
        if(abs(lh - rh) > 1) return false;
        return isBalanced(node->left) && isBalanced(node->right);
    }

    // Diameter of tree
    int diameter(TreeNode* node, int &dia){
        if(!node) return 0;
        int lh = diameter(node->left, dia);
        int rh = diameter(node->right, dia);
        dia = max(dia, lh + rh);
        return 1 + max(lh, rh);
    }

    // Lowest Common Ancestor
    TreeNode* LCA(TreeNode* node, int n1, int n2){
        if(!node) return nullptr;
        if(node->val > n1 && node->val > n2)
            return LCA(node->left, n1, n2);
        if(node->val < n1 && node->val < n2)
            return LCA(node->right, n1, n2);
        return node;
    }

    // Maximum Path Sum
    int maxPathSumUtil(TreeNode* node, int &res){
        if(!node) return 0;
        int left = max(maxPathSumUtil(node->left, res), 0);
        int right = max(maxPathSumUtil(node->right, res), 0);
        res = max(res, left + right + node->val);
        return max(left, right) + node->val;
    }

    int maxPathSum(){
        int res = INT_MIN;
        maxPathSumUtil(root, res);
        return res;
    }

    // Reconstruct tree from inorder and postorder
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder){
        int n = inorder.size();
        unordered_map<int, int> idx_map;
        for(int i=0;i<n;i++) idx_map[inorder[i]] = i;
        return build(inorder, postorder, 0, n-1, 0, n-1, idx_map);
    }

    TreeNode* build(vector<int>& inorder, vector<int>& postorder, int inStart, int inEnd, int postStart, int postEnd, unordered_map<int, int>& idx_map){
        if(inStart > inEnd || postStart > postEnd) return nullptr;
        int rootVal = postorder[postEnd];
        TreeNode* root = new TreeNode(rootVal);
        int inRoot = idx_map[rootVal];
        int numsLeft = inRoot - inStart;
        root->left = build(inorder, postorder, inStart, inRoot-1, postStart, postStart+numsLeft-1, idx_map);
        root->right = build(inorder, postorder, inRoot+1, inEnd, postStart+numsLeft, postEnd-1, idx_map);
        return root;
    }

    // Vertical Order Traversal
    vector<vector<int>> verticalOrder(){
        map<int, vector<int>> m;
        queue<pair<TreeNode*, int>> q;
        vector<vector<int>> res;
        if(!root) return res;
        q.push({root, 0});
        while(!q.empty()){
            auto p = q.front(); q.pop();
            TreeNode* node = p.first;
            int hd = p.second;
            m[hd].push_back(node->val);
            if(node->left) q.push({node->left, hd-1});
            if(node->right) q.push({node->right, hd+1});
        }
        for(auto it : m){
            res.push_back(it.second);
        }
        return res;
    }

    // Merge two trees
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2){
        if(!t1) return t2;
        if(!t2) return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
    // Find minimum
    int findMin(){
        TreeNode* node = root;
        while(node->left) node = node->left;
        return node->val;
    }

    // Find maximum
    int findMax(){
        TreeNode* node = root;
        while(node->right) node = node->right;
        return node->val;
    }
};

void printTree(TreeNode* root) {
    if (!root) {
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();

            cout << node->val << " ";

            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }

        cout << endl;
    }
}


int main() {
    BinaryTree bt;
    TreeNode* t1 = new TreeNode(5);
    t1->left = new TreeNode(6);
    t1->right = new TreeNode(9);

    TreeNode* t2 = new TreeNode(1);
    t2->left = new TreeNode(2);
    t2->right = new TreeNode(3);
    //BinarySearchTree bst;
    int choice, val;
    cout << "\nBinary Tree Operations:\n"
    <<"1. Insert\n"
    << "2. Delete\n"
    << "3. Search\n"
    << "4. Pre-order Traversal\n"
    << "5. In-order Traversal\n"
    << "6. Post-order Traversal\n"
    << "7. Level-order Traversal\n"
    << "8. Calculate Height\n"
    << "9. Check if Balanced\n"
    << "10. Calculate Diameter\n"
    << "11. Lowest Common Ancestor\n"
    << "12. Maximum Path Sum\n"
    << "13. Reconstruct Tree from Inorder and Postorder\n"
    << "14. Vertical Order Traversal\n"
    << "17. 2 Tree Merging\n"
    << "\nBinary Search Tree Operations:\n"
    << "15. Find Minimum\n"
    << "16. Find Maximum\n";
    while (true) {
        cout << "Choose an operation: ";
        cin>>choice;
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                bt.insert(val);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                bt.deleteNode(bt.root, val);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                if (bt.search(val)) {
                    cout << "Value found.\n";
                } else {
                    cout << "Value not found.\n";
                }
                break;
            case 4: {
                vector<int> preorder;
                bt.preorder(bt.root, preorder);
                cout << "Pre-order traversal: ";
                for (int val : preorder) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 5: {
                vector<int> inorder;
                bt.inorder(bt.root, inorder);
                cout << "In-order traversal: ";
                for (int val : inorder) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 6: {
                vector<int> postorder;
                bt.postorder(bt.root, postorder);
                cout << "Post-order traversal: ";
                for (int val : postorder) {
                    cout << val << " ";
                }
                cout << endl;
                break;
            }
            case 7: {
                vector<vector<int>> levelOrder = bt.levelOrder();
                cout << "Level-order traversal:\n";
                for (const vector<int>& level : levelOrder) {
                    for (int val : level) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 8:
                cout << "Height of the tree: " << bt.height(bt.root) << endl;
                break;
            case 9:
                if (bt.isBalanced(bt.root)) {
                    cout << "The tree is balanced.\n";
                } else {
                    cout << "The tree is not balanced.\n";
                }
                break;
            case 10: {
                int diameter = 0;
                bt.diameter(bt.root, diameter);
                cout << "Diameter of the tree: " << diameter << endl;
                break;
            }
            case 11: {
                int n1, n2;
                cout << "Enter two node values: ";
                cin >> n1 >> n2;
                TreeNode* lca = bt.LCA(bt.root, n1, n2);
                if (lca) {
                    cout << "Lowest common ancestor: " << lca->val << endl;
                } else {
                    cout << "Nodes not found in the tree.\n";
                }
                break;
            }
            case 12:
                cout << "Maximum path sum: " << bt.maxPathSum() << endl;
                break;
            case 13: {
                vector<int> inorder = { 4, 2, 5, 1, 6, 3, 7 };
                vector<int> postorder = { 4, 5, 2, 6, 7, 3, 1 };
                cout<<"Inorder array: 4, 2, 5, 1, 6, 3, 7"<<endl
                <<"Postorder array: 4, 5, 2, 6, 7, 3, 1"<<endl;
                TreeNode* reconstructed = bt.buildTree(inorder, postorder);
                cout<<"Reconstructed;"<<endl;
                printTree(reconstructed);
                break;
            }
            case 14: {
                vector<vector<int>> verticalOrder = bt.verticalOrder();
                cout << "Vertical order traversal:\n";
                for (const vector<int>& level : verticalOrder) {
                    for (int val : level) {
                        cout << val << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 15:
                cout << "Minimum value in BST: " << bt.findMin() << endl;
                break;
            case 16:
                cout << "Maximum value in BST: " << bt.findMax() << endl;
                break;
            case 17:
                cout<<"Tree 1:"<<endl; printTree(t1);
                cout<<"Tree 2:"<<endl; printTree(t2);
                cout<<"Merged tree:"<<endl;
                bt.mergeTrees(t1,t2);
                printTree(t1);
                break;
            default:
                cout << "Invalid choice.\n";
                return 0;
        }
    }
    return 0;
}
