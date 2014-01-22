#include "panel.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QRadialGradient>

Panel::Panel(int x, int y, int w, int h, QObject *parent)
    : QObject(parent)
{
    panel = new QGraphicsRectItem( 0, 0, 100, 100, this );
    panel->setPen( QPen(Qt::black, 3) ); // see QColor

    //ball->setBrush( QBrush( QColor("yellow") ) );

     QRadialGradient gradient( 50, 50, 50, 20, 20 );

    gradient.setColorAt( 0.0, Qt::white );
    gradient.setColorAt( 0.7, Qt::yellow );
    gradient.setColorAt( 1.0, Qt::black );

    panel->setBrush( QBrush(gradient));
}
