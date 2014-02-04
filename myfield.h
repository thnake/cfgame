#ifndef MYFIELD_H
#define MYFIELD_H

#include <QGraphicsPixmapItem>
#include <QObject>


/// <summary>
/// Klasse für das Spielbrett. Die Mehrfachvererbung ist
/// für die Animation notwendig
/// </summary>
class MyField : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
     Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    MyField();
};

#endif // MYFIELD_H
