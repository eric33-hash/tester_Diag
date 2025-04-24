#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString hmi = ui->title->text();
    hmi += "-";
    hmi += ui->message->text();
    hmi += "-";
    hmi += ui->instruction->text();
    hmi += "-";
    hmi += ui->name->text();
    emit dialogclick(hmi);
}
