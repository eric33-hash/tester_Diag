#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtoolbar.h>
#include <qmovie.h>
#include <QLine>
#define DISPLAY_OUTPUT(StringSeg)   \
{                                      \
    QDateTime currentTime = QDateTime::currentDateTime();  \
    QString outPutTime = "[" + currentTime.toString("yyyy-MM-dd hh:mm:ss") + "] ";  \
    ui->text_output_2->append(outPutTime + StringSeg);    \
}  \

MainWindow* MainWindow::m_pInstance = NULL;
MainWindow* MainWindow::GetInstance()
{
    if(m_pInstance == NULL)
        m_pInstance = new MainWindow(nullptr);
    return m_pInstance;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));
    ui->SendData_Line->installEventFilter(this);
    ui->SendData_mqtt->installEventFilter(this);
    ui->MsgData1->installEventFilter(this);
    ui->MsgData2->installEventFilter(this);
    ui->MsgData3->installEventFilter(this);
    ui->MsgData4->installEventFilter(this);
    ui->MsgData5->installEventFilter(this);
    ui->MsgData6->installEventFilter(this);
    ui->MsgData7->installEventFilter(this);
    ui->MsgData8->installEventFilter(this);
    ui->Message_ID->installEventFilter(this);
    ui->txt_PhyReq->installEventFilter(this);
    ui->txt_funReq->installEventFilter(this);
    ui->txt_phyRes->installEventFilter(this);
    setDateTime();
    ui->tabWidget->setTabText(0,"OTA");
    ui->tabWidget->setTabText(1,"ODX-Parse");
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels({"odx_d.attr_model_version"});
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->setHeaderHidden(true);
    isRuntime = 1;
    connect(this,&MainWindow::sendMessage,this,&MainWindow::recieveMsg,Qt::QueuedConnection);
    connect(this,&MainWindow::sendCount,this,&MainWindow::recieveCount);
    connect(this,&MainWindow::sendJson,this,&MainWindow::receiveJson);
    connect(this,&MainWindow::sendJsonotx,this,&MainWindow::receiveJsonotx);

    connect(ui->chart_rect,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Rect()));
    //connect(ui->chart_diam,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Diamond()));
    connect(ui->chart_roundrect,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_RoundRect()));
    connect(ui->chart_ellipse,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Ellipse()));
    connect(ui->chart_line,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_Line()));
    connect(ui->chart_trapezoid,SIGNAL(clicked()),ui->flowChart_widget,SLOT(setPaintChart_trapezoid()));
    getCANoeConfig();
    popMenu =new QMenu(this);

    QAction *actionDiag = popMenu->addAction("diag:ExecuteDiagService");
    QAction *actionAssign = popMenu->addAction("ns:Assignment");
    QAction *actionConfirmDialog = popMenu->addAction("hmi:ConfirmDialog");
    QAction *actionChoiceDialog = popMenu->addAction("hmi:ChoiceDialog");
    QAction *actionInputDialog = popMenu->addAction("hmi:InputDialog");
    QAction *actionwait = popMenu->addAction("event:WaitForEvent");
    connect(actionDiag ,&QAction::triggered ,this ,[=](){
        ui->flowChart_widget->setPaintChart_RectSelf("diag:ExecuteDiagService-");
    });
    connect(actionAssign ,&QAction::triggered ,this ,[=](){
        ui->flowChart_widget->setPaintChart_RectSelf("ns:Assignment-");
    });
    connect(actionConfirmDialog ,&QAction::triggered ,this ,[=](){
        Dialog *diag = new Dialog();
        diag->show();
        connect(diag,&Dialog::dialogclick,this,[=](QString hmi){
            ui->flowChart_widget->setPaintChart_RectSelf("hmi:ConfirmDialog-" + hmi);
        });
    });

    connect(actionChoiceDialog ,&QAction::triggered ,this ,[=](){
        ChoiceDialog *choicedialog = new ChoiceDialog();
        choicedialog->show();
        connect(choicedialog,&ChoiceDialog::dialogclick,this,[=](QString hmi){
            ui->flowChart_widget->setPaintChart_RectSelf("hmi:ChoiceDialog-" + hmi);
        });
    });

    connect(actionInputDialog ,&QAction::triggered ,this ,[=](){
        InputDialog *inputdialog = new InputDialog();
        inputdialog->show();
        connect(inputdialog,&InputDialog::dialogclick,this,[=](QString hmi){
            ui->flowChart_widget->setPaintChart_RectSelf("hmi:InputDialog-" + hmi);
        });
    });
    connect(actionwait ,&QAction::triggered ,this ,[=](){
            ui->flowChart_widget->setPaintChart_RectSelf("event:WaitForEvent-");
    });

    connect(ui->chart_diam,&QPushButton::clicked,this,[=](){
        conditionDialog *conditionaldialog = new conditionDialog();
        conditionaldialog->show();
        connect(conditionaldialog,&conditionDialog::dialogclick,this,[=](QString hmi){
            ui->flowChart_widget->setPaintChart_DiamondSelf(hmi);
        });
    });

    ui->flowChart_widget->setFixedSize(201800,65535);


    rowIndex = 0;
//    ui->tableWidget->setRowCount(6);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setColumnWidth(0,380);
    ui->tableWidget->setHorizontalHeaderLabels({"FileName","StartAddress","EndAddress","FileSize"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    maxProgress = 0;

    msg = new activeMsg();
    msgThread = new QThread(this);
    msg->moveToThread(msgThread);

    msg_channle = new activeMsg();
    msgThread_channle = new QThread(this);
    msg_channle->moveToThread(msgThread_channle);

    connect(this,&MainWindow::startsignal,msg,&activeMsg::thread);
    connect(this,&MainWindow::startsignal_c,msg_channle,&activeMsg::thread_channel);

    initMQTTUI();
//    connect(ui->Btn_File_parseotx,SIGNAL(triggered(bool)),ui->flowChart_widget,SLOT(openChartFile()));

    ui->txt_PhyReq->setText("716");
    ui->txt_phyRes->setText("71E");
    ui->comboBox_4->setCurrentIndex(1);

    initToolBar();

}

void MainWindow::setDateTime()
{
    ui->dateTime_StartTime->setDateTime(QDateTime::currentDateTime());
    ui->dateTime_EndTime->setDateTime(QDateTime::currentDateTime());
    ui->line_period->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
    if(obj == ui->SendData_Line)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->SendData_Line->grabKeyboard();
        }
    }
    else if(obj == ui->SendData_mqtt)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->SendData_mqtt->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData1)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData1->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData2)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData2->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData3)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData3->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData4)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData4->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData5)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData5->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData6)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData6->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData7)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData7->grabKeyboard();
        }
    }
    else if(obj == ui->MsgData8)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->MsgData8->grabKeyboard();
        }
    }
    else if(obj == ui->Message_ID)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->Message_ID->grabKeyboard();
        }
    }
    else if(obj == ui->txt_PhyReq)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->txt_PhyReq->grabKeyboard();
        }
    }
    else if(obj == ui->txt_funReq)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->txt_funReq->grabKeyboard();
        }
    }
    else if(obj == ui->txt_phyRes)
    {
        if(event->type() == QEvent::FocusIn)
        {
            ui->txt_phyRes->grabKeyboard();
        }
    }
    return QWidget::eventFilter(obj,event);
}

QString MainWindow::creatDir(QString dirName)
{
   QString filePath = QCoreApplication::applicationDirPath() + "/task/" + dirName;
   QDir dir(filePath);
   if(!dir.exists())
   {
       dir.mkdir(filePath);
   }
   return filePath;
}

void MainWindow::createTaskJson(QString jsonDir)
{
    QJsonObject json_TaskInfo;
    json_TaskInfo["name"] = ui->line_taskID->text();

    QJsonArray json_priority;
    json_priority.append("HMI");
    if(ui->tasktyperuntime->isChecked())
    {
        json_priority.append("Immediately");
    }
    else
    {
        json_priority.append("Normal");
    }
    json_TaskInfo["priority"] = json_priority;

    json_TaskInfo["strategy"] = "single";

    QJsonObject json_period;
    json_period["cycle"] = ui->line_period->text();
    json_period["startingTime"] = ui->dateTime_StartTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    json_period["endingTime"] = ui->dateTime_EndTime->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    json_TaskInfo["period"] = json_period;

    json_TaskInfo["documentation"] = "https://www.example.com/task1-documentation";


    QJsonDocument jsonDoc(json_TaskInfo);

    QFile *file = new QFile(jsonDir + "/task.json");
    QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    if(file->open(QIODevice::ReadWrite))
    {
        file->write(jsonString);
    }
    else
    {
        return;
    }
    file->close();
    delete file;
}

void MainWindow::createDataflowJson(QString jsonDir,QString filenName)
{
    QJsonObject json_dataSeq;
    json_dataSeq["flashFile"] = ui->line_FilePath->text();
    json_dataSeq["deviceType"] = "CAN";
    json_dataSeq["PhyRequestID"] = ui->lineEdit_3->text();
    json_dataSeq["ResponseID"] = ui->lineEdit_11->text();
    QJsonArray json_sequences;
    QFile filese(filenName);
    QByteArray jsonSeq;
    if(filese.open(QIODevice::ReadOnly))
    {
        jsonSeq = filese.readAll();
    }
    json_sequences = QJsonDocument::fromJson(jsonSeq).object()["sequences"].toArray();
    json_dataSeq["sequences"] = json_sequences;

    QJsonDocument jsonDoc(json_dataSeq);

    QFile *file = new QFile(jsonDir + "/dataflow.json");
    QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    if(file->open(QIODevice::ReadWrite))
    {
        file->write(jsonString);
    }
    else
    {
        return;
    }
    ui->text_json->setText(jsonString);
    file->close();
    delete file;

}

void MainWindow::on_pushButton_clicked()
{
    ui->text_json->setText("");
    QString s = QFileDialog::getOpenFileName(this,"选择诊断序列","./","All files(*.*)");
    QString jsonDir = creatDir(ui->line_taskID->text());
    createTaskJson(jsonDir);
    createDataflowJson(jsonDir,s);
}

void MainWindow::on_Btn_File_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"open flash file","/home","bin files(*.bin);;hex files(*.hex)");
    ui->line_FilePath->setText(s);
}

void MainWindow::recieveMsg(QString strMsg)
{
    ui->text_output->append(strMsg);
}

void MainWindow::recieveCount(int execount, int sucessCount)
{
    ui->line_period_2->setText(QString::number(execount));
    ui->line_period_3->setText(QString::number(sucessCount));
    ui->line_period_4->setText(QString::number(execount - sucessCount));
}

void MainWindow::receiveJson(QString strMsg)
{

     mSequences.append(strMsg);
     mDataSeq["sequences"] = mSequences;
     QJsonDocument jsonDoc(mDataSeq);
     QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Indented);
     ui->txt_diagscript->setText(jsonString);
}

void MainWindow::receiveJsonotx(QString strMsg)
{
     mSequences.append(strMsg);
     mDataSeq["sequences"] = mSequences;
     QJsonDocument jsonDoc(mDataSeq);
     QByteArray jsonString = jsonDoc.toJson(QJsonDocument::Indented);
     ui->txt_diagscript_otx->setText(jsonString);
}

void MainWindow::call_cpp_class_add(char *msg1,unsigned char *msg,uint8_t len)
{
    QString dataStr;
    QString sendData;
    int i = 0;
    while(i<len)
    {
        dataStr += QString("%1").arg(*msg,1,16,QLatin1Char('0'));
        dataStr.append(" ");
        msg++;
        i++;
    }
    sendData = QString(msg1) + dataStr;
    emit sendMessage(sendData);
        return;
}

