#ifndef PASSENGERPANEL_H
#define PASSENGERPANEL_H
#include "passenger_client.h"
#include <QWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QFile>
#include<QString>
#include <QTextStream>
#include <QtCore>
#include<QtGui>
#include <QInputDialog>
#include <QTableWidgetItem>
namespace Ui {
class passengerPanel;
}

class passengerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit passengerPanel(PassengerClient *passengerClient,QWidget *parent = 0);
    ~passengerPanel();

private slots:

    void on_deleteField_clicked();

    void on_addField_clicked();


    void on_universeTree_itemClicked(QTreeWidgetItem *item, int column);

    void on_discontCmd_clicked();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_chargeCmd_clicked();

    void on_pushButton_2_clicked();

    void on_reloadCmd_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_destinationList_itemChanged(QTableWidgetItem *item);

    void on_vipCheck_clicked();

    void on_requestCmd_clicked();

private:
    Ui::passengerPanel *ui;
    PassengerClient *passengerClient;
    void loadUniverse();
    QTreeWidgetItem* addRoot(QString name);
    void addChild(QString name,QTreeWidgetItem *parent);
    void on_universeTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void reloadTripStatus();
    void refreshCostDistance();
};

#endif // PASSENGERPANEL_H
