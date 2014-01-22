#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <databaseaccessclass.h>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = 0, DataBaseAccessClass *dao = 0);

private:
    DataBaseAccessClass *dao;

signals:
    
public slots:
    
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MYGRAPHICSVIEW_H
