/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *title;
    QLabel *label_2;
    QTextEdit *content;
    QLabel *label_3;
    QComboBox *comboBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(453, 454);
        Dialog->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(100, 410, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 70, 51, 21));
        title = new QLineEdit(Dialog);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(110, 70, 271, 27));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 140, 81, 21));
        content = new QTextEdit(Dialog);
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(110, 140, 271, 181));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 340, 111, 19));
        comboBox = new QComboBox(Dialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 340, 181, 27));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Title:", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "content:", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "MessageType", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Dialog", "INFO", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Dialog", "WARNING", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Dialog", "ERROR", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Dialog", "YESNO_QUESTION", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Dialog", "YESNOCANCEL_QUESTION", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
