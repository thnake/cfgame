#include "dialog.h"
#include "ui_dialog.h"
#include <cstddef>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    cfGame = NULL;

    connect(ui->btnPlay,SIGNAL(clicked()),SLOT(btnPlay()));



}


void Dialog::btnPlay()
{
    cfGame = new ConnectFour(ui->sboxRows->value(),
                             ui->sboxColumns->value(),
                             ui->lePlayer1->text(),
                             ui->lePlayer2->text(),
                             ui->cbxDifficulty->currentIndex(),
                             ui->cbFullscreen->isChecked());
    accept();
    close();
}

Dialog::~Dialog()
{
    delete ui;
}