void MainWindow::call_cpp_class_show(int execount, int sucessCount)
{
    emit sendCount(execount,sucessCount);
}

void MainWindow::InsertFirstNode(QString nodeName)
{
    QTreeWidgetItem* topItem = new QTreeWidgetItem(ui->treeWidget);
    topItem->setText(0,nodeName.split(".").at(3));
    QFont fnt = topItem->font(0);
    fnt.setBold(true);
    topItem->setFont(0,fnt);
}

void MainWindow::InsertWait()
{
    QTreeWidgetItem* topItem = new QTreeWidgetItem(ui->treeWidget);
    topItem->setText(0,"Wait");
    QFont fnt = topItem->font(0);
    fnt.setBold(true);
    topItem->setFont(0,fnt);
}

void MainWindow::receiveTreeNode(QString nodeName,QString subName,QString description)
{
    QTreeWidgetItem* var11 = new QTreeWidgetItem(ui->treeWidget->findItems(nodeName.split(".").at(3),Qt::MatchExactly|Qt::MatchRecursive, 0).at(0), 2);

    var11->setText(0,subName + "   (" +description +")" );
}

void MainWindow::on_Btn_File_5_clicked()
{
    QString s = QFileDialog::getOpenFileName(nullptr,"open flash file","/home","odx-d(*.odx-d)");
    ui->line_FilePath_3->setText(s);
}

void MainWindow::parseODX(QString fileName)
{
    LoadODX_D *odx = new LoadODX_D();

    ODX_D  odx_d;
    odx_d = odx->load(fileName);
    ecu = odx_d.child_diag_layer_container.child_ecu_variants.child_ecu_variant.at(0);
    int FunctClassSize = ecu.child_funclass.child_funclass.size();
    int ServiceSize = ecu.child_diag_comms.child_DIAGCOMM.size();
    int RequestSize = ecu.child_request.child_request.size();
    int FunctClassSizeIndex = 0;
    while (FunctClassSizeIndex < FunctClassSize) {
        QString FunctClassName = ecu.child_funclass.child_funclass.at(FunctClassSizeIndex).child_short_name;
        InsertFirstNode(FunctClassName);
        int ServiceSizeIndex = 0;
        while (ServiceSizeIndex < ServiceSize) {
            Service mService;
            QString ServiceREF = ecu.child_diag_comms.child_DIAGCOMM.at(ServiceSizeIndex).FUNCTCLASS_REF;
            QString ServiceName = ecu.child_diag_comms.child_DIAGCOMM.at(ServiceSizeIndex).child_short_name;
            mService.serviceName = ServiceName;
            mService.ECUID = ecu.child_short_name;
            mService.ServiceClass =  FunctClassName;
            QString RequestREF = ecu.child_diag_comms.child_DIAGCOMM.at(ServiceSizeIndex).REQUEST_REF;
            if(strcmp(FunctClassName.toLatin1().data(),ServiceREF.toLatin1().data()) == 0)
            {
                int RequestSizeIndex = 0;
                while(RequestSizeIndex < RequestSize)
                {
                    QString RequestName = ecu.child_request.child_request.at(RequestSizeIndex).attr_id;
                    QString ServiceID = QString("%1 ").arg(ecu.child_request.child_request.at(RequestSizeIndex).child_params.child_param.at(0).child_coded_value.data_value.toInt(nullptr,10),2,16,QLatin1Char('0')).toUpper();
                    if(strcmp(RequestName.toLatin1().data(),RequestREF.toLatin1().data()) == 0)
                    {
                        QString udsCommand = "";
                        QVector<PARAM> params = ecu.child_request.child_request.at(RequestSizeIndex).child_params.child_param;

                        udsCommand = ServiceID;
                        mService.serviceID = ServiceID;
                        foreach (PARAM param, params) {

                            if(strcmp(param.attr_semantic.toLatin1().data(),"SUBFUNCTION") == 0 || strcmp(param.attr_semantic.toLatin1().data(),"ACCESSMODE") == 0)
                            {
                                QString subServiceID = QString("%1 ").arg(param.child_coded_value.data_value.toInt(nullptr,10),2,16,QLatin1Char('0')).toUpper();
                                udsCommand += subServiceID;
                                mService.subService = subServiceID;
                            }
                            else if(strcmp(param.attr_semantic.toLatin1().data(),"ID") == 0 && strcmp(param.attr_xsi_type.toLatin1().data(),"TABLE-KEY") == 0)
                            {
                                foreach (TABLE table, ecu.child_diag_data_dictionary_spec.child_tables.child_table)
                                {
                                   if(param.child_table_row_ref.startsWith(table.attr_id.toLatin1().data(),Qt::CaseSensitive))
                                   {
                                        foreach (TABLE_ROW tablerow, table.child_table_row)
                                        {
                                            if(strcmp(param.child_table_row_ref.toLatin1().data(),tablerow.attr_id.toLatin1().data()) == 0)
                                            {
                                                QString Highbyte = QString("%1 ").arg(tablerow.child_key.toInt(nullptr,10),4,16,QLatin1Char('0')).mid(0,2).toUpper();
                                                QString Lowbyte = QString("%1 ").arg(tablerow.child_key.toInt(nullptr,10),4,16,QLatin1Char('0')).mid(2,4).toUpper();
                                                udsCommand += Highbyte +" " + Lowbyte;
                                                mService.subService = QString("%1 ").arg(tablerow.child_key.toInt(nullptr,10),4,16,QLatin1Char('0')).toUpper();
                                                if(!tablerow.child_structure_ref.isEmpty())
                                                {
                                                    foreach (STRUCTURE structure, ecu.child_diag_data_dictionary_spec.child_structures.child_structure) {
                                                        if(structure.attr_id == tablerow.child_structure_ref)
                                                        {
                                                            mService.serviceparams.attr_id = structure.attr_id;
                                                            foreach (PARAM param, structure.child_params.child_param) {
                                                                DOPPARAM dopparam;
                                                                dopparam.attr_semantic = param.attr_semantic;
                                                                dopparam.attr_xsi_type = param.attr_xsi_type;
                                                                dopparam.child_byte_position.data_value = param.child_byte_position.data_value;
                                                                dopparam.child_short_name = param.child_short_name;
                                                                bool iffind = false;
                                                                 foreach (STRUCTURE structureref, ecu.child_diag_data_dictionary_spec.child_structures.child_structure)
                                                                 {
                                                                     if(structureref.attr_id == param.child_dop_ref)
                                                                     {
                                                                         dopparam.child_byte_size = structureref.byte_size;
                                                                         iffind = true;
                                                                     }
                                                                 }
                                                                 if(!iffind)
                                                                 {
                                                                     foreach (DATA_OBJECT_PROP dopref, ecu.child_diag_data_dictionary_spec.child_data_object_props.child_data_object_prop) {
                                                                         if(dopref.attr_id == param.child_dop_ref){
                                                                             dopparam.child_byte_size = dopref.child_diag_coded_type.child_bit_length + "bits";
                                                                         }
                                                                     }
                                                                 }
                                                                mService.serviceparams.child_params.child_param.append(dopparam);
                                                            }
                                                            break;
                                                            //mService.serviceparams = structure.child_params;
                                                        }
                                                    }
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                            else if(strcmp(param.attr_semantic.toLatin1().data(),"ID") == 0 && strcmp(param.attr_xsi_type.toLatin1().data(),"CODED-CONST") == 0)
                            {
                                QString Highbyte = QString("%1 ").arg(param.child_coded_value.data_value.toInt(nullptr,10),param.child_diag_coded_type.child_bit_length.toInt(nullptr,10)/4,16,QLatin1Char('0')).mid(0,2).toUpper();
                                QString Lowbyte = QString("%1 ").arg(param.child_coded_value.data_value.toInt(nullptr,10),param.child_diag_coded_type.child_bit_length.toInt(nullptr,10)/4,16,QLatin1Char('0')).mid(2,4).toUpper();
                                udsCommand += Highbyte +" " + Lowbyte;
                                mService.subService = QString("%1 ").arg(param.child_coded_value.data_value.toInt(nullptr,10),param.child_diag_coded_type.child_bit_length.toInt(nullptr,10)/4,16,QLatin1Char('0')).toUpper();
                            }
                            else if(strcmp(param.attr_semantic.toLatin1().data(),"DATA") == 0 && strcmp(param.attr_xsi_type.toLatin1().data(),"VALUE") == 0)
                            {
                                DOPPARAM dopparam;
                                dopparam.attr_semantic = param.attr_semantic;
                                dopparam.attr_xsi_type = param.attr_xsi_type;
                                dopparam.child_byte_position.data_value = param.child_byte_position.data_value;
                                dopparam.child_short_name = param.child_short_name;
                                dopparam.data_type = param.child_dop_ref;
                                bool findFlag = false;
                                foreach (DATA_OBJECT_PROP dopref, ecu.child_diag_data_dictionary_spec.child_data_object_props.child_data_object_prop) {
                                    if(dopref.attr_id == param.child_dop_ref){
                                        dopparam.child_byte_size = dopref.child_diag_coded_type.child_bit_length + "bits";
                                        findFlag = true;
                                    }
                                }
                                if(!findFlag)
                                {
                                    foreach (STRUCTURE structure, ecu.child_diag_data_dictionary_spec.child_structures.child_structure) {
                                        if(structure.attr_id == param.child_dop_ref)
                                        {
                                            dopparam.child_byte_size = structure.byte_size;
                                            dopparam.data_type = structure.child_params.child_param.at(0).child_dop_ref.split('.').at(structure.child_params.child_param.at(0).child_dop_ref.split('.').size() - 1);
                                        }
                                    }
                                }
                                mService.serviceparams.child_params.child_param.append(dopparam);
                            }
                        }
                        receiveTreeNode(FunctClassName,ServiceName,udsCommand);
                        mODXDataMatch.insert(ServiceName,udsCommand);
                        ecu_service.Services.append(mService);
                    }
                    RequestSizeIndex++;
                }
            }
            ServiceSizeIndex++;
        }
        FunctClassSizeIndex++;
    }
    InsertWait();

    emit sendODX(ecu_service);
}

void MainWindow::on_Btn_File_4_clicked()
{
   // ui->line_FilePath_3->setText("/home/zihaohu/Documents/ALKS_CDD_DEMO/ECU_CDD.odx-d");
    if(ui->line_FilePath_3->text().isEmpty())
    {
        QMessageBox::information(nullptr,"Warning","file Path is Empty");
        return;
    }
    parseODX(ui->line_FilePath_3->text());
}

void MainWindow::on_Btn_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "保存文件",
                                                    "./",
                                                    "Json(*.json)");
    if(!filename.endsWith(".json", Qt::CaseInsensitive))
    {
        filename += ".json";
    }
    QFile file(filename);

    if(!file.open(QFile::WriteOnly))
    {
        return;
    }

    QString textJson = ui->txt_diagscript->toPlainText();

    QTextStream out(&file);
    out << textJson;

    file.close();

}

void MainWindow::on_treeWidget_doubleClicked(const QModelIndex &index)
{
    QString doubleData = index.data().toString();
    if(strcmp(doubleData.toLatin1().data(),"Wait") == 0)
    {
        QString jsonMsg = doubleData + ";" ;
        bool ok = false;
        QString strName = QInputDialog::getText(
                        this,
                        "请输入延时时间",
                        "延时时间，单位为毫秒（ms）",
                        QLineEdit::Normal,
                        "5000",
                        &ok
                        );
            if(ok && !strName.isEmpty()){
                jsonMsg += strName;
            }

        emit sendJson(jsonMsg);
    }
    else if(doubleData.contains('(') && doubleData.contains(')'))
    {
        QString data = doubleData.mid(doubleData.indexOf('(') + 1,doubleData.indexOf(')') - doubleData.indexOf('(')-2);
        QString jsonMsg = "phyRequest;" + data + ";" + QString("%1 ").arg(data.mid(0,2).toInt(nullptr,16)+0x40,2,16,QLatin1Char('0')).toUpper() + data.mid(data.indexOf(')') + 4,-1);
        emit sendJson(jsonMsg);
       // ui->txt_diagscript->append(jsonMsg);
    }

}

void MainWindow::on_Btn_clear_clicked()
{
    ui->txt_diagscript->setText("");
    int size = mSequences.size();
    for(int i=0 ; i< size;i++) {
          mSequences.removeFirst();
      }
     mDataSeq.remove("sequences");

}

void MainWindow::on_Btn_update_clicked()
{
//    if(ui->tasktyperuntime->isChecked())
//    {
//        isRuntime = 1;
//        DiagnosticSeqence Diag;
//        QString taskID = ui->line_taskID->text();
//        Diag = parseSequence((QApplication::applicationDirPath() +"/task/" + taskID).toLatin1().data());
//        executeLinklistTask(Diag);
//    }
//    else
//    {
//        isRuntime = 0;
//    }
}

void MainWindow::on_line_taskID_textChanged(const QString &arg1)
{
    QDir dir(QApplication::applicationDirPath() +  "/task");
    QStringList dirName = dir.entryList(QDir::Dirs| QDir::NoDotAndDotDot);
    QCompleter *completer = new QCompleter(dirName, this);
    completer->setFilterMode(Qt::MatchContains);
    ui->line_taskID->setCompleter(completer);
}

void MainWindow::on_line_taskID_editingFinished()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/task/" + ui->line_taskID->text();
    QDir dir(filePath);
    if(dir.exists())
    {
        QFile *file = new QFile(filePath + "/dataflow.json");
        QByteArray fileData;
        if(file->open(QIODevice::ReadWrite))
        {
            fileData = file->readAll();
        }
        else
        {
            return;
        }
        ui->text_json->setText(fileData);
        file->close();
        delete file;
    }
}

void MainWindow::on_Btn_File_otx_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"open flash file","/home","otx(*.otx)");
    ui->line_otx_filePath->setText(s);
}

void MainWindow::on_Btn_File_parseotx_clicked()
{
    ui->flowChart_widget->openChartFile(ui->line_otx_filePath->text());
    if(mODXDataMatch.size() != 0)
    {
        foreach (QString udsCommand, ui->flowChart_widget->otx.commandData) {
            if(udsCommand.contains(":"))
                udsCommand = udsCommand.split(":").at(1);
//            else
//            {
//                QString jsonMsg = "Wait;" + udsCommand ;
//                emit sendJsonotx(jsonMsg);
//                continue;
//            }
            QString udsData = mODXDataMatch.value(udsCommand);
            if(!udsData.isEmpty())
            {
                QString jsonMsg = "phyRequest;" + udsData + ";" + QString("%1 ").arg(udsData.mid(0,2).toInt(nullptr,16)+0x40,2,16,QLatin1Char('0')).toUpper() + udsData.mid(3,-1);
                emit sendJsonotx(jsonMsg);
            }
        }
    }

}

void MainWindow::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* curItem=ui->treeWidget->itemAt(pos);
    if(curItem==NULL)return;
    QVariant var = curItem->data(0,Qt::UserRole);
    if(0 == var)
    {
       QMenu *popMenu =new QMenu(this);//定义一个右键弹出菜单

       popMenu->addAction("ui->action_newDB");//往菜单内添加QAction   该action在前面用设计器定义了
       popMenu->addAction("ui->action_openDB");
       popMenu->addAction("ui->action_delDB");
       popMenu->exec(QCursor::pos());//弹出右键菜单，菜单位置为光标位置
    }
    else
    {
        QString clickSerive = QString(curItem->text(0)).split('(').at(0);
        foreach (Service service, ecu_service.Services) {
            if(service.serviceName == clickSerive.trimmed())
            {
                QString info = "serviceName : " + service.serviceName + "\n" + "serviceID : " + service.serviceID + "\n"
                        + "subservice/DID : " + service.subService  + "\n" ;

                foreach (DOPPARAM param, service.serviceparams.child_params.child_param) {
                    QString layoutPos;
                    layoutPos = "  Param name : " + param.child_short_name + "\n" ;
                    layoutPos += "  Param pos : " + param.child_byte_position.data_value + "\n" ;
                    if(!param.child_byte_size.isEmpty())
                        layoutPos += "  Param size : " + param.child_byte_size + "\n";
                    info += layoutPos;
                }
                QMessageBox::information(this,
                                         tr("服务细节"),
                                         info,
                                         QMessageBox::Ok,
                                         QMessageBox::Cancel);

            }
        }

    }
}

