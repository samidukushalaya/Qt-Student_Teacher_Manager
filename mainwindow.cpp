#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginButtonClicked()
{
    QString username = ui->userLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.compare(QString("admin")) == 0 && password.compare(QString("admin")) == 0)
    {
        m_hod = new HOD(this);
        m_hod->show();
    }
    else
    {
        if(username=="123")
        {
            ui->statusbar->showMessage("Password is incorrect");
        }
        else
        {
            ui->statusbar->showMessage("Username is incorrect");
        }
    }

}

