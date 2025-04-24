#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void dialogclick(QString hmi);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
