#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <iostream>
class Node : public QObject
{
    Q_OBJECT
public:

    QString mfilename;
    uint32_t mfileStart;
    uint32_t mfileEnd;
    uint32_t mfileSize;

    Node* next;

    Node(QString filename,uint32_t fileStart,uint32_t fileEnd,uint32_t fileSize) :
        mfilename(filename),mfileStart(fileStart),mfileEnd(fileEnd),mfileSize(fileSize), next(nullptr) {}

signals:

};

class LinkedList : public QObject
{
    Q_OBJECT
public:
    Node* head;      // 链表的头指针

public:
    // 构造函数
    LinkedList() : head(nullptr) {}

    // 析构函数
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 在链表末尾插入节点
    void append(QString filename,uint32_t fileStart,uint32_t fileEnd,uint32_t fileSize) ;

    // 删除头结点
    void deleteHead();

//    // 打印链表
//    void printList() const {
//        Node* current = head;
//        while (current) {
//            std::cout << current->value << " ";
//            current = current->next;
//        }
//        std::cout << std::endl;
//    }
};


#endif // NODE_H
