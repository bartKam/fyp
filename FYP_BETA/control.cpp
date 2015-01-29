

#include <QtWidgets>
#include "control.h"
#include "qcustomplot.h"
#include <QFileDialog>
#include <QTextStream>
#include <QPen>
#include <cstdio>

//change

using namespace std;
//control::control(QStandardItemModel *model)
//control::control(QStringListModel *model)
control::control(QStandardItemModel *model)

{

 count =0;
 itemsCount=0;
 smodel=model;
 db=QSqlDatabase::addDatabase("QSQLITE");
 db.setDatabaseName("D:/FYP/db/FYP.sqlite");
 activeItem= new QStandardItem("");
 addFlag=true;
 //query = new QSqlQuery(*db);
 if(db.open()){

     qDebug()<< "ok";
 }
}


void control::openFile(){





    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Files (*.txt)"));

//QWidget * parent = 0;


    QString fileName = QFileDialog::getOpenFileName(NULL, "Open File",
                                                      "",
                                                      "Files (*.txt)");


    QFile file(fileName);

   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
   ;

   }

  QTextStream in(&file);





   while (!in.atEnd()) {
       QString line = in.readLine();
       insertRecord(line);
       //add(line);

       //product/productId: 0-18
        //printf ("linekkk");
       // printf (line.toLocal8Bit().constData());
        //fonts.append(line);
      }
    qDebug() << itemsCount;
   createStatistics();
   file.close();

//smodel->setStringList(fonts);
}
void control::add(QString s){
std::string str1 = s.toLocal8Bit().constData();


    if(str1.compare(0,18,"product/productId:") == 0){
        QStandardItem *idItem = new QStandardItem(s);
        itemsCount++;

        if(idItem->text().compare(activeItem->text())==0){
            // record exits and was used last time
            // its row location is current "count" -1
            QStandardItem *tempItem;

            tempItem = smodel->item(count-1,2);
            int newCount ;
            newCount = (tempItem->text().toInt())+1;
            insertCount(count-1, newCount);


            //QVariant tQV;
//            tQV = tempItem->data(Qt::UserRole);

            // append itneger at location - row = "count" -1(just found), column 2(hardcoded)
            addFlag=false;
        }
        else if(false){
            // record exists in the model butit was update som time ago
            // find its row location
            // append ineger at location - row(just found), column 2(hardcoded)
            addFlag=false;
        }
        else{
            // new record - create it
            // update active record with this one
            activeItem=idItem;
            insertID(s);
            addFlag=true;

        }
    }
    //creating a new entry - adding prduct/title and initialising all numerical values
    if(addFlag==true){
        if(str1.compare(0,14,"product/title:") == 0){
        insertTitle(s);
        insertCount(count, 1);
        // count++;
        }
        if(str1.compare(0,13,"review/score:") == 0){
        float newScore =s.right(3).toFloat();
        QString newS = QString::number(newScore);
        insertScore(count, newS);
        count++;
        }


    }
    //entry already exists, checking existing value and addig new review/score
    if(addFlag==false){
       if(str1.compare(0,13,"review/score:") == 0){

              QStandardItem *tempItem;
              tempItem = smodel->item(count-1,3);
              float newScore =s.right(3).toFloat()+tempItem->text().toFloat();
              QString newS = QString::number(newScore);
              insertScore(count-1,newS);
                  }
    }






}

void control::insertRecord(QString s){
std::string str1 = s.toLocal8Bit().constData();
QString temp="";

//time to date

//    int unixTime = 1234567890;
//    QDateTime timestamp;
//    timestamp.setTime_t(unixTime);
//    qDebug() << timestamp.toString(Qt::SystemLocaleShortDate);



    //QSqlQuery query;
       // query.exec("INSERT INTO main.amazon (id, title, price, userID, uName, helpfulness , score , time , summary , text) "
    //               "VALUES ('id', 'title', 65000,'userID','uName',8,8,1168300800,'summary','text')");
/*
        QSqlQuery query;
            query.prepare("INSERT INTO main.amazon (id, title, price, userID, uName, helpfulness , score , time , summary , text) "
                          "VALUES (:id, :title, :price, :userID, :uName, :helpfulness , :score , :time , :summary , :text) ");
*/

    if(str1.compare(0,18,"product/productId:") == 0){
       // qDebug()<< s.right(s.length()-19);
        stringVector.append(s.right(s.length()-19));
    }
    if(str1.compare(0,14,"product/title:") == 0){
       // qDebug()<< s.right(s.length()-15);
        stringVector.append(s.right(s.length()-15));
    }
    if(str1.compare(0,14,"review/userId:") == 0){
      //   qDebug()<< s.right(s.length()-15);
         stringVector.append(s.right(s.length()-15));
     }
     if(str1.compare(0,19,"review/profileName:") == 0){
     //    qDebug()<< s.right(s.length()-20);
         stringVector.append(s.right(s.length()-20));
     }
     if(str1.compare(0,15,"review/summary:") == 0){
      //   qDebug()<< s.right(s.length()-16);
         stringVector.append(s.right(s.length()-16));
     }
     if(str1.compare(0,12,"review/text:") == 0){
       //  qDebug()<< s.right(s.length()-13);
         stringVector.append(s.right(s.length()-13));
         addDBRecord();
     }
     // numerical data
      if(str1.compare(0,14,"product/price:") == 0){
         // qDebug()<< s.right(s.length()-15);
        temp=s.right(s.length()-15);
             if(temp.compare("unknown")){
             floatVector.append(0);
            }
            else{
            floatVector.append(temp.toFloat());
             }

      }
      if(str1.compare(0,13,"review/score:") == 0){
          temp = s.right(s.length()-14);
           floatVector.append(temp.toFloat());
      }
      if(str1.compare(0,12,"review/time:") == 0){
          temp = s.right(s.length()-13);
           floatVector.append(temp.toFloat());
      }
      if(str1.compare(0,19,"review/helpfulness:") == 0){
         temp= s.right(s.length()-20);
         QStringList list;
         list= temp.split('/');
         floatVector.append( list.at(0).toFloat()/ list.at(1).toFloat());
      }


//      for ( int i = 0; i < stringVector.size(); i++) {
//               qDebug()<<stringVector[i] << " ";
//            }
//      for ( int j = 0; j < floatVector.size(); j++) {
//               qDebug()<< floatVector[j] << " ";
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":id", "1001");
//            }
//            if(str1.compare(0,18,"product/title:") == 0){
//            query.bindValue(":title", "Thad Beaumont");
//            }
//            if(str1.compare(0,18,"product/price:") == 0){
//            query.bindValue(":price", 65000);
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":userID", "1001");
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":uName", "Thad Beaumont");
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":helpfulness", 65000);
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":score", 1001);
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":time", 0);
//            }
//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":summary", "65000");
//            }

