#include "mygradient.h"
#include <QLinearGradient>
#include <QObject>
#include <QDebug>

MyGradient::MyGradient() : QLinearGradient(), QObject()
{
}

MyGradient::MyGradient(QPoint p, QPoint q) : QLinearGradient(p,q), QObject(NULL)
{

}


void MyGradient::setCEnd(const QColor &value, float e)
{
    cEnd = value;
    this->end = e;
}


void MyGradient::setCMiddle(const QColor &value, float m)
{
    cMiddle = value;
    this->middle = m;
}


void MyGradient::setCStart(const QColor &value, float s)
{
    cStart = value;
    this->start = s;
}


float MyGradient::getMiddle()
{
    return middle;
}



void MyGradient::setMiddle(float value)
{

    stops()[2].first = (qreal)value;
    stops()[2].second = Qt::green;

    //setColorAt(value, Qt::white);
    middle = value;
    qDebug() << stops().count();
/*
    setColorAt(0,Qt::black);
    setColorAt(value,Qt::white);
    setColorAt(1,Qt::black);
*/
}

