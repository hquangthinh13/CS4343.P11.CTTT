//MSSV: 22521407
//Full name: Huỳnh Quang Thịnh
//Session 05 - Homework 07
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct EmployeeNode {
    string name;
    vector<EmployeeNode*> subordinates;

    EmployeeNode(const string& name) : name(name) {}
};

class OrganizationalChart {
private:
    EmployeeNode* root;

    // Helper function to find an employee node by name
    EmployeeNode* findEmployee(EmployeeNode* node, const string& name) {
        if (!node) return nullptr;
        if (node->name == name) return node;
        for (EmployeeNode* subordinate : node->subordinates) {
            EmployeeNode* found = findEmployee(subordinate, name);
            if (found) return found;
        }
        return nullptr;
    }

    // Helper function to print the hierarchy
    void printHierarchy(EmployeeNode* node, int depth) {
        if (!node) return;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->name << endl;
        for (EmployeeNode* subordinate : node->subordinates) {
            printHierarchy(subordinate, depth + 1);
        }
    }

public:
    OrganizationalChart(const string& ceoName) {
        root = new EmployeeNode(ceoName);
    }

    // Add an employee under a manager
    void addEmployee(const string& managerName, const string& employeeName) {
        EmployeeNode* manager = findEmployee(root, managerName);
        if (manager) {
            manager->subordinates.push_back(new EmployeeNode(employeeName));
        } else {
            cout << "Manager not found: " << managerName << endl;
        }
    }

    // Remove an employee
    void removeEmployee(const string& employeeName) {
        if (root->name == employeeName) {
            cout << "Cannot remove the CEO." << endl;
            return;
        }
        removeEmployeeRec(root, employeeName);
    }

    // Helper function to remove an employee recursively
    bool removeEmployeeRec(EmployeeNode* node, const string& employeeName) {
        if (!node) return false;
        for (auto it = node->subordinates.begin(); it != node->subordinates.end(); ++it) {
            if ((*it)->name == employeeName) {
                delete *it;
                node->subordinates.erase(it);
                return true;
            }
            if (removeEmployeeRec(*it, employeeName)) return true;
        }
        return false;
    }

    // Display the hierarchy
    void displayHierarchy() {
        printHierarchy(root, 0);
    }
};

int main() {
    OrganizationalChart orgChart("CEO");

    orgChart.addEmployee("CEO", "VP1");
    orgChart.addEmployee("CEO", "VP2");
    orgChart.addEmployee("VP1", "Manager1");
    orgChart.addEmployee("VP1", "Manager2");
    orgChart.addEmployee("VP2", "Manager3");
    orgChart.addEmployee("Manager1", "Employee1");
    orgChart.addEmployee("Manager1", "Employee2");

    cout << "Organizational Hierarchy:" << endl;
    orgChart.displayHierarchy();

    cout << "\nRemoving Manager1..." << endl;
    orgChart.removeEmployee("Manager1");

    cout << "Organizational Hierarchy after removal:" << endl;
    orgChart.displayHierarchy();

    return 0;
}
