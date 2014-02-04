#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>

/// <summary>
/// Setzt den Schwierigkeitslevel. von 0 - 3
/// </summary>
aiPlayer::aiPlayer(int difficulty)
{
    this->difficulty = difficulty;
}

/// <summary>
/// Liefert eine Instanz auf eine aiPlayer Klasse
/// </summary>
aiPlayer::aiPlayer()
{
    difficulty = 1;
}


/// <summary>
/// Liefert einen zufällig generierten Zug zurück. Der Zug bechtet keine ungültigen Züge
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Auswahl stehen</param>
/// <returns>Wert der gewählten Spalte</returns>
int aiPlayer::getStupidMove(int columns)
{
    qsrand(QTime::currentTime().msec());
    return qrand() % columns;
}

/// <summary>
/// Liefert den Schwierigkeitsgrad der KI
/// </summary>
int aiPlayer::getDifficulty() const
{
    return difficulty;
}

/// <summary>
/// Setzt den Schwierigkeitsgrad der KI
/// </summary>
void aiPlayer::setDifficulty(int value)
{
    difficulty = value;
}


/// <summary>
/// Führt einen Zug entsprechend des gewählten Schwierigskeitsgrades aus.
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Verfügung stehen</param>
/// <returns>Gewählte Spalte</returns>
int aiPlayer::getMove(int columns)
{
    int res = 0;
    switch (difficulty)
    {

        case 0:
            res = getStupidMove(columns);
            break;

        default:
            res = getStupidMove(columns);
            break;
    }
    return res;

}

#include "audioplayer.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QFile>



AudioPlayer::AudioPlayer()
{
}


void AudioPlayer::Play()
{


    QAudioFormat  format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");      // PCM, sollte immer gehen
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    //if (!info.isFormatSupported(format)) … // Fehlerbehandlung

    QFile  inputFile; // class member .
    inputFile.setFileName("c:\\COWBELL1.WAV");
    inputFile.open(QIODevice::ReadOnly);
    QAudioOutput* audio  = new QAudioOutput(format);


    audio->start(&inputFile);

}
#include "chip.h"
#include "MyAnimation.h"

#include <QAbstractAnimation>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QRadialGradient>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <cstddef>


/// <summary>
/// Konstruktor der Klasse Chip. Erstellt einen Spielstein für Vier Gewinnt
/// </summary>
/// <param name="x">x Position des bounding rect</param>
/// <param name="y">x Position des bounding rect</param>
/// <param name="w">Breite Position des bounding rect</param>
/// <param name="h">Höhe</param>
/// <param name="player">Spielernummer</param>
/// <param name="parent">Standardparameter</param>
Chip::Chip(int x, int y, int w, int h, int player, QObject *parent)
    : QObject(parent), QGraphicsEllipseItem((qreal)x,(qreal)y,(qreal)w,(qreal)h)
{
    this->player = player;
}

/// <summary>
/// Liefert einen Zeiger auf eine MyAnimation Instanz zurück,
/// die dann ausgeführt werden kann
/// </summary>
/// <param name="end">Endposition der Animation</param>
/// <param name="duration">Dauer der Animation</param>
/// <param name="curve">Zur Beeinflussung des Animationsverhaltens</param>
MyAnimation* Chip::animate(QPointF end, int duration,  const QEasingCurve &curve)
{
    MyAnimation* animation = new MyAnimation(this, "pos");
    animation->setDuration(duration);
    animation->setEndValue(end);
    animation->setEasingCurve(curve);
    return animation;
}



/// <summary>
/// Liefert einen Zeiger auf eine QPointF Instanz,
/// die den Mittelpunkt des Objektes beschreibt.
/// </summary>
QPointF* Chip::getCenter()
{
    QPointF *c = new QPointF();
    c->setX(pos().x() + boundingRect().width()/2);
    c->setY(pos().y() + boundingRect().width()/2);
  //  qDebug() << c->y();

    return c;
}

/// <summary>
/// Liefert den Spieler zurück, der den Stein gelegt hat.
/// </summary>
int Chip::getPlayer()
{
    return player;
}

#include "connectfour.h"
#include <QVector>
#include <QtCore>
#include <QObject>

