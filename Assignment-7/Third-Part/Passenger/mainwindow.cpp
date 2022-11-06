#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registrationform.h"
#include "passengerpanel.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(PassengerClient *passengerClient, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
   passengerClient(passengerClient)
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
    string response=passengerClient->sendRequest(("login "+username+" "+password).toStdString());
    if(response.size())
         ui->errLbl->setText(QString::fromStdString(response));
    else{
        passengerPanel *panel= new passengerPanel(passengerClient);
        panel->show();
        close();
    }

}


void MainWindow::on_pushButton_clicked()
{
    registrationForm *regfrm=new registrationForm(passengerClient);
    regfrm->show();
    close();
}
