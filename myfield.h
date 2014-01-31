#ifndef MYFIELD_H
#define MYFIELD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class MyField : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
     Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    MyField();
};

#endif // MYFIELD_H
