#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H
#include "passenger_client.h"
#include <QWidget>
#include <QFile>
#include<QString>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include "mainwindow.h"
namespace Ui {
class registrationForm;
}

class registrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit registrationForm(PassengerClient* _client, QWidget *parent = 0);
    ~registrationForm();

private slots:


    void on_retypeTxt_textChanged(const QString &arg1);



    void on_pushButton_clicked();

private:
    Ui::registrationForm *ui;
    void initialModels();
    PassengerClient *client;

};

#endif // REGISTRATIONFORM_H
