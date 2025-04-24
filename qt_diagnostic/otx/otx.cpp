#include "otx.h"
#include <QDebug>
OTX::OTX()
{
    m_otxSequence = initList();
}
struct diagnsoticCommand * OTX::getSequenceData()
{
    return m_otxSequence;
}

void OTX::load(const QString fileName)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(fileName.toLatin1().data());

    if (!result) {
       std::cout << "LoadIndex load content failed!" << std::endl;

    }

    // Access the root node: FLASH
    pugi::xml_node root = doc.child("otx");

    if (!root.empty()) {
                // 输出OTX文件的一些基本信息
                for (pugi::xml_node rootData = root.first_child(); rootData; rootData = rootData.next_sibling()) {
                    if(strcmp(rootData.name(),"metaData") == 0)
                    {
                        for (pugi::xml_node metadata = rootData.first_child(); metadata; metadata = metadata.next_sibling())
                        {
                            if(strcmp(metadata.name(),"data") == 0)
                            {
                                if(strcmp(metadata.first_attribute().value(),"EditorVersion") == 0)
                                {
                                    qDebug() << "Editor Information:" << metadata.child_value();
                                }
                                else if(strcmp(metadata.first_attribute().value(),"attributes") == 0)
                                {
                                    qDebug() << "otx information";
                                    //ECU and otx information;
                                }
                            }
                        }

                    }
                    else if(strcmp(rootData.name(),"procedures") == 0)
                    {
                        for(pugi::xml_node procedureData = rootData.first_child(); procedureData; procedureData = procedureData.next_sibling())
                        {
                            if(strcmp(procedureData.attribute("name").value(),"main") == 0)
                            {
                                for(pugi::xml_node procedure = procedureData.first_child(); procedure; procedure = procedure.next_sibling())
                                {
                                    if(strcmp(procedure.name(),"realisation") == 0)
                                    {
                                        qDebug() << "dataflow:";
                                        pugi::xml_node flow = procedure.child("flow");
                                        for(pugi::xml_node flowID = flow.first_child();flowID;flowID = flowID.next_sibling())
                                        {
                                            if(QString(flowID.name()).contains("action"))
                                            {
                                                readActionNode(flowID);
                                            }
                                            if(QString(flowID.name()).contains("branch"))
                                            {
                                                readBranchNode(flowID);
                                            }
                                            if(QString(flowID.name()).contains("loop"))
                                            {
                                                readLoopNode(flowID);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            } else {
                std::cerr << "Error: Root element not found." << std::endl;
            }
}

void OTX::readActionNode(pugi::xml_node action)
{
    pugi::xml_node realisation = action.child("realisation");
    QString xsiType = realisation.attribute("xsi:type").value();
    if(strcmp(realisation.attribute("xsi:type").value(),"diag:ExecuteDiagService") == 0)
    {
        pugi::xml_node diagnode = realisation.child("diag:diagService");
        if(strcmp(diagnode.attribute("xsi:type").value(),"diag:CreateDiagServiceByName") == 0)
        {
            pugi::xml_node diag = diagnode.child("diag:name");

            QString data = diag.attribute("value").value();
            QString type = "action";
            pugi::xml_node diagrequestsnode = realisation.child("diag:requestParameters");
            if(diagrequestsnode != NULL)
            {
                qDebug() << "RequestParameters";
                for(pugi::xml_node diagrequestnode = diagrequestsnode.first_child();diagrequestnode;diagrequestnode = diagrequestnode.next_sibling())
                {
                    data += ":";
                    data += diagrequestnode.child("diag:value").first_attribute().value();
                    qDebug() << "-------------------" << diagrequestnode.child("diag:value").first_attribute().value();
                }
            }
            m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);
            commandData.append(data);

        }

        pugi::xml_node diagresponsessnode = realisation.child("diag:responseParameters");
        if(diagresponsessnode != NULL)
        {
            qDebug() << "ResponseParameters";
            for(pugi::xml_node diagresponsenode = diagresponsessnode.first_child();diagresponsenode;diagresponsenode = diagresponsenode.next_sibling())
            {
                if(strcmp(diagresponsenode.name(),"diag:responseParam") == 0)
                {
                     qDebug() << "-------------------" << diagresponsenode.child("diag:target").first_attribute().value();
                }
            }
        }

    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"ns:Assignment") == 0)
    {
        QString assignmentnode = realisation.child("result").attribute("name").value();
        if(!QString(realisation.child("term").attribute("value").value()).isEmpty())
        {
            assignmentnode += " = ";
            assignmentnode += realisation.child("term").attribute("value").value();
        }
        QString data = assignmentnode;
        QString type = "action";
        m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);

    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"hmi:ChoiceDialog") == 0)
    {
        QString assignmentnode = realisation.child("hmi:title").attribute("value").value();
        assignmentnode += realisation.child("hmi:message").attribute("value").value();

        QString data = assignmentnode;
        QString type = "action";
        m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);

    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"hmi:ConfirmDialog") == 0)
    {
        QString assignmentnode = realisation.child("hmi:title").attribute("value").value();
        for(pugi::xml_node valueNode = realisation.child("hmi:message").first_child();valueNode;valueNode = valueNode.next_sibling())
        {
            assignmentnode += valueNode.attribute("value").value();
        }
        //assignmentnode += realisation.child("hmi:message").attribute("value").value();
        QString data = assignmentnode;
        QString type = "action";
        m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);
    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"hmi:InputDialog") == 0)
    {
        QString assignmentnode = realisation.child("hmi:title").attribute("value").value();
        assignmentnode += "-";
        assignmentnode += realisation.child("hmi:message").attribute("value").value();
        assignmentnode += "-";
        assignmentnode += realisation.child("hmi:instruction").attribute("value").value();
        assignmentnode += "-";
        assignmentnode += realisation.child("hmi:initialValue").attribute("valueOf").value();
        QString data = assignmentnode;
        QString type = "action";
        m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);
    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"event:WaitForEvent") == 0)
    {
        QString assignmentnode = realisation.child("event:source").child("event:timeout").attribute("value").value();

        QString data = assignmentnode;
        QString type = "action";
        m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);
        commandData.append(data);
    }
}

