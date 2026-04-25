#include <iostream>
#include <string>
#include <memory> // Needed for unique_ptr

using namespace std;

struct SmartListNode {
    int id;
    string name;
    unique_ptr<SmartListNode> next;
};

class SmartNodeList {
private:
    unique_ptr<SmartListNode> head;
public:
    SmartNodeList() : head(nullptr) {}

    void addNode(int id, string name) {
        auto newNode = make_unique<SmartListNode>();
        newNode->id = id;
        newNode->name = name;

	newNode->next = move(head);

        head = move(newNode);
    }

    void display() {
        SmartListNode* temp = head.get();
        while (temp) {
            cout << "[" << temp->id << ": " << temp->name << "] -> ";
            temp = temp->next.get();
        }
        cout << "NULL" << endl;
    }
};

int main() {
    SmartNodeList list;
    list.addNode(1, "Router-A");
    list.addNode(2, "Router-B");
    list.display();
    return 0;
}
