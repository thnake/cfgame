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

 public slots:
    void btnPlay();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
