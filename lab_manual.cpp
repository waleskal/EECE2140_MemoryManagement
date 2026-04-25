#include <iostream>
#include <string>

using namespace std;

struct ListNode {
    int id;
    string name;
    ListNode* next;
};

class NodeList {
private:
    ListNode* head;
public:
    NodeList() : head(nullptr) {}

    void addNode(int id, string name) {
        ListNode* newNode = new ListNode;
        newNode->id = id;
        newNode->name = name;
        newNode->next = head;
        head = newNode;
    }

     ~NodeList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void display() {
        ListNode* temp = head;
        while (temp) {
            cout << "[" << temp->id << ": " << temp->name << "] -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    NodeList list;
    list.addNode(1, "Router-A");
    list.addNode(2, "Router-B");
    list.display();
    return 0;
}
