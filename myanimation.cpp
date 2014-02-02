#include "myanimation.h"
#include <QPointF>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsItem>




/// <summary>
/// Liefert den 2d-Richtungsvektor der Animation seit der letzten Änderung.
/// </summary>
QPointF MyAnimation::getOldVector() const
{
    return oldVector;
}


/// <summary>
/// Speichert einen 2D-Vektor, der durch die letzte Änderung entstanden ist.
/// </summary>
void MyAnimation::setOldVector(const QPointF &value)
{
    oldVector = value;
}


/// <summary>
/// Liefert die Position vor der letzten Änderung.
/// </summary>
QPointF MyAnimation::getOldPosition() const
{
    return oldPosition;
}


/// <summary>
/// Speichert die Position seit der letzten änderung.
/// </summary>
void MyAnimation::setOldPosition(const QPointF &value)
{
    oldPosition = value;
}


/// <summary>
/// Konstruktor der Klasse MyAnimation.
/// </summary>
/// <param name="target">QObject, das animiert werden soll</param>
/// <param name="propertyName">Property, die zur Animation  benutzt werden soll</param>
MyAnimation::MyAnimation(QObject * target, const QByteArray & propertyName) :
    QPropertyAnimation(target, propertyName)
{

}

/// <summary>
/// Konstruktor der Klasse MyAnimation.
/// </summary>
MyAnimation::MyAnimation(QObject *parent) : QPropertyAnimation(parent)
{

}







