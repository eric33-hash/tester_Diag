#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString hmi = ui->title->text();
    hmi += "-";
    hmi += ui->content->toPlainText();
    hmi += "-";
    hmi += ui->comboBox->currentText();
    emit dialogclick(hmi);
}