/// <summary>
/// Konstruktor der Klasse ConnectFour.
/// Die Instanz bildet die Regeln des Spiels Vier Gewinnt ab.
/// </summary>
ConnectFour::ConnectFour() : QObject()
{

}

/// <summary>
/// Feld für den gewählten Schwierigkeitsgrad.
/// </summary>
int ConnectFour::getDifficulty() const
{
    return difficulty;
}

/// <summary>
/// Liefert die Anzahl der bisherigen Züge zurück
/// </summary>
int  ConnectFour::getMoves()
{
    return  moves;
}

/// <summary>
/// Liefert die Spielernummer des letzten Zuges zurück.
/// </summary>
int ConnectFour::getLastPlayer()
{
    int res = 0;
    switch (currentPlayer) {
    case 1:
        res = 2;
        break;
    case 2:
        res = 1;
        break;
    }
    return res;
}

/// <summary>
/// Liefert den Namen des zweiten Spielers
/// </summary>
QString ConnectFour::getName2() const
{
    return name2;
}


/// <summary>
/// Liefert den Namen des ersten Spielers
/// </summary>
QString ConnectFour::getName1() const
{
    return name1;
}

/// <summary>
/// Liefert die Spielernummer des Siegers zurück
/// </summary>
int ConnectFour::getWinner()
{
    return winner;
}


/// <summary>
/// Konstruktor der Klasse ConnectFour.
/// Die Instanz bildet die Regeln des Spiels Vier Gewinnt ab.
/// </summary>
/// <param name="x">Spalten</param>
/// <param name="y">Zeileen</param>
/// <param name="player1Name">Name des ersten Spielers</param>
/// <param name="player2Name">Name des zweiten Spielers</param>
/// <param name="difficultyLevel">Schwierigkeitsgrad</param>
/// <param name="startingPlayer">Nummer des beginnenden Spielers</param>
ConnectFour::ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel, int startingPlayer): QObject()
{
    fieldsx = x;
    fieldsy = y;
    currentPlayer = 1;
    name1 = player1Name;
    name2 = player2Name;
    history = "";

    currentPlayer = startingPlayer;
    this->startingPlayer = startingPlayer;

    difficulty = difficultyLevel;

    moves = 0;


    for(int i = 0; i < x; i++)
    {
        QVector<int> row;
        for(int j = 0; j < y; j++)
        {
            row.push_back(0);
        }
        board.push_back(row);
    }

    directions = QVector<QVector<int> >();

    QVector<int> *dir = new QVector<int>();
    dir->push_back(0);
    dir->push_back(1);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(1);
    dir->push_back(1);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(1);
    dir->push_back(0);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(-1);
    dir->push_back(1);
    directions.push_back(*dir);

    winner = 0;

}

/// <summary>
/// Liefert eine Zeichenkette, die den Spielverlauf darstellt
/// </summary>
/// <retuns>Zeichenkette mit dem Spielverlauf</retuns>
QString ConnectFour::getGameState()
{
    QString state = "";
    for(int j = 0; j < fieldsy; j++)
    {
        for(int i = 0; i < fieldsx; i++)
        {
            state += QString::number(board[i][j]);
        }
    }
   return state;
}

/// <summary>
/// Liefert die aktuelle Spielernummer zurück.
/// </summary>
int ConnectFour::getCurrentPlayer()
{
    return currentPlayer;
}

/// <summary>
/// Prüft, ob ein Zug gültig ist, oder nicht. Wird von der KI im einfachen Modus benötigt.
/// <param name="x">Gewählte Spalte für den Zug</param>
/// </summary>
bool ConnectFour::checkMove(int x)
{
    bool result = false;
    for(int i = 0; i < fieldsy; i++)
    {
        if(board[x][i] == 0)
        {
            result = true;
            break;
        }
    }
    return result;
}

/// <summary>
/// Liefert den Spielverlauf in Form einer Zeichenkette zurück.
/// </summary>
QString ConnectFour::getHistory() const
{
    return history;
}


/// <summary>
/// Bereitet das Laden eines Spielverlaufs vor.
/// </summary>
void ConnectFour::setHistoryToLoad(QString hl)
{
    this->historyToLoad = hl;
}




