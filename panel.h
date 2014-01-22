#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>

class Panel : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit Panel(int x, int y, int w, int h, QObject *parent=NULL);
    //explicit MyGraphicsItem( )
    int x,y;
private:
    QGraphicsRectItem *panel;
};

#endif // MYGRAPHICSITEM_H
