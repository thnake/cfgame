#ifndef MYGRADIENT_H
#define MYGRADIENT_H

#include <QLinearGradient>
#include <QColor>
#include <QObject>
#include <QPointF>


class MyGradient : public QObject, public QLinearGradient
{
    Q_OBJECT
    Q_PROPERTY(float Middle READ getMiddle() WRITE setMiddle())

public:
    MyGradient();
    MyGradient(QPoint p, QPoint q);

    QColor cStart;
    QColor cMiddle;
    QColor cEnd;

    float start;
    float middle;
    float end;

    float getMiddle();
    void setMiddle(float value);


    void setCStart(const QColor &value, float s);

    void setCMiddle(const QColor &value, float m);

    void setCEnd(const QColor &value, float e);
};

#endif // MYGRADIENT_H