// position ist die startposition
// u ist der einheitsvektor, in dessen richtung wir sammeln
// sign ist das vorzeichen
int ConnectFour::getStartingPlayer() const
{
    return startingPlayer;
}

/// <summary>
/// Läuft ausgehend von einer gewünschten Position eine gewünschte Richtung ab und sammelt die Punkte
/// </summary>
/// <param name="position">Startpunkt der Suche</param>
/// <param name="u">Richtungsvektor, zur Suche</param>
/// <param name="sign">Schrittweite. Zum Rückwärtslaufen einen negativen wert übergeben</param>
int ConnectFour::collectPointsInDirection(QVector<int> position, QVector<int> u, int scale)
{
    int sum = 0;

    while(position[0] < fieldsx
          && position[1] < fieldsy
          && position[0] > -1
          && position[1] > -1
          && board[position[0]][position[1]] == currentPlayer)
    {
        sum++;
        position[0] += u[0] * scale; // in richtung des Einheitsvektors u
        position[1] += u[1] * scale;
    }

    return sum;
}

/// <summary>
/// Liefert die noch zu ladende Spielehistorie zurück
/// </summary>
QString ConnectFour::getHistoryToLoad() const
{
    return historyToLoad;
}


/// <summary>
/// Verschiebt einen Punkt entlang der Linien (diagonal, senkrecht, horizontal)
/// und summiert die Spielerchips auf.
/// </summary>
/// <param name="x">x-Wert des Punktes</param>
/// <param name="y">y-Wert des Punktes</param>
bool ConnectFour::checkVictory(int x, int y)
{
    //int* point = new int[2];
    QVector<int> *pos = new QVector<int>();

    pos->push_back(x);
    pos->push_back(y);
    bool victory = false;

    // u ist unitvector
    QVector<int> u;
    foreach (u, directions) {

        int sum = 0;
        sum += collectPointsInDirection(*pos,u, 1);
        sum += collectPointsInDirection(*pos,u, -1);
        sum--; // der startpunkt wurde doppelt gezählt


        if(sum>3) // Siegesbedingung: vier gewinnt
        {
            victory = true;
            this->winner = currentPlayer;
            break;
        }
    }

    return victory;

}

/// <summary>
/// Prüft, ob ein unentschieden vorliegt
/// </summary>
bool ConnectFour::checkDraw()
{
    return winner == 0 && history.length() == fieldsx*fieldsy;
}


/// <summary>
/// liefert die Zeile zurück, in der der Stein gelandet ist.
/// Prüft, ob der Zug siegreich war. Prüfen mit getWinner()
/// </summary>
/// <returns>Zeilennummer, in der der Stein gelandet ist</returns>
int ConnectFour::setStone(int x)
{

    if(board[x][fieldsy-1] != 0)
    {
        return -1;
    }

    int result = -1;
    for(int i = 0; i < fieldsy; i++){
        if(board[x][i] == 0)
        {
            result = i;
            board[x][i] = currentPlayer;
            checkVictory(x,i);
            moves++;
            history += QString::number(x);
            qDebug() << history;
            break;
        }
    }

    if(currentPlayer == 1)
    {
        currentPlayer = 2;
    }
    else
    {
        currentPlayer = 1;
    }

    return result;
}



#include <QSqlError>
#include  <QSqlQuery>
#include <QDebug>
#include <QMapIterator>
#include <QString>
#include <QDataStream>
#include <QByteArray>
#include <QSqlRecord>
#include <QSqlField>
#include <QTableView>
#include <QSqlQueryModel>

#include "QVariant.h"
#include "databaseaccessclass.h"
#include "qmessagebox.h"
#include "connectfour.h"


/// <summary>
/// Liefert das zuletzt ausgeführte SQL im klartext zurück
/// </summary>
/// <param name="query">Instanz des ausgeführten Querys</param>
QString DataBaseAccessClass::getLastExecutedQuery( QSqlQuery query)
{
    QString str = query.lastQuery();
    QMapIterator<QString, QVariant> it(query.boundValues());
    while (it.hasNext())
    {
        it.next();
        str.replace(it.key(),it.value().toString());
    }
    return str;
}