void MainWindow::on_pushButton_2_clicked()
{
     ui->flowChart_widget->saveChartFile(ecu_service);
}

void MainWindow::on_chart_rect_customContextMenuRequested(const QPoint &pos)
{
     popMenu->exec(QCursor::pos());
}

void MainWindow::on_Btn_ChoiceECU_clicked()
{
    QPoint  getY = ui->flowChart_widget->paintrect("ns:Assignment-ECUList-BASE_VARIANT",0,0);
    int count = ui->flowChart_widget->charts.size();
    getY = ui->flowChart_widget->paintrect("hmi:ChoiceDialog-Select Ecu-Select Ecu to Configuration-ECUList-ECU",0,getY.y() + 10);
    count = ui->flowChart_widget->charts.size();
    ui->flowChart_widget->paintline(ui->flowChart_widget->charts[count - 2],ui->flowChart_widget->charts[count - 1],ORIENTION::SOUTH);

    getY = ui->flowChart_widget->paintrect("ns:Assignment-ECUName-ECU",0,getY.y() + 10);
    count = ui->flowChart_widget->charts.size();
    ui->flowChart_widget->paintline(ui->flowChart_widget->charts[count - 2],ui->flowChart_widget->charts[count - 1],ORIENTION::SOUTH);

    getY = ui->flowChart_widget->paintrect("ns:Assignment-ECUChannel-ECUName",0,getY.y() + 10);
    count = ui->flowChart_widget->charts.size();
    ui->flowChart_widget->paintline(ui->flowChart_widget->charts[count - 2],ui->flowChart_widget->charts[count - 1],ORIENTION::SOUTH);

    getY = ui->flowChart_widget->paintrect("ns:Assignment-ComChannel-ECUChannel",0,getY.y() + 10);
    count = ui->flowChart_widget->charts.size();
    ui->flowChart_widget->paintline(ui->flowChart_widget->charts[count - 2],ui->flowChart_widget->charts[count - 1],ORIENTION::SOUTH);
}

XLstatus MainWindow::getCANoeConfig()
{
    XLstatus          xlStatus;
    xlStatus = xlOpenDriver ();

    if(XL_SUCCESS == xlStatus) {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus)
    {
        unsigned int i;
        char         str[100];

        ui->text_output_2->append("\t\t----------------------------------------------------------");
        ui->text_output_2->append(QString("\t\t- %1 channels       Hardware Configuration               -").arg(g_xlDrvConfig.channelCount));
        ui->text_output_2->append("\t\t----------------------------------------------------------");

        for (i=0; i < g_xlDrvConfig.channelCount; i++)
        {
            ui->text_output_2->append(QString("\t\t-Ch:%1,CM:0x%2,%3").arg(g_xlDrvConfig.channel[i].channelIndex,2,10,QChar('0'))
                                    .arg(g_xlDrvConfig.channel[i].channelMask,3,16,QChar('0'))
                                    .arg(g_xlDrvConfig.channel[i].name));
            ui->comboBox->addItem(g_xlDrvConfig.channel[i].name);
            std::cout << ("- Ch:%02d, CM:0x%03I64x,",
            g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

          strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
          std::cout << (" %23s,", str);

          memset(str, 0, sizeof(str));

          if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
            strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
            std::cout << ("%13s -\n", str);
          }
          else std::cout << ("    no Cab!   -\n");


        }

        std::cout << ("----------------------------------------------------------\n\n");
    }
    return xlStatus;
}

XLstatus MainWindow::getCANoeConfigAva()
{
    XLstatus          xlStatus;

    if(XL_SUCCESS == xlStatus) {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus)
    {
        unsigned int i;
        char         str[100];

        ui->text_output->append("\t\t----------------------------------------------------------");
        ui->text_output->append(QString("\t\t- %1 channels       Hardware Configuration               -").arg(g_xlDrvConfig.channelCount));
        ui->text_output->append("\t\t----------------------------------------------------------");

        for (i=0; i < g_xlDrvConfig.channelCount; i++)
        {
            if(g_xlDrvConfig.channel[i].isOnBus == 0)
            {
                ui->text_output->append(QString("\t\t-Ch:%1,CM:0x%2,%3").arg(g_xlDrvConfig.channel[i].channelIndex,2,10,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].channelMask,3,16,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].name));
                ui->comboBox_2->addItem(g_xlDrvConfig.channel[i].name);
              std::cout << ("- Ch:%02d, CM:0x%03I64x,",
                g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

              strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
              std::cout << (" %23s,", str);

              memset(str, 0, sizeof(str));

              if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
                strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
                std::cout << ("%13s -\n", str);
              }
              else std::cout << ("    no Cab!   -\n");
            }

        }

        std::cout << ("----------------------------------------------------------\n\n");
    }
    return xlStatus;
}

void MainWindow::on_Btn_Fresh_clicked()
{
    XLstatus          xlStatus;
    ui->comboBox->clear();
    if(XL_SUCCESS == xlStatus)
    {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus)
    {
        unsigned int i;
        char         str[100];

        ui->text_output_2->append("\t\t----------------------------------------------------------");
        ui->text_output_2->append(QString("\t\t- %1 channels       Hardware Configuration               -").arg(g_xlDrvConfig.channelCount));
        ui->text_output_2->append("\t\t----------------------------------------------------------");

        for (i=0; i < g_xlDrvConfig.channelCount; i++)
        {
            if(g_xlDrvConfig.channel[i].isOnBus == 0)
            {
                ui->text_output_2->append(QString("\t\t-Ch:%1,CM:0x%2,%3").arg(g_xlDrvConfig.channel[i].channelIndex,2,10,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].channelMask,3,16,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].name));
                ui->comboBox->addItem(g_xlDrvConfig.channel[i].name);
                std::cout << ("- Ch:%02d, CM:0x%03I64x,",
                g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

                strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
                std::cout << (" %23s,", str);

                memset(str, 0, sizeof(str));

              if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE)
              {
                strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
                std::cout << ("%13s -\n", str);
              }
              else
                  std::cout << ("    no Cab!   -\n");
            }

        }
     }
     ui->text_output_2->append("\t\t----------------------------------------------------------");
}

void MainWindow::on_Btn_FileDiaglog_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"open config file","/home","json files(*.json)");
    ui->lineEdit_DiagConf->setText(s);
}

void MainWindow::displayString(QString str)
{
    ui->text_output_2->append(str);
}

void MainWindow::deletethread()
{
    if(_workerThread->isRunning())
    {
        _workerThread->exit();
    }
    ui->Btn_Start->setEnabled(true);
    ui->Btn_StopFlash->setEnabled(false);
    ui->Btn_FIle->setEnabled(true);
}

