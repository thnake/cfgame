#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include "chip.h"
#include "connectfour.h"
#include "panel.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <cstddef>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include <QPointF>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent ,ConnectFour *game, int selectedDesign);

    ConnectFour *getCfgame() const;
    void setCfgame(ConnectFour *value);
    float scalarProduct(QPointF u, QPointF v);
    void designChip(Chip *chip);

signals:
    
public slots:
    void bounceSound(QVariant v);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void resizeEvent(QResizeEvent * event );

private:
    int design;
    int wCol = 0;
    void makeMove(int column, bool grouped);
    void loadHistory();
    void drawField();
    QSequentialAnimationGroup animationGroup;
    ConnectFour *cfgame;
    Chip *item = NULL;



};

#endif