/// <summary>
/// Konstruktor der Datenbankzugriffsklasse.
/// </summary>
DataBaseAccessClass::DataBaseAccessClass()
{
    connect();
}

/// <summary>
/// Lädt die Datensätze der Spiele in ein TableView
/// </summary>
void DataBaseAccessClass::loadGames(QTableView *tv)
{

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM game;");

    model->setHeaderData( 0, Qt::Horizontal, QObject::tr("key") );
    model->setHeaderData( 1, Qt::Horizontal, QObject::tr("Player1") );
    model->setHeaderData( 2, Qt::Horizontal, QObject::tr("Player2") );

    tv->setModel(model);


}

/// <summary>
/// Speichert eine Spielinstanz in der Datenbank ab
/// </summary>
/// <returns>Erfolg oder Misserfolg des Speicherns</returns>
bool DataBaseAccessClass::saveGame(ConnectFour *game)
{

    QSqlQuery *q = new QSqlQuery();

    q->prepare("INSERT INTO game (name1,name2,columns,rows,winner,moves,difficulty,history,startingPlayer)"
               "VALUES (:name1, :name2, :columns, :rows, :winner, :moves, :difficulty,:history,:startingPlayer);");
    q->bindValue(":name1",game->getName1() );
    q->bindValue(":name2", game->getName2());
    q->bindValue(":columns", game->fieldsx);
    q->bindValue(":rows", game->fieldsy);
    q->bindValue(":winner", game->getWinner());
    q->bindValue(":moves", game->getMoves());
    q->bindValue(":difficulty", game->getDifficulty());
    q->bindValue(":history", game->getHistory());
    q->bindValue(":startingPlayer", game->getStartingPlayer());

    if(!q->exec())
    {
        qDebug() << db.lastError().text();
        return false;
    }

    qDebug() << getLastExecutedQuery(*q);
    delete q;
    return true;
}

/// <summary>
///
/// </summary>
bool DataBaseAccessClass::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("connectfour.sqlite");
    db.setUserName("user");
    db.setPassword("pass");

    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),  db.lastError().text());
        return false;
    }

    //tabelle erstellen
    //QSqlQuery drop("DROP TABLE if exists game;");
    //drop.exec();
    QSqlQuery qHighscore("CREATE TABLE IF NOT EXISTS game"
                    "(hspk INTEGER PRIMARY KEY AUTOINCREMENT, name1 varchar(12), name2 varchar(12),columns smallint, rows smallint,"
                         " winner smallint, moves smallint, difficulty smallint, history varchar(100), startingPlayer smallint);");

    if (!qHighscore.exec())
    {
        qDebug() << "Table highscore not created";
    }

    return true;
}
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
/// Erstellt einen Dialog zum vorbereiten des Spiels
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

    printDialog->setWindowTitle(tr("Print Document"));

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
#include <QApplication>
#include <QtSql/QSqlDatabase>

#include "mygraphicsview.h"
#include "mygraphicsscene.h"
#include "databaseaccessclass.h"

#include "mainwindow.h"
#include "dialog.h"




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    DataBaseAccessClass *dao = new DataBaseAccessClass();

    Dialog d;
    d.dao = dao;

    if (d.exec() == Dialog::Accepted)
    {
        MyGraphicsView *view = new  MyGraphicsView();
        MyGraphicsScene *scene = new MyGraphicsScene(view, d.cfGame, d.getDesign());

        view->setScene(scene);
        view->show();

        return a.exec();
    }
}


#include "myanimation.h"
#include <QPointF>
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsItem>




/// <summary>
/// Liefert den 2d-Richtungsvektor der Animation seit der letzten Änderung.
/// </summary>
QPointF MyAnimation::getOldVector() const
{
    return oldVector;
}


/// <summary>
/// Speichert einen 2D-Vektor, der durch die letzte Änderung entstanden ist.
/// </summary>
void MyAnimation::setOldVector(const QPointF &value)
{
    oldVector = value;
}


/// <summary>
/// Liefert die Position vor der letzten Änderung.
/// </summary>
QPointF MyAnimation::getOldPosition() const
{
    return oldPosition;
}


