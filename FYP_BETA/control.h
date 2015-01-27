#ifndef CONTROL_H
#define CONTROL_H
#include <QStringListModel>
#include <QWidget>
#include <QStandardItemModel>
#include <QTreeView>
#include <QtSql>
#include <QFileInfo>
#include <QString>

class control
{

public:
   //control(QStandardItemModel *model);
   //control(QStringListModel *model);
    control(QStandardItemModel *model);
    //fast testing stuff
    void add(QString s);
    //fast testing stuff
    void openFile();
    void sort();
    void printMap();
    void createStatistics();
    void insertRecord(QString s);
    void insertID(QString s);
    void insertTitle(QString s);
    void insertScore(int row, QString s);
    void insertCount(int row, int c);
    ~control();
    QStandardItemModel *smodel;
    QStandardItem *activeItem;
    bool addFlag;

private:
    void addDBRecord();
    QHash<QString, QStandardItemModel*> modelHash;
    QHash<QString, int> hash;
    int count;// row location for an item
    int itemsCount;
    QSqlDatabase db;
    QVector<QString> stringVector;
    QVector<float> floatVector;



};

#endif // CONTROL_H
