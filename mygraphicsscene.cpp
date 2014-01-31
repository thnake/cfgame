#include "mygraphicsscene.h"
#include "connectfour.h"

#include <audioplayer.h>
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
#include <QGradientStop>
#include <QSequentialAnimationGroup>
#include <myanimation.h>
#include <iostream>
#include <QSound>

MyGraphicsScene::MyGraphicsScene(QObject *parent, ConnectFour *game, int selectedDesign) :
    QGraphicsScene(parent)
{

    this->cfgame = game;
    design = selectedDesign;

    MyGraphicsView *view = (MyGraphicsView*)parent;

    setSceneRect(0,0,(cfgame->fieldsx ) * 100,cfgame->fieldsy * 100);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,sceneRect().width(),sceneRect().height());

    addItem(rect);

    QGraphicsRectItem *foreground = new QGraphicsRectItem( 100, 100, 400, 200 );

    foreground->setBrush( QBrush( QColor(118,185,0,128) ) );
    foreground->setZValue(1);
    resizeEvent(NULL);
    drawField();
    loadHistory();

}

void MyGraphicsScene::drawField()
{

    float width = wCol * cfgame->fieldsx;
    float height = wCol * cfgame->fieldsy;

    QImage *_image = new QImage(cfgame->fieldsx * 100, cfgame->fieldsy * 100, QImage::Format_ARGB32);
    QPainter *_painter = new QPainter(_image);

    _painter->setRenderHint(QPainter::Antialiasing, true);


    QLinearGradient *gradient;
    QConicalGradient *cgradient;
    switch(design)
    {
        case 0:
             gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::gray);
            gradient->setColorAt(0.5, Qt::blue);
            gradient->setColorAt(1, Qt::green);
            _painter->setBrush(*gradient);
            break;
        case 1:
            gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::white);
            gradient->setColorAt(0.3, Qt::green);
            gradient->setColorAt(1, Qt::black);
            _painter->setBrush(*gradient);
        break;

        default :
            cgradient = new QConicalGradient(QPoint(width , height / 2 + 10), 0);
            cgradient->setColorAt(0, Qt::blue);
            cgradient->setColorAt(0.5, Qt::darkMagenta);
            cgradient->setColorAt(1, Qt::blue);
            _painter->setBrush(*cgradient);
            break;

    }

    _painter->setPen(Qt::NoPen);
    _painter->drawRect(0, 0, wCol*cfgame->fieldsx,cfgame->fieldsy * wCol);
    _painter->setCompositionMode(QPainter::CompositionMode_Clear);
    _painter->setBrush(QColor(255, 0, 0));
    _painter->drawRect(0, 0, wCol*cfgame->fieldsx, 0);

    int transparentX = 0;
    int transparentY = 0;

    for (unsigned int rows = 0; rows < cfgame->fieldsy; ++rows)
    {
      for (unsigned int columns = 0; columns < cfgame->fieldsx; ++columns)
      {
        _painter->drawEllipse(transparentX+5, transparentY+5, wCol-10, wCol-10);
        transparentX += wCol;
      }

      transparentX = 0;
      transparentY += wCol;
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
        //std::cout << (char)7;
        AudioPlayer ap;
        ap.Play();

    }
    s->setOldPosition(v.toPointF());
    s->setOldVector(*newVector);
}

float MyGraphicsScene::scalarProduct(QPointF u, QPointF v)
{
    return u.x()*v.x() + u.y()*v.y();
}

void MyGraphicsScene::designChip(Chip *chip)
{
    QColor color;
    QGradient gradient;

    if (cfgame->getCurrentPlayer() == 0)
      color = QColor(Qt::yellow);
    else
      color = QColor(Qt::blue);

    // theme


    gradient = QRadialGradient(QPoint(0, 0), 200, QPoint(10, 10));
    if (cfgame->getCurrentPlayer() == 1)
    {
      gradient.setColorAt(0.0, Qt::red);
      gradient.setColorAt(0.35, QColor(200, 200, 0));
      gradient.setColorAt(0.45, QColor(120, 120, 0));

    } else
    {
      gradient.setColorAt(0.0, Qt::red);
      gradient.setColorAt(0.35, QColor(0, 20, 190));
      gradient.setColorAt(0.45, QColor(0, 10, 100));
    }

    gradient.setColorAt(0.5, Qt::black);
    gradient.setColorAt(0.55, color);
    gradient.setColorAt(1.0, color);

    chip->setPen(QPen(color));
    chip->setBrush(QBrush(gradient));

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
        designChip(item);
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



