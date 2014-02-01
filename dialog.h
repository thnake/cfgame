#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "connectfour.h"
#include "databaseaccessclass.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    ConnectFour *cfGame;
    DataBaseAccessClass *dao;
    int getDesign();

 public slots:
    void btnPlay();
    void btnLoad();
    void cbxAi();
    void btnPrint();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
