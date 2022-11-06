#include "driverpanel.h"
#include "ui_driverpanel.h"
#include <QFile>
#include <QMessageBox>
using namespace std;
driverPanel::driverPanel(DriverClient* driverClient, QWidget *parent) :
    QWidget(parent),
    driverClient(driverClient),
    ui(new Ui::driverPanel)
{

    ui->setupUi(this);
    loadUniverse();
     connect(ui->availableCheck, SIGNAL(clicked()), this, SLOT(on_availableCheck_clicked()));

}

driverPanel::~driverPanel()
{
    delete ui;
}

void driverPanel::on_availableCheck_clicked()
{

    ui->universeTree->setEnabled(ui->availableCheck->checkState());
    if(!ui->availableCheck->checkState()){
       ui->locationLbl->setText("");
       driverClient->sendRequest(("set_status unavailable"));
    }

}

void driverPanel::loadUniverse(){

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
QTreeWidgetItem* driverPanel::addRoot(QString name){

    QTreeWidgetItem *item=new QTreeWidgetItem(ui->universeTree);
    item->setText(0,name);
    ui->universeTree->addTopLevelItem(item);
    return item;
}

void driverPanel::addChild(QString name,QTreeWidgetItem *parent){

    QTreeWidgetItem *item=new QTreeWidgetItem();
    item->setText(0,name);
 parent->addChild(item);
}

void driverPanel::on_universeTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{

   if(!current->parent())
       return;

   QString currentAddress= current->parent()->text(0)+','+current->text(0);

   string response=driverClient->sendRequest(("set_status available "+currentAddress).toStdString());

   if(response.size()){
       QMessageBox messageBox;
       messageBox.critical(0,"Set Location",QString::fromStdString(response));
       messageBox.setFixedSize(500,200);
   }else
       ui->locationLbl->setText(current->parent()->text(0)+','+current->text(0));

}

void driverPanel::on_tabWidget_tabBarClicked(int index)
{
    if(index==1) reloadTripsTable();
}


void driverPanel::reloadTripsTable(){

    ui->requestsTable->setRowCount(0);
    if(!driverClient->sendRequest("show_trip_requests").size())
        return;
    int maxFileds=0;
    QStringList lines=QString::fromStdString(driverClient->sendRequest("show_trip_requests")).split('\n');
    for(int i=0;i<lines.size();i++)
        if(maxFileds<lines[i].split(' ').size())
            maxFileds=lines[i].split(' ').size();
    ui->requestsTable->setColumnCount(maxFileds);
    QStringList fieldTitles;
    fieldTitles<<"Username"<<"Source address";
    for(int i=2;i<maxFileds-3;i++)
        fieldTitles<<"Destination"+QString::number(i-1);
    fieldTitles<<"Final Destination"<<"Trip Cost"<<"Trip Distance";
    ui->requestsTable->setHorizontalHeaderLabels(fieldTitles);

    for(int i=0;i<lines.size();i++){
        QStringList fieldItems=lines[i].split(' ');
        ui->requestsTable->insertRow(ui->requestsTable->rowCount());

        int rowCnt=ui->requestsTable->rowCount();
        for(int j=0;j<fieldItems.size()-3;j++)
            ui->requestsTable->setItem(rowCnt-1,j,new QTableWidgetItem(fieldItems[j]));

         ui->requestsTable->setItem(rowCnt-1,maxFileds-3,new QTableWidgetItem(fieldItems[fieldItems.size()-3]));
         ui->requestsTable->setItem(rowCnt-1,maxFileds-2,new QTableWidgetItem(fieldItems[fieldItems.size()-2]));
         ui->requestsTable->setItem(rowCnt-1,maxFileds-1,new QTableWidgetItem(fieldItems[fieldItems.size()-1]));

    }
     ui->retranslateUi(this);
}

void driverPanel::on_acceptCmd_clicked()
{
    if(!ui->requestsTable->selectedItems().size())
        return;
    string response=driverClient->sendRequest(("accept_trip_request "+ui->requestsTable->selectedItems()[0]->text()).toStdString());
    if(response.size()){
        QMessageBox messageBox;
        messageBox.critical(0,"Trip Acception",QString::fromStdString(response));
        messageBox.setFixedSize(500,200);
    }
    reloadTripsTable();

}

void driverPanel::on_reloadCmd_clicked()
{
    reloadTripsTable();
}

void driverPanel::on_endTripCmd_clicked()
{
   driverClient->sendRequest("end_trip");
}

void driverPanel::on_arrivedCmd_clicked()
{
    driverClient->sendRequest("arrived");
}

void driverPanel::on_logoutCmd_clicked()
{
    driverClient->sendRequest("logout");
    MainWindow *login=new MainWindow(driverClient);
    login->show();
    close();
}
