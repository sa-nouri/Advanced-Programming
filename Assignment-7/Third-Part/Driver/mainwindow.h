#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "driver_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DriverClient*,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loginCmd_clicked();



    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DriverClient *driverClient;

};

#endif // MAINWINDOW_H
