#ifndef OTX_H
#define OTX_H

#include <iostream>
#include "odx/pugixml/pugixml.h"
#include <QObject>
#include <QVector>

using namespace std;
struct sequenceData
{
    char data[1024];
    char type[20];
};
struct diagnsoticCommand
{
    struct sequenceData m_seq;
    struct diagnsoticCommand* nextcommand;
    struct diagnsoticCommand* conditionalCommand;
    char xsi_type[128];
};

//struct OTX_Data
//{
//    QVector<diagnsoticCommand> command;
//};
class OTX
{
public:
    OTX();

    void load(const QString fileName);

    void readActionNode(pugi::xml_node action);

    void readLoopNode(pugi::xml_node loop);

    void readBranchNode(pugi::xml_node branch);

    struct diagnsoticCommand* readSubActionNode(pugi::xml_node action,struct diagnsoticCommand* subotxData);

    struct diagnsoticCommand* readSubBranchNode(pugi::xml_node branch,struct diagnsoticCommand* subflow);

    struct diagnsoticCommand* initList();

    struct diagnsoticCommand* insertAtBeginning(struct diagnsoticCommand* head,QString data,QString type);

    struct diagnsoticCommand* insertAtEnd(struct diagnsoticCommand* head, QString data,QString type,QString xsiType);

    struct diagnsoticCommand* insertAtEndcondition(struct diagnsoticCommand* head,struct diagnsoticCommand* node);

    struct diagnsoticCommand* insertAtPosition(struct diagnsoticCommand* head, QString data,QString type);

    struct diagnsoticCommand* searchNode(struct diagnsoticCommand* head,QString data,QString type);

    struct diagnsoticCommand* deleteAtBeginning(struct diagnsoticCommand* head);

    struct diagnsoticCommand* deleteNode(struct diagnsoticCommand* head,QString data,QString type);

    struct diagnsoticCommand* deleteAtEnd(struct diagnsoticCommand* head);

    void freeList(struct diagnsoticCommand* head);

    struct diagnsoticCommand *getSequenceData();

    QStringList commandData;

   // OTX_Data otxdata;
private:

    struct diagnsoticCommand *m_otxSequence;

};

#endif // OTX_H
