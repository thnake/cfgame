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
    explicit Chip(int x, int y, int w, int h, int player, QObject *parent=NULL);
    void setDesign();
    int getPlayer();
    void setGradient(QPointF p);
    QPointF *getCenter();


private:
    QRadialGradient gradient;
    int player;

};

#endif // MYGRAPHICSITEM_H
