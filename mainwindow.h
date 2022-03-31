#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTimer();
    
    void on_NewGame_triggered();
    
    void on_Restart_triggered();
    
    void on_Tiles_cellClicked(int row, int column);

    void on_Quit_triggered();

private:
    Ui::MainWindow *ui;
    int hours, minutes, seconds;
    QTimer *time;
    QTableWidgetItem *itNum = new QTableWidgetItem;
    void showField();
};
#endif // MAINWINDOW_H
