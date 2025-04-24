/********************************************************************************
** Form generated from reading UI file 'conditiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONDITIONDIALOG_H
#define UI_CONDITIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_conditionDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *ifText;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *elseText;

    void setupUi(QDialog *conditionDialog)
    {
        if (conditionDialog->objectName().isEmpty())
            conditionDialog->setObjectName(QString::fromUtf8("conditionDialog"));
        conditionDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(conditionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ifText = new QLineEdit(conditionDialog);
        ifText->setObjectName(QString::fromUtf8("ifText"));
        ifText->setGeometry(QRect(160, 60, 113, 27));
        label = new QLabel(conditionDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(28, 60, 101, 20));
        label_2 = new QLabel(conditionDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 110, 131, 20));
        elseText = new QLineEdit(conditionDialog);
        elseText->setObjectName(QString::fromUtf8("elseText"));
        elseText->setGeometry(QRect(160, 110, 113, 27));

        retranslateUi(conditionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), conditionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), conditionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(conditionDialog);
    } // setupUi

    void retranslateUi(QDialog *conditionDialog)
    {
        conditionDialog->setWindowTitle(QCoreApplication::translate("conditionDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("conditionDialog", "IF Condition", nullptr));
        label_2->setText(QCoreApplication::translate("conditionDialog", "elseIF Condition", nullptr));
    } // retranslateUi

};

namespace Ui {
    class conditionDialog: public Ui_conditionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONDITIONDIALOG_H
