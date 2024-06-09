#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dia = new Dialog(this);
    gel = new GenreList(this);
    connect(ui->pbAdd, &QPushButton::clicked, this, &MainWindow::UpdateList);
    connect(ui->pbAddAfter, &QPushButton::clicked, this, &MainWindow::UpdateList);
    connect(ui->pbRemove, &QPushButton::clicked, this, &MainWindow::UpdateList);
    connect(ui->pbEdit, &QPushButton::clicked, this, &MainWindow::UpdateList);
    connect(ui->pbSort, &QPushButton::clicked, this, &MainWindow::UpdateList);
    ui->twMusic->setColumnCount(4);
    for(int c = 0; c < ui->twMusic->horizontalHeader()->count(); ++c) {
        ui->twMusic->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    sta=Stats::Not;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showMessage(QString str) {
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}

void MainWindow::on_pbAdd_clicked()
{
    dia->clearLE();
    bool flag = true;
    dia->setMess("Введите название музыки");
    for(int i = 0; i<4;i++) {
        if(dia->exec() == QDialog::DialogCode::Accepted) {
            switch(i) {
                case 0:
                    p.name=dia->getData();
                    dia->setMess("Введите ФИО создателей");
                    dia->clearLE();
                    break;
                case 1:
                    p.creator=dia->getData();
                    dia->setMess("Введите жанр");
                    dia->clearLE();
                    break;
                case 2:
                    p.genre=dia->getData();
                    dia->setMess("Введите длительность музыки в секундах или в виде Минута:Секунда");
                    dia->clearLE();
                    break;
                case 3:
                    QString sf = dia->getData();
                    if(sf.split(":").length()==1) {
                        p.time = sf.toInt();
                    } else if(sf.split(":").length()==2) {
                        if(sf.split(":")[1].toInt()<60) p.time = sf.split(":")[0].toInt()*60+sf.split(":")[1].toInt();
                    } else {
                        flag = false;
                    }
                    dia->clearLE();
                    break;
            }
        } else {
            flag = false;
            break;
        }
    }
    if(flag) lst.push_back(p);
}

void MainWindow::UpdateList() {
    ui->twMusic->clear();
    ui->twMusic->setColumnCount(4);
    ui->twMusic->setRowCount(lst.length());
    Node* y = lst.first;
    while(y) {
    //ui->twMusic->setItem(0, 0, new QTableWidgetItem("Hello"));
        for(int i = 0; i<4; i++) {
            switch(i) {
                case 0:
                    ui->twMusic->setItem(y->number, i, new QTableWidgetItem(y->val.name));
                    break;
                case 1:
                    ui->twMusic->setItem(y->number, i, new QTableWidgetItem(y->val.creator));
                    break;
                case 2:
                    ui->twMusic->setItem(y->number, i, new QTableWidgetItem(y->val.genre));
                    break;
                case 3:
                    ui->twMusic->setItem(y->number, i, new QTableWidgetItem(QString::number(y->val.time/60) + ":" + QString::number(y->val.time%60+100).mid(1)));
                    break;
            }
        }
        y=y->next;
    }
    ui->lblStatEdit->setText("(not saved)");
}

void MainWindow::on_pbAddAfter_clicked()
{
    dia->clearLE();
    if(ui->twMusic->selectionModel()->hasSelection()) {
        Node* kp = lst.find(ui->twMusic->currentRow());
        if(kp) {
            bool flag = true;
            dia->setMess("Введите название музыки");
            for(int i = 0; i<4;i++) {
                if(dia->exec() == QDialog::DialogCode::Accepted) {
                    switch(i) {
                        case 0:
                            p.name=dia->getData();
                            dia->setMess("Введите ФИО создателей");
                            dia->clearLE();
                            break;
                        case 1:
                            p.creator=dia->getData();
                            dia->setMess("Введите жанр");
                            dia->clearLE();
                            break;
                        case 2:
                            p.genre=dia->getData();
                            dia->setMess("Введите длительность музыки в секундах или в виде Минута:Секунда");
                            dia->clearLE();
                            break;
                        case 3:
                            QString sf = dia->getData();
                            if(sf.split(":").length()==1) {
                                p.time = sf.toInt();
                            } else if(sf.split(":").length()==2) {
                                if(sf.split(":")[1].toInt()<60) p.time = sf.split(":")[0].toInt()*60+sf.split(":")[1].toInt();
                            } else {
                                flag = false;
                            }
                            dia->clearLE();
                            break;
                    }
                } else {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                kp=kp->next;
                while(kp) {
                    if(kp->next!=nullptr) {
                        music2=kp->next->val;
                        music1=kp->val;
                        kp->val=p;
                        kp->next->val=music1;
                        p=music2;
                    } else {
                        music1=kp->val;
                        kp->val=p;
                        p=music1;
                    }
                    kp=kp->next;
                }
                lst.push_back(p);
                kp = lst.first;
                for(int i = 0; kp; i++) {
                    kp->number=i;
                    kp=kp->next;
                }
            }
        }
    }

}


/*void MainWindow::on_lwName_itemSelectionChanged()
{
    ui->lwCreator->setCurrentRow(ui->lwName->currentRow());
    ui->lwGenre->setCurrentRow(ui->lwName->currentRow());
    ui->lwLength->setCurrentRow(ui->lwName->currentRow());
}


void MainWindow::on_lwCreator_itemSelectionChanged()
{
    ui->lwName->setCurrentRow(ui->lwCreator->currentRow());
    ui->lwGenre->setCurrentRow(ui->lwCreator->currentRow());
    ui->lwLength->setCurrentRow(ui->lwCreator->currentRow());
}


void MainWindow::on_lwGenre_itemSelectionChanged()
{
    ui->lwName->setCurrentRow(ui->lwGenre->currentRow());
    ui->lwCreator->setCurrentRow(ui->lwGenre->currentRow());
    ui->lwLength->setCurrentRow(ui->lwGenre->currentRow());
}



void MainWindow::on_lwLength_itemSelectionChanged()
{
    ui->lwName->setCurrentRow(ui->lwLength->currentRow());
    ui->lwCreator->setCurrentRow(ui->lwLength->currentRow());
    ui->lwGenre->setCurrentRow(ui->lwLength->currentRow());
}*/


void MainWindow::on_pbRemove_clicked()
{
    if(ui->twMusic->selectionModel()->hasSelection()) lst.remove(ui->twMusic->currentRow());
    else showMessage("Выберите музыку из списка");
}


void MainWindow::on_pbEdit_clicked()
{
    if(ui->twMusic->selectionModel()->hasSelection()) {
        Node* kp = lst.find(ui->twMusic->currentRow());
        if(kp) {
            bool flag = true;
            dia->setMess("Введите название музыки");
            dia->setInput(ui->twMusic->item(ui->twMusic->currentRow(), 0)->text());
            for(int i = 0; i<4;i++) {
                if(dia->exec() == QDialog::DialogCode::Accepted) {
                    switch(i) {
                        case 0:
                            p.name=dia->getData();
                            dia->setMess("Введите ФИО создателей");
                            dia->setInput(ui->twMusic->item(ui->twMusic->currentRow(), 1)->text());
                            break;
                        case 1:
                            p.creator=dia->getData();
                            dia->setMess("Введите жанр");
                            dia->setInput(ui->twMusic->item(ui->twMusic->currentRow(), 2)->text());
                            break;
                        case 2:
                            p.genre=dia->getData();
                            dia->setMess("Введите длительность музыки в секундах");
                            dia->setInput(ui->twMusic->item(ui->twMusic->currentRow(), 3)->text());
                            break;
                        case 3:
                            QString sf = dia->getData();
                            if(sf.split(":").length()==1) {
                                p.time = sf.toInt();
                            } else if(sf.split(":").length()==2) {
                                if(sf.split(":")[1].toInt()<60) p.time = sf.split(":")[0].toInt()*60+sf.split(":")[1].toInt();
                            } else {
                                flag = false;
                            }
                            dia->clearLE();
                            break;
                    }
                } else {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                kp->val=p;
            }
        }
    }
}


void MainWindow::on_pbSort_clicked()
{
    if (!lst.is_empty()) {
        for (Node* q = lst.first; q; q = q->next) {
            for (Node* r = q->next; r; r = r->next) {
                if (q->val.time > r->val.time) {
                    p = r->val;
                    r->val = q->val;
                    q->val = p;
                }
            }
        }

    }
}


void MainWindow::on_acSave_triggered()
{
    bool flag = false;
    QString fileName;
    if(sta==Stats::Not) {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                          "NewFile",
                                                          tr("Texts (*.txt)"));
        memoryurl=fileName;
        ui->lblNameFile->setText(memoryurl);

    } else fileName = memoryurl;
    if(!fileName.isNull() && !lst.is_empty()) {
        sta=Stats::Opened;
        QFile fil(fileName);
        if (fil.open(QIODevice::WriteOnly)) {
            QTextStream out(&fil);
            Node *gh = lst.first;
            while(gh) {
                out << gh->val.name << ";";
                out << gh->val.creator << ";";
                out << gh->val.genre << ";";
                out << gh->val.time << "\n";
                gh=gh->next;
            }
            flag=true;
            fil.close();
        }
    }
    if(flag) ui->lblStatEdit->setText("(saved)");
}


void MainWindow::on_acOpen_triggered()
{
    bool flag = false;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "",
                                                      tr("Texts (*.txt)"));

    if(!fileName.isNull()) {
        memoryurl=fileName;
        ui->lblNameFile->setText(memoryurl);
        sta=Stats::Opened;
        QFile fil(fileName);
        QString lnt;
        while(!lst.is_empty()) lst.remove(lst.first->number);
        if (fil.open(QIODevice::ReadOnly)) {
            QTextStream in(&fil);
            while(!in.atEnd()) {
                in>>lnt;
                QStringList stls = lnt.split(";");
                if(stls.length()==4) {
                    p.name = stls[0];
                    p.creator = stls[1];
                    p.genre = stls[2];
                    p.time = stls[3].toInt();
                    lst.push_back(p);
                }

            }
            fil.close();
            flag=true;
            UpdateList();
        }
        if(flag)
        ui->lblStatEdit->setText("(saved)");
    }
}


void MainWindow::on_acSaveHow_triggered()
{
    bool flag =false;
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                          "NewFile",
                                                          tr("Texts (*.txt)"));
    memoryurl=fileName;
    ui->lblNameFile->setText(memoryurl);

    if(!fileName.isNull() && !lst.is_empty()) {
        sta=Stats::Opened;
        QFile fil(fileName);
        if (fil.open(QIODevice::WriteOnly)) {
            QTextStream out(&fil);
            Node *gh = lst.first;
            while(gh) {
                out << gh->val.name << ";";
                out << gh->val.creator << ";";
                out << gh->val.genre << ";";
                out << gh->val.time << "\n";
                gh=gh->next;
            }
            fil.close();
            flag=true;
        }
        if(flag)
        ui->lblStatEdit->setText("(saved)");
    }

}


void MainWindow::on_pbChoose_clicked()
{
    QString nameGenre = ui->leInput->text();
    Node *q = lst.first;
    gel->clear();
    while(q) {
        if(q->val.genre==nameGenre) {
            gel->pushback(q->val);
        }
        q=q->next;
    }
    gel->UpdateList();
    gel->exec();
}