/// <summary>
/// Speichert die Position seit der letzten änderung.
/// </summary>
void MyAnimation::setOldPosition(const QPointF &value)
{
    oldPosition = value;
}


/// <summary>
/// Konstruktor der Klasse MyAnimation.
/// </summary>
/// <param name="target">QObject, das animiert werden soll</param>
/// <param name="propertyName">Property, die zur Animation  benutzt werden soll</param>
MyAnimation::MyAnimation(QObject * target, const QByteArray & propertyName) :
    QPropertyAnimation(target, propertyName)
{

}

/// <summary>
/// Konstruktor der Klasse MyAnimation.
/// </summary>
MyAnimation::MyAnimation(QObject *parent) : QPropertyAnimation(parent)
{

}







#include "myfield.h"
#include <QObject>
#include <QGraphicsPixmapItem>

/// <summary>
/// Konstruktor der Klasse MyField.
/// </summary>
MyField::MyField() : QObject() , QGraphicsPixmapItem()
{

}
#include "mygradient.h"
#include <QLinearGradient>
#include <QObject>
#include <QDebug>

MyGradient::MyGradient() : QLinearGradient(), QObject()
{
}

MyGradient::MyGradient(QPoint p, QPoint q) : QLinearGradient(p,q), QObject(NULL)
{

}


void MyGradient::setCEnd(const QColor &value, float e)
{
    cEnd = value;
    this->end = e;
}


void MyGradient::setCMiddle(const QColor &value, float m)
{
    cMiddle = value;
    this->middle = m;
}


void MyGradient::setCStart(const QColor &value, float s)
{
    cStart = value;
    this->start = s;
}


float MyGradient::getMiddle()
{
    return middle;
}



void MyGradient::setMiddle(float value)
{

    stops()[2].first = (qreal)value;
    stops()[2].second = Qt::green;

    //setColorAt(value, Qt::white);
    middle = value;
    qDebug() << stops().count();
/*
    setColorAt(0,Qt::black);
    setColorAt(value,Qt::white);
    setColorAt(1,Qt::black);
*/
}

#include "mygraphicsscene.h"
#include "connectfour.h"

#include <audioplayer.h>
#include <QtCore>
#include <QObject>
#include <QtGui>
#include <QtWidgets>
#include <QEasingCurve>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <mygraphicsview.h>
#include <cstddef>
#include <QGraphicsScene>
#include <QThread>
#include <QGradientStop>
#include <QRadialGradient>
#include <QSequentialAnimationGroup>
#include <myanimation.h>
#include <iostream>
#include <QSound>

#include <qglobal.h>
#include <QTime>


/// <summary>
/// Konstruktor der Klasse MyGraphicScene. Liefert eine Instanz zur Darstellung des
/// Connect Four-Spiels
/// </summary>
/// <param name="parent">Parentobjekt</param>
/// <param name="game">Instanz des Spiels</param>
/// <param name="game">gewähltes Design</param>
MyGraphicsScene::MyGraphicsScene(QObject *parent, ConnectFour *game, int selectedDesign) :
    QGraphicsScene(parent)
{

    this->cfgame = game;
    design = selectedDesign;

    ai.setDifficulty(game->getDifficulty());

    setSceneRect(0,0,(cfgame->fieldsx ) * 100,cfgame->fieldsy * 100);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,sceneRect().width(),sceneRect().height());

    addItem(rect);

    QGraphicsRectItem *foreground = new QGraphicsRectItem( 100, 100, 400, 200 );

    foreground->setBrush( QBrush( QColor(118,185,0,128) ) );
    foreground->setZValue(1);
    resizeEvent(NULL);
    createField();
    loadHistory();

    if(cfgame->history.length() == 0 && cfgame->getCurrentPlayer() == 2)
    {
        aiMove();
    }

    qDebug() << "starting";
    qDebug() << cfgame->getStartingPlayer();
}