void MainWindow::on_Btn_StartDiag_clicked()
{
    struct DiagnosticSeqence sequence_script;

    FILE *file = fopen(ui->lineEdit_DiagConf->text().toLatin1().data(),"rb");

    if(!file)
    {
        ui->text_output_2->append("failed to open fail,error: no file\n");
        return;
    }
    fseek(file,0,SEEK_END);
    int length = ftell(file);
    fseek(file,0,SEEK_SET);
    char* buf = (char*)malloc(length + 1);

    fread(buf,1,length,file);
    buf[length] = '\0';
    cJSON *json = NULL;
    json = cJSON_Parse(buf);
    if(!json)
    {
        ui->text_output_2->append("json format error");
        return;
    }
    sequence_script.sequence = cJSON_Duplicate(json,1);
    flashobj->setFlashSeq(sequence_script);

    _workerThread->start();
    emit startFlash(NULL);
}

void MainWindow::on_Btn_Send_clicked()
{
    QString sendData = ui->SendData_Line->text();
    QStringList udsData = sendData.split(';');
    int loopIdx = 0;
    uint8_t data[128];
    QString seqdata = QString("phyRequest;");
    seqdata += sendData;
    struct DiagnosticSeqence sequence_version;
    cJSON *root = cJSON_CreateObject();
    cJSON *seq = cJSON_CreateArray();

    cJSON_AddItemToArray(seq, cJSON_CreateString(seqdata.toStdString().c_str()));
    cJSON_AddItemToObject(root, "sequences", seq);

    sequence_version.sequence = cJSON_Duplicate(root,1);
    cJSON_Delete(root);
    flashobj->setFlashSeq(sequence_version);

    _workerThread->start();
    emit startFlash(NULL);
}

void MainWindow::on_Btn_Connect_clicked()
{
    TPCANStatus status = PCAN_ERROR_OK;
    QString dataflowPath = QCoreApplication::applicationDirPath() + "/Conf";
    if(ui->comboBox->currentText() == "PCAN")
    {
        status = CAN_Initialize(PCAN_USBBUS1,PCAN_BAUD_500K);
        if(status == PCAN_ERROR_OK)
        {
            DISPLAY_OUTPUT("PCAN Device Connected");
            if(ui->checkBox->checkState() == Qt::CheckState::Checked)
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),0);
            }
            else
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),1);
            }
            ui->Btn_Connect->setEnabled(false);
            ui->Btn_disConnect->setEnabled(true);
            ui->Btn_FIle->setEnabled(true);
            tool = 0;
        }
        else
        {
            DISPLAY_OUTPUT("Check your PCAN Device");
        }
    }
    //else if(ui->comboBox->currentText() == "Vector")
    {
        XLstatus      xlStatus;
        unsigned int  xlChanIndex = 0;
        xlStatus = InitDriver(&xlChanIndex,ui->comboBox->currentIndex());
        DISPLAY_OUTPUT("- Init             : " + QString(xlGetErrorString(xlStatus)));
        if(XL_SUCCESS == xlStatus)
        {
            if(ui->checkBox->checkState() == Qt::CheckState::Checked)
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),0);
            }
            else
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),1);
            }

            DISPLAY_OUTPUT("Vector Device Connected");
            ui->Btn_Connect->setEnabled(false);
            ui->Btn_disConnect->setEnabled(true);
            ui->Btn_FIle->setEnabled(true);
            tool = 1;
            getCANoeConfigAva();
        }
        else
            return;
    }

    dataflowPath = QCoreApplication::applicationDirPath() + "/Conf";
    sequence = parseSequence(dataflowPath.toLatin1().data(),1);
    sequence.requestID = ui->txt_PhyReq->text().toUInt(nullptr,16);
    sequence.responseID = ui->txt_phyRes->text().toUInt(nullptr,16);
    sequence.cantype = ui->comboBox_4->currentIndex();
    flashobj = new  flash(sequence);
    flashobj->initCANTP();
    _workerThread= new QThread(this);
    flashobj->moveToThread(_workerThread);
    connect(this, &MainWindow::startFlash,flashobj, &flash::testquenceList);
    connect(flashobj,&flash::emitString,this,&MainWindow::displayString);
    connect(flashobj,&flash::emitStop,this,&MainWindow::deletethread);
    connect(flashobj,&flash::emitDataSize,this,&MainWindow::displayProgress);


}

void MainWindow::on_Btn_disConnect_clicked()
{
    if(ui->comboBox->currentText() == "PCAN")
    {
        TPCANStatus status = PCAN_ERROR_OK;
        status = CAN_Uninitialize(PCAN_USBBUS1);
        if(status == PCAN_ERROR_OK)
        {
            DISPLAY_OUTPUT("PCAN Device disconnected");
            ui->Btn_Connect->setEnabled(true);
            ui->Btn_disConnect->setEnabled(false);
        }
        else
        {
            DISPLAY_OUTPUT("Check your PCAN Device");
        }
    }
    cleanUpDriver();
    DISPLAY_OUTPUT("Vector Device disconnected");
//     else if(ui->comboBox->currentText() == "Vector")
//     {
//         cleanUpDriver();
//         DISPLAY_OUTPUT("Vector Device disconnected");
//     }
    ui->Btn_Connect->setEnabled(true);
    ui->Btn_disConnect->setEnabled(false);
//     delete msg;
//     delete msg_channle;
}

void MainWindow::displayProgress(u_int64 data)
{
    static int progress = 0;
    progress += data;
    ui->progressBar->setValue(progress);
}

