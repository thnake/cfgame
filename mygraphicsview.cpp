#include "mygraphicsview.h"
#include "connectfour.h"
#include "mygraphicsscene.h"
#include "databaseaccessclass.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>

MyGraphicsView::MyGraphicsView(QWidget *parent,  DataBaseAccessClass *dao) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    this->dao = dao;
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "resize: " << event->size();
    fitInView( sceneRect(), Qt::KeepAspectRatio );

}

void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_S)
    {
        qDebug() << "save";
        MyGraphicsScene *s = (MyGraphicsScene*)scene();
        dao->saveGame(s->getCfgame());

    }

    if(event->key() == Qt::Key_F)
    {
        if(!isFullScreen())
        {
            this->showFullScreen();
        }else
        {
            this->showNormal();
        }



    }

}



