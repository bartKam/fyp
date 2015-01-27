#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QStandardItemModel>
#include <QTreeView>
#include "control.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    //QStringListModel *smodel = new QStringListModel;
    QStandardItemModel  *smodel = new 	QStandardItemModel ;
    c = new control(smodel);
    ui->setupUi(this);
    ui->mainListView->setModel(smodel);
    ui->tableView->setModel(smodel);
    //ui->treeView->setModel(smodel);

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_openFilebtn_clicked()
{
    ui->lbl1->setText("Clicked");
   // c->add();
   c->openFile();
}

void MainWindow::on_sortbtn_clicked()
{
    c->sort();
}

void MainWindow::on_printHashbtn_clicked()
{
    c->printMap();
}