struct diagnsoticCommand* OTX::readSubActionNode(pugi::xml_node action,struct diagnsoticCommand* subflow)
{
    pugi::xml_node realisation = action.child("realisation");
    QString xsiType = realisation.attribute("xsi:type").value();
    if(strcmp(realisation.attribute("xsi:type").value(),"diag:ExecuteDiagService") == 0)
    {
        pugi::xml_node diagnode = realisation.child("diag:diagService");
        if(strcmp(diagnode.attribute("xsi:type").value(),"diag:CreateDiagServiceByName") == 0)
        {
            pugi::xml_node diag = diagnode.child("diag:name");

            QString data = diag.attribute("value").value();
            QString type = "action";
            subflow = insertAtEnd(subflow,data,type,xsiType);
            commandData.append(data);
        }
        pugi::xml_node diagrequestsnode = realisation.child("diag:requestParameters");
        if(diagrequestsnode != NULL)
        {
            qDebug() << "RequestParameters";
            for(pugi::xml_node diagrequestnode = diagrequestsnode.first_child();diagrequestnode;diagrequestnode = diagrequestnode.next_sibling())
            {
                qDebug() << "-------------------" << diagrequestnode.child("diag:value").first_attribute().value();
            }
        }
        pugi::xml_node diagresponsessnode = realisation.child("diag:responseParameters");
        if(diagresponsessnode != NULL)
        {
            qDebug() << "ResponseParameters";
            for(pugi::xml_node diagresponsenode = diagresponsessnode.first_child();diagresponsenode;diagresponsenode = diagresponsenode.next_sibling())
            {
                if(strcmp(diagresponsenode.name(),"diag:responseParam") == 0)
                {
                     qDebug() << "-------------------" << diagresponsenode.child("diag:target").first_attribute().value();
                }
            }
        }

    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"ns:Assignment") == 0)
    {
        QString assignmentnode = realisation.child("result").attribute("name").value();
        QString data = assignmentnode;
        QString type = "action";
        subflow = insertAtEnd(subflow,data,type,xsiType);
    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"hmi:ChoiceDialog") == 0)
    {
        QString assignmentnode = realisation.child("hmi:title").attribute("value").value();
        assignmentnode += realisation.child("hmi:message").attribute("value").value();
        QString data = assignmentnode;
        QString type = "action";
        subflow = insertAtEnd(subflow,data,type,xsiType);
    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"hmi:ConfirmDialog") == 0)
    {
        QString assignmentnode = realisation.child("hmi:title").attribute("value").value();
        assignmentnode += realisation.child("hmi:message").attribute("value").value();

        QString data = assignmentnode;
        QString type = "action";
        subflow = insertAtEnd(subflow,data,type,xsiType);
    }
    else if(strcmp(realisation.attribute("xsi:type").value(),"diag:CloseComChannel") == 0)
    {
        QString assignmentnode;
        for(pugi::xml_node data = realisation.first_child();data;data = data.next_sibling())
        {
            assignmentnode += data.name();
            assignmentnode += data.first_attribute().value();
        }


        QString data = assignmentnode;
        QString type = "action";
        subflow = insertAtEnd(subflow,data,type,xsiType);
    }
    return subflow;
}

