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
#include <QRadialGradient>
#include <QSequentialAnimationGroup>
#include <myanimation.h>
#include <iostream>
#include <QSound>

#include <qglobal.h>
#include <QTime>


/// <summary>
/// Konstruktor der Klasse MyGraphicScene. Liefert eine Instanz zur Darstellung des
/// Connect Four-Spiels
/// </summary>
/// <param name="parent">Parentobjekt</param>
/// <param name="game">Instanz des Spiels</param>
/// <param name="game">gewähltes Design</param>
MyGraphicsScene::MyGraphicsScene(QObject *parent, ConnectFour *game, int selectedDesign) :
    QGraphicsScene(parent)
{

    this->cfgame = game;
    design = selectedDesign;

    ai.setDifficulty(game->getDifficulty());

    setSceneRect(0,0,(cfgame->fieldsx ) * 100,cfgame->fieldsy * 100);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,sceneRect().width(),sceneRect().height());

    addItem(rect);

    QGraphicsRectItem *foreground = new QGraphicsRectItem( 100, 100, 400, 200 );

    foreground->setBrush( QBrush( QColor(118,185,0,128) ) );
    foreground->setZValue(1);
    resizeEvent(NULL);
    createField();
    loadHistory();

    if(cfgame->history.length() == 0 && cfgame->getCurrentPlayer() == 2)
    {
        aiMove();
    }

    qDebug() << "starting";
    qDebug() << cfgame->getStartingPlayer();
}


/// <summary>
/// Erzeugt das überdeckende Spielfeld
/// </summary>
void MyGraphicsScene::createField()
{

    float width = wCol * cfgame->fieldsx;
    float height = wCol * cfgame->fieldsy;

    QImage *img = new QImage(cfgame->fieldsx * 100, cfgame->fieldsy * 100, QImage::Format_ARGB32);
    QPainter *painter = new QPainter(img);

    painter->setRenderHint(QPainter::Antialiasing, true);


    QLinearGradient *gradient;
    QConicalGradient *cgradient;
    switch(design)
    {
        case 0:
             gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::gray);
            gradient->setColorAt(0.5, Qt::blue);
            gradient->setColorAt(1, Qt::green);
            painter->setBrush(*gradient);
            break;

        case 1:
            gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::white);
            gradient->setColorAt(0.3, Qt::green);
            gradient->setColorAt(1, Qt::black);
            painter->setBrush(*gradient);
        break;

        default :
            cgradient = new QConicalGradient(QPoint(width , height / 2 + 10), 0);
            cgradient->setColorAt(0, Qt::blue);
            cgradient->setColorAt(0.5, Qt::darkMagenta);
            cgradient->setColorAt(1, Qt::blue);
            painter->setBrush(*cgradient);
            break;
    }

    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, wCol*cfgame->fieldsx,cfgame->fieldsy * wCol);
    painter->setCompositionMode(QPainter::CompositionMode_Clear);
    painter->setBrush(QColor(255, 0, 0));
    painter->drawRect(0, 0, wCol*cfgame->fieldsx, 0);

    int transparentX = 0;
    int transparentY = 0;

    for (unsigned int rows = 0; rows < cfgame->fieldsy; ++rows)
    {
      for (unsigned int columns = 0; columns < cfgame->fieldsx; ++columns)
      {
        painter->drawEllipse(transparentX+5, transparentY+5, wCol-10, wCol-10);
        transparentX += wCol;
      }

      transparentX = 0;
      transparentY += wCol;
    }

    painter->end();

    fieldItem = new MyField();
    fieldItem->setPixmap(QPixmap::fromImage(*img));
    fieldItem->setZValue(1);
    fieldItem->setTransformationMode(Qt::SmoothTransformation);
    fieldItem->pos().setX(0);
    fieldItem->pos().setY(0);

    addItem(fieldItem);
}


/// <summary>
/// Speichert das Spiel ab.
/// </summary>
void MyGraphicsScene::saveGame()
{
    MyGraphicsView *view = (MyGraphicsView*)parent();

}

