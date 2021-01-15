#include "helpDialog.h"
#include "ui_helpDialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::setText(QString text)
{
    ui->plainTextEdit->document()->setPlainText(text);
}