//            if(str1.compare(0,18,"product/productId:") == 0){
//            query.bindValue(":text", "1001");
//            query.exec();
//            query.clear();
//            }




//    std::string str1 = s.toLocal8Bit().constData();





//    if(str1.compare(0,18,"product/productId:") == 0){
//    QStandardItem *item = new QStandardItem(s);
//    smodel->setItem(count,0,item);
//    }
//    if(str1.compare(0,14,"product/title:") == 0){
//    QStandardItem *item = new QStandardItem(s);
//    smodel->setItem(count,1,item);
//    QStandardItem *pcount = new QStandardItem;
//    pcount->setData(QVariant((uint)1), Qt::DisplayRole);
//    smodel->setItem(count,2,pcount);
//    count++;
//    }

//    }
}
void control::addDBRecord(){
    QSqlQuery query;
        query.prepare("INSERT INTO main.amazon (id, title, price, userID, uName, helpfulness , score , time , summary , text) "
                      "VALUES (:id, :title, :price, :userID, :uName, :helpfulness , :score , :time , :summary , :text) ");

            query.bindValue(":id", stringVector.at(0));
            query.bindValue(":title", stringVector.at(1));
            query.bindValue(":price", floatVector.at(0));
            query.bindValue(":userID", stringVector.at(2));
            query.bindValue(":uName", stringVector.at(3));
            query.bindValue(":helpfulness", floatVector.at(1));
            query.bindValue(":score", floatVector.at(2));
            query.bindValue(":time", floatVector.at(3));
            query.bindValue(":summary", stringVector.at(4));
            query.bindValue(":text", stringVector.at(5));
            count++;
            qDebug() << count;
            query.exec();
            stringVector.clear();
            floatVector.clear();
            query.clear();

  }

void control::printMap(){

/*
    hash.insert("January", 1);
    hash.insert("February", 2);
    hash.insert("December", 12);

    QHashIterator<QString, int> i(hash);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
    }
    */
    QHashIterator<QString, QStandardItemModel*> i(modelHash);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
    }


}


void control::createStatistics(){

    QPixmap *qpmap = new QPixmap(100,40) ;
    QPainter painter(qpmap);




    int i=0;

    for (i=0; i<count; i++){

       float percentage = smodel->item(i,3)->text().toFloat()/ (smodel->item(i,2)->text().toFloat()*5)*100;
       QString newS = QString::number(percentage);
       newS= newS+ " %";
       QStandardItem *item = new QStandardItem(newS);
       smodel->setItem(i,4,item);

       QRectF r1(QPoint(0, 0), QSize(percentage, 40));
       QRectF r2(QPoint(percentage, 0), QSize(100-percentage, 40));

       if(percentage>75){
       painter.fillRect(r1,QColor("Green"));
       }
       else if(percentage>50){
       painter.fillRect(r1,QColor("Yellow"));
       }
       else if(percentage>25){
       painter.fillRect(r1,QColor("Orange"));
       }
       else{
       painter.fillRect(r1,QColor("Red"));
       }
       painter.fillRect(r2,QColor("Grey"));
       QIcon undoicon = QIcon(*qpmap);
       QStandardItem *icon = new QStandardItem(undoicon,"");
       smodel->setItem(i,5,icon);
    }


}

void control::insertID(QString s){
    QStandardItem *item = new QStandardItem(s);
    smodel->setItem(count,0,item);
    QStandardItemModel  *tempmodel = new QStandardItemModel ;
    modelHash.insert(item->text(), tempmodel);
}

void control::insertTitle(QString s){
    QStandardItem *item = new QStandardItem(s);
    smodel->setItem(count,1,item);

}

void control::insertCount(int row, int c){
    QStandardItem *pcount = new QStandardItem;
    pcount->setData(QVariant((uint)c), Qt::DisplayRole);
    smodel->setItem(row,2,pcount);
}
void control::insertScore(int c, QString s){
    QStandardItem *item = new QStandardItem(s);
    //qDebug()<< s.right(3);
    smodel->setItem(c,3,item);

}

void control::sort(){
   // smodel->sort(2,Qt::AscendingOrder);
    smodel->sort(2,Qt::DescendingOrder);
}

control::~control()
{

}

