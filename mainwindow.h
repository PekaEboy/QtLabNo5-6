#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
#include "list.h"
#include "genrelist.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Dialog* dia;
    GenreList* gel;
    List lst;
    Music p;
    Music music1;
    Music music2;
    enum Stats {
        Opened, Not
    };
    Stats sta;
    QString memoryurl;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbAdd_clicked();
    void UpdateList();
    void on_pbAddAfter_clicked();
    /*
    void on_lwName_itemSelectionChanged();

    void on_lwCreator_itemSelectionChanged();

    void on_lwGenre_itemSelectionChanged();

    void on_lwLength_itemSelectionChanged();*/

    void on_pbRemove_clicked();

    void on_pbEdit_clicked();

    void on_pbSort_clicked();

    void on_acSave_triggered();

    void on_acOpen_triggered();

    void on_acSaveHow_triggered();

    void on_pbChoose_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
