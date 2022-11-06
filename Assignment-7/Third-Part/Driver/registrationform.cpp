#include "registrationform.h"
#include "ui_registrationform.h"

using namespace std;
registrationForm::registrationForm(DriverClient *_client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrationForm)
{

    client=_client;
    ui->setupUi(this);
    initialModels();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

registrationForm::~registrationForm()
{
    delete ui;
}
void registrationForm::initialModels(){
     ui->models->addItem("");
    QFile filePtr (":/CFG/vehicles.cfg");
    if(!filePtr.open(QFile::ReadOnly|QFile::Text)){
        cerr<<"Unable to open"<<endl;
        return;
    }
    QTextStream in(&filePtr);
    while(!in.atEnd()){
        QString line=in.readLine();
        ui->models->addItem(line);
    }
    filePtr.close();
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
    QString model=ui->models->currentText();
    QString year=ui->yearTxt->text();
    QString color=ui->colortxt->text();
    if(ui->retypeTxt->text()!=password)
        return;
    if(!(username.size()&&password.size()&&model.size()&&number.size()&&year.size()&&color.size()))
        QMessageBox::warning(this,tr("Undone fileds"),tr("All the fields are necessary.\n Please fill all of them."));
    QString request="register "+username+" "+password+" "+number+" "+model+" "+year+" "+color;
    if(ui->VIPCheck->checkState())
        request+=" VIP";

    string response=client->sendRequest((request).toStdString());

    if(response.size())
        ui->errlbl->setText(QString::fromStdString(response));
    else{
        MainWindow *loginPage=new MainWindow(client);
        loginPage->show();
        close();

    }

}
