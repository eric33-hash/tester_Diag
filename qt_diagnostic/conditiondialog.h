#ifndef CONDITIONDIALOG_H
#define CONDITIONDIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class conditionDialog;
}

class conditionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit conditionDialog(QWidget *parent = nullptr);
    ~conditionDialog();

signals:
    void dialogclick(QString hmi);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::conditionDialog *ui;
};

#endif // CONDITIONDIALOG_H
