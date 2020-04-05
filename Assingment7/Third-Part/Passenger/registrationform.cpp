#include "registrationform.h"
#include "ui_registrationform.h"

using namespace std;
registrationForm::registrationForm(PassengerClient* _client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrationForm)
{

    client=_client;
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

registrationForm::~registrationForm()
{
    delete ui;
}


void registrationForm::on_retypeTxt_textChanged(const QString &arg1)
{
    if(ui->passwordTxt->text()!=ui->retypeTxt->text())
        ui->retypeTxt->setStyleSheet("border: 1px solid red");
    else
        ui->retypeTxt->setStyleSheet("border: 1px solid green");
}

void registrationForm::on_pushButton_clicked()
{
    QString username=ui->usernameTxt->text();
    QString password=ui->passwordTxt->text();
    QString number=ui->numberTxt->text();

    if(ui->retypeTxt->text()!=password)
        return;
    if(!(username.size()&&password.size()&&number.size()))
        QMessageBox::warning(this,tr("Undone fileds"),tr("All the fields are necessary.\n Please fill all of them."));
    QString request="register "+username+" "+password+" "+number;


    string response=client->sendRequest((request).toStdString());

    if(response.size())
        ui->errlbl->setText(QString::fromStdString(response));
    else{
        MainWindow *loginPage=new MainWindow(client);
        loginPage->show();
        close();

    }

}