/// <summary>
/// Erzeugt das überdeckende Spielfeld
/// </summary>
void MyGraphicsScene::createField()
{

    float width = wCol * cfgame->fieldsx;
    float height = wCol * cfgame->fieldsy;

    QImage *img = new QImage(cfgame->fieldsx * 100, cfgame->fieldsy * 100, QImage::Format_ARGB32);
    QPainter *painter = new QPainter(img);

    painter->setRenderHint(QPainter::Antialiasing, true);


    QLinearGradient *gradient;
    QConicalGradient *cgradient;
    switch(design)
    {
        case 0:
             gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::gray);
            gradient->setColorAt(0.5, Qt::blue);
            gradient->setColorAt(1, Qt::green);
            painter->setBrush(*gradient);
            break;

        case 1:
            gradient = new QLinearGradient(QPoint(10, 10), QPoint(width, height));
            gradient->setColorAt(0, Qt::white);
            gradient->setColorAt(0.3, Qt::green);
            gradient->setColorAt(1, Qt::black);
            painter->setBrush(*gradient);
        break;

        default :
            cgradient = new QConicalGradient(QPoint(width , height / 2 + 10), 0);
            cgradient->setColorAt(0, Qt::blue);
            cgradient->setColorAt(0.5, Qt::darkMagenta);
            cgradient->setColorAt(1, Qt::blue);
            painter->setBrush(*cgradient);
            break;
    }

    painter->setPen(Qt::NoPen);
    painter->drawRect(0, 0, wCol*cfgame->fieldsx,cfgame->fieldsy * wCol);
    painter->setCompositionMode(QPainter::CompositionMode_Clear);
    painter->setBrush(QColor(255, 0, 0));
    painter->drawRect(0, 0, wCol*cfgame->fieldsx, 0);

    int transparentX = 0;
    int transparentY = 0;

    for (unsigned int rows = 0; rows < cfgame->fieldsy; ++rows)
    {
      for (unsigned int columns = 0; columns < cfgame->fieldsx; ++columns)
      {
        painter->drawEllipse(transparentX+5, transparentY+5, wCol-10, wCol-10);
        transparentX += wCol;
      }

      transparentX = 0;
      transparentY += wCol;
    }

    painter->end();

    fieldItem = new MyField();
    fieldItem->setPixmap(QPixmap::fromImage(*img));
    fieldItem->setZValue(1);
    fieldItem->setTransformationMode(Qt::SmoothTransformation);
    fieldItem->pos().setX(0);
    fieldItem->pos().setY(0);

    addItem(fieldItem);
}


/// <summary>
/// Speichert das Spiel ab.
/// </summary>
void MyGraphicsScene::saveGame()
{
    MyGraphicsView *view = (MyGraphicsView*)parent();

}

/// <summary>
/// Animation für das Spielfeld. Stellt ein erschüttern dar. Zum Anzeigen von ungültigen Zügen
/// </summary>
void MyGraphicsScene::shatterFieldAnimation()
{
    QPointF pEnd(0-fieldItem->boundingRect().width()/20, 0);
    QSequentialAnimationGroup *ag = new QSequentialAnimationGroup();

    MyAnimation *shake  = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);

    pEnd.setX(0+fieldItem->boundingRect().width()/20);
    shake = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);

    pEnd.setX(0);
    shake = new MyAnimation(fieldItem, "pos");
    shake->setDuration(50);
    shake->setEndValue(pEnd);
    shake->setEasingCurve(QEasingCurve::Linear);
    ag->addAnimation(shake);
    ag->start(QAbstractAnimation::DeleteWhenStopped);

}


/// <summary>
/// Setzt das Design des Spielsteins fest
/// </summary>
/// <param name="chip">Instanz des Spielsteins</param>
void MyGraphicsScene::designChip(Chip* chip)
{
  QColor color;
  QRadialGradient gradient;


  if (this->cfgame->getCurrentPlayer() == 1)
    color = QColor(Qt::yellow);
  else
    color = QColor(Qt::blue);

  switch (design)
  {
    case 0 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::yellow);
      else
        color = QColor(Qt::blue);
      break;

    case 1 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::green);
      else
        color = QColor(Qt::red);
      break;

    case 2 :
      if (this->cfgame->getCurrentPlayer() == 1)
        color = QColor(Qt::magenta);
      else
        color = QColor(Qt::cyan);
      break;

    default :

      break;
  }

  chip->setBrush(QBrush(color));
  chip->setPen(QPen(Qt::black));
  chip->setZValue(-1);

}

