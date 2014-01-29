#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include "chip.h"
#include "connectfour.h"
#include "panel.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <cstddef>
#include <QResizeEvent>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent ,ConnectFour *game);

    ConnectFour *getCfgame() const;
    void setCfgame(ConnectFour *value);

signals:
    
public slots:

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void resizeEvent(QResizeEvent * event );
private:
    int wCol = 0;
    void makeMove(int column);
    void loadHistory();

    ConnectFour *cfgame;
    Chip *item = NULL;


};

#endif
