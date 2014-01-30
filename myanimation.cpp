#include "myanimation.h"
#include <QPointF>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsItem>




QPointF MyAnimation::getOldVector() const
{
    return oldVector;
}

void MyAnimation::setOldVector(const QPointF &value)
{
    oldVector = value;
}

QPointF MyAnimation::getOldPosition() const
{
    return oldPosition;
}

void MyAnimation::setOldPosition(const QPointF &value)
{
    oldPosition = value;
}
MyAnimation::MyAnimation(QObject * target, const QByteArray & propertyName) :
    QPropertyAnimation(target, propertyName)
{

}







