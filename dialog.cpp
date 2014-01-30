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


}


void Dialog::btnPlay()
{
    cfGame = new ConnectFour(ui->sboxRows->value(),
                             ui->sboxColumns->value(),
                             ui->lePlayer1->text(),
                             ui->lePlayer2->text(),
                             ui->cbxDifficulty->currentIndex());
    accept();
    close();
}

int Dialog::getDesign()
{
    return ui->comboBox->currentIndex();
}

void Dialog::btnLoad()
{
  //  QSqlQueryModel model = (QSqlQueryModel) ui->tableView->model();


    int i = ui->tableView->currentIndex().row();

    qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(i,2)).toString();
    QString name1 =  ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toString();
    QString name2 =  ui->tableView->model()->data(ui->tableView->model()->index(i,2)).toString();
    int columns =  ui->tableView->model()->data(ui->tableView->model()->index(i,3)).toInt();
    int rows =  ui->tableView->model()->data(ui->tableView->model()->index(i,4)).toInt();
    int winner =  ui->tableView->model()->data(ui->tableView->model()->index(i,5)).toInt();
    int difficulty =  ui->tableView->model()->data(ui->tableView->model()->index(i,7)).toInt();
    QString history =  ui->tableView->model()->data(ui->tableView->model()->index(i,8)).toString();

    cfGame = new ConnectFour(columns,rows,name1,name2,difficulty);
    cfGame->setHistoryToLoad(history);


    accept();
    close();


    /*
    cfGame = new ConnectFour(record.field("columns").value().toInt(),
                                     record.field("rows").value().toInt(),
                                     record.field("name1").value().toString(),
                                     record.field("name2").value().toString(),
                                     record.field("difficulty").value().toInt(),
                                     record.field("fullscreen").value().toBool());
                                     */

}

Dialog::~Dialog()
{
    delete ui;
}
