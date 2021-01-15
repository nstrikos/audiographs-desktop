#include "errorDisplayDialog.h"
#include "ui_errorDisplayDialog.h"

ErrorDisplayDialog::ErrorDisplayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDisplayDialog)
{
    ui->setupUi(this);
}

ErrorDisplayDialog::~ErrorDisplayDialog()
{
    delete ui;
}

void ErrorDisplayDialog::setText(QString text)
{
    ui->plainTextEdit->document()->setPlainText(text);
}
