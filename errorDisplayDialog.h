#ifndef ERRORDISPLAYDIALOG_H
#define ERRORDISPLAYDIALOG_H

#include <QDialog>

namespace Ui {
class ErrorDisplayDialog;
}

class ErrorDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDisplayDialog(QWidget *parent = nullptr);
    ~ErrorDisplayDialog();
    void setText(QString text);

private:
    Ui::ErrorDisplayDialog *ui;
};

#endif // ERRORDISPLAYDIALOG_H
