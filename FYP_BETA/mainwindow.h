#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "control.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    control *c;

private slots:


    void on_openFilebtn_clicked();

    void on_sortbtn_clicked();

    void on_printHashbtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
