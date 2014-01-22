#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // button im MainWindow (parent)
    // Speicher wird automat. freigegeben, wenn parent delete
    //QPushButton *button = new QPushButton(this);

   // button->setText( tr("OK") );

    //qDebug() << "MainWindow ctor" << button;

    //ui->dateTimeEdit->setCalendarPopup(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
