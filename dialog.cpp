#include "dialog.h"
#include "ui_dialog.h"
#include <cstddef>
#include <QDebug>
#include <QModelIndex>
#include <QSqlRecord>
#include <QSqlQueryModel>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    cfGame = NULL;
    dao->loadGames(ui->tableView);

    connect(ui->btnPlay,SIGNAL(clicked()),SLOT(btnPlay()));
    connect(ui->btnLoad, SIGNAL(clicked()), SLOT(btnLoad()));    
    connect(ui->cbxDifficulty, SIGNAL(currentIndexChanged(int)), SLOT(cbxAi()));
    ui->radPlayer1->setVisible(false);
    ui->radPlayer2->setVisible(false);

}


void Dialog::btnPlay()
{
    cfGame = new ConnectFour(ui->sboxRows->value(),
                             ui->sboxColumns->value(),
                             ui->lePlayer1->text(),
                             ui->lePlayer2->text(),
                             ui->cbxDifficulty->currentIndex(),
                             1);
    accept();
    close();
}

int Dialog::getDesign()
{
    return ui->cbxDesign->currentIndex();
}

void Dialog::btnLoad()
{

    int i = ui->tableView->currentIndex().row();

    qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(i,2)).toString();
    QString name1 =  ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toString();
    QString name2 =  ui->tableView->model()->data(ui->tableView->model()->index(i,2)).toString();
    int columns =  ui->tableView->model()->data(ui->tableView->model()->index(i,3)).toInt();
    int rows =  ui->tableView->model()->data(ui->tableView->model()->index(i,4)).toInt();
    int winner =  ui->tableView->model()->data(ui->tableView->model()->index(i,5)).toInt();
    int difficulty =  ui->tableView->model()->data(ui->tableView->model()->index(i,7)).toInt();
    QString history =  ui->tableView->model()->data(ui->tableView->model()->index(i,8)).toString();

    cfGame = new ConnectFour(columns,rows,name1,name2,difficulty,1);
    cfGame->setHistoryToLoad(history);

    accept();
    close();

}

void Dialog::cbxAi()
{
    if(ui->cbxDifficulty->currentIndex() != 0)
    {
        ui->radPlayer1->setVisible(true);
        ui->radPlayer2->setVisible(true);
        ui->lePlayer2->setText(ui->cbxDifficulty->currentText() + " AI");
    }
    else
    {
        ui->radPlayer1->setVisible(false);
        ui->radPlayer2->setVisible(false);
    }
}

Dialog::~Dialog()
{
    delete ui;
}