/// <summary>
/// Animation für das Spielfeld. Stellt ein erschüttern dar. Zum Anzeigen von ungültigen Zügen
/// </summary>
void MyGraphicsScene::shatterFieldAnimation()
{
    QPointF pEnd(0-fieldItem->boundingRect().width()/20, 0);
    QSequentialAnimationGroup *ag = new QSequentialAnimationGroup();

    MyAnimation *shake  = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);

    pEnd.setX(0+fieldItem->boundingRect().width()/20);
    shake = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);

    pEnd.setX(0);
    shake = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);
    ag->start(QAbstractAnimation::DeleteWhenStopped);

}


/// <summary>
/// Setzt das Design des Spielsteins fest
/// </summary>
/// <param name="chip">Instanz des Spielsteins</param>
void MyGraphicsScene::designChip(Chip* chip)
{
  QColor color;
  QRadialGradient gradient;


  if (this->cfgame->getCurrentPlayer() == 1)
    color = QColor(Qt::yellow);
  else
    color = QColor(Qt::blue);

  switch (design)
  {
    case 0 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::yellow);
      else
        color = QColor(Qt::blue);
      break;

    case 1 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::green);
      else
        color = QColor(Qt::red);
      break;

    case 2 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::magenta);
      else
        color = QColor(Qt::cyan);
      break;

    default :

      break;
  }

  chip->setBrush(QBrush(color));
  chip->setPen(QPen(Qt::black));
  chip->setZValue(-1);

}

/// <summary>
/// Slot für das Abspielen von Bounce geräuschen. Bei jeder Richtungsänderung des Objekts kann zur
/// entsprechenden Easingkurve das geräusch abgespielt werden. Die Soundwiedergabe ist nicht implementiert.
/// </summary>
/// <param name="v">Sender des Signals</param>
void MyGraphicsScene::bounceSound(QVariant v)
{

    MyAnimation *s = (MyAnimation*)QObject::sender();
    QPointF *newVector = new QPointF();

    newVector->setX(s->getOldPosition().x() - v.toPointF().x());
    newVector->setY(s->getOldPosition().y() - v.toPointF().y());

    float sp = this->scalarProduct(*newVector, s->getOldVector());

    if(sp < 0)
    {
        qDebug() << "bounce sound abspielen";
    }
    s->setOldPosition(v.toPointF());
    s->setOldVector(*newVector);
}

/// <summary>
/// Liefert das Skalarprodukt zweier 2d-Vektoren
/// </summary>
float MyGraphicsScene::scalarProduct(QPointF u, QPointF v)
{
    return u.x()*v.x() + u.y()*v.y();
}

/// <summary>
/// Fängt das Resize Event ab und berechnet die Spaltenbreite
/// </summary>
void MyGraphicsScene::resizeEvent(QResizeEvent *event)
{
    wCol = (int)sceneRect().width()/cfgame->fieldsx;
}

/// <summary>
/// Liefert einen Zeiger auf die Instanz der Spielklasse
/// </summary>
ConnectFour *MyGraphicsScene::getCfgame() const
{
    return cfgame;
}

/// <summary>
/// Setzt die Instanz der Spielklasse fest
/// </summary>
void MyGraphicsScene::setCfgame(ConnectFour *value)
{
    cfgame = value;
}

/// <summary>
/// Rekonstruiert eine Historie, die in cfGame bereit steht
/// </summary>
void MyGraphicsScene::loadHistory()
{
    QString h = cfgame->getHistoryToLoad();
    for(int i = 0; i < h.length(); i++)
    {
        makeMove(h[i].digitValue(), true);
    }

    animationGroup.start(QAbstractAnimation::DeleteWhenStopped);
    cfgame->setHistoryToLoad("");

}

/// <summary>
/// Animiert das Fallen eines Spielsteins
/// </summary>
/// <param name="chip">Zeiger auf den Spielstein</param>
/// <param name="end">Punkt, zu dem der Stein fallen soll</param>
/// <param name="grouped">Entscheidet, ob eine Gruppenanimation genutzt werden soll</param>
void MyGraphicsScene::animateChipDrop(Chip *chip, QPointF end, bool grouped)
{

    MyAnimation *animation = chip->animate(end, 1000, QEasingCurve::OutBounce);
    connect(animation,SIGNAL(valueChanged(QVariant)),SLOT(bounceSound(QVariant)));

     if(!grouped) {
        animation->start(QAbstractAnimation::DeleteWhenStopped);
     }else{
         animation->setEasingCurve(QEasingCurve::InOutSine);
         animation->setDuration(150);
         animationGroup.addAnimation(animation);
     }

}


