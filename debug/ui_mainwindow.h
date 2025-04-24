/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <otx/flowchart.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QTextEdit *text_output;
    QGroupBox *groupBox;
    QLineEdit *line_period_4;
    QLineEdit *lineEdit_4;
    QDateTimeEdit *dateTime_StartTime;
    QLineEdit *lineEdit_7;
    QDateTimeEdit *dateTime_EndTime;
    QLineEdit *lineEdit;
    QLabel *label;
    QLineEdit *line_period;
    QLineEdit *lineEdit_2;
    QLineEdit *line_period_2;
    QLineEdit *lineEdit_5;
    QLineEdit *line_taskID;
    QLineEdit *line_period_3;
    QPushButton *pushButton;
    QPushButton *Btn_File;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_6;
    QLineEdit *line_FilePath;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QPushButton *Btn_update;
    QTextEdit *text_json;
    QGroupBox *groupBox_2;
    QRadioButton *tasktyperuntime;
    QRadioButton *tasktypeperiod;
    QWidget *tab_4;
    QTreeWidget *treeWidget;
    QPushButton *Btn_File_4;
    QLineEdit *line_FilePath_3;
    QPushButton *Btn_File_5;
    QTextEdit *txt_diagscript;
    QLabel *label_2;
    QPushButton *Btn_save;
    QPushButton *Btn_clear;
    QWidget *tab;
    QPushButton *Btn_File_otx;
    QLineEdit *line_otx_filePath;
    QPushButton *Btn_File_parseotx;
    QScrollArea *scrollArea_Painter;
    QWidget *scrollAreaWidgetContents_main;
    QGridLayout *gridLayout_2;
    FlowChart *flowChart_widget;
    QTextEdit *txt_diagscript_otx;
    QScrollArea *scrollArea_GraphSelect;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *chart_ellipse;
    QPushButton *chart_roundrect;
    QPushButton *chart_diam;
    QPushButton *chart_rect;
    QPushButton *chart_trapezoid;
    QPushButton *chart_line;
    QGroupBox *groupBox_4;
    QPushButton *Btn_ChoiceECU;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_2;
    QWidget *tab_5;
    QPushButton *Btn_Save;
    QPushButton *Btn_FIle;
    QPushButton *Btn_StopFlash;
    QPushButton *Btn_Start;
    QPushButton *Btn_disConnect;
    QTextEdit *text_output_2;
    QTableWidget *tableWidget;
    QProgressBar *progressBar;
    QPushButton *Btn_Clearlog;
    QGroupBox *groupBox_6;
    QComboBox *comboBox_2;
    QPushButton *pushButton_3;
    QFrame *frame;
    QPushButton *pushButton_4;
    QLineEdit *MsgData1;
    QLineEdit *MsgData2;
    QLineEdit *MsgData3;
    QLineEdit *MsgData4;
    QLineEdit *MsgData5;
    QLineEdit *MsgData6;
    QLineEdit *MsgData7;
    QLineEdit *MsgData8;
    QLineEdit *Message_ID;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox_7;
    QLabel *label_7;
    QComboBox *comboBox;
    QLineEdit *txt_funReq;
    QCheckBox *checkBox;
    QComboBox *comboBox_4;
    QLabel *label_4;
    QLineEdit *txt_PhyReq;
    QLabel *label_8;
    QLineEdit *txt_phyRes;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *Btn_Fresh;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit_12;
    QLabel *label_3;
    QPushButton *Btn_Connect;
    QGroupBox *groupBox_8;
    QPushButton *Btn_ConnectMqtt;
    QPushButton *Btn_disConnectMqtt;
    QLineEdit *SendData_mqtt;
    QPushButton *Btn_SendMqtt;
    QPushButton *Btn_getVersion;
    QComboBox *comboBox_ECU;
    QLineEdit *SendData_mqttPath;
    QPushButton *Btn_FileDiaglogMqtt;
    QPushButton *Btn_SendMqttScript;
    QPushButton *Btn_EOL;
    QPushButton *Btn_AfterSale;
    QGroupBox *groupBox_9;
    QLineEdit *lineEdit_DiagConf;
    QPushButton *Btn_StartDiag;
    QPushButton *Btn_FileDiaglog;
    QPushButton *Btn_Send;
    QLineEdit *SendData_Line;
    QPushButton *Btn_ReadVersion;
    QWidget *tab_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *Btn_StackFlashTool;
    QPushButton *Btn_StackTeleDiag;
    QPushButton *Btn_StackOTX;
    QPushButton *Btn_StackODX;
    QPushButton *Btn_StackVersion;
    QPushButton *Btn_StackDiagnosticFunc;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1995, 942);
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \345\256\213\344\275\223 Std L"));
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setEnabled(false);
        text_output = new QTextEdit(tab_3);
        text_output->setObjectName(QString::fromUtf8("text_output"));
        text_output->setGeometry(QRect(500, 10, 761, 761));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 80, 481, 311));
        line_period_4 = new QLineEdit(groupBox);
        line_period_4->setObjectName(QString::fromUtf8("line_period_4"));
        line_period_4->setGeometry(QRect(400, 240, 71, 27));
        line_period_4->setReadOnly(false);
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(0, 200, 71, 27));
        lineEdit_4->setReadOnly(true);
        dateTime_StartTime = new QDateTimeEdit(groupBox);
        dateTime_StartTime->setObjectName(QString::fromUtf8("dateTime_StartTime"));
        dateTime_StartTime->setGeometry(QRect(80, 120, 171, 28));
        dateTime_StartTime->setCalendarPopup(true);
        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(160, 240, 71, 27));
        lineEdit_7->setReadOnly(true);
        dateTime_EndTime = new QDateTimeEdit(groupBox);
        dateTime_EndTime->setObjectName(QString::fromUtf8("dateTime_EndTime"));
        dateTime_EndTime->setGeometry(QRect(80, 160, 171, 28));
        dateTime_EndTime->setTime(QTime(0, 0, 0));
        dateTime_EndTime->setCalendarPopup(true);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(0, 120, 71, 27));
        lineEdit->setReadOnly(true);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 210, 79, 19));
        line_period = new QLineEdit(groupBox);
        line_period->setObjectName(QString::fromUtf8("line_period"));
        line_period->setGeometry(QRect(80, 200, 71, 27));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(0, 160, 71, 27));
        lineEdit_2->setReadOnly(true);
        line_period_2 = new QLineEdit(groupBox);
        line_period_2->setObjectName(QString::fromUtf8("line_period_2"));
        line_period_2->setGeometry(QRect(80, 240, 71, 27));
        line_period_2->setReadOnly(false);
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(0, 80, 71, 27));
        lineEdit_5->setReadOnly(true);
        line_taskID = new QLineEdit(groupBox);
        line_taskID->setObjectName(QString::fromUtf8("line_taskID"));
        line_taskID->setGeometry(QRect(80, 80, 171, 27));
        line_period_3 = new QLineEdit(groupBox);
        line_period_3->setObjectName(QString::fromUtf8("line_period_3"));
        line_period_3->setGeometry(QRect(240, 240, 71, 27));
        line_period_3->setReadOnly(false);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 180, 201, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Adobe \345\256\213\344\275\223 Std L"));
        font1.setPointSize(27);
        pushButton->setFont(font1);
        Btn_File = new QPushButton(groupBox);
        Btn_File->setObjectName(QString::fromUtf8("Btn_File"));
        Btn_File->setGeometry(QRect(370, 40, 100, 27));
        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(320, 240, 71, 27));
        lineEdit_8->setReadOnly(true);
        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(0, 240, 71, 27));
        lineEdit_6->setReadOnly(true);
        line_FilePath = new QLineEdit(groupBox);
        line_FilePath->setObjectName(QString::fromUtf8("line_FilePath"));
        line_FilePath->setGeometry(QRect(0, 40, 351, 27));
        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(0, 280, 101, 27));
        lineEdit_9->setReadOnly(true);
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 280, 113, 27));
        lineEdit_10 = new QLineEdit(groupBox);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(240, 280, 101, 27));
        lineEdit_10->setReadOnly(true);
        lineEdit_11 = new QLineEdit(groupBox);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(360, 280, 113, 27));
        Btn_update = new QPushButton(groupBox);
        Btn_update->setObjectName(QString::fromUtf8("Btn_update"));
        Btn_update->setGeometry(QRect(270, 90, 201, 51));
        Btn_update->setFont(font1);
        text_json = new QTextEdit(tab_3);
        text_json->setObjectName(QString::fromUtf8("text_json"));
        text_json->setGeometry(QRect(10, 400, 481, 371));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 481, 71));
        tasktyperuntime = new QRadioButton(groupBox_2);
        tasktyperuntime->setObjectName(QString::fromUtf8("tasktyperuntime"));
        tasktyperuntime->setGeometry(QRect(10, 40, 124, 25));
        tasktypeperiod = new QRadioButton(groupBox_2);
        tasktypeperiod->setObjectName(QString::fromUtf8("tasktypeperiod"));
        tasktypeperiod->setGeometry(QRect(170, 40, 124, 25));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tab_4->setEnabled(false);
        treeWidget = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(10, 40, 801, 741));
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        Btn_File_4 = new QPushButton(tab_4);
        Btn_File_4->setObjectName(QString::fromUtf8("Btn_File_4"));
        Btn_File_4->setGeometry(QRect(730, 10, 81, 27));
        line_FilePath_3 = new QLineEdit(tab_4);
        line_FilePath_3->setObjectName(QString::fromUtf8("line_FilePath_3"));
        line_FilePath_3->setGeometry(QRect(10, 10, 591, 27));
        Btn_File_5 = new QPushButton(tab_4);
        Btn_File_5->setObjectName(QString::fromUtf8("Btn_File_5"));
        Btn_File_5->setGeometry(QRect(610, 10, 100, 27));
        txt_diagscript = new QTextEdit(tab_4);
        txt_diagscript->setObjectName(QString::fromUtf8("txt_diagscript"));
        txt_diagscript->setGeometry(QRect(820, 40, 451, 741));
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(820, 10, 121, 19));
        Btn_save = new QPushButton(tab_4);
        Btn_save->setObjectName(QString::fromUtf8("Btn_save"));
        Btn_save->setGeometry(QRect(1180, 10, 81, 27));
        Btn_clear = new QPushButton(tab_4);
        Btn_clear->setObjectName(QString::fromUtf8("Btn_clear"));
        Btn_clear->setGeometry(QRect(1090, 10, 81, 27));
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setEnabled(false);
        Btn_File_otx = new QPushButton(tab);
        Btn_File_otx->setObjectName(QString::fromUtf8("Btn_File_otx"));
        Btn_File_otx->setGeometry(QRect(610, 10, 100, 27));
        line_otx_filePath = new QLineEdit(tab);
        line_otx_filePath->setObjectName(QString::fromUtf8("line_otx_filePath"));
        line_otx_filePath->setGeometry(QRect(10, 10, 591, 27));
        Btn_File_parseotx = new QPushButton(tab);
        Btn_File_parseotx->setObjectName(QString::fromUtf8("Btn_File_parseotx"));
        Btn_File_parseotx->setGeometry(QRect(720, 10, 81, 27));
        Btn_File_parseotx->setContextMenuPolicy(Qt::CustomContextMenu);
        scrollArea_Painter = new QScrollArea(tab);
        scrollArea_Painter->setObjectName(QString::fromUtf8("scrollArea_Painter"));
        scrollArea_Painter->setEnabled(false);
        scrollArea_Painter->setGeometry(QRect(170, 50, 1171, 721));
        scrollArea_Painter->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_Painter->setWidgetResizable(true);
        scrollAreaWidgetContents_main = new QWidget();
        scrollAreaWidgetContents_main->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_main"));
        scrollAreaWidgetContents_main->setEnabled(false);
        scrollAreaWidgetContents_main->setGeometry(QRect(0, 0, 2018, 1018));
        scrollAreaWidgetContents_main->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_main);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        flowChart_widget = new FlowChart(scrollAreaWidgetContents_main);
        flowChart_widget->setObjectName(QString::fromUtf8("flowChart_widget"));
        flowChart_widget->setEnabled(false);
        flowChart_widget->setMinimumSize(QSize(2000, 1000));

        gridLayout_2->addWidget(flowChart_widget, 0, 0, 1, 1);

        scrollArea_Painter->setWidget(scrollAreaWidgetContents_main);
        txt_diagscript_otx = new QTextEdit(tab);
        txt_diagscript_otx->setObjectName(QString::fromUtf8("txt_diagscript_otx"));
        txt_diagscript_otx->setGeometry(QRect(1350, 30, 451, 741));
        scrollArea_GraphSelect = new QScrollArea(tab);
        scrollArea_GraphSelect->setObjectName(QString::fromUtf8("scrollArea_GraphSelect"));
        scrollArea_GraphSelect->setGeometry(QRect(10, 50, 150, 710));
        scrollArea_GraphSelect->setMinimumSize(QSize(150, 0));
        scrollArea_GraphSelect->setMaximumSize(QSize(150, 16777215));
        scrollArea_GraphSelect->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 127, 881));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(100, 0));
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        chart_ellipse = new QPushButton(groupBox_3);
        chart_ellipse->setObjectName(QString::fromUtf8("chart_ellipse"));
        chart_ellipse->setMinimumSize(QSize(34, 34));
        chart_ellipse->setMaximumSize(QSize(34, 34));
        chart_ellipse->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/Round.png);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/images/img/Round.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_ellipse->setIcon(icon);

        gridLayout_3->addWidget(chart_ellipse, 0, 0, 1, 1);

        chart_roundrect = new QPushButton(groupBox_3);
        chart_roundrect->setObjectName(QString::fromUtf8("chart_roundrect"));
        chart_roundrect->setMinimumSize(QSize(34, 34));
        chart_roundrect->setMaximumSize(QSize(34, 34));
        chart_roundrect->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/Rounded_Rectangle.png);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/images/img/Rounded_Rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_roundrect->setIcon(icon1);

        gridLayout_3->addWidget(chart_roundrect, 2, 0, 1, 1);

        chart_diam = new QPushButton(groupBox_3);
        chart_diam->setObjectName(QString::fromUtf8("chart_diam"));
        chart_diam->setMinimumSize(QSize(34, 34));
        chart_diam->setMaximumSize(QSize(34, 34));
        chart_diam->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/diamond.png);"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/prefix1/images/img/diamond.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_diam->setIcon(icon2);

        gridLayout_3->addWidget(chart_diam, 0, 1, 1, 1);

        chart_rect = new QPushButton(groupBox_3);
        chart_rect->setObjectName(QString::fromUtf8("chart_rect"));
        chart_rect->setMinimumSize(QSize(34, 34));
        chart_rect->setMaximumSize(QSize(34, 34));
        chart_rect->setContextMenuPolicy(Qt::CustomContextMenu);
        chart_rect->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/rectangle.png);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/new/prefix1/images/img/rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_rect->setIcon(icon3);

        gridLayout_3->addWidget(chart_rect, 2, 1, 1, 1);

        chart_trapezoid = new QPushButton(groupBox_3);
        chart_trapezoid->setObjectName(QString::fromUtf8("chart_trapezoid"));
        chart_trapezoid->setMinimumSize(QSize(34, 34));
        chart_trapezoid->setMaximumSize(QSize(34, 34));
        chart_trapezoid->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/trapezoid.png);"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/new/prefix1/images/img/trapezoid.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_trapezoid->setIcon(icon4);

        gridLayout_3->addWidget(chart_trapezoid, 3, 0, 1, 1);

        chart_line = new QPushButton(groupBox_3);
        chart_line->setObjectName(QString::fromUtf8("chart_line"));
        chart_line->setMinimumSize(QSize(34, 34));
        chart_line->setMaximumSize(QSize(34, 34));
        chart_line->setStyleSheet(QString::fromUtf8("background-image: url(:/images/img/line.png);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/new/prefix1/images/img/arrow0.png"), QSize(), QIcon::Normal, QIcon::Off);
        chart_line->setIcon(icon5);

        gridLayout_3->addWidget(chart_line, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 200));
        Btn_ChoiceECU = new QPushButton(groupBox_4);
        Btn_ChoiceECU->setObjectName(QString::fromUtf8("Btn_ChoiceECU"));
        Btn_ChoiceECU->setGeometry(QRect(10, 30, 100, 27));

        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 500));

        verticalLayout->addWidget(groupBox_5);

        scrollArea_GraphSelect->setWidget(scrollAreaWidgetContents);
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(820, 10, 100, 27));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        Btn_Save = new QPushButton(tab_5);
        Btn_Save->setObjectName(QString::fromUtf8("Btn_Save"));
        Btn_Save->setGeometry(QRect(1350, 760, 93, 28));
        Btn_FIle = new QPushButton(tab_5);
        Btn_FIle->setObjectName(QString::fromUtf8("Btn_FIle"));
        Btn_FIle->setGeometry(QRect(670, 670, 121, 31));
        Btn_StopFlash = new QPushButton(tab_5);
        Btn_StopFlash->setObjectName(QString::fromUtf8("Btn_StopFlash"));
        Btn_StopFlash->setGeometry(QRect(380, 670, 93, 31));
        Btn_Start = new QPushButton(tab_5);
        Btn_Start->setObjectName(QString::fromUtf8("Btn_Start"));
        Btn_Start->setGeometry(QRect(530, 670, 93, 31));
        Btn_disConnect = new QPushButton(tab_5);
        Btn_disConnect->setObjectName(QString::fromUtf8("Btn_disConnect"));
        Btn_disConnect->setGeometry(QRect(710, 30, 81, 61));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../ReleaseDiagnostic/images/disconnect.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        icon6.addFile(QString::fromUtf8("../ReleaseDiagnostic/images/disconnect.jpg"), QSize(), QIcon::Normal, QIcon::On);
        Btn_disConnect->setIcon(icon6);
        Btn_disConnect->setIconSize(QSize(50, 50));
        text_output_2 = new QTextEdit(tab_5);
        text_output_2->setObjectName(QString::fromUtf8("text_output_2"));
        text_output_2->setGeometry(QRect(840, 10, 601, 741));
        tableWidget = new QTableWidget(tab_5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(30, 320, 771, 341));
        progressBar = new QProgressBar(tab_5);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(30, 760, 741, 23));
        progressBar->setValue(0);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        Btn_Clearlog = new QPushButton(tab_5);
        Btn_Clearlog->setObjectName(QString::fromUtf8("Btn_Clearlog"));
        Btn_Clearlog->setGeometry(QRect(1240, 760, 93, 28));
        groupBox_6 = new QGroupBox(tab_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(30, 170, 771, 141));
        comboBox_2 = new QComboBox(groupBox_6);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(10, 20, 171, 31));
        pushButton_3 = new QPushButton(groupBox_6);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(200, 20, 71, 31));
        frame = new QFrame(groupBox_6);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 60, 761, 71));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_4 = new QPushButton(frame);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(680, 20, 71, 41));
        MsgData1 = new QLineEdit(frame);
        MsgData1->setObjectName(QString::fromUtf8("MsgData1"));
        MsgData1->setGeometry(QRect(130, 20, 51, 41));
        MsgData2 = new QLineEdit(frame);
        MsgData2->setObjectName(QString::fromUtf8("MsgData2"));
        MsgData2->setGeometry(QRect(200, 20, 51, 41));
        MsgData3 = new QLineEdit(frame);
        MsgData3->setObjectName(QString::fromUtf8("MsgData3"));
        MsgData3->setGeometry(QRect(270, 20, 51, 41));
        MsgData4 = new QLineEdit(frame);
        MsgData4->setObjectName(QString::fromUtf8("MsgData4"));
        MsgData4->setGeometry(QRect(340, 20, 51, 41));
        MsgData5 = new QLineEdit(frame);
        MsgData5->setObjectName(QString::fromUtf8("MsgData5"));
        MsgData5->setGeometry(QRect(410, 20, 51, 41));
        MsgData6 = new QLineEdit(frame);
        MsgData6->setObjectName(QString::fromUtf8("MsgData6"));
        MsgData6->setGeometry(QRect(480, 20, 51, 41));
        MsgData7 = new QLineEdit(frame);
        MsgData7->setObjectName(QString::fromUtf8("MsgData7"));
        MsgData7->setGeometry(QRect(550, 20, 51, 41));
        MsgData8 = new QLineEdit(frame);
        MsgData8->setObjectName(QString::fromUtf8("MsgData8"));
        MsgData8->setGeometry(QRect(620, 20, 51, 41));
        Message_ID = new QLineEdit(frame);
        Message_ID->setObjectName(QString::fromUtf8("Message_ID"));
        Message_ID->setGeometry(QRect(10, 20, 91, 41));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 0, 72, 15));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(130, 0, 111, 16));
        groupBox_7 = new QGroupBox(tab_5);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(30, 20, 511, 141));
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(290, 120, 81, 20));
        comboBox = new QComboBox(groupBox_7);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 50, 171, 41));
        txt_funReq = new QLineEdit(groupBox_7);
        txt_funReq->setObjectName(QString::fromUtf8("txt_funReq"));
        txt_funReq->setGeometry(QRect(380, 70, 113, 31));
        checkBox = new QCheckBox(groupBox_7);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(130, 10, 101, 19));
        comboBox_4 = new QComboBox(groupBox_7);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(380, 110, 111, 31));
        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 30, 81, 16));
        txt_PhyReq = new QLineEdit(groupBox_7);
        txt_PhyReq->setObjectName(QString::fromUtf8("txt_PhyReq"));
        txt_PhyReq->setGeometry(QRect(380, 10, 113, 31));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(290, 80, 81, 20));
        txt_phyRes = new QLineEdit(groupBox_7);
        txt_phyRes->setObjectName(QString::fromUtf8("txt_phyRes"));
        txt_phyRes->setGeometry(QRect(380, 40, 113, 31));
        label_9 = new QLabel(groupBox_7);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(291, 10, 81, 20));
        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(280, 50, 91, 20));
        Btn_Fresh = new QPushButton(groupBox_7);
        Btn_Fresh->setObjectName(QString::fromUtf8("Btn_Fresh"));
        Btn_Fresh->setGeometry(QRect(190, 60, 71, 28));
        checkBox_2 = new QCheckBox(groupBox_7);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(20, 110, 91, 19));
        lineEdit_12 = new QLineEdit(groupBox_7);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(210, 110, 71, 21));
        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 110, 101, 20));
        Btn_Connect = new QPushButton(tab_5);
        Btn_Connect->setObjectName(QString::fromUtf8("Btn_Connect"));
        Btn_Connect->setGeometry(QRect(560, 30, 81, 61));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../ReleaseDiagnostic/images/connect.jpeg"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_Connect->setIcon(icon7);
        Btn_Connect->setIconSize(QSize(50, 50));
        groupBox_8 = new QGroupBox(tab_5);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setEnabled(false);
        groupBox_8->setGeometry(QRect(1460, 220, 341, 551));
        Btn_ConnectMqtt = new QPushButton(groupBox_8);
        Btn_ConnectMqtt->setObjectName(QString::fromUtf8("Btn_ConnectMqtt"));
        Btn_ConnectMqtt->setGeometry(QRect(20, 30, 81, 61));
        Btn_ConnectMqtt->setIcon(icon7);
        Btn_ConnectMqtt->setIconSize(QSize(50, 50));
        Btn_disConnectMqtt = new QPushButton(groupBox_8);
        Btn_disConnectMqtt->setObjectName(QString::fromUtf8("Btn_disConnectMqtt"));
        Btn_disConnectMqtt->setGeometry(QRect(140, 30, 81, 61));
        Btn_disConnectMqtt->setIcon(icon6);
        Btn_disConnectMqtt->setIconSize(QSize(50, 50));
        SendData_mqtt = new QLineEdit(groupBox_8);
        SendData_mqtt->setObjectName(QString::fromUtf8("SendData_mqtt"));
        SendData_mqtt->setGeometry(QRect(20, 110, 171, 41));
        SendData_mqtt->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        SendData_mqtt->setInputMethodHints(Qt::ImhDigitsOnly);
        Btn_SendMqtt = new QPushButton(groupBox_8);
        Btn_SendMqtt->setObjectName(QString::fromUtf8("Btn_SendMqtt"));
        Btn_SendMqtt->setGeometry(QRect(210, 110, 121, 41));
        Btn_getVersion = new QPushButton(groupBox_8);
        Btn_getVersion->setObjectName(QString::fromUtf8("Btn_getVersion"));
        Btn_getVersion->setGeometry(QRect(20, 280, 111, 28));
        comboBox_ECU = new QComboBox(groupBox_8);
        comboBox_ECU->setObjectName(QString::fromUtf8("comboBox_ECU"));
        comboBox_ECU->setGeometry(QRect(230, 30, 87, 31));
        SendData_mqttPath = new QLineEdit(groupBox_8);
        SendData_mqttPath->setObjectName(QString::fromUtf8("SendData_mqttPath"));
        SendData_mqttPath->setGeometry(QRect(20, 160, 311, 41));
        SendData_mqttPath->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        SendData_mqttPath->setInputMethodHints(Qt::ImhDigitsOnly);
        Btn_FileDiaglogMqtt = new QPushButton(groupBox_8);
        Btn_FileDiaglogMqtt->setObjectName(QString::fromUtf8("Btn_FileDiaglogMqtt"));
        Btn_FileDiaglogMqtt->setGeometry(QRect(80, 220, 100, 27));
        Btn_SendMqttScript = new QPushButton(groupBox_8);
        Btn_SendMqttScript->setObjectName(QString::fromUtf8("Btn_SendMqttScript"));
        Btn_SendMqttScript->setGeometry(QRect(230, 220, 100, 27));
        Btn_EOL = new QPushButton(groupBox_8);
        Btn_EOL->setObjectName(QString::fromUtf8("Btn_EOL"));
        Btn_EOL->setGeometry(QRect(140, 280, 93, 28));
        Btn_AfterSale = new QPushButton(groupBox_8);
        Btn_AfterSale->setObjectName(QString::fromUtf8("Btn_AfterSale"));
        Btn_AfterSale->setGeometry(QRect(240, 280, 93, 28));
        groupBox_9 = new QGroupBox(tab_5);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setEnabled(false);
        groupBox_9->setGeometry(QRect(1460, 10, 341, 201));
        lineEdit_DiagConf = new QLineEdit(groupBox_9);
        lineEdit_DiagConf->setObjectName(QString::fromUtf8("lineEdit_DiagConf"));
        lineEdit_DiagConf->setGeometry(QRect(10, 20, 321, 41));
        Btn_StartDiag = new QPushButton(groupBox_9);
        Btn_StartDiag->setObjectName(QString::fromUtf8("Btn_StartDiag"));
        Btn_StartDiag->setGeometry(QRect(50, 90, 93, 28));
        Btn_FileDiaglog = new QPushButton(groupBox_9);
        Btn_FileDiaglog->setObjectName(QString::fromUtf8("Btn_FileDiaglog"));
        Btn_FileDiaglog->setGeometry(QRect(210, 90, 100, 27));
        Btn_Send = new QPushButton(groupBox_9);
        Btn_Send->setObjectName(QString::fromUtf8("Btn_Send"));
        Btn_Send->setGeometry(QRect(200, 140, 121, 41));
        SendData_Line = new QLineEdit(groupBox_9);
        SendData_Line->setObjectName(QString::fromUtf8("SendData_Line"));
        SendData_Line->setGeometry(QRect(20, 140, 171, 41));
        SendData_Line->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        SendData_Line->setInputMethodHints(Qt::ImhDigitsOnly);
        Btn_ReadVersion = new QPushButton(tab_5);
        Btn_ReadVersion->setObjectName(QString::fromUtf8("Btn_ReadVersion"));
        Btn_ReadVersion->setGeometry(QRect(560, 100, 111, 28));
        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setEnabled(true);
        stackedWidget = new QStackedWidget(tab_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        stackedWidget->setGeometry(QRect(0, 0, 1331, 611));
        stackedWidget->setFont(font);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        Btn_StackFlashTool = new QPushButton(page);
        Btn_StackFlashTool->setObjectName(QString::fromUtf8("Btn_StackFlashTool"));
        Btn_StackFlashTool->setGeometry(QRect(20, 30, 241, 181));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setWeight(75);
        Btn_StackFlashTool->setFont(font2);
        Btn_StackTeleDiag = new QPushButton(page);
        Btn_StackTeleDiag->setObjectName(QString::fromUtf8("Btn_StackTeleDiag"));
        Btn_StackTeleDiag->setGeometry(QRect(800, 30, 241, 181));
        Btn_StackTeleDiag->setFont(font2);
        Btn_StackOTX = new QPushButton(page);
        Btn_StackOTX->setObjectName(QString::fromUtf8("Btn_StackOTX"));
        Btn_StackOTX->setGeometry(QRect(540, 30, 241, 181));
        Btn_StackOTX->setFont(font2);
        Btn_StackODX = new QPushButton(page);
        Btn_StackODX->setObjectName(QString::fromUtf8("Btn_StackODX"));
        Btn_StackODX->setGeometry(QRect(280, 30, 241, 181));
        Btn_StackODX->setFont(font2);
        Btn_StackVersion = new QPushButton(page);
        Btn_StackVersion->setObjectName(QString::fromUtf8("Btn_StackVersion"));
        Btn_StackVersion->setGeometry(QRect(1060, 30, 241, 181));
        Btn_StackVersion->setFont(font2);
        Btn_StackDiagnosticFunc = new QPushButton(page);
        Btn_StackDiagnosticFunc->setObjectName(QString::fromUtf8("Btn_StackDiagnosticFunc"));
        Btn_StackDiagnosticFunc->setGeometry(QRect(20, 240, 241, 181));
        Btn_StackDiagnosticFunc->setFont(font2);
        Btn_StackDiagnosticFunc->setIconSize(QSize(100, 200));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1995, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(3);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Diagnose(20250214_V2.0.1)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\257\212\346\226\255\344\273\273\345\212\241", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "\350\260\203\347\224\250\345\221\250\346\234\237", nullptr));
        dateTime_StartTime->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy/M/d h:mm", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("MainWindow", "\346\210\220\345\212\237\346\254\241\346\225\260", nullptr));
        dateTime_EndTime->setDisplayFormat(QCoreApplication::translate("MainWindow", "yyyy/M/d h:mm", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ms", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "\344\273\273\345\212\241ID", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Btn_File->setText(QCoreApplication::translate("MainWindow", "FileDiaglog", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("MainWindow", "\345\244\261\350\264\245\346\254\241\346\225\260", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\346\254\241\346\225\260", nullptr));
        lineEdit_9->setText(QCoreApplication::translate("MainWindow", "RequestID", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "7E5", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("MainWindow", "ResponseID", nullptr));
        lineEdit_11->setText(QCoreApplication::translate("MainWindow", "7ED", nullptr));
        Btn_update->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\350\257\212\346\226\255\347\261\273\345\236\213", nullptr));
        tasktyperuntime->setText(QCoreApplication::translate("MainWindow", "\345\256\236\346\227\266\350\257\212\346\226\255", nullptr));
        tasktypeperiod->setText(QCoreApplication::translate("MainWindow", "\345\221\250\346\234\237\350\257\212\346\226\255", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "OTA", nullptr));
        Btn_File_4->setText(QCoreApplication::translate("MainWindow", "\350\247\243\346\236\220", nullptr));
        Btn_File_5->setText(QCoreApplication::translate("MainWindow", "FileDiaglog", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\257\212\346\226\255\345\272\217\345\210\227\350\204\232\346\234\254", nullptr));
        Btn_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        Btn_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "ODX-Parse", nullptr));
        Btn_File_otx->setText(QCoreApplication::translate("MainWindow", "FileDiaglog", nullptr));
        Btn_File_parseotx->setText(QCoreApplication::translate("MainWindow", "\350\247\243\346\236\220", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\345\237\272\347\241\200\345\233\276\345\275\242", nullptr));
        chart_ellipse->setText(QString());
        chart_roundrect->setText(QString());
        chart_diam->setText(QString());
        chart_rect->setText(QString());
        chart_trapezoid->setText(QString());
        chart_line->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\350\257\212\346\226\255\346\250\241\345\235\227", nullptr));
        Btn_ChoiceECU->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251ECU", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "UML\347\224\250\344\276\213\345\233\276", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "OTX-Parse", nullptr));
        Btn_Save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Btn_FIle->setText(QCoreApplication::translate("MainWindow", "Add File", nullptr));
        Btn_StopFlash->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        Btn_Start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        Btn_disConnect->setText(QString());
        Btn_Clearlog->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\347\275\221\347\273\234\347\256\241\347\220\206\346\212\245\346\226\207\345\217\221\351\200\201", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Message data", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\345\210\267\345\206\231\351\205\215\347\275\256", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "CAN/CANFD", nullptr));
        txt_funReq->setText(QCoreApplication::translate("MainWindow", "7DF", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Service_27", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "CAN", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "CANFD", nullptr));

        label_4->setText(QCoreApplication::translate("MainWindow", "DeviceType", nullptr));
        txt_PhyReq->setText(QCoreApplication::translate("MainWindow", "704", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "FunRequest", nullptr));
        txt_phyRes->setText(QCoreApplication::translate("MainWindow", "70C", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "PhyRequest", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "PhyResponse", nullptr));
        Btn_Fresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "10 02\345\272\224\347\255\224", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\255\211\345\276\205 \346\227\266\351\227\264\357\274\210s\357\274\211", nullptr));
        Btn_Connect->setText(QString());
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "MQTT", nullptr));
        Btn_ConnectMqtt->setText(QString());
        Btn_disConnectMqtt->setText(QString());
        Btn_SendMqtt->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        Btn_getVersion->setText(QCoreApplication::translate("MainWindow", "VersionInfo", nullptr));
        Btn_FileDiaglogMqtt->setText(QCoreApplication::translate("MainWindow", "FileDiaglog", nullptr));
        Btn_SendMqttScript->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        Btn_EOL->setText(QCoreApplication::translate("MainWindow", "\350\275\246\350\276\206\344\270\213\347\272\277", nullptr));
        Btn_AfterSale->setText(QCoreApplication::translate("MainWindow", "\345\224\256\345\220\216\346\215\242\344\273\266 ", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "Diagnostic Raw", nullptr));
        Btn_StartDiag->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        Btn_FileDiaglog->setText(QCoreApplication::translate("MainWindow", "FileDiaglog", nullptr));
        Btn_Send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        Btn_ReadVersion->setText(QCoreApplication::translate("MainWindow", "ReadVersion", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "FlashTool", nullptr));
        Btn_StackFlashTool->setText(QCoreApplication::translate("MainWindow", "Flash Tool", nullptr));
        Btn_StackTeleDiag->setText(QCoreApplication::translate("MainWindow", "Tele- \n"
"Diagnostis", nullptr));
        Btn_StackOTX->setText(QCoreApplication::translate("MainWindow", "OTX-Parse", nullptr));
        Btn_StackODX->setText(QCoreApplication::translate("MainWindow", "ODX-Parse", nullptr));
        Btn_StackVersion->setText(QCoreApplication::translate("MainWindow", "Version", nullptr));
        Btn_StackDiagnosticFunc->setText(QCoreApplication::translate("MainWindow", "Special-Diagnosis", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
