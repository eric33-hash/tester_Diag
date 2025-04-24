#include "node.h"


void LinkedList::append(QString filename,uint32_t fileStart,uint32_t fileEnd,uint32_t fileSize)
{
    Node* newNode = new Node(filename,fileStart,fileEnd,fileSize);
    if (!head) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void LinkedList::deleteHead() {
    if (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
