#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registrationform.h"
#include "driverpanel.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(DriverClient *driverClient,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
   driverClient(driverClient)
{
    ui->setupUi(this);
    connect(ui->loginCmd, SIGNAL(clicked()), this, SLOT(on_loginCmd_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginCmd_clicked()
{
    QString username=ui->userNameTxt->text();
    QString password= ui->passTxt->text();
    if(username.size()==0||password.size()==0){
        ui->errLbl->setText("Please enter required fields.");
        return ;
    }
    string response=driverClient->sendRequest(("login "+username+" "+password).toStdString());
    if(response.size())
         ui->errLbl->setText(QString::fromStdString(response));
    else{
        driverPanel *panel= new driverPanel(driverClient);
        panel->show();
        close();
    }

}


void MainWindow::on_pushButton_clicked()
{
    registrationForm *regfrm=new registrationForm(driverClient);
    regfrm->show();
    close();
}
