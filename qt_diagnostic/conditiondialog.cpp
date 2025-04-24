#include "conditiondialog.h"
#include "ui_conditiondialog.h"

conditionDialog::conditionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conditionDialog)
{
    ui->setupUi(this);
}

conditionDialog::~conditionDialog()
{
    delete ui;
}

void conditionDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString hmi = ui->ifText->text();
    hmi += "-";
    hmi += ui->elseText->text();
    emit dialogclick(hmi);
}
