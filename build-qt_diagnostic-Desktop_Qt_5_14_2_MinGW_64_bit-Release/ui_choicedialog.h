/********************************************************************************
** Form generated from reading UI file 'choicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEDIALOG_H
#define UI_CHOICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ChoiceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *title;
    QLabel *label_2;
    QLineEdit *information;
    QLabel *label_3;
    QLineEdit *category;
    QLabel *label_4;
    QLineEdit *result;

    void setupUi(QDialog *ChoiceDialog)
    {
        if (ChoiceDialog->objectName().isEmpty())
            ChoiceDialog->setObjectName(QString::fromUtf8("ChoiceDialog"));
        ChoiceDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ChoiceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(ChoiceDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 41, 19));
        title = new QLineEdit(ChoiceDialog);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(110, 30, 281, 27));
        label_2 = new QLabel(ChoiceDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 91, 19));
        information = new QLineEdit(ChoiceDialog);
        information->setObjectName(QString::fromUtf8("information"));
        information->setGeometry(QRect(110, 80, 281, 27));
        label_3 = new QLabel(ChoiceDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 130, 71, 20));
        category = new QLineEdit(ChoiceDialog);
        category->setObjectName(QString::fromUtf8("category"));
        category->setGeometry(QRect(110, 130, 281, 27));
        label_4 = new QLabel(ChoiceDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 180, 91, 20));
        result = new QLineEdit(ChoiceDialog);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(110, 180, 281, 27));

        retranslateUi(ChoiceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChoiceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChoiceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChoiceDialog);
    } // setupUi

    void retranslateUi(QDialog *ChoiceDialog)
    {
        ChoiceDialog->setWindowTitle(QCoreApplication::translate("ChoiceDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("ChoiceDialog", "Title", nullptr));
        label_2->setText(QCoreApplication::translate("ChoiceDialog", "information", nullptr));
        label_3->setText(QCoreApplication::translate("ChoiceDialog", "Category", nullptr));
        label_4->setText(QCoreApplication::translate("ChoiceDialog", "resultName", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChoiceDialog: public Ui_ChoiceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEDIALOG_H