struct diagnsoticCommand* OTX::readSubBranchNode(pugi::xml_node branch,struct diagnsoticCommand* subflow)
{
    pugi::xml_node ifNode = branch.child("realisation").child("if");

    pugi::xml_node termNode = ifNode.child("condition").child("realisation");
    QString xsiType = termNode.attribute("xsi:type").value();
    QString equal;
    for(pugi::xml_node node = termNode.first_child();node;node = node.next_sibling())
    {
        if(strcmp(node.first_attribute().name(),"valueOf") == 0)
        {
            equal += node.first_attribute().value();
            equal += "==";
        }
        else if(strcmp(node.first_attribute().name(),"value") == 0)
        {
            equal += node.first_attribute().value();
        }
    }
    QString data = equal;
    QString type = "branch";

    subflow = insertAtEnd(subflow,data,type,xsiType);

    pugi::xml_node trueNode = ifNode.child("flow");
    struct diagnsoticCommand* subFlowIDTrue = initList();
    for(pugi::xml_node flowID = trueNode.first_child();flowID;flowID = flowID.next_sibling())
    {
        if(QString(flowID.name()).contains("action"))
        {
            subFlowIDTrue = readSubActionNode(flowID,subFlowIDTrue);
        }
    }

    struct diagnsoticCommand* current = subflow;
    while (current->nextcommand) {
        current = current->nextcommand;
    }

    current->nextcommand = subFlowIDTrue;

    int i = 0;
    for(pugi::xml_node data = branch.child("realisation").first_child();data;data = data.next_sibling())
    {
        if(QString(data.name()).contains("elseif"))
        {
            struct diagnsoticCommand* subFlowID = initList();
            pugi::xml_node termNode = data.child("condition").child("realisation");
            QString equal;
            for(pugi::xml_node node = termNode.first_child();node;node = node.next_sibling())
            {
                if(strcmp(node.first_attribute().name(),"valueOf") == 0)
                {
                    equal += node.first_attribute().value();
                    equal += "==";
                }
                else if(strcmp(node.first_attribute().name(),"value") == 0)
                {
                    equal += node.first_attribute().value();
                }
            }
            QString dataname = equal;
            QString type = "branch";
            subFlowID = insertAtEnd(subFlowID,dataname,type,xsiType);
            for(pugi::xml_node flowID = data.child("flow").first_child();flowID;flowID = flowID.next_sibling())
            {
                if(QString(flowID.name()).contains("action"))
                {
                    subFlowID = readSubActionNode(flowID,subFlowID);
                }
                if(QString(flowID.name()).contains("return"))
                {

                }
                if(QString(flowID.name()).contains("branch"))
                {
                    pugi::xml_node lastnode = flowID.child("realisation").child("if");
                    struct diagnsoticCommand* subFlowlast = initList();
                    pugi::xml_node termNodelast = lastnode.child("condition").child("realisation");
                    QString equal;
                    for(pugi::xml_node nodelast = termNodelast.first_child();nodelast;nodelast = nodelast.next_sibling())
                    {
                        if(strcmp(nodelast.first_attribute().name(),"valueOf") == 0)
                        {
                            equal += nodelast.first_attribute().value();
                            equal += "==";
                        }
                        else if(strcmp(nodelast.first_attribute().name(),"value") == 0)
                        {
                            equal += nodelast.first_attribute().value();
                        }
                    }
                    QString dataname = equal;
                    QString type = "branch";
                    subFlowlast = insertAtEnd(subFlowlast,dataname,type,xsiType);

                    struct diagnsoticCommand* subFlowIDTrue = initList();
                    for(pugi::xml_node flowIDlast = lastnode.child("flow").first_child();flowIDlast;flowIDlast = flowIDlast.next_sibling())
                    {
                        if(QString(flowIDlast.name()).contains("action"))
                        {
                            subFlowIDTrue = readSubActionNode(flowIDlast,subFlowIDTrue);
                        }
                        if(QString(flowIDlast.name()).contains("return"))
                        {

                        }
                    }
                    struct diagnsoticCommand* currentlastlast = subFlowlast;
                    while (currentlastlast->nextcommand) {
                        currentlastlast = currentlastlast->nextcommand;
                    }

                    currentlastlast->nextcommand = subFlowIDTrue;

                    struct diagnsoticCommand* currentlast = subFlowID;
                    while (currentlast->nextcommand) {
                        currentlast = currentlast->nextcommand;
                    }

                    currentlast->nextcommand = subFlowlast;

                }
            }
            if(i == 0)
            {
                current->conditionalCommand = subFlowID;
            }
            else if(i == 1)
            {
                current->conditionalCommand->conditionalCommand = subFlowID;
            }
            //subflow = insertAtEndcondition(subflow,subFlowID);
            i++;
        }

    }

