#include "passengerpanel.h"
#include "ui_passengerpanel.h"
#include <iostream>
#include<QMessageBox>
using namespace std;
#include "mainwindow.h"
passengerPanel::passengerPanel(PassengerClient *passengerClient, QWidget *parent) :
    QWidget(parent),
    passengerClient(passengerClient),
    ui(new Ui::passengerPanel)
{
    ui->setupUi(this);
    ui->destinationList->insertRow(0);
    loadUniverse();

}

passengerPanel::~passengerPanel()
{
    delete ui;
}

void passengerPanel::on_deleteField_clicked()
{
    if(!ui->destinationList->columnCount())
        return;

    if(ui->destinationList->selectedItems().size())
        ui->destinationList->removeColumn(ui->destinationList->selectedItems()[0]->column());

    else
        ui->destinationList->removeColumn(ui->destinationList->columnCount());
    refreshCostDistance();
}

void passengerPanel::on_addField_clicked()
{
    if(ui->destinationList->selectedItems().size()){
        ui->destinationList->insertColumn(ui->destinationList->selectedItems()[0]->column()+1);
        ui->destinationList->setItem(0,ui->destinationList->selectedItems()[0]->column()+1,new QTableWidgetItem(""));
    }
    else{
        ui->destinationList->insertColumn(ui->destinationList->columnCount());
        ui->destinationList->setItem(0,ui->destinationList->columnCount()-1,new QTableWidgetItem(""));
    }
    refreshCostDistance();

}

void passengerPanel::loadUniverse(){

    ui->universeTree->setColumnCount(1);
    QFile filePtr (":/CFG/topology.cfg");
    if(!filePtr.open(QFile::ReadOnly|QFile::Text)){
        cerr<<"Unable to open"<<endl;
        return;
    }
    QTextStream in(&filePtr);
    while(!in.atEnd()){
        QString line=in.readLine();
        int numOfGalaxy=line.toInt();

        for(int i=0;i<numOfGalaxy;i++){
            line=in.readLine();
            int numOfPlanet=line.split(" ")[1].toInt();
           QTreeWidgetItem *root=addRoot(line.split(" ")[0]);
            for(int j=0;j<numOfPlanet;j++){
                line=in.readLine();
                int neighbors=line.split(" ")[1].toInt();
               addChild(line.split(" ")[0],root);
                for(int k=0;k<neighbors;k++)
                    line=in.readLine();

            }
        }
    }
    filePtr.close();
}
QTreeWidgetItem* passengerPanel::addRoot(QString name){

    QTreeWidgetItem *item=new QTreeWidgetItem(ui->universeTree);
    item->setText(0,name);
    ui->universeTree->addTopLevelItem(item);
    return item;
}

void passengerPanel::addChild(QString name,QTreeWidgetItem *parent){

    QTreeWidgetItem *item=new QTreeWidgetItem();
    item->setText(0,name);
    parent->addChild(item);
}






void passengerPanel::on_universeTree_itemClicked(QTreeWidgetItem *item, int column)
{

    if(!item->parent())
        return;
    if(!ui->destinationList->selectedItems().size()){
        QMessageBox messageBox;
        messageBox.critical(0,"Creating Destination","Please first select destination cell.");
        messageBox.setFixedSize(500,200);

    }else
        ui->destinationList->selectedItems()[0]->setText(item->parent()->text(0)+','+item->text(0));
}

void passengerPanel::on_discontCmd_clicked()
{
    QString response=QString::fromStdString(passengerClient->sendRequest("get_discount_code"));

    QMessageBox messageBox;
    messageBox.information(0,"Discount Code","Discount code: "+response.split(' ')[0]+'\n'+"Remained times: "+response.split(' ')[1]);
    messageBox.setFixedSize(500,200);

}

void passengerPanel::on_pushButton_clicked()
{
    QString response=QString::fromStdString(passengerClient->sendRequest("cancel_trip_request"));
    if(!response.size()) return;
    QMessageBox messageBox;
    messageBox.critical(0,"Trip Cancelation",response);
    messageBox.setFixedSize(500,200);

}

void passengerPanel::on_horizontalSlider_valueChanged(int value)
{
    passengerClient->sendRequest("rate_driver "+QString::number(value).toStdString());
}

