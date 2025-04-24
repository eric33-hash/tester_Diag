#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

signals:
    void dialogclick(QString hmi);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
