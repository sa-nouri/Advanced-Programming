#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "passenger_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PassengerClient*,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loginCmd_clicked();



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PassengerClient *passengerClient;

};

#endif // MAINWINDOW_H