/// <summary>
/// Slot für das Abspielen von Bounce geräuschen. Bei jeder Richtungsänderung des Objekts kann zur
/// entsprechenden Easingkurve das geräusch abgespielt werden. Die Soundwiedergabe ist nicht implementiert.
/// </summary>
/// <param name="v">Sender des Signals</param>
void MyGraphicsScene::bounceSound(QVariant v)
{

    MyAnimation *s = (MyAnimation*)QObject::sender();
    QPointF *newVector = new QPointF();

    newVector->setX(s->getOldPosition().x() - v.toPointF().x());
    newVector->setY(s->getOldPosition().y() - v.toPointF().y());

    float sp = this->scalarProduct(*newVector, s->getOldVector());

    if(sp < 0)
    {
        qDebug() << "bounce sound abspielen";
    }
    s->setOldPosition(v.toPointF());
    s->setOldVector(*newVector);
}

/// <summary>
/// Liefert das Skalarprodukt zweier 2d-Vektoren
/// </summary>
float MyGraphicsScene::scalarProduct(QPointF u, QPointF v)
{
    return u.x()*v.x() + u.y()*v.y();
}

/// <summary>
/// Fängt das Resize Event ab und berechnet die Spaltenbreite
/// </summary>
void MyGraphicsScene::resizeEvent(QResizeEvent *event)
{
    wCol = (int)sceneRect().width()/cfgame->fieldsx;
}

/// <summary>
/// Liefert einen Zeiger auf die Instanz der Spielklasse
/// </summary>
ConnectFour *MyGraphicsScene::getCfgame() const
{
    return cfgame;
}

/// <summary>
/// Setzt die Instanz der Spielklasse fest
/// </summary>
void MyGraphicsScene::setCfgame(ConnectFour *value)
{
    cfgame = value;
}

/// <summary>
/// Rekonstruiert eine Historie, die in cfGame bereit steht
/// </summary>
void MyGraphicsScene::loadHistory()
{
    QString h = cfgame->getHistoryToLoad();
    for(int i = 0; i < h.length(); i++)
    {
        makeMove(h[i].digitValue(), true);
    }

    animationGroup.start(QAbstractAnimation::DeleteWhenStopped);
    cfgame->setHistoryToLoad("");

}

/// <summary>
/// Animiert das Fallen eines Spielsteins
/// </summary>
/// <param name="chip">Zeiger auf den Spielstein</param>
/// <param name="end">Punkt, zu dem der Stein fallen soll</param>
/// <param name="grouped">Entscheidet, ob eine Gruppenanimation genutzt werden soll</param>
void MyGraphicsScene::animateChipDrop(Chip *chip, QPointF end, bool grouped)
{

    MyAnimation *animation = chip->animate(end, 1000, QEasingCurve::OutBounce);
    connect(animation,SIGNAL(valueChanged(QVariant)),SLOT(bounceSound(QVariant)));

     if(!grouped) {
        animation->start(QAbstractAnimation::DeleteWhenStopped);
     }else{
         animation->setEasingCurve(QEasingCurve::InOutSine);
         animation->setDuration(150);
         animationGroup.addAnimation(animation);
     }

}


/// <summary>
/// Lässt die KI einen Zug durchführen
/// </summary>
void MyGraphicsScene::aiMove()
{
    int row = 0;
    do{
        row = ai.getMove(cfgame->fieldsx);

    }while(cfgame->checkMove(row) == false);
    makeMove(row, false);
}

/// <summary>
/// Lässt ein Label mit einer Nachricht aufpoppen
/// </summary>
/// <param name="msg">Nachricht an den Spieler</param>
void MyGraphicsScene::showMessage(QString msg)
{
    QLabel *l = new QLabel();
    l->setObjectName("lblMessage");
    QString text = "<html><head/><body><p align=\"center\"><span style=\" font-size:20pt; font-weight:500;\">" + msg + "</span></p></body></html>";


    QByteArray byteArray = text.toUtf8();
    const char* cString = byteArray.constData();

    QString text2 = QString::fromUtf8(cString);
    l->setText(QApplication::translate("Winner", cString, 0));
    l->show();

}