void MainWindow::on_Btn_Start_clicked()
{
    int linkIndex = 0;
    ui->progressBar->setValue(0);
    maxProgress = 0;
    while(linkIndex < ui->tableWidget->rowCount())
    {
        linklist.append(ui->tableWidget->item(linkIndex,0)->text(),
                        ui->tableWidget->item(linkIndex,1)->text().toUInt(nullptr,16),
                        ui->tableWidget->item(linkIndex,2)->text().toUInt(nullptr,16),
                        ui->tableWidget->item(linkIndex,3)->text().toUInt(nullptr,16));
        maxProgress += ui->tableWidget->item(linkIndex,3)->text().toUInt(nullptr,16);
        linkIndex++;
    }
    ui->progressBar->setRange(0,maxProgress);

    struct DiagnosticSeqence sequence_flash;
    cJSON *root = cJSON_CreateObject();
    cJSON *seq = cJSON_CreateArray();
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;10 83"));
//    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;10 03"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;31 01 02 03;71 01 02 03 00"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;85 82;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;28 83 03;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));
    if(ui->checkBox_2->checkState())
    {
        cJSON_AddItemToArray(seq, cJSON_CreateString("sendMsgData;10 02;"));
        QString wait = "waitTime;" + ui->lineEdit_12->text();
        cJSON_AddItemToArray(seq, cJSON_CreateString(wait.toLatin1().data()));
    }
    else
    {
        cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;10 02;50 02"));
        cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;2000"));
    }
    cJSON_AddItemToArray(seq, cJSON_CreateString("seeds;27 09;67 09"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("keys;27 0A;67 0A"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("downloadRequestHex;34 00 44;74"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("downloadHex;36;76"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;37;77"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("checkCRC;31 01 02 02;71 01 02 02 00"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("next;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;31 01 FF 01;71 01 FF 01 00"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;11 01;51 01"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;2000"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;10 83;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;28 80 03;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;85 81;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("funRequest;10 81;"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("waitTime;200"));

    cJSON_AddItemToObject(root, "sequences", seq);
    sequence_flash.sequence = cJSON_Duplicate(root,1);
    cJSON_Delete(root);
    flashobj->setFlashSeq(sequence_flash);

    _workerThread->start();
    emit startFlash(&linklist);
    ui->Btn_Start->setEnabled(false);
    ui->Btn_FIle->setEnabled(false);
}

QString MainWindow::getHexInfo(const char* rpath)
{
    IHexResult result;
    IHexRecord record;

    ConvertContext ctx;
    InitContext(&ctx);
    QString info = "";
    uint32_t currentDataFileAddr = 0;
    uint32_t endDataFileAddr = 0;
    int blockIndex = 1;
    uint8_t loopIndex = ui->tableWidget->rowCount();
    if (NULL == (ctx.rfile = fopen(rpath, "r")))
    {
        ExitApplication(&ctx, STRING_OPEN_FILEERROR, rpath);
        return info;

    }

    if (NULL == (ctx.strbuff = (char*)malloc(IHEX_STRING_BUFF_SIZE)) ||
        NULL == (ctx.binbuff = (uint8_t*)malloc(IHEX_MAX_BINDATA_NUM)))
    {
        ExitApplication(&ctx, STRING_MALLO_MEMERROR);
        return info;
    }


    uint32_t startaddress = 0;
    IHex_InitRecord(&record, ctx.binbuff);
    for (int clen = 0;;)
    {
        if (NULL == fgets(ctx.strbuff, IHEX_RECORD_STR_LEN, ctx.rfile))
        {
            ExitApplication(&ctx, STRING_READ_ERROREND);
            return info;
        }

        ++clen;
        if (CheckSpaceLine(ctx.strbuff))       // 空行
            continue;

        result = IHex_GetNextHeadInfo(&record, ctx.strbuff);
        if(record.type == IHEX_TYPE_DATARECORD)
        {
            if((currentDataFileAddr != record.fileAddr) && (clen >2))
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(rowIndex,0,new QTableWidgetItem(QString::fromLocal8Bit(rpath)));
                ui->tableWidget->setItem(rowIndex,1,new QTableWidgetItem(QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper()));
                ui->tableWidget->setItem(rowIndex,2,new QTableWidgetItem(QString("%1").arg(endDataFileAddr,8,16,QLatin1Char('0')).toUpper()));
                ui->tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(endDataFileAddr - record.minAddr + 1,8,16,QLatin1Char('0')).toUpper()));

                ui->tableWidget->item(rowIndex,0)->setFlags(ui->tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget->item(rowIndex,1)->setFlags(ui->tableWidget->item(rowIndex,1)->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget->item(rowIndex,2)->setFlags(ui->tableWidget->item(rowIndex,2)->flags() & ~Qt::ItemIsEditable);
                ui->tableWidget->item(rowIndex,3)->setFlags(ui->tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);

                DISPLAY_OUTPUT(QString("文件:\"%1(block%2)\" 读取成功\r\n").arg(rpath).arg(QString::number(blockIndex,10)));
                ui->text_output_2->append(QString("\t\t  文件记录数据范围为:0x%1 - 0x%2\r\n").arg(QString::number(record.minAddr,16).toUpper()).arg(QString::number(endDataFileAddr,16).toUpper()));
                ui->text_output_2->append(QString("\t\t  共: %1 字节数据 %2 行\r\n").arg(QString::number(endDataFileAddr - record.minAddr + 1,10)).arg(QString::number(clen,10)));


                record.minAddr = record.maxAddr - record.count + 1;
                rowIndex++;
                blockIndex++;

            }
            currentDataFileAddr = record.fileAddr + record.count;
            endDataFileAddr = record.maxAddr;

        }

        if (IHEX_RESULT_NOERROR != result)
        {
            ExitApplication(&ctx, STRING_FILE_ERROR, result, clen);
            return info;
        }
        else if (record.type == IHEX_TYPE_STARTADDRESS)
        {
            startaddress = record.fileAddr;
        }
        else if (record.type == IHEX_TYPE_ENDFILE)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(rowIndex,0,new QTableWidgetItem(QString::fromLocal8Bit(rpath)));
            ui->tableWidget->setItem(rowIndex,1,new QTableWidgetItem(QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper()));
            ui->tableWidget->setItem(rowIndex,2,new QTableWidgetItem(QString("%1").arg(record.maxAddr,8,16,QLatin1Char('0')).toUpper()));
            ui->tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(record.maxAddr - record.minAddr + 1,8,16,QLatin1Char('0')).toUpper()));

            ui->tableWidget->item(rowIndex,0)->setFlags(ui->tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->item(rowIndex,1)->setFlags(ui->tableWidget->item(rowIndex,1)->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->item(rowIndex,2)->setFlags(ui->tableWidget->item(rowIndex,2)->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->item(rowIndex,3)->setFlags(ui->tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);

            rowIndex++;
            DISPLAY_OUTPUT(QString("文件:\"%1(block%2)\" 读取成功\r\n").arg(rpath).arg(QString::number(blockIndex,10)));
            ui->text_output_2->append(QString("\t\t  文件记录数据范围为:0x%1 - 0x%2\r\n").arg(QString::number(record.minAddr,16).toUpper()).arg(QString::number(record.maxAddr,16).toUpper()));
            ui->text_output_2->append(QString("\t\t  共: %1 字节数据 %2 行\r\n").arg(QString::number(record.maxAddr- record.minAddr + 1,10)).arg(QString::number(clen,10)));
            if (startaddress)
                ui->text_output_2->append(QString("\t\t  起始地址为：0x%1\r\n").arg(QString::number(startaddress,16).toUpper()));
            info = " | " + QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper() + " | " +  QString("%1").arg(record.maxAddr- record.minAddr,8,16,QLatin1Char('0')).toUpper();
            break;
        }
    }

    while(loopIndex < rowIndex)
    {
        ui->tableWidget->setItem(loopIndex,2,new QTableWidgetItem(QString("%1").arg(record.maxAddr,8,16,QLatin1Char('0')).toUpper()));
        loopIndex++;
    }
    ExitApplication(&ctx,"Success");

    return info;
}

void MainWindow::on_Btn_FIle_clicked()
{
    if(lastFilePath.isEmpty())
        lastFilePath = QDir::homePath();
    QString filePath = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"),
                                                    lastFilePath, QObject::tr("All Files (*)"));

    if(!filePath.isEmpty())
    {
        QString Info;
        if(filePath.toLower().contains(".hex"))
        {
            if(!(Info = getHexInfo(filePath.toStdString().c_str())).isEmpty())
            {
                DISPLAY_OUTPUT(filePath + " loaded sucessfully");
                filePath += Info;
            }
            else
            {
                DISPLAY_OUTPUT( filePath + "loaded failed,please check the file");
                return;
            }

        }
        else if(filePath.contains(".bin"))
        {
            QFileInfo fileInfo(filePath);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(rowIndex,0,new QTableWidgetItem(filePath));

            ui->tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(fileInfo.size(),8,16,QLatin1Char('0')).toUpper()));

            ui->tableWidget->item(rowIndex,0)->setFlags(ui->tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->item(rowIndex,3)->setFlags(ui->tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);
            DISPLAY_OUTPUT(filePath + " loaded sucessfully");
            rowIndex++;
        }
        QFileInfo fileInfo(filePath);
        lastFilePath = fileInfo.absolutePath();
    }
    else
    {
         DISPLAY_OUTPUT(filePath + "loaded failed,please check the path");
    }
}

void MainWindow::on_Btn_StopFlash_clicked()
{
    if(_workerThread->isRunning())
    {
        _workerThread->exit();
    }
    ui->Btn_FIle->setEnabled(true);
    ui->Btn_Start->setEnabled(true);
}

void MainWindow::on_Btn_Save_clicked()
{
    QDateTime datatime = QDateTime::currentDateTime();
    QFile file(QCoreApplication::applicationDirPath() + "/Log/" + datatime.toString("yyyyMMddhhmmss") + ".txt");
    qDebug() << QCoreApplication::applicationDirPath() + "/Log/" + datatime.toString("yyyyMMddhhmmss") + ".txt";
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Cannot open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << ui->text_output_2->toPlainText();
    file.close();
}

void MainWindow::on_Btn_ConnectMqtt_clicked()
{
    mq = new mqttClient();
    if(mq->connectMqtt())
    {
        DISPLAY_OUTPUT("MQTT 连接成功");
        ui->Btn_ConnectMqtt->setEnabled(false);
        ui->Btn_disConnectMqtt->setEnabled(true);
        
        connect(mq,&mqttClient::emitMqttMsg,this,[=](QString msg)
        {
            int topicStartPos = msg.indexOf("Topic:") + 6;
            int topicEndPos = msg.indexOf(" Message:");
            QString topic = msg.mid(topicStartPos, topicEndPos - topicStartPos).trimmed();
            int messageStartPos = msg.indexOf("Message:") + 8;
            QString jsonString = msg.mid(messageStartPos).trimmed();

            if(topic.contains("versionInfoResp"))
            {
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                if (jsonDoc.isNull())
                {
                    ui->text_output_2->append("VersionInfoResp error\n");
                    return;
                }
                QJsonObject jsonObject = jsonDoc.object();
                uint8_t loopIndex = 0;
                QJsonArray ecusArray = jsonObject["ecus"].toArray();
                while (loopIndex < ecusArray.size()) {
                    ui->comboBox_ECU->addItem(ecusArray[loopIndex].toObject()["name"].toString());
                    m_ecusArray.append(ecusArray[loopIndex].toObject());
                    loopIndex++;
                }
                ui->Btn_SendMqtt->setEnabled(true);
                ui->Btn_SendMqttScript->setEnabled(true);
                ui->Btn_FileDiaglogMqtt->setEnabled(true);
                ui->Btn_EOL->setEnabled(true);
                ui->Btn_AfterSale->setEnabled(true);
            }
            else
            {
                ui->text_output_2->append(msg);
            }
        });
        mq->sendMqttMsg("versionInfoReq","version");
        ui->Btn_getVersion->setEnabled(true);
    }
    else
    {
        DISPLAY_OUTPUT("MQTT 连接失败");
        delete mq;
    }
}

void MainWindow::initMQTTUI()
{
    ui->Btn_SendMqtt->setEnabled(false);
    ui->Btn_SendMqttScript->setEnabled(false);
    ui->Btn_disConnectMqtt->setEnabled(false);
    ui->Btn_ConnectMqtt->setEnabled(true);
    ui->Btn_FileDiaglogMqtt->setEnabled(false);
    ui->Btn_getVersion->setEnabled(false);
    ui->Btn_EOL->setEnabled(false);
    ui->Btn_AfterSale->setEnabled(false);
}

void MainWindow::on_Btn_disConnectMqtt_clicked()
{
    mq->disconnectMqtt();
    delete mq;
    DISPLAY_OUTPUT("MQTT 断开连接");
    ui->Btn_ConnectMqtt->setEnabled(true);
}

void MainWindow::on_Btn_SendMqtt_clicked()
{
    QString sendData = ui->SendData_mqtt->text();
    QJsonArray sequences;
    QString DiagECU = ui->comboBox_ECU->currentText();
    sequences.append(QString("phyRequest;")+sendData);
    for (int loopIdx = 0;loopIdx < m_ecusArray.size();loopIdx++)
    {
        if(m_ecusArray[loopIdx].toObject()["name"].toString() == DiagECU)
        {
            QJsonObject ecuDiag = m_ecusArray[loopIdx].toObject();
            ecuDiag["sequences"] = sequences;
            QJsonDocument jsonDoc(ecuDiag);
            mq->sendMqttMsg("diagnosticScript",jsonDoc.toJson(QJsonDocument::Indented));
        }
    }

}

void MainWindow::on_Btn_getVersion_clicked()
{
    mq->sendMqttMsg("versionInfoReq","version");
}

void MainWindow::on_Btn_FileDiaglogMqtt_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"open config file","./","json files(*.json)");
    ui->SendData_mqttPath->setText(s);
    QFile file(s);
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }
        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        if (doc.isNull()) {
            ui->text_output_2->append(QString("诊断文件JSON格式错误"));
            return;
        }

        if (!doc.isObject()) {
            ui->text_output_2->append(QString("诊断文件JSON格式错误"));
            return;
        }

        QJsonObject jsonObj = doc.object();
        QJsonArray sequences;
        if (jsonObj.contains("sequences") && jsonObj["sequences"].isArray()) {
            sequences = jsonObj["sequences"].toArray();
            ui->text_output_2->append(QJsonDocument(sequences).toJson(QJsonDocument::Indented));
        }
        else
        {
            ui->text_output_2->append(QString("诊断文件中不含有诊断诊断序列"));
            return;
        }

}

void MainWindow::on_Btn_SendMqttScript_clicked()
{
    QString diagseq = ui->SendData_mqttPath->text();
    QString DiagECU = ui->comboBox_ECU->currentText();
    QFile file(diagseq);
        if (!file.open(QIODevice::ReadOnly)) {
            return;
        }
        QByteArray fileData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        if (doc.isNull()) {
            ui->text_output_2->append(QString("诊断文件JSON格式错误"));
            return;
        }

        if (!doc.isObject()) {
            ui->text_output_2->append(QString("诊断文件JSON格式错误"));
            return;
        }

        QJsonObject jsonObj = doc.object();
        QJsonArray sequences;
        if (jsonObj.contains("sequences") && jsonObj["sequences"].isArray()) {
            sequences = jsonObj["sequences"].toArray();
        }
        else
        {
            ui->text_output_2->append(QString("诊断文件中不含有诊断诊断序列"));
            return;
        }
        for (int loopIdx = 0;loopIdx < m_ecusArray.size();loopIdx++)
        {
            if(m_ecusArray[loopIdx].toObject()["name"].toString() == DiagECU)
            {
                QJsonObject ecuDiag = m_ecusArray[loopIdx].toObject();
                ecuDiag["sequences"] = sequences;
                QJsonDocument jsonDoc(ecuDiag);
                mq->sendMqttMsg("diagnosticScript",jsonDoc.toJson(QJsonDocument::Indented));
            }
        }
}

