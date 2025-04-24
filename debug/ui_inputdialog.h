/********************************************************************************
** Form generated from reading UI file 'inputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *title;
    QLineEdit *message;
    QLineEdit *instruction;
    QLineEdit *name;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QString::fromUtf8("InputDialog"));
        InputDialog->resize(439, 338);
        buttonBox = new QDialogButtonBox(InputDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(70, 290, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        title = new QLineEdit(InputDialog);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(190, 40, 221, 41));
        message = new QLineEdit(InputDialog);
        message->setObjectName(QString::fromUtf8("message"));
        message->setGeometry(QRect(190, 100, 221, 41));
        instruction = new QLineEdit(InputDialog);
        instruction->setObjectName(QString::fromUtf8("instruction"));
        instruction->setGeometry(QRect(190, 160, 221, 41));
        name = new QLineEdit(InputDialog);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(190, 230, 221, 41));
        label = new QLabel(InputDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 79, 19));
        label_2 = new QLabel(InputDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 110, 79, 19));
        label_3 = new QLabel(InputDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 170, 171, 19));
        label_4 = new QLabel(InputDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 240, 161, 19));

        retranslateUi(InputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QCoreApplication::translate("InputDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("InputDialog", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("InputDialog", "Message", nullptr));
        label_3->setText(QCoreApplication::translate("InputDialog", "Message instruction", nullptr));
        label_4->setText(QCoreApplication::translate("InputDialog", "Result name/value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H
