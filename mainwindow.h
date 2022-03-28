#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resetAllFields();

private slots:
    void on_pbRestart_clicked();
    void on_pbNewGame_clicked();
    void on_twPetno_cellDoubleClicked(int row, int column);
    void showTime();
    
    void on_pb100Moves_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;

    void showTable();
};
#endif // MAINWINDOW_H