void MainWindow::on_pushButton_3_clicked()
{
    XLstatus      xlStatus;
    unsigned int  xlChanIndex = 0;
    XLportHandle handle = XL_INVALID_PORTHANDLE;
    VCANMsg msg_ui;
    xlStatus = connectDriver(&xlChanIndex,ui->comboBox_2->currentIndex(),&handle);
    if(XL_SUCCESS == xlStatus)
    {
        std::cout << "handle" << handle;
        msgThread_channle->start();
        DISPLAY_OUTPUT(ui->comboBox_2->currentText() + "connect sucessfully,send wakeup message");

        msg_ui.ID = ui->Message_ID->text().toUInt(nullptr,16);
        msg_ui.LEN = 0;
        if(!ui->MsgData1->text().isEmpty())
        {
            msg_ui.DATA[0] = ui->MsgData1->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData2->text().isEmpty())
        {
            msg_ui.DATA[1] = ui->MsgData2->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData3->text().isEmpty())
        {
            msg_ui.DATA[2] = ui->MsgData3->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData4->text().isEmpty())
        {
            msg_ui.DATA[3] = ui->MsgData4->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData5->text().isEmpty())
        {
            msg_ui.DATA[4] = ui->MsgData5->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData6->text().isEmpty())
        {
            msg_ui.DATA[5] = ui->MsgData6->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData7->text().isEmpty())
        {
            msg_ui.DATA[6] = ui->MsgData7->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        if(!ui->MsgData8->text().isEmpty())
        {
            msg_ui.DATA[7] = ui->MsgData8->text().toUInt(nullptr,16);
            msg_ui.LEN++;
        }
        msg_channle->setactiveMsg_channle(msg_ui,ui->comboBox_2->currentIndex() +1);
        emit startsignal_c();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    msgThread->start();
    VCANMsg msg_ui;
    msg_ui.ID = ui->Message_ID->text().toUInt(nullptr,16);
    msg_ui.LEN = 0;
    if(!ui->MsgData1->text().isEmpty())
    {
        msg_ui.DATA[0] = ui->MsgData1->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData2->text().isEmpty())
    {
        msg_ui.DATA[1] = ui->MsgData2->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData3->text().isEmpty())
    {
        msg_ui.DATA[2] = ui->MsgData3->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData4->text().isEmpty())
    {
        msg_ui.DATA[3] = ui->MsgData4->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData5->text().isEmpty())
    {
        msg_ui.DATA[4] = ui->MsgData5->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData6->text().isEmpty())
    {
        msg_ui.DATA[5] = ui->MsgData6->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData7->text().isEmpty())
    {
        msg_ui.DATA[6] = ui->MsgData7->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    if(!ui->MsgData8->text().isEmpty())
    {
        msg_ui.DATA[7] = ui->MsgData8->text().toUInt(nullptr,16);
        msg_ui.LEN++;
    }
    msg->setactiveMsg(msg_ui);
    emit startsignal();
}

void MainWindow::on_Btn_ReadVersion_clicked()
{
    struct DiagnosticSeqence sequence_version;
    cJSON *root = cJSON_CreateObject();
    cJSON *seq = cJSON_CreateArray();
    cJSON_AddItemToArray(seq, cJSON_CreateString("phyRequest;10 01;50 01"));
//    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 87;62 F1 87"));
//    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 8A;62 F1 8A"));
//    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 97;62 F1 97"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 89;62 F1 89"));
//    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F0 89;62 F0 89"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 93;62 F1 93"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 95;62 F1 95"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 8C;62 F1 8C"));
    cJSON_AddItemToArray(seq, cJSON_CreateString("readVersionASCII;22 F1 80;62 F1 80"));
    cJSON_AddItemToObject(root, "sequences", seq);

    sequence_version.sequence = cJSON_Duplicate(root,1);
    cJSON_Delete(root);
    flashobj->setFlashSeq(sequence_version);

    _workerThread->start();
    emit startFlash(NULL);
}

void MainWindow::on_Btn_EOL_clicked()
{
    QString sendData = ui->SendData_mqtt->text();
    QJsonArray sequences;
    QString DiagECU = QString("DKM_M");
    sequences.append(QString("phyRequest;10 03;50 03"));
    sequences.append(QString("seeds;27 01;67 01"));
    sequences.append(QString("keys;27 02;67 02"));
    sequences.append(QString("seeds;27 01;67 01"));
    for (int loopIdx = 0;loopIdx < m_ecusArray.size();loopIdx++)
    {
        if(m_ecusArray[loopIdx].toObject()["name"].toString() == DiagECU)
        {
            QJsonObject ecuDiag = m_ecusArray[loopIdx].toObject();
            ecuDiag["sequences"] = sequences;
            QJsonDocument jsonDoc(ecuDiag);
            mq->sendMqttMsg("diagnosticScript",jsonDoc.toJson(QJsonDocument::Indented));
        }
    }
}



void MainWindow::initToolBar()
{
    setWindowIcon(QIcon(":/images/logo.ico"));
    m_Toolbar = new QToolBar();
    actionHome = new QAction("<-");
    this->addToolBar(m_Toolbar);
    actionHome->setIcon(QIcon(":/images/home.png"));
    actionHome->setText(QString("返回主页面"));
    m_Toolbar->addAction(actionHome);
    connect(actionHome,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(0);
    });
    actionNetwork = new QAction("<-");
    actionNetwork->setIcon(QIcon(":/images/nomqtt.png"));
    actionNetwork->setText(QString("当前网络状态为未连接"));
    m_Toolbar->addAction(actionNetwork);

    actionReturn = new QAction("<-");
    actionReturn->setIcon(QIcon(":/images/return.png"));
    actionReturn->setText(QString("返回上一级目录"));
    m_Toolbar->addAction(actionReturn);

    actionFresh = new QAction("<-");
    actionFresh->setIcon(QIcon(":/images/refresh.png"));
    actionFresh->setText(QString("刷新当前页面"));
    m_Toolbar->addAction(actionFresh);

    connect(actionNetwork,&QAction::triggered,[=](){
        if(actionNetwork->text().contains(QString("当前网络状态为未连接")))
        {
            mq = new mqttClient();
            lbl = new QLabel(this);


            static QMovie *movie = new QMovie("dddddd");
            movie->setFileName(":/images/1.gif");
            lbl->setMovie(movie);
            movie->start();
            lbl->resize(movie->frameRect().width(), movie->frameRect().height());
            lbl->move(width()/2-lbl->width()/2, height()/2-lbl->height()/2);
            lbl->show();
            ui->tab_2->setEnabled(false);
            if(mq->connectMqtt())
            {
                connect(mq,&mqttClient::emitMqttMsg,this,[=](QString msg)
                {
                    int topicStartPos = msg.indexOf("Topic:") + 6;
                    int topicEndPos = msg.indexOf(" Message:");
                    QString topic = msg.mid(topicStartPos, topicEndPos - topicStartPos).trimmed();
                    int messageStartPos = msg.indexOf("Message:") + 8;
                    QString jsonString = msg.mid(messageStartPos).trimmed();

                    if(topic.contains("versionInfoResp"))
                    {
                        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
                        if (jsonDoc.isNull())
                        {
                            ui->text_output_2->append("VersionInfoResp error\n");
                            return;
                        }
                        QJsonObject jsonObject = jsonDoc.object();
                        uint8_t loopIndex = 0;
                        QJsonArray ecusArray = jsonObject["ecus"].toArray();
                        while (loopIndex < ecusArray.size()) {
                            ui->comboBox_ECU->addItem(ecusArray[loopIndex].toObject()["name"].toString());
                            m_ecusArray.append(ecusArray[loopIndex].toObject());
                            loopIndex++;
                        }
                        ui->tab_2->setEnabled(true);
                        actionNetwork->setIcon(QIcon(":/images/mqtt.png"));
                        actionNetwork->setText(QString("当前网络状态为连接"));

                        movie->stop();
                        delete lbl;

                    }
                    else
                    {
                        ui->text_output_2->append(msg);
                    }
                });
                mq->sendMqttMsg("versionInfoReq","version");
                ui->Btn_getVersion->setEnabled(true);

            }
            else
            {
                DISPLAY_OUTPUT("MQTT 连接失败");
                delete mq;
            }
        }
        else
        {
            mq->disconnectMqtt();
            delete mq;
            actionNetwork->setIcon(QIcon(":/images/nomqtt.png"));
            actionNetwork->setText(QString("当前网络状态为未连接"));
        }

    });

    connect(actionReturn,&QAction::triggered,[=](){
        uint8_t indx = ui->stackedWidget->currentIndex();
        QWidget *w = ui->stackedWidget->widget(indx - 1);
        ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
        ui->stackedWidget->setCurrentWidget(w);
    });
}

void MainWindow::on_Btn_StackVersion_clicked()
{
    uint8_t loopIdx = 0;
    QScrollArea *ScroArea = new QScrollArea(this);
    ScroArea->setWidgetResizable(true);
    ScroArea->setFixedSize(1080,610);

    ScroArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ScroArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    ui->stackedWidget->addWidget(ScroArea);
    ui->stackedWidget->setCurrentWidget(ScroArea);
//    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex());

    QWidget *w = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(w); // 为page1设置布局

    while(loopIdx < m_ecusArray.size())
    {
        QHBoxLayout *layoutH = new QHBoxLayout;
        QLabel *label = new QLabel(QString::number(loopIdx), this);
        label->setFixedSize(65,90);
        label->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        QFont font;
        font.setFamily("华文中宋");
        font.setPointSize(21);
        label->setFont(font);
        CustomButton *customButton = new CustomButton(m_ecusArray[loopIdx].toObject()["name"].toString(),"","",this);

        QPushButton *button2 = new QPushButton("无故障", this);
        button2->setFixedSize(120,90);
        button2->setStyleSheet("QPushButton{"\
                                    "border: none;"\
                                    "color: rgb(0,0,0);                "\
                                    "font: bold 16px;"\
                                    "text-align : bottom;         "\
                                    "image: url(:/images/nofault.png);"\
                                    "image-position: top;"\
                                    "}");
        QPushButton *buttoninfo = new QPushButton(this);
        buttoninfo->setIcon(QIcon(":/images/info.png"));
        buttoninfo->setIconSize(QSize(80,40));
        buttoninfo->setFixedSize(120,90);
        layoutH->addWidget(label);
        layoutH->addWidget(customButton);
        layoutH->addWidget(button2);
        layoutH->addWidget(buttoninfo);
        layoutH->addStretch();

        layout->addLayout(layoutH);

        connect(buttoninfo,&QPushButton::clicked,[=](){
                clickECUInfo(m_ecusArray[loopIdx].toObject()["name"].toString());
         });
        loopIdx++;
    }
    layout->addStretch();

    ScroArea->setWidget(w);


}

void MainWindow::clickECUInfo(QString ECUName)
{

    QWidget *w = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(w);

    ui->stackedWidget->addWidget(w);
    QHBoxLayout *layoutH = new QHBoxLayout;
    QPushButton *buttoninfo = new QPushButton("模块信息",w);
    buttoninfo->setFixedSize(150,150);
    layoutH->addWidget(buttoninfo);
    QPushButton *buttonDTCinfo = new QPushButton("故障信息",w);
    buttonDTCinfo->setFixedSize(150,150);
    layoutH->addWidget(buttonDTCinfo);
    QPushButton *buttonDTCclear = new QPushButton("故障清除",w);
    buttonDTCclear->setFixedSize(150,150);
    layoutH->addWidget(buttonDTCclear);
    QPushButton *buttondata = new QPushButton("数据流采集",w);
    buttondata->setFixedSize(150,150);
    layoutH->addWidget(buttondata);
    layoutH->addStretch();
    layout->addLayout(layoutH);
    QHBoxLayout *layout2 = new QHBoxLayout;
    QPushButton *buttonupdateLog = new QPushButton("升级记录",w);
    buttonupdateLog->setFixedSize(150,150);
    layout2->addWidget(buttonupdateLog);
    layout2->addStretch();
    layout->addLayout(layout2);
    layout->addStretch();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    connect(buttoninfo,&QPushButton::clicked,[=]()
    {
        //读取版本信息
        QJsonArray seq;
        QJsonObject json;
        uint8_t loopIdx = 0;
        while(loopIdx < m_ecusArray.size())
        {
            if(m_ecusArray[loopIdx].toObject()["name"].toString() == ECUName)
            {
                json = m_ecusArray[loopIdx].toObject();
                break;
            }
            loopIdx++;
        }
        seq.append("phyRequest;10 01;50 01");
        seq.append("readVersionASCII;22 F1 89;62 F1 89");
        json.insert("sequence",QJsonValue(seq));
        QJsonDocument doc(json);
//        ui->text_output_2->append(doc.toJson(QJsonDocument::Indented));
//        mq->sendMqttMsg("versionInfoReq",doc.toJson(QJsonDocument::Indented));
        QWidget *w = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(w);
        ui->stackedWidget->addWidget(w);
        QTextEdit *textedit = new QTextEdit(w);
        textedit->setFixedSize(1080,610);
        textedit->append(QString("版本信息管理"));
        layout->addWidget(textedit);
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    });
    connect(buttonDTCinfo,&QPushButton::clicked,[=]()
    {
        //读取DTC
    });
    connect(buttonDTCclear,&QPushButton::clicked,[=]()
    {
        //清除DTC
    });
    connect(buttondata,&QPushButton::clicked,[=]()
    {
        //报文数据采集
    });
    connect(buttonupdateLog,&QPushButton::clicked,[=]()
    {
        //升级日志
    });

}

void MainWindow::on_Btn_StackFlashTool_clicked()
{
    QWidget *w = new QWidget;
    QHBoxLayout *LAYOUTFlash = new QHBoxLayout(w);
    QVBoxLayout *LAYOUT = new QVBoxLayout;
//刷写配置
    QHBoxLayout *layout = new QHBoxLayout;
    QGroupBox *groupBox_Conf = new QGroupBox("刷写配置",w);
    groupBox_Conf->setFixedSize(220,200);
    layout->addWidget(groupBox_Conf);
    QHBoxLayout *layoutH = new QHBoxLayout;
    QVBoxLayout *layoutConfg = new QVBoxLayout(groupBox_Conf);
    layoutH->addStretch(4);
    QLabel *label1 = new QLabel("PhyRequest ",groupBox_Conf);
    layoutH->addWidget(label1);
    QLineEdit *line_PhyReq = new QLineEdit(this);
    layoutH->addWidget(line_PhyReq);
    layoutConfg->addLayout(layoutH);

    QHBoxLayout *layoutH1 = new QHBoxLayout;
    layoutH1->addStretch(1);
    QLabel *label2 = new QLabel("PhyResponse ",groupBox_Conf);
    layoutH1->addWidget(label2);
    QLineEdit *line_PhyResp = new QLineEdit(groupBox_Conf);
    line_PhyResp->installEventFilter(groupBox_Conf);
    layoutH1->addWidget(line_PhyResp);
    layoutConfg->addLayout(layoutH1);

    QHBoxLayout *layoutH2 = new QHBoxLayout;
    layoutH2->addStretch(1);
    QLabel *label3 = new QLabel("FunRequest ",groupBox_Conf);
    layoutH2->addWidget(label3);
    QLineEdit *line_funReq = new QLineEdit(groupBox_Conf);
    line_funReq->installEventFilter(groupBox_Conf);
    layoutH2->addWidget(line_funReq);
    layoutConfg->addLayout(layoutH2);

    QHBoxLayout *layoutH3 = new QHBoxLayout;
    layoutH3->addStretch(2);
    QLabel *label4 = new QLabel("CAN/CANFD ",groupBox_Conf);
    layoutH3->addWidget(label4);
    QComboBox *combox_CAN = new QComboBox(groupBox_Conf);
    combox_CAN->addItem("CAN");
    combox_CAN->addItem("CANFD");
    layoutH3->addWidget(combox_CAN);
    layoutConfg->addLayout(layoutH3);

    QHBoxLayout *layoutH4 = new QHBoxLayout;
    QLabel *label5 = new QLabel("DeviceType ",groupBox_Conf);
    layoutH4->addWidget(label5);
    QComboBox *channel = new QComboBox(groupBox_Conf);
    layoutH4->addWidget(channel);
    layoutConfg->addLayout(layoutH4);

//网络管理报文发送
    QGroupBox *groupBox_network = new QGroupBox("网络管理报文发送",w);
    groupBox_network->setFixedSize(430,150);
    layout->addWidget(groupBox_network);
    LAYOUT->addLayout(layout);

//连接、断开连接、刷新按键
    QVBoxLayout *layoutConnect = new QVBoxLayout;
    QPushButton *connectBtn = new QPushButton("连接",w);
    layoutConnect->addWidget(connectBtn);
    QPushButton *disconnect = new QPushButton("断开连接",w);
    layoutConnect->addWidget(disconnect);
    QPushButton* fresh = new QPushButton(w);
    fresh->setText("刷新");
    layoutConnect->addWidget(fresh);
    layout->addLayout(layoutConnect);
    layout->addStretch();

//刷写文件加载
    QTableWidget *tablewidget = new QTableWidget(w);
    tablewidget->setFixedSize(760,350);
    tablewidget->setColumnCount(4);
    tablewidget->setColumnWidth(0,380);
    tablewidget->setHorizontalHeaderLabels({"FileName","StartAddress","EndAddress","FileSize"});
    tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    LAYOUT->addWidget(tablewidget);

//文件添加、开始刷写、停止刷写按键
    QHBoxLayout *layoutButton = new QHBoxLayout;
    layoutButton->addStretch();
    QPushButton *stop = new QPushButton("stop",w);
    layoutButton->addWidget(stop);
    QPushButton *start = new QPushButton("start",w);
    layoutButton->addWidget(start);
    QPushButton *addfile = new QPushButton("Add File",w);
    layoutButton->addWidget(addfile);
    layoutButton->addStretch();

    LAYOUT->addLayout(layoutButton);

    LAYOUTFlash->addLayout(LAYOUT);
//刷写流程显示
    QTextEdit *textDisplay = new QTextEdit(w);
    LAYOUTFlash->addWidget(textDisplay);

    CANFlashChannelGet(textDisplay,channel);
    ui->stackedWidget->addWidget(w);
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);

    line_PhyReq->setText("7E0");
    line_PhyResp->setText("7E8");
    line_funReq->setText("7DF");

    connect(fresh,&QPushButton::clicked,[=](){
        CANFlashChannelGet_BtnFresh(textDisplay,channel);
    });

    connect(addfile,&QPushButton::clicked,[=](){
        CANFlashFile_Add(textDisplay,tablewidget);
    });

    connect(connectBtn,&QPushButton::clicked,[=](){
        CANFlash_ConnectCAN(textDisplay,channel,combox_CAN,
                       line_PhyReq,line_PhyResp,
                       connectBtn,disconnect,addfile);
    });

    connect(disconnect,&QPushButton::clicked,[=](){
        CANFlash_disConnectCAN(textDisplay,channel,connectBtn,disconnect);
    });
}

XLstatus MainWindow::CANFlashChannelGet(QTextEdit *textDisplay,QComboBox *combox)
{
    XLstatus          xlStatus;
    xlStatus = xlOpenDriver ();

    if(XL_SUCCESS == xlStatus) {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus)
    {
        unsigned int i;
        char         str[100];

        textDisplay->append("\t\t--------------------------------------");
        textDisplay->append(QString("\t- %1 channels Hardware Configuration -").arg(g_xlDrvConfig.channelCount));
        textDisplay->append("\t\t---------------------------------------");

        for (i=0; i < g_xlDrvConfig.channelCount; i++)
        {
            textDisplay->append(QString("\t-Ch:%1,CM:0x%2,%3").arg(g_xlDrvConfig.channel[i].channelIndex,2,10,QChar('0'))
                                    .arg(g_xlDrvConfig.channel[i].channelMask,3,16,QChar('0'))
                                    .arg(g_xlDrvConfig.channel[i].name));
            combox->addItem(g_xlDrvConfig.channel[i].name);
            std::cout << ("- Ch:%02d, CM:0x%03I64x,",
            g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

          strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
          std::cout << (" %23s,", str);

          memset(str, 0, sizeof(str));

          if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
            strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
            std::cout << ("%13s -\n", str);
          }
          else std::cout << ("    no Cab!   -\n");


        }

        std::cout << ("----------------------------------------------------------\n\n");
    }
    return xlStatus;
}

XLstatus MainWindow::CANFlashChannelGet_BtnFresh(QTextEdit *textDisplay,QComboBox *combox)
{
    XLstatus          xlStatus;

    if(XL_SUCCESS == xlStatus) {
      xlStatus = xlGetDriverConfig(&g_xlDrvConfig);
    }

    if(XL_SUCCESS == xlStatus)
    {
        unsigned int i;
        char         str[100];

        textDisplay->append("\t\t----------------------------------------------------------");
        textDisplay->append(QString("\t\t- %1 channels       Hardware Configuration               -").arg(g_xlDrvConfig.channelCount));
        textDisplay->append("\t\t----------------------------------------------------------");

        for (i=0; i < g_xlDrvConfig.channelCount; i++)
        {
            if(g_xlDrvConfig.channel[i].isOnBus == 0)
            {
                textDisplay->append(QString("\t\t-Ch:%1,CM:0x%2,%3").arg(g_xlDrvConfig.channel[i].channelIndex,2,10,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].channelMask,3,16,QChar('0'))
                                        .arg(g_xlDrvConfig.channel[i].name));
                combox->addItem(g_xlDrvConfig.channel[i].name);
              std::cout << ("- Ch:%02d, CM:0x%03I64x,",
                g_xlDrvConfig.channel[i].channelIndex, g_xlDrvConfig.channel[i].channelMask);

              strncpy_s(str, 100, g_xlDrvConfig.channel[i].name, 23);
              std::cout << (" %23s,", str);

              memset(str, 0, sizeof(str));

              if (g_xlDrvConfig.channel[i].transceiverType != XL_TRANSCEIVER_TYPE_NONE) {
                strncpy_s( str, 100, g_xlDrvConfig.channel[i].transceiverName, 13);
                std::cout << ("%13s -\n", str);
              }
              else std::cout << ("    no Cab!   -\n");
            }

        }

        std::cout << ("----------------------------------------------------------\n\n");
    }
    return xlStatus;
}

void MainWindow::CANFlashFile_Add(QTextEdit *textDisplay,QTableWidget* tableWidget)
{
    if(lastFilePath.isEmpty())
        lastFilePath = QDir::homePath();
    QString filePath = QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"),
                                                    lastFilePath, QObject::tr("All Files (*)"));

    if(!filePath.isEmpty())
    {
        QString Info;
        if(filePath.toLower().contains(".hex"))
        {
            if(!(Info = CANFlashFile_Parse(filePath.toStdString().c_str(),textDisplay,tableWidget)).isEmpty())
            {
                textDisplay->append(filePath + " loaded sucessfully");
                filePath += Info;
            }
            else
            {
                textDisplay->append( filePath + "loaded failed,please check the file");
                return;
            }

        }
        else if(filePath.contains(".bin"))
        {
            QFileInfo fileInfo(filePath);
            tableWidget->insertRow(tableWidget->rowCount());
            tableWidget->setItem(rowIndex,0,new QTableWidgetItem(filePath));

            tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(fileInfo.size(),8,16,QLatin1Char('0')).toUpper()));

            tableWidget->item(rowIndex,0)->setFlags(tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
            tableWidget->item(rowIndex,3)->setFlags(tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);
            textDisplay->append(filePath + " loaded sucessfully");
            rowIndex++;
        }
        QFileInfo fileInfo(filePath);
        lastFilePath = fileInfo.absolutePath();
    }
    else
    {
         textDisplay->append(filePath + "loaded failed,please check the path");
    }
}

