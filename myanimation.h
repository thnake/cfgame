#ifndef MYANIMATION_H
#define MYANIMATION_H
#include <QPropertyAnimation>
#include <QPointF>

class MyAnimation : public QPropertyAnimation
{
private:
    QObject *item;
    QPointF oldVector;
    QPointF oldPosition;
    bool directionChanged;

public:
    MyAnimation(QObject * target, const QByteArray & propertyName);



    QPointF getOldVector() const;
    void setOldVector(const QPointF &value);

    QPointF getOldPosition() const;
    void setOldPosition(const QPointF &value);

protected:

};

#endif // MYANIMATION_H
