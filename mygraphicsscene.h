#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include "chip.h"
#include "connectfour.h"
#include "panel.h"
#include "aiplayer.h"

#include <QGraphicsScene>
#include <QMouseEvent>
#include <cstddef>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include <QPointF>
#include <myfield.h>



class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent ,ConnectFour *game, int selectedDesign);

    ConnectFour *getCfgame() const;
    void setCfgame(ConnectFour *value);
    float scalarProduct(QPointF u, QPointF v);
   // void designChip(Chip *chip);


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
    int makeMove(int column, bool grouped);
    void loadHistory();
    void drawField();
    void animateText(QString text);
    void saveGame();
    void shatterFieldAnimation();
    void animateChipDrop(Chip *chip, QPointF end, bool grouped);
    void aiMove();
    void animateVictory();

    QPointF getRandomPoint();
    MyField *fieldItem;
    aiPlayer ai;
    void designChip(Chip* chip);
    QSequentialAnimationGroup animationGroup;
    ConnectFour *cfgame;
    Chip *chip = NULL;
    QVector<Chip*> chips;


};

#endif
