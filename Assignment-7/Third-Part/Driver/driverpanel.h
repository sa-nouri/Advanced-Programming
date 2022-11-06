#ifndef DRIVERPANEL_H
#define DRIVERPANEL_H
#include "driver_client.h"
#include <QWidget>
#include "tools.h"
#include <vector>
#include <QFile>
#include<QString>
#include <QTextStream>
#include <QMessageBox>
#include <QtCore>
#include<QtGui>
#include <QTreeWidgetItem>
#include "mainwindow.h"
namespace Ui {
class driverPanel;
}

class driverPanel : public QWidget
{
    Q_OBJECT

public:
    explicit driverPanel(DriverClient *driverClient, QWidget *parent = 0);
    ~driverPanel();

private slots:


    void on_availableCheck_clicked();

    void on_universeTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_tabWidget_tabBarClicked(int index);
    void reloadTripsTable();

    void on_acceptCmd_clicked();

    void on_reloadCmd_clicked();

    void on_endTripCmd_clicked();

    void on_arrivedCmd_clicked();

    void on_logoutCmd_clicked();

private:
    Ui::driverPanel *ui;
    DriverClient* driverClient;
    void loadUniverse();
    QTreeWidgetItem* addRoot(QString name);
    void addChild(QString name, QTreeWidgetItem *parent);
};

#endif // DRIVERPANEL_H
