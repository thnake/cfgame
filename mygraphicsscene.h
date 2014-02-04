#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include "chip.h"
#include "connectfour.h"
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


signals:
    
public slots:
    void bounceSound(QVariant v);
    void animateVictory();

protected:
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void resizeEvent(QResizeEvent * event );



private:
    int design;
    int wCol = 0;
    int makeMove(int column, bool grouped);
    void loadHistory();
    void createField();
    void saveGame();
    void shatterFieldAnimation();
    void animateChipDrop(Chip *chip, QPointF end, bool grouped);
    void aiMove();
    void showMessage(QString msg);

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
