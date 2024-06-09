#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pbOk, &QPushButton::clicked, this, &Dialog::accept);
    connect(ui->pbCancel, &QPushButton::clicked, this, &Dialog::reject);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getData() {
    return ui->leInput->text();
}

void Dialog::setMess(QString val) {
    ui->lblText->setText(val);
}

void Dialog::clearLE() {
    ui->leInput->clear();
}

void Dialog::setInput(QString val) {
    ui->leInput->setText(val);
}
