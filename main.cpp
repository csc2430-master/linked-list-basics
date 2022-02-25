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
void Print(Node* head);

int main() {
    Node *head = nullptr;
    char command;

    do {
        string line;
        stringstream ss;
        int item;

        cout << "Enter P(repend) number, D(isplay), or E(xit)";
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
