#include "dialog.h"
#include "ui_dialog.h"
#include <cstddef>
#include <QDebug>
#include <QModelIndex>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>


/// <summary>
/// Erstellt einen Dialog zum vorbereiten des Spiels.
/// </summary>
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
    connect(ui->btnPrint, SIGNAL(clicked()), SLOT(btnPrint()));
    ui->radPlayer1->setVisible(false);
    ui->radPlayer2->setVisible(false);

    if(ui->tableView->model()->rowCount() == 0)
    {
        ui->btnLoad->setVisible(false);
    }
}

/// <summary>
/// Beginnt das Spiel, ohne zu laden.
/// </summary>
void Dialog::btnPlay()
{
    int firstplayer = 1;
    if(ui->cbxDifficulty->currentIndex() != 0)
    {
        if(ui->radPlayer2->isChecked()){
            firstplayer = 2;
        }
    }
    cfGame = new ConnectFour(ui->sboxRows->value(),
                             ui->sboxColumns->value(),
                             ui->lePlayer1->text(),
                             ui->lePlayer2->text(),
                             ui->cbxDifficulty->currentIndex(),
                             firstplayer);
    accept();
    close();
}


/// <summary>
/// Liefert das gewählte Design zurück
/// </summary>
int Dialog::getDesign()
{
    return ui->cbxDesign->currentIndex();
}


/// <summary>
/// Slot für das Laden von Spieldaten
/// </summary>
void Dialog::btnLoad()
{

    int i = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();

    QString name1 =  model->data(model->index(i,1)).toString();
    QString name2 =  model->data(model->index(i,2)).toString();
    int columns =  model->data(model->index(i,3)).toInt();
    int rows =  model->data(model->index(i,4)).toInt();
    int winner =  model->data(model->index(i,5)).toInt();
    int difficulty =  model->data(model->index(i,7)).toInt();
    QString history =  model->data(model->index(i,8)).toString();
    int startingPlayer =  model->data(model->index(i,9)).toInt();

    cfGame = new ConnectFour(columns,rows,name1,name2,difficulty,startingPlayer);
    cfGame->setHistoryToLoad(history);

    accept();
    close();

}


/// <summary>
/// Slot für die Auswahl einer KI-Stufe
/// </summary>
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


/// <summary>
/// Slot für das Drucken der Highscores
/// </summary>
void Dialog::btnPrint()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *printDialog = new QPrintDialog(&printer);
    QTextDocument *doc = new QTextDocument();

    if (printDialog->exec() == QDialog::Accepted)
    {
      QString text = "<table>";
      text.append("<tr>");
      text.append("<th>Key</th>");
      text.append("<th>Name 1</th>");
      text.append("<th>Name 2</th>");
      text.append("<th>Columns</th>");
      text.append("<th>Rows</th>");
      text.append("<th>Winner</th>");
      text.append("<th>Moves</th>");
      text.append("<th>Difficulty</th>");
      text.append("<th>History</th>");
      text.append("<th>startingPlayer</th>");
      text.append("</tr>");

      for (int i = 0; i < ui->tableView->model()->rowCount(); i++)
      {
        text.append("<tr>");

        for (int j = 0; j < ui->tableView->model()->columnCount(); j++)
        {
          text.append("<td>");
          text.append(ui->tableView->model()->index(i, j).data().toString());
          text.append("</td>");
        }
        text.append("</tr>");
      }

      text.append("</table>");
      doc->setHtml(text);
      doc->print(&printer);
    }
}


Dialog::~Dialog()
{
    delete ui;
}