    return subflow;
}

void OTX::readBranchNode(pugi::xml_node branch)
{
    pugi::xml_node ifNode = branch.child("realisation").child("if");
    pugi::xml_node termNode = ifNode.child("condition").child("realisation");
    QString xsiType = termNode.attribute("xsi:type").value();
    QString equal;
    for(pugi::xml_node node = termNode.first_child();node;node = node.next_sibling())
    {
        if(strcmp(node.first_attribute().name(),"valueOf") == 0)
        {
            equal += node.first_attribute().value();
            equal += "==";
        }
        else if(strcmp(node.first_attribute().name(),"value") == 0)
        {
            equal += node.first_attribute().value();
        }
    }
    QString data = equal;
    QString type = "branch";

    m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);

    pugi::xml_node elseifNode = branch.child("realisation").child("elseif");
    pugi::xml_node flowNode = elseifNode.child("flow");

    struct diagnsoticCommand* subFlowID = initList();
    for(pugi::xml_node flowID = flowNode.first_child();flowID;flowID = flowID.next_sibling())
    {
        if(QString(flowID.name()).contains("action"))
        {
            subFlowID = readSubActionNode(flowID,subFlowID);
        }
        if(QString(flowID.name()).contains("return"))
        {

        }
    }

    m_otxSequence = insertAtEndcondition(m_otxSequence,subFlowID);
}

void OTX::readLoopNode(pugi::xml_node loop)
{
    pugi::xml_node realisation = loop.child("realisation");
    pugi::xml_node node = realisation.child("configuration");
    QString xsiType = realisation.attribute("xsi:type").value();
    QString equal;
    for(pugi::xml_node nodeConfig = node.first_child();nodeConfig;nodeConfig = nodeConfig.next_sibling())
   {
        if(strcmp(nodeConfig.first_attribute().name(),"isPostTested") == 0)
        {
            equal += nodeConfig.first_attribute().value();
            equal += "==";
            equal += nodeConfig.child("test").attribute("valueOf").value();
        }
        else if(strcmp(nodeConfig.first_attribute().name(),"valueOf") == 0)
        {
            equal += nodeConfig.first_attribute().value();
        }
    }
    QString data = equal;
    QString type = "loop";

    m_otxSequence = insertAtEnd(m_otxSequence,data,type,xsiType);

    pugi::xml_node flow = realisation.child("flow");

    struct diagnsoticCommand* subFlowID = initList();
    struct diagnsoticCommand* subFlowIDbranch = initList();
    for(pugi::xml_node flowID = flow.first_child();flowID;flowID = flowID.next_sibling())
    {
        if(QString(flowID.name()).contains("action"))
        {
            subFlowID = readSubActionNode(flowID,subFlowID);
        }
        if(QString(flowID.name()).contains("return"))
        {

        }
        if(QString(flowID.name()).contains("branch"))
        {
            subFlowID = readSubBranchNode(flowID,subFlowID);
        }
    }

    struct diagnsoticCommand* current = m_otxSequence;
    while (current->nextcommand) {
        current = current->nextcommand;
    }

   // current->nextcommand = subFlowID;
    m_otxSequence = insertAtEndcondition(m_otxSequence,subFlowID);
}

struct diagnsoticCommand* OTX::initList()
{

    //struct diagnsoticCommand * otxSequence = (struct diagnsoticCommand *)malloc(sizeof(struct diagnsoticCommand));
    return NULL;
}

struct diagnsoticCommand* OTX::insertAtBeginning(struct diagnsoticCommand* head, QString data,QString type) {
    struct diagnsoticCommand* newNode = (struct diagnsoticCommand*)malloc(sizeof(struct diagnsoticCommand));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

//    newNode->m_seq.data = data;
//    newNode->m_seq.type = type;
//    newNode->nextcommand = head;
//    newNode->conditionalCommand = head;
    return newNode;
}

