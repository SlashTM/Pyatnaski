#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPicture>
#include "pyatnashki.h"
#include <QMessageBox>

Pyatnashki game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Tiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Tiles->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    time = new QTimer();
    time->setInterval(1000);
    connect(time,SIGNAL(timeout()), this, SLOT(updateTimer()));
    ui -> playTimer -> setText("00:00:00");
    seconds = 0; minutes = 0; hours = 0;
    showField();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete time;
}

void MainWindow::showField() {
    if(game.getMoves() == 1){
        time->start();
    }

    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (game.getTile(i, j) == 0) {
                itNum -> setText("  ");
            }
            else {
                itNum -> setText(QString::number(game.getTile(i,j)));
            }
            ui -> Tiles -> setItem(i, j, new QTableWidgetItem(*itNum));
        }
    }
    ui -> moves_counter -> setText(QString::number(game.getMoves()));
}

void MainWindow::updateTimer() {
    seconds++;
    if (seconds == 60){
        minutes++;
        seconds = 0;
    }
    if (minutes == 60){
        hours++;
        minutes = 0;
    }

    QString h,m,s;

    if (seconds >= 10){
        s = QString::number(seconds);
    }
    else s = "0" + QString::number(seconds);

    if (minutes >= 10){
        m = QString::number(minutes);
    }
    else m = "0" + QString::number(minutes);

    if (hours >= 10){
        h = QString::number(hours);
    }
    else h = "0" + QString::number(hours);
    ui -> playTimer -> setText(h + ':' + m + ':' + s);
}

void MainWindow::on_NewGame_triggered()
{
    game.start();
    seconds = 0;
    minutes = 0;
    hours = 0;
    time->stop();
    ui -> playTimer -> setText("00:00:00");
    showField();
}

void MainWindow::on_Restart_triggered()
{
    game.restart();
    seconds = 0;
    minutes = 0;
    hours = 0;
    time->stop();
    ui -> playTimer -> setText("00:00:00");
    showField();
}

void MainWindow::on_Tiles_cellClicked(int row, int column)
{
    game.MoveNull(row, column);
    showField();
    if (game.gameIsWon()) {
        time->stop();
        if(QMessageBox::question(this,"Вы выиграли!","Желаете ещё сыграть?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            QApplication::quit();
        else {
            seconds = -1;
            minutes = 0;
            hours = 0;
            game.start();
            showField();
        }
    }
}

void MainWindow::on_Quit_triggered()
{
    QApplication::quit();
}