/// <summary>
/// Lässt die KI einen Zug durchführen
/// </summary>
void MyGraphicsScene::aiMove()
{
    int row = 0;
    do{
        row = ai.getMove(cfgame->fieldsx);

    }while(cfgame->checkMove(row) == false);
    makeMove(row, false);
}

/// <summary>
/// Lässt ein Label mit einer Nachricht aufpoppen
/// </summary>
/// <param name="msg">Nachricht an den Spieler</param>
void MyGraphicsScene::showMessage(QString msg)
{
    QLabel *l = new QLabel();
    l->setObjectName("lblMessage");
    QString text = "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:500;\">" + msg + "</span></p></body></html>";


    QByteArray byteArray = text.toUtf8();
    const char* cString = byteArray.constData();

    QString text2 = QString::fromUtf8(cString);
    l->setText(QApplication::translate("Winner", cString, 0));
    l->show();

}


/// <summary>
/// Signalisiert dem Spieler den Endzustand des Spiels durch eine Animation
/// </summary>
void MyGraphicsScene::animateVictory()
{

    MyAnimation *animation;
    QVector<Chip*> wchips;

    //qsrand(QTime::currentTime().msec());
    for(int i=0; i<chips.count(); i++)
    {    
        animation = chips[i]->animate(getRandomPoint(), 500,  QEasingCurve::Linear);
        connect(animation, SIGNAL(finished()), SLOT(animateVictory()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

/// <summary>
/// Liefert einen zufälligen Punkt aus dem Feld zurück.
/// </summary>
QPointF MyGraphicsScene::getRandomPoint()
{
    float x = qrand() % (int)fieldItem->boundingRect().width();
    float y = qrand() % (int)fieldItem->boundingRect().height();
    QPointF res;
    res.setX(x);
    res.setY(y);
    return res;
}

/// <summary>
/// Führt einen Spielzug durch.
/// </summary>
/// <param name="column">Spalte, die in dem Zug benutzt werden soll</param>
/// <param name="loadHistory">Gibt an, dass mit diesem Zug die Historie geladen wird</param>
int MyGraphicsScene::makeMove(int column, bool loadHistory)
{


    int stacked = cfgame->setStone(column);
    if(stacked > -1)
    {
        chip  = new Chip(column*wCol, 0-wCol, wCol, wCol,cfgame->getLastPlayer());
        chip->setVisible(true);
        QPointF p(chip->pos().x(), sceneRect().height() - wCol*stacked);
        qDebug() << chip->pos().x();
        designChip(chip);
        addItem(chip);
        animateChipDrop(chip, p, loadHistory);
        chips.push_back(chip);
    }
    else
    {
        shatterFieldAnimation();
    }

    if(cfgame->getWinner() != 0)
    {
        if(cfgame->getWinner() == 1)
        {
            showMessage(cfgame->getName1()+ " wins!!!");
        }
        else
        {
            showMessage(cfgame->getName2()+ " wins!!! :D");
        }

        animateVictory();
        saveGame();

    }else if(cfgame->checkDraw())
    {

        showMessage("Draw!!!");
        saveGame();
        animateVictory();

    }
    return stacked;

}


/// <summary>
/// Fängt den Spieler click ab, der seine Spalte durch anclicken wählen soll.
/// </summary>
/// <param name="event">enthält die clickinformationen</param>
void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(cfgame->getWinner() == 0)
    {
        int col = event->scenePos().x() / wCol;

        // click in Spielfeld
        if (col > -1 && col < cfgame->fieldsx && event->scenePos().x() >= 0)
        {

            int stacked = makeMove(col, false);
            if(cfgame->getDifficulty() != 0 && stacked > -1 && cfgame->getWinner() == 0)
            {

                this->aiMove();
            }
        }
    }
}



