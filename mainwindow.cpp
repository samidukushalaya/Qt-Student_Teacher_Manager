#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("    UserName");
    ui->lineEdit_2->setPlaceholderText("    Password");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if(username=="123" && password=="123"){

      hod = new HOD(this);
      hod->show();
    }

    else{
        if(username=="123"){

            ui->statusbar->showMessage("   Password is incorrect");}

        else{
            ui->statusbar->showMessage("   Username is incorrect");
            }

    }

}

