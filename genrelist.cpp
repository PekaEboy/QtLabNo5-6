#include "genrelist.h"
#include "ui_genrelist.h"

GenreList::GenreList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenreList)
{
    ui->setupUi(this);
}

GenreList::~GenreList()
{
    delete ui;
}

void GenreList::pushback(Music var) {
    genlist.push_back(var);
}

void GenreList::UpdateList() {
    ui->twGenreList->clear();
    ui->twGenreList->setColumnCount(4);
    for(int c = 0; c < ui->twGenreList->horizontalHeader()->count(); ++c) {
        ui->twGenreList->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
    ui->twGenreList->setRowCount(genlist.length());
    Node* y = genlist.first;
    while(y) {
    //ui->twMusic->setItem(0, 0, new QTableWidgetItem("Hello"));
        for(int i = 0; i<4; i++) {
            switch(i) {
                case 0:
                    ui->twGenreList->setItem(y->number, i, new QTableWidgetItem(y->val.name));
                    break;
                case 1:
                    ui->twGenreList->setItem(y->number, i, new QTableWidgetItem(y->val.creator));
                    break;
                case 2:
                    ui->twGenreList->setItem(y->number, i, new QTableWidgetItem(y->val.genre));
                    break;
                case 3:
                    ui->twGenreList->setItem(y->number, i, new QTableWidgetItem(QString::number(y->val.time/60) + ":" + QString::number(y->val.time%60+100).mid(1)));
                    break;
            }
        }
        y=y->next;
    }
}

void GenreList::clear() {
    while(!genlist.is_empty()) genlist.remove(genlist.first->number);
}