struct diagnsoticCommand* OTX::insertAtEnd(struct diagnsoticCommand* head,QString data,QString type,QString xsiType) {
    struct diagnsoticCommand* newNode = (struct diagnsoticCommand*)malloc(sizeof(struct diagnsoticCommand));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->m_seq.data, data.toLatin1().data(), sizeof(newNode->m_seq.data));
    strncpy(newNode->m_seq.type, type.toLatin1().data(), sizeof(newNode->m_seq.type));
    strncpy(newNode->xsi_type, xsiType.toLatin1().data(), sizeof(newNode->xsi_type));
    newNode->nextcommand = NULL;
    newNode->conditionalCommand = NULL;

    if (!head) {
        return newNode;
    }

    struct diagnsoticCommand* current = head;
    while (current->nextcommand) {
        current = current->nextcommand;
    }

    current->nextcommand = newNode;
    return head;
}

struct diagnsoticCommand* OTX::insertAtEndcondition(struct diagnsoticCommand* head,struct diagnsoticCommand* node)
{
    struct diagnsoticCommand* current = head;
    while (current->nextcommand) {
        current = current->nextcommand;
    }
    current->conditionalCommand = node;
    return head;
}

struct diagnsoticCommand* OTX::insertAtPosition(struct diagnsoticCommand* head, QString data,QString type) {
    struct diagnsoticCommand* newNode = (struct diagnsoticCommand*)malloc(sizeof(struct diagnsoticCommand));
        if (!newNode) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

//        newNode->m_seq.data = data;
//        newNode->m_seq.type = type;
//        newNode->nextcommand = NULL;

        // 如果链表为空，将新节点作为头节点
        if (!head) {
            return newNode;
        }

        // 如果新节点值小于头节点值，插入为新头节点
        if (data == head->m_seq.data) {
            newNode->nextcommand = head;
            return newNode;
        }

        // 遍历链表找到插入位置
        struct diagnsoticCommand* current = head;
        struct diagnsoticCommand* prev = NULL;
        while (current && (data == current->m_seq.data)) {
            prev = current;
            current = current->nextcommand;
        }

        // 插入新节点
        prev->nextcommand = newNode;
        newNode->nextcommand = current;
        return head;
}

struct diagnsoticCommand* OTX::searchNode(struct diagnsoticCommand* head, QString data,QString type) {
    struct diagnsoticCommand* current = head;
    while (current) {
        if (current->m_seq.data == data) {
            return current;
        }
        current = current->nextcommand;
    }
    return NULL;
}

struct diagnsoticCommand* OTX::deleteAtBeginning(struct diagnsoticCommand* head) {
    if (!head) {
        printf("List is empty.\n");
        return NULL;
    }

    struct diagnsoticCommand* newHead = head->nextcommand;
    free(head);
    return newHead;
}

struct diagnsoticCommand* OTX::deleteAtEnd(struct diagnsoticCommand* head) {
    if (!head) {
        printf("List is empty.\n");
        return NULL;
    }

    if (!head->nextcommand) {
        free(head);
        return NULL;
    }

    struct diagnsoticCommand* current = head;
    struct diagnsoticCommand* prev = NULL;

    while (current->nextcommand) {
        prev = current;
        current = current->nextcommand;
    }

    prev->nextcommand = NULL;
    free(current);
    return head;
}

struct diagnsoticCommand* OTX::deleteNode(struct diagnsoticCommand* head, QString data,QString type) {
    // 如果链表为空，无需删除
    if (!head) {
        printf("List is empty.\n");
        return NULL;
    }

    struct diagnsoticCommand* current = head;
    struct diagnsoticCommand* prev = NULL;

    // 查找要删除的节点
    while (current && current->m_seq.data != data) {
        prev = current;
        current = current->nextcommand;
    }

    // 如果未找到要删除的节点
    if (!current) {
        //printf("Node with value %d not found.\n", value);
        return head;
    }

    // 如果要删除的是头节点
    if (prev == NULL) {
        struct diagnsoticCommand* newHead = current->nextcommand;
        free(current);
        return newHead;
    }

    // 删除中间或尾部节点
    prev->nextcommand = current->nextcommand;
    free(current);
    return head;
}

void OTX::freeList(struct diagnsoticCommand* head) {
    struct diagnsoticCommand* current = head;
    while (current) {
        struct diagnsoticCommand* next = current->nextcommand;
        free(current);
        current = next;
    }
}
