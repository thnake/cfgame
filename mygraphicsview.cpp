#include "mygraphicsview.h"
#include "connectfour.h"
#include "mygraphicsscene.h"
#include "databaseaccessclass.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>



/// <summary>
/// Konstruktor der Klasse MyGraphicsView.
/// </summary>
/// <param name="parent">Parentobjekt</param>
/// <param name="dao">Objekt zum Zugriff auf die Spieledatenbank</param>
MyGraphicsView::MyGraphicsView(QWidget *parent,  DataBaseAccessClass *dao) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    this->dao = dao;
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}


/// <summary>
/// Zum erhalt der Seitenverhältnisse
/// </summary>
void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "resize: " << event->size();
    fitInView( sceneRect(), Qt::KeepAspectRatio );

}


/// <summary>
/// Fängt benutzereingaben ab.
/// [Ss] speichert das Spiel
/// [Ff] aktiviert und deaktiviert den Fullscreen modus
/// </summary>
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



