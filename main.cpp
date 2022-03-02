/**
 * Title:   Linked List Example
 *
 * Purpose: Illustrate code covered in class on Feb 25 and Feb 28
 * Class:   CSC 2430 Winter 2022
 * Author:  Max Benson
 * Date:    2022-02-25
 */

 #include <iostream>
#include <sstream>
#include <string>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::stringstream;
using std::string;

class Node {
public:
    int   item;
    Node* next;
};

void Prepend(int item, Node** ptrToHead);
bool InsertAfter(int itemToInsert, int afterItem, Node* head);
bool RemoveItem(int item, Node** ptrToHead);
void Print(Node* head);
bool RemoveNotInHead(int item, Node* head);
Node* FindItem(int item, Node* head);
Node* FindItemBefore(int item, Node* head);

int main() {
    Node *head = nullptr;
    char command;

    do {
        string line;
        stringstream ss;
        int item;
        int after;

        cout << "Enter P(repend) number, I(nsert) number after, R(emove) number, D(isplay), or E(xit)";
        getline(cin, line);
        ss.str(line);
        ss >> command;
        switch (command) {
            case 'P':
                ss >> item;
                if (ss.fail()) {
                    cerr << "You need to enter a number after 'P'" <<endl;
                }
                else {
                    Prepend( item, &head );
                }
                break;
            case 'I':
                ss >> item;
                ss >> after;
                if (ss.fail()) {
                    cerr << "You need to enter two numbers after 'I'" <<endl;
                }
                else {
                    if (!InsertAfter(item, after, head)) {
                        cerr << after << " does not appear in the list" << endl;
                    }
                }
                break;
            case 'R':
                ss >> item;
                if (ss.fail()) {
                    cerr << "You need to enter a number after 'R'" <<endl;
                }
                else {
                    if (!RemoveItem( item, &head )) {
                        cerr << item << " does not appear in the list" << endl;
                    }
                }
                break;
            case 'D':
                Print( head );
                break;
            case 'E':
                break;
            default:
                cerr << "Unrecognized command '" << command << "'" << endl;
                break;
        }
    } while (command != 'E' && !cin.eof());
    return 0;
}

void Prepend(int item, Node** ptrToHead) {
    Node* newHead;

    newHead = new Node;
    newHead->item = item;
    newHead->next = *ptrToHead;
    *ptrToHead = newHead;
}

bool InsertAfter(int itemToInsert, int afterItem, Node* head) {
    Node* ptr = FindItem(afterItem, head);

    if (ptr != nullptr) {
        Node* newNode = new Node;
        newNode->item = itemToInsert;
        newNode->next = ptr->next;
        ptr->next = newNode;
        return true;
    }
    return false;
}

bool RemoveItem(int item, Node** ptrToHead) {
    Node* head = *ptrToHead;

    if (nullptr == head) {
        return false;
    }
    else if (head->item == item) {
        Node* nodeToDelete = head;	// Save pointer to node to be deleted
        *ptrToHead = head->next;	// Update pointer to head
        delete nodeToDelete;		// Deallocate the old head node
        return true;
    }
    else {
        return RemoveNotInHead(item, head);
    }
}

void Print(Node* head) {
    cout << "[";
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        if (ptr != head) {
            cout << ", ";
        }
        cout << ptr->item;
    }
    cout << "]" << endl;
}

bool RemoveNotInHead(int item, Node* head) {
    Node* nodeToDelete;
    Node* nodeBefore = FindItemBefore(item, head);

    if (nullptr == nodeBefore) {
        return false;
    }
    nodeToDelete = nodeBefore->next;
    nodeBefore->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}

Node* FindItem(int item, Node* head) {
    // Starting at "head" search the linked list for a node containing item
    // If found, return a pointer to the node, otherwise return nullptr
    for (Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        if (ptr->item == item) {
            return ptr;
        }
    }
    return nullptr;
}

Node* FindItemBefore(int item, Node* head) {
    // Starting at "head" search the linked list for a node    // containing item.  If found return a pointer to the node before
    // before, otherwise return nullptr
    if (head != nullptr) {
        for (Node* ptr = head; ptr->next != nullptr; ptr = ptr->next) {
            if (ptr->next->item == item) {
                return ptr;
            }
        }
    }
    return nullptr;
}