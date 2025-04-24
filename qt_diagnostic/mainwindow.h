#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "odx/load_odx_d.h"
#include <QStandardItemModel>
#include <QList>
#include <QVector>
#include <QInputDialog>
#include "mainDiag.h"
#include <QCompleter>
#include "otx/otx.h"
#include "otx/flowchart.h"
#include <QHash>
#include <QMessageBox>
#include "dialog.h"
#include "choicedialog.h"
#include "conditiondialog.h"
#include "inputdialog.h"
#include <QInputDialog>
#include "diagTP/vectorCan.h"
#include "flash/flash.h"
#include <QThread>
#include "activeMsg/activemsg.h"
#include "mqtt/mqttclient.h"
#include "httpsclient/httpsclient.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QComboBox>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MainWindow(QWidget *parent = nullptr);

    static MainWindow *m_pInstance;

public:
    static MainWindow* GetInstance();

    void setDateTime();

    void createTaskJson(QString jsonDir);

    void createDataflowJson(QString jsonDir,QString filename);

    QString creatDir(QString dirName);

    virtual void call_cpp_class_add(char *msg1,unsigned char *msg2,uint8_t len);

    virtual void call_cpp_class_show(int,int);

    void parseODX(QString fileName);

    void receiveTreeNode(QString nodeName,QString subName,QString description);

    void InsertFirstNode(QString nodeName);

    void InsertWait();

    XLstatus getCANoeConfig();

    XLstatus getCANoeConfigAva();

    bool eventFilter(QObject *obj,QEvent *event);

    QString getHexInfo(const char* rpath);

    void initMQTTUI();

    void initToolBar();

    void clickECUInfo(QString ECUName);

    XLstatus CANFlashChannelGet(QTextEdit *textDisplay,QComboBox *combox);

    XLstatus CANFlashChannelGet_BtnFresh(QTextEdit *textDisplay,QComboBox *combox);

    QString CANFlashFile_Parse(const char* rpath,QTextEdit *textDisplay,QTableWidget* tableWidget);

    void CANFlashFile_Add(QTextEdit *textDisplay,QTableWidget* tableWidget);

    void CANFlash_ConnectCAN(
            QTextEdit *textDisplay,QComboBox *combox_devicetype,QComboBox *combox_canType,
            QLineEdit *phyReq,QLineEdit *phyResp,
            QPushButton *connectBtn,QPushButton *disconnectBtn,QPushButton *addfileBtn);

    void CANFlash_disConnectCAN(
            QTextEdit *textDisplay,QComboBox *combox_devicetype,
            QPushButton *connectBtn,QPushButton *disconnectBtn);

    ~MainWindow();

signals:
    void sendMessage(QString);

    void sendCount(int,int);

    void sendJson(QString);

    void sendJsonotx(QString);

    void sendODX(ECU_SERVICE ecu);

    void startFlash(LinkedList *path);

    void startsignal();

    void startsignal_c();

public slots:
    void recieveMsg(QString strMsg);

    void recieveCount(int,int);

    void receiveJson(QString strMsg);

    void receiveJsonotx(QString strMsg);

    void deletethread();

    void displayString(QString str);

private slots:
    void displayProgress(u_int64 data);

    void on_pushButton_clicked();

    void on_Btn_File_clicked();

    void on_Btn_File_4_clicked();

    void on_Btn_File_5_clicked();

    void on_Btn_save_clicked();

    void on_treeWidget_doubleClicked(const QModelIndex &index);

    void on_Btn_clear_clicked();

    void on_Btn_update_clicked();

    void on_line_taskID_textChanged(const QString &arg1);

    void on_line_taskID_editingFinished();

    void on_Btn_File_otx_clicked();

    void on_Btn_File_parseotx_clicked();

    void on_treeWidget_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_2_clicked();

    void on_chart_rect_customContextMenuRequested(const QPoint &pos);

    void on_Btn_ChoiceECU_clicked();

    void on_Btn_Connect_clicked();


    void on_Btn_Fresh_clicked();

    void on_Btn_FileDiaglog_clicked();

    void on_Btn_StartDiag_clicked();

    void on_Btn_Send_clicked();

    void on_Btn_disConnect_clicked();

    void on_Btn_Start_clicked();

    void on_Btn_FIle_clicked();

    void on_Btn_StopFlash_clicked();

    void on_Btn_Save_clicked();

    void on_Btn_ConnectMqtt_clicked();

    void on_Btn_disConnectMqtt_clicked();

    void on_Btn_SendMqtt_clicked();

    void on_Btn_getVersion_clicked();

    void on_Btn_FileDiaglogMqtt_clicked();

    void on_Btn_SendMqttScript_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_Btn_ReadVersion_clicked();

    void on_Btn_EOL_clicked();
    
    void on_Btn_StackVersion_clicked();

    void on_Btn_StackFlashTool_clicked();

    void on_Btn_StackDiagnosticFunc_clicked();

public:
    Ui::MainWindow *ui;

    QJsonObject mDataSeq;

    QJsonArray mSequences;

    int isRuntime;

    QHash<QString,QString> mODXDataMatch;

    ECU_VARIANT ecu;

    ECU_SERVICE ecu_service;

    QMenu *popMenu;

    struct DiagnosticSeqence sequence;

    flash *flashobj;

    QThread *_workerThread;

    LinkedList linklist;

    int maxProgress;

    int rowIndex;

    activeMsg *msg;

    QThread *msgThread;

    activeMsg *msg_channle;

    QThread *msgThread_channle;

    mqttClient *mq;

    QJsonArray m_ecusArray;

    HttpsClient *mHttpsClient;

    QString lastFilePath;

    QToolBar* m_Toolbar;
    QAction* actionHome;
    QAction* actionNetwork;
    QAction* actionReturn;
    QAction* actionFresh;
    QLabel *lbl;
    QList<QPushButton*> btnECUInfo;
//    QPushButton *button1;

 class CustomButton : public QPushButton {
    public:
        CustomButton(QString name,QString version1,QString version2,QWidget* parent = nullptr) : QPushButton(parent) {
            // 创建主布局
//            setStyleSheet("border: none; padding: 5px;");
            QVBoxLayout* mainLayout = new QVBoxLayout(this);
            mainLayout->setSpacing(0);
            // 第一行布局
            QHBoxLayout* firstRowLayout = new QHBoxLayout();
            QLabel* firstImageLabel = new QLabel();
            firstImageLabel->setPixmap(QPixmap(":/images/DU.png").scaled(40, 40, Qt::KeepAspectRatio)); // 替换为真实路径
            QLabel* firstTextLabel = new QLabel(name);
            firstRowLayout->addWidget(firstImageLabel);
            firstRowLayout->addWidget(firstTextLabel);
            firstRowLayout->addStretch();
            // 第二行布局
            QHBoxLayout* secondRowLayout = new QHBoxLayout();
            QLabel* secondImageLabelLeft = new QLabel();
            secondImageLabelLeft->setPixmap(QPixmap(":/images/version2.png").scaled(32, 32, Qt::KeepAspectRatio)); // 替换为真实路径
            QLabel* secondTextLabelLeft = new QLabel();
            if(!version1.isEmpty())
            {
                secondTextLabelLeft->setText(version1);
            }
            else
            {
                secondTextLabelLeft->setText("消极应答");
            }

            QLabel* secondImageLabelRight = new QLabel();
            secondImageLabelRight->setPixmap(QPixmap(":/images/version1.png").scaled(32, 32, Qt::KeepAspectRatio));
            QLabel* secondTextLabelRight = new QLabel();
            if(!version2.isEmpty())
            {
                secondTextLabelRight->setText(version2);
            }
            else
            {
                secondTextLabelRight->setText("消极应答");
            }


            secondRowLayout->addWidget(secondImageLabelLeft);
            secondRowLayout->setSpacing(0);
            secondRowLayout->addWidget(secondTextLabelLeft);
            secondRowLayout->addStretch();

            secondRowLayout->addWidget(secondImageLabelRight);
            secondRowLayout->setSpacing(0);
            secondRowLayout->addWidget(secondTextLabelRight);
            secondRowLayout->addStretch(); // 添加弹性空间
            // 将行布局添加到主布局
            mainLayout->addLayout(firstRowLayout);
            mainLayout->addLayout(secondRowLayout);

            // 设置布局
            setLayout(mainLayout);
//            adjustSize();
            setFixedSize(620, 90);
//            this->setStyleSheet("QPushButton{ border:none;}");
        }
    };

};





#endif // MAINWINDOW_H
