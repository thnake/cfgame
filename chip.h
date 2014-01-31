#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>
#include <QRadialGradient>

class Chip : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit Chip(int x, int y, int w, int h, QObject *parent=NULL);
    void setDesign();
    void setPlayer(int p);
    void setGradient(QPointF p);
    QPointF *getCenter();


private:
    QRadialGradient gradient;

};

#endif // MYGRAPHICSITEM_H