void passengerPanel::on_chargeCmd_clicked()
{
    bool ok;
    int i = QInputDialog::getInt(this, tr("Charge Account"),
                                 tr("amount:"),0,-2147483647 ,2147483647 , 1, &ok);
    if (ok)
        passengerClient->sendRequest("charge_account "+QString::number(i).toStdString());
}

void passengerPanel::on_pushButton_2_clicked()
{
     passengerClient->sendRequest("logout");
     MainWindow *login=new MainWindow(passengerClient);
     login->show();
     close();
}
void passengerPanel::reloadTripStatus(){

    ui->tripStatusTable->setRowCount(0);
    ui->tripStatusTable->setColumnCount(4);
    QStringList titles;titles<<"Username"<<"Address"<<"Model"<<"Spaceship Color";
    ui->tripStatusTable->setHorizontalHeaderLabels(titles);

    QString response=QString::fromStdString(passengerClient->sendRequest("trip_status"));
    ui->statusLbl->setText(response);
    if(response.split(' ')[0]=="accepted")
        ui->statusLbl->setText("accepted");
    if(response=="waiting"||response.split(' ')[0]!="accepted")
        return;

    QStringList fieldItems=response.split(' ');
    ui->tripStatusTable->insertRow(0);
    for(int i=1;i<5;i++)
        ui->tripStatusTable->setItem(0,i-1,new QTableWidgetItem(fieldItems[i]));
}

void passengerPanel::on_reloadCmd_clicked()
{
    reloadTripStatus();
}

void passengerPanel::on_tabWidget_tabBarClicked(int index)
{
    if(index==1) reloadTripStatus();
}

void passengerPanel::on_destinationList_itemChanged(QTableWidgetItem *item)
{
    refreshCostDistance();
}
void passengerPanel::refreshCostDistance(){

    QString destinationsStr;
    for(int i=0;i<ui->destinationList->columnCount();i++)
        if(ui->destinationList->item(0,i)->text().size())
            destinationsStr+=ui->destinationList->item(0,i)->text()+" ";
    destinationsStr=destinationsStr.trimmed();
    string request="estimate_trip ";
    if(ui->vipCheck->checkState())
        request+="VIP ";
    request=request+destinationsStr.toStdString();

    QString response=QString::fromStdString(passengerClient->sendRequest(request));

    if(response=="Bad arguments."){
        ui->costLbl->setText("");
        ui->distanceLbl->setText("");
        return;
    }
    if(/*response=="Last trip is still undone."||response=="Last trip is not rated."||response=="No driver is available at the moment."||*/response=="Invalid address."){
        QMessageBox messageBox;
        messageBox.critical(0,"Trip Estimation",response);
        messageBox.setFixedSize(500,200);
    }
    ui->costLbl->setText(response.split(' ')[0]);
    ui->distanceLbl->setText(response.split(' ')[1]);

}

void passengerPanel::on_vipCheck_clicked()
{
    refreshCostDistance();
}

void passengerPanel::on_requestCmd_clicked()
{
    QString destinationsStr;
    for(int i=0;i<ui->destinationList->columnCount();i++)
        if(ui->destinationList->item(0,i)->text().size())
            destinationsStr+=ui->destinationList->item(0,i)->text()+" ";
    destinationsStr=destinationsStr.trimmed();
    string request="request_trip ";
    if(ui->vipCheck->checkState())
        request+="VIP ";
    request=request+destinationsStr.toStdString();

    QString response=QString::fromStdString(passengerClient->sendRequest(request));

    if(response=="Bad arguments."){
        ui->costLbl->setText("");
        ui->distanceLbl->setText("");
        return;
    }
    if(response.split(' ')[1]=="doesn't"||response=="Last trip is still undone."||response=="Last trip is not rated."||response=="No driver is available at the moment."||response=="Invalid address."){
        QMessageBox messageBox;
        messageBox.critical(0,"Trip Cancelation",response);
        messageBox.setFixedSize(500,200);
        ui->costLbl->setText("");
        ui->distanceLbl->setText("");
        return;
    }
    ui->costLbl->setText(response.split(' ')[0]);
    ui->distanceLbl->setText(response.split(' ')[1]);
}
