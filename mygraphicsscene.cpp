#include "mygraphicsscene.h"
#include "connectfour.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QEasingCurve>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <mygraphicsview.h>
#include <cstddef>
#include <QGraphicsScene>


MyGraphicsScene::MyGraphicsScene(QObject *parent, ConnectFour *game) :
    QGraphicsScene(parent)
{

    this->cfgame = game;

    MyGraphicsView *view = (MyGraphicsView*)parent;

    setSceneRect(0,0,(cfgame->fieldsx ) * 100,cfgame->fieldsy * 100);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,sceneRect().width(),sceneRect().height());

    addItem(rect);

    // ein halbtransparenter Vordergrund:
    QGraphicsRectItem *foreground = new QGraphicsRectItem( 100, 100, 400, 200 );
    //addItem(foreground);
    // HTW grün: http://www.htw-berlin.de/hochschulstruktur/zentrale-referate/presse-und-oeffentlichkeitsarbeit/corporate-design/farbklima-schriften/

    foreground->setBrush( QBrush( QColor(118,185,0,128) ) );
    foreground->setZValue(1);

}



void MyGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
    return;
    qDebug() << "key press.: " << event->key();
    /*
    QPropertyAnimation *animation  = new QPropertyAnimation( item, "pos" );
    animation->setDuration(2000);
    animation->setEndValue( QPoint(qrand() % (600-100), qrand() % (400-100) ) );
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->start();
    */
}





void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(false)
    {
        qDebug() << event->scenePos().y();

        item->setGradient(event->pos());

    }
}
ConnectFour *MyGraphicsScene::getCfgame() const
{
    return cfgame;
}

void MyGraphicsScene::setCfgame(ConnectFour *value)
{
    cfgame = value;
}



void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    
    if(cfgame->getWinner() == 0)
    {
        int wCol = (int)sceneRect().width()/cfgame->fieldsx;
        int col = event->scenePos().x() / wCol;

        qDebug() << col;
        if (col > -1 && col < cfgame->fieldsx && event->scenePos().x() >= 0)
        {
            // click in Spielfeld
            int stacked = cfgame->setStone(col);
            if(stacked > -1)
            {
                item  = new Chip(col*wCol, 0-wCol, wCol, wCol);
                item->setVisible(true);
                //item->setBrush();
                item->setPlayer(cfgame->currentPlayer);
                QPropertyAnimation *animation  = new QPropertyAnimation(item, "pos");
                addItem(item);
                QPointF p(item->pos().x(),sceneRect().height() - wCol*stacked);
                animation->setDuration(1000);
                animation->setEndValue(p);
                animation->setEasingCurve(QEasingCurve::OutBounce);
                animation->start();
            }

        }
    }

}



