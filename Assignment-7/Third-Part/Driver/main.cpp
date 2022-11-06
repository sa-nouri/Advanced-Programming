#include "mainwindow.h"
#include <QApplication>
#include "network_exception.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        DriverClient driverClient("127.0.0.1",12000);
        MainWindow w(&driverClient);

        w.show();

        return a.exec();

    }catch(NetworkException ex){

        QMessageBox messageBox;
        messageBox.critical(0,"Connection Error","Can not connect to the server.");
        messageBox.setFixedSize(500,200);

        return 0;
    }
}
