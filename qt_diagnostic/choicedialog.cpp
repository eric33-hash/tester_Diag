#include "choicedialog.h"
#include "ui_choicedialog.h"

ChoiceDialog::ChoiceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoiceDialog)
{
    ui->setupUi(this);
}

ChoiceDialog::~ChoiceDialog()
{
    delete ui;
}

void ChoiceDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    QString hmi = ui->title->text();
    hmi += "-";
    hmi += ui->information->text();
    hmi += "-";
    hmi += ui->category->text();
    hmi += "-";
    hmi += ui->result->text();
    emit dialogclick(hmi);
}
