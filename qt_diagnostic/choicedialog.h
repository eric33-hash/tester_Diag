#ifndef CHOICEDIALOG_H
#define CHOICEDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ChoiceDialog;
}

class ChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoiceDialog(QWidget *parent = nullptr);
    ~ChoiceDialog();

signals:
    void dialogclick(QString hmi);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ChoiceDialog *ui;
};

#endif // CHOICEDIALOG_H
