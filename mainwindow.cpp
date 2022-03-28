#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Petno.h"
#include <QMessageBox>
#include <QTimer>
#include <QTime>

Petno petno;
Petno petno_start_copy;
int move_count = 0;
QTime game_time;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);

    game_time.setHMS(0,0,0);
    ui->label->setText(game_time.toString("hh:mm:ss"));

    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();

    petno = Petno();
    petno.startGame();
    petno_start_copy = petno;
    showTable();
}

MainWindow::~MainWindow()
{
    if (timer->isActive()) {
        timer->stop();
    }
    delete ui;
}

void MainWindow::showTime()
{
    game_time = game_time.addSecs(1);
    ui->label->setText(game_time.toString("hh:mm:ss"));
}

void MainWindow::showTable()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++){
            if (petno.getItem(i,j) != 16) {
            ui->twPetno->setItem(i, j, new QTableWidgetItem((QString::number(petno.getItem(i,j)))));
            } else {
                ui->twPetno->setItem(i, j, new QTableWidgetItem(" "));
            }
    }
}

void MainWindow::resetAllFields()
{
    move_count = 0;
    ui->label_3->setText(QString::number(move_count));

    game_time.setHMS(0,0,0);
    ui->label->setText(game_time.toString("hh:mm:ss"));
    if (timer->isActive()) {
        timer->stop();
    }
    timer->start();
}

void MainWindow::on_twPetno_cellDoubleClicked(int row, int column)
{
    if (petno.exchange(row,column)) {
        move_count++;
        ui->label_3->setText(QString::number(move_count));

        showTable();

        if (petno.isFinished()) {
            timer->stop();
            if (QMessageBox::question(this, "Игра закончена!", "Победа! Желаете сыграть снова?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
                 QApplication::quit();
            } else {
                on_pbNewGame_clicked();
            }
        }
    }
}

void MainWindow::on_pbRestart_clicked()
{
    petno = petno_start_copy;
    resetAllFields();
    showTable();
}

void MainWindow::on_pbNewGame_clicked()
{
    petno.startGame();
    petno_start_copy = petno;
    resetAllFields();
    showTable();
}

void MainWindow::on_pb100Moves_clicked()
{
    petno.move100();
    showTable();
}