QString MainWindow::CANFlashFile_Parse(const char* rpath,QTextEdit *textDisplay,QTableWidget* tableWidget)
{
    IHexResult result;
    IHexRecord record;

    ConvertContext ctx;
    InitContext(&ctx);
    QString info = "";
    uint32_t currentDataFileAddr = 0;
    uint32_t endDataFileAddr = 0;
    int blockIndex = 1;
    uint8_t loopIndex = tableWidget->rowCount();
    if (NULL == (ctx.rfile = fopen(rpath, "r")))
    {
        ExitApplication(&ctx, STRING_OPEN_FILEERROR, rpath);
        return info;

    }

    if (NULL == (ctx.strbuff = (char*)malloc(IHEX_STRING_BUFF_SIZE)) ||
        NULL == (ctx.binbuff = (uint8_t*)malloc(IHEX_MAX_BINDATA_NUM)))
    {
        ExitApplication(&ctx, STRING_MALLO_MEMERROR);
        return info;
    }


    uint32_t startaddress = 0;
    IHex_InitRecord(&record, ctx.binbuff);
    for (int clen = 0;;)
    {
        if (NULL == fgets(ctx.strbuff, IHEX_RECORD_STR_LEN, ctx.rfile))
        {
            ExitApplication(&ctx, STRING_READ_ERROREND);
            return info;
        }

        ++clen;
        if (CheckSpaceLine(ctx.strbuff))       // 空行
            continue;

        result = IHex_GetNextHeadInfo(&record, ctx.strbuff);
        if(record.type == IHEX_TYPE_DATARECORD)
        {
            if((currentDataFileAddr != record.fileAddr) && (clen >2))
            {
                tableWidget->insertRow(tableWidget->rowCount());
                tableWidget->setItem(rowIndex,0,new QTableWidgetItem(QString::fromLocal8Bit(rpath)));
                tableWidget->setItem(rowIndex,1,new QTableWidgetItem(QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper()));
                tableWidget->setItem(rowIndex,2,new QTableWidgetItem(QString("%1").arg(endDataFileAddr,8,16,QLatin1Char('0')).toUpper()));
                tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(endDataFileAddr - record.minAddr + 1,8,16,QLatin1Char('0')).toUpper()));

                tableWidget->item(rowIndex,0)->setFlags(tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
                tableWidget->item(rowIndex,1)->setFlags(tableWidget->item(rowIndex,1)->flags() & ~Qt::ItemIsEditable);
                tableWidget->item(rowIndex,2)->setFlags(tableWidget->item(rowIndex,2)->flags() & ~Qt::ItemIsEditable);
                tableWidget->item(rowIndex,3)->setFlags(tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);

                textDisplay->append(QString("文件:\"%1(block%2)\" 读取成功\r\n").arg(rpath).arg(QString::number(blockIndex,10)));
                textDisplay->append(QString("\t\t  文件记录数据范围为:0x%1 - 0x%2\r\n").arg(QString::number(record.minAddr,16).toUpper()).arg(QString::number(endDataFileAddr,16).toUpper()));
                textDisplay->append(QString("\t\t  共: %1 字节数据 %2 行\r\n").arg(QString::number(endDataFileAddr - record.minAddr + 1,10)).arg(QString::number(clen,10)));


                record.minAddr = record.maxAddr - record.count + 1;
                rowIndex++;
                blockIndex++;

            }
            currentDataFileAddr = record.fileAddr + record.count;
            endDataFileAddr = record.maxAddr;

        }

        if (IHEX_RESULT_NOERROR != result)
        {
            ExitApplication(&ctx, STRING_FILE_ERROR, result, clen);
            return info;
        }
        else if (record.type == IHEX_TYPE_STARTADDRESS)
        {
            startaddress = record.fileAddr;
        }
        else if (record.type == IHEX_TYPE_ENDFILE)
        {
            tableWidget->insertRow(tableWidget->rowCount());
            tableWidget->setItem(rowIndex,0,new QTableWidgetItem(QString::fromLocal8Bit(rpath)));
            tableWidget->setItem(rowIndex,1,new QTableWidgetItem(QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper()));
            tableWidget->setItem(rowIndex,2,new QTableWidgetItem(QString("%1").arg(record.maxAddr,8,16,QLatin1Char('0')).toUpper()));
            tableWidget->setItem(rowIndex,3,new QTableWidgetItem(QString("%1").arg(record.maxAddr - record.minAddr + 1,8,16,QLatin1Char('0')).toUpper()));

            tableWidget->item(rowIndex,0)->setFlags(tableWidget->item(rowIndex,0)->flags() & ~Qt::ItemIsEditable);
            tableWidget->item(rowIndex,1)->setFlags(tableWidget->item(rowIndex,1)->flags() & ~Qt::ItemIsEditable);
            tableWidget->item(rowIndex,2)->setFlags(tableWidget->item(rowIndex,2)->flags() & ~Qt::ItemIsEditable);
            tableWidget->item(rowIndex,3)->setFlags(tableWidget->item(rowIndex,3)->flags() & ~Qt::ItemIsEditable);

            rowIndex++;
            textDisplay->append(QString("文件:\"%1(block%2)\" 读取成功\r\n").arg(rpath).arg(QString::number(blockIndex,10)));
            textDisplay->append(QString("\t\t  文件记录数据范围为:0x%1 - 0x%2\r\n").arg(QString::number(record.minAddr,16).toUpper()).arg(QString::number(record.maxAddr,16).toUpper()));
            textDisplay->append(QString("\t\t  共: %1 字节数据 %2 行\r\n").arg(QString::number(record.maxAddr- record.minAddr + 1,10)).arg(QString::number(clen,10)));
            if (startaddress)
                textDisplay->append(QString("\t\t  起始地址为：0x%1\r\n").arg(QString::number(startaddress,16).toUpper()));
            info = " | " + QString("%1").arg(record.minAddr,8,16,QLatin1Char('0')).toUpper() + " | " +  QString("%1").arg(record.maxAddr- record.minAddr,8,16,QLatin1Char('0')).toUpper();
            break;
        }
    }

    while(loopIndex < rowIndex)
    {
        tableWidget->setItem(loopIndex,2,new QTableWidgetItem(QString("%1").arg(record.maxAddr,8,16,QLatin1Char('0')).toUpper()));
        loopIndex++;
    }
    ExitApplication(&ctx,"Success");

    return info;
}

void MainWindow::CANFlash_ConnectCAN(
        QTextEdit *textDisplay,QComboBox *combox_devicetype,QComboBox *combox_canType,
        QLineEdit *phyReq,QLineEdit *phyResp,
        QPushButton *connectBtn,QPushButton *disconnectBtn,QPushButton *addfileBtn)
{
    TPCANStatus status = PCAN_ERROR_OK;
    QString dataflowPath = QCoreApplication::applicationDirPath() + "/Conf";
    if(combox_devicetype->currentText() == "PCAN")
    {
        status = CAN_Initialize(PCAN_USBBUS1,PCAN_BAUD_500K);
        if(status == PCAN_ERROR_OK)
        {
            DISPLAY_OUTPUT("PCAN Device Connected");
            if(ui->checkBox->checkState() == Qt::CheckState::Checked)
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),0);
            }
            else
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),1);
            }
            connectBtn->setEnabled(false);
            disconnectBtn->setEnabled(true);
            addfileBtn->setEnabled(true);
            tool = 0;
        }
        else
        {
            textDisplay->append("Check your PCAN Device");
        }
    }
    //else if(ui->comboBox->currentText() == "Vector")
    {
        XLstatus      xlStatus;
        unsigned int  xlChanIndex = 0;
        xlStatus = InitDriver(&xlChanIndex,combox_devicetype->currentIndex());
        textDisplay->append("- Init             : " + QString(xlGetErrorString(xlStatus)));
        if(XL_SUCCESS == xlStatus)
        {
            if(ui->checkBox->checkState() == Qt::CheckState::Checked)
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),0);
            }
            else
            {
                sequence = parseSequence(dataflowPath.toLatin1().data(),1);
            }

            textDisplay->append("Vector Device Connected");
            connectBtn->setEnabled(false);
            disconnectBtn->setEnabled(true);
            addfileBtn->setEnabled(true);
            tool = 1;
            CANFlashChannelGet_BtnFresh(textDisplay,combox_devicetype);
        }
        else
            return;
    }

    dataflowPath = QCoreApplication::applicationDirPath() + "/Conf";
    sequence = parseSequence(dataflowPath.toLatin1().data(),1);
    sequence.requestID = phyReq->text().toUInt(nullptr,16);
    sequence.responseID = phyResp->text().toUInt(nullptr,16);
    sequence.cantype = combox_canType->currentIndex();
    flashobj = new  flash(sequence);
    flashobj->initCANTP();
    _workerThread= new QThread(this);
    flashobj->moveToThread(_workerThread);
    connect(this, &MainWindow::startFlash,flashobj, &flash::testquenceList);
    connect(flashobj,&flash::emitString,this,&MainWindow::displayString);
    connect(flashobj,&flash::emitStop,this,&MainWindow::deletethread);
    connect(flashobj,&flash::emitDataSize,this,&MainWindow::displayProgress);
}

void MainWindow::CANFlash_disConnectCAN(
        QTextEdit *textDisplay,QComboBox *combox_devicetype,
        QPushButton *connectBtn,QPushButton *disconnectBtn)
{
    if(combox_devicetype->currentText() == "PCAN")
    {
        TPCANStatus status = PCAN_ERROR_OK;
        status = CAN_Uninitialize(PCAN_USBBUS1);
        if(status == PCAN_ERROR_OK)
        {
            textDisplay->append("PCAN Device disconnected");
            connectBtn->setEnabled(true);
            disconnectBtn->setEnabled(false);
        }
        else
        {
            textDisplay->append("Check your PCAN Device");
        }
    }
    cleanUpDriver();
    textDisplay->append("Vector Device disconnected");
//     else if(ui->comboBox->currentText() == "Vector")
//     {
//         cleanUpDriver();
//         DISPLAY_OUTPUT("Vector Device disconnected");
//     }
    connectBtn->setEnabled(true);
    disconnectBtn->setEnabled(false);
//     delete msg;
//     delete msg_channle;
}

void MainWindow::on_Btn_StackDiagnosticFunc_clicked()
{
    QWidget *w = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(w);

    ui->stackedWidget->addWidget(w);
    QHBoxLayout *layoutH = new QHBoxLayout;
    QPushButton *buttonEOL = new QPushButton("EOL",w);
    buttonEOL->setFixedSize(200,200);
    layoutH->addWidget(buttonEOL);
    QPushButton *buttonRevokeBLE = new QPushButton("吊销蓝牙钥匙",w);
    buttonRevokeBLE->setFixedSize(200,200);
    layoutH->addWidget(buttonRevokeBLE);
    QPushButton *buttonOpenBLE = new QPushButton("开通蓝牙钥匙",w);
    buttonOpenBLE->setFixedSize(200,200);
    layoutH->addWidget(buttonOpenBLE);
    QPushButton *buttonCali = new QPushButton("标定",w);
    buttonCali->setFixedSize(200,200);
    layoutH->addWidget(buttonCali);
    QPushButton *buttonupdateLog = new QPushButton("升级记录",w);
    buttonupdateLog->setFixedSize(200,200);
    layoutH->addWidget(buttonupdateLog);
    layoutH->addStretch();
    layout->addLayout(layoutH);
//    QHBoxLayout *layout2 = new QHBoxLayout;
//    layout2->addWidget(buttonupdateLog);
//    layout2->addStretch();
//    layout->addLayout(layout2);
    layout->addStretch();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);

    connect(buttonEOL,&QPushButton::clicked,[=]()
    {
        //车辆EOL
    });
    connect(buttonRevokeBLE,&QPushButton::clicked,[=]()
    {
        //注销蓝牙钥匙
    });
    connect(buttonOpenBLE,&QPushButton::clicked,[=]()
    {
        //开通蓝牙钥匙
    });
    connect(buttonCali,&QPushButton::clicked,[=]()
    {
        //ECU 标定
    });
    connect(buttonupdateLog,&QPushButton::clicked,[=]()
    {
        //升级日志
    });
}