/// <summary>
/// Signalisiert dem Spieler den Endzustand des Spiels durch eine Animation
/// </summary>
void MyGraphicsScene::animateVictory()
{

    MyAnimation *animation;
    QVector<Chip*> wchips;

    //qsrand(QTime::currentTime().msec());
    for(int i=0; i<chips.count(); i++)
    {    
        animation = chips[i]->animate(getRandomPoint(), 500,  QEasingCurve::Linear);
        connect(animation, SIGNAL(finished()), SLOT(animateVictory()));
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

/// <summary>
/// Liefert einen zufälligen Punkt aus dem Feld zurück.
/// </summary>
QPointF MyGraphicsScene::getRandomPoint()
{
    float x = qrand() % (int)fieldItem->boundingRect().width();
    float y = qrand() % (int)fieldItem->boundingRect().height();
    QPointF res;
    res.setX(x);
    res.setY(y);
    return res;
}

/// <summary>
/// Führt einen Spielzug durch.
/// </summary>
/// <param name="column">Spalte, die in dem Zug benutzt werden soll</param>
/// <param name="loadHistory">Gibt an, dass mit diesem Zug die Historie geladen wird</param>
int MyGraphicsScene::makeMove(int column, bool loadHistory)
{


    int stacked = cfgame->setStone(column);
    if(stacked > -1)
    {
        chip  = new Chip(column*wCol, 0-wCol, wCol, wCol,cfgame->getLastPlayer());
        chip->setVisible(true);
        QPointF p(chip->pos().x(), sceneRect().height() - wCol*stacked);
        qDebug() << chip->pos().x();
        designChip(chip);
        addItem(chip);
        animateChipDrop(chip, p, loadHistory);
        chips.push_back(chip);
    }
    else
    {
        shatterFieldAnimation();
    }

    if(cfgame->getWinner() != 0)
    {
        if(cfgame->getWinner() == 1)
        {
            showMessage(cfgame->getName1()+ " wins!!!");
        }
        else
        {
            showMessage(cfgame->getName2()+ " wins!!! :D");
        }

        animateVictory();
        saveGame();

    }else if(cfgame->checkDraw())
    {

        showMessage("Draw!!!");
        saveGame();
        animateVictory();

    }
    return stacked;

}


/// <summary>
/// Fängt den Spieler click ab, der seine Spalte durch anclicken wählen soll.
/// </summary>
/// <param name="event">enthält die clickinformationen</param>
void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(cfgame->getWinner() == 0)
    {
        int col = event->scenePos().x() / wCol;

        // click in Spielfeld
        if (col > -1 && col < cfgame->fieldsx && event->scenePos().x() >= 0)
        {

            int stacked = makeMove(col, false);
            if(cfgame->getDifficulty() != 0 && stacked > -1 && cfgame->getWinner() == 0)
            {

                this->aiMove();
            }
        }
    }
}



#include "mygraphicsview.h"
#include "connectfour.h"
#include "mygraphicsscene.h"
#include "databaseaccessclass.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QDebug>



/// <summary>
/// Konstruktor der Klasse MyGraphicsView.
/// </summary>
/// <param name="parent">Parentobjekt</param>
/// <param name="dao">Objekt zum Zugriff auf die Spieledatenbank</param>
MyGraphicsView::MyGraphicsView(QWidget *parent,  DataBaseAccessClass *dao) :
    QGraphicsView(parent)
{
    setMouseTracking(true);
    this->dao = dao;
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}


/// <summary>
/// Zum erhalt der Seitenverhältnisse
/// </summary>
void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "resize: " << event->size();
    fitInView( sceneRect(), Qt::KeepAspectRatio );

}


/// <summary>
/// Fängt benutzereingaben ab.
/// [Ss] speichert das Spiel
/// [Ff] aktiviert und deaktiviert den Fullscreen modus
/// </summary>
void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_S)
    {
        qDebug() << "save";
        MyGraphicsScene *s = (MyGraphicsScene*)scene();
        dao->saveGame(s->getCfgame());

    }
    if(event->key() == Qt::Key_F)
    {
        if(!isFullScreen())
        {
            this->showFullScreen();
        }else
        {
            this->showNormal();
        }

    }

}



