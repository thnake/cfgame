#include <QApplication>
#include <QtSql/QSqlDatabase>

#include "mygraphicsview.h"
#include "mygraphicsscene.h"
#include "databaseaccessclass.h"

#include "dialog.h"




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    DataBaseAccessClass *dao = new DataBaseAccessClass();

    Dialog d;
    d.dao = dao;

    while (d.exec() == Dialog::Accepted)
    {
        MyGraphicsView *view = new  MyGraphicsView();
        MyGraphicsScene *scene = new MyGraphicsScene(view, d.cfGame, d.getDesign());

        view->setScene(scene);
        view->show();

        return a.exec();
    }
}


