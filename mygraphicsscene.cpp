#include "mygraphicsscene.h"
#include "connectfour.h"

#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QtWidgets>
#include <QEasingCurve>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <mygraphicsview.h>
#include <cstddef>
#include <QGraphicsScene>
#include <QThread>
#include <QSequentialAnimationGroup>
#include <myanimation.h>

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
    resizeEvent(NULL);
    drawField();

    loadHistory();


}

void MyGraphicsScene::drawField()
{
  //  checkFieldSize();

   // calculateFieldWidthAndHeight();


    QImage *_image = new QImage(cfgame->fieldsx * 100, cfgame->fieldsy * 100, QImage::Format_ARGB32);
    QPainter *_painter = new QPainter(_image);

    _painter->setRenderHint(QPainter::Antialiasing, true);
    _painter->setBrush(QColor(118, 185, 0, 255));
    _painter->setPen(Qt::NoPen);
    _painter->drawRect(0, 0, wCol*cfgame->fieldsx,cfgame->fieldsy * wCol);
    _painter->setCompositionMode(QPainter::CompositionMode_Clear);
    _painter->setBrush(QColor(255, 0, 0));
    _painter->drawRect(0, 0, wCol*cfgame->fieldsx, 0);

    //Building the field with the correct number of columns and rows
    int positionHoleX = 0;
    int positionHoleY = 0;

    for (unsigned int rows = 0; rows < cfgame->fieldsy; ++rows)
    {
      for (unsigned int columns = 0; columns < cfgame->fieldsx; ++columns)
      {
        _painter->drawEllipse(positionHoleX, positionHoleY, wCol, wCol);
        positionHoleX += wCol;
      }

      positionHoleX = 0;
      positionHoleY += wCol;
    }

    _painter->end();

    QGraphicsPixmapItem *_field = new QGraphicsPixmapItem();
    _field->setPixmap(QPixmap::fromImage(*_image));
    _field->setZValue(1);
    _field->setTransformationMode(Qt::SmoothTransformation);
    _field->pos().setX(0);
    _field->pos().setY(0);
    //setSceneRect(0, 0, _width, _height);

    addItem(_field);
}



void MyGraphicsScene::keyPressEvent(QKeyEvent *event)
{

}

void MyGraphicsScene::bounceSound(QVariant v)
{
   // qDebug() << "bounce";
    MyAnimation *s = (MyAnimation*)QObject::sender();
    QPointF *newVector = new QPointF();

    newVector->setX(s->getOldPosition().x() - v.toPointF().x());
    newVector->setY(s->getOldPosition().y() - v.toPointF().y());

    float sp = this->scalarProduct(*newVector, s->getOldVector());

    if(sp < 0)
    {
        qDebug() << "bounce";
    }
    s->setOldPosition(v.toPointF());
    s->setOldVector(*newVector);
}

float MyGraphicsScene::scalarProduct(QPointF u, QPointF v)
{
    return u.x()*v.x() + u.y()*v.y();
}


void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(false)
    {
        qDebug() << event->scenePos().y();

        item->setGradient(event->pos());

    }
}

void MyGraphicsScene::resizeEvent(QResizeEvent *event)
{
    wCol = (int)sceneRect().width()/cfgame->fieldsx;
}
ConnectFour *MyGraphicsScene::getCfgame() const
{
    return cfgame;
}

void MyGraphicsScene::setCfgame(ConnectFour *value)
{
    cfgame = value;
}

void MyGraphicsScene::loadHistory()
{
    QString h = cfgame->getHistoryToLoad();
    qDebug() << h;
    for(int i = 0; i < h.length(); i++)
    {
        makeMove(h[i].digitValue(), true);

    }

    animationGroup.start();
    cfgame->setHistoryToLoad("");
}

void  MyGraphicsScene::makeMove(int column, bool grouped)
{
    int stacked = cfgame->setStone(column);
    if(stacked > -1)
    {
        item  = new Chip(column*wCol, 0-wCol, wCol, wCol);
        item->setVisible(true);
        item->setPlayer(cfgame->currentPlayer);
        MyAnimation *animation  = new MyAnimation(item, "pos");

        addItem(item);
        QPointF p(item->pos().x(), sceneRect().height() - wCol*stacked);
        animation->setDuration(1000);
        animation->setEndValue(p);
        animation->setEasingCurve(QEasingCurve::OutBounce);
        if(!grouped) {
           animation->start();
        }else{
            animation->setEasingCurve(QEasingCurve::InOutSine);
            animation->setDuration(150);
            animationGroup.addAnimation(animation);
        }


        connect(animation,SIGNAL(valueChanged(QVariant)),SLOT(bounceSound(QVariant)));


    }
    else
    {
        // todo
        // ungültiger zug
        // sound
        qDebug() << "ungültiger Zug";
    }
}


void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    
    if(cfgame->getWinner() == 0)
    {
        int col = event->scenePos().x() / wCol;

        // click in Spielfeld
        if (col > -1 && col < cfgame->fieldsx && event->scenePos().x() >= 0)
        {
            makeMove(col, false);
        }
    }

}



