#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "connectfour.h"
#include "databaseaccessclass.h"

namespace Ui {
class Dialog;
}


/// <summary>
/// Konfigurationsdialog für Das Spiel. Beim bestätigen werden die Felder zum erzeugen eines
/// Vier Gewinnt Spiels genutzt. Beim Laden werden die Daten aus dem TableView genutzt.
/// Das cfGame kann dann von außen abgegriffen und verwendet werden.
/// </summary>
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
