#ifndef GENRELIST_H
#define GENRELIST_H

#include <QDialog>
#include "list.h"

namespace Ui {
class GenreList;
}

class GenreList : public QDialog
{
    Q_OBJECT
    List genlist;

public:
    explicit GenreList(QWidget *parent = nullptr);
    ~GenreList();
    void pushback(Music var);
    void UpdateList();
    void clear();

private:
    Ui::GenreList *ui;
};

#endif // GENRELIST_H
