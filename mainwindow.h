#pragma once

#include <QMainWindow>

#include"hod.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void onLoginButtonClicked();

private:
    Ui::MainWindow* ui;
    HOD* m_hod;
};
