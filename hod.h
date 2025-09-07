#ifndef HOD_H
#define HOD_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>



namespace Ui {
class HOD;
}

class HOD : public QDialog
{
    Q_OBJECT
public:
    QSqlDatabase DB;

    void connclose()
    {
        DB.close();
        DB.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connopen()
    {
        DB=QSqlDatabase::addDatabase("QSQLITE");
        DB.setDatabaseName("C:/Users/hp/Desktop/LMS/Stu.db");

        if(!DB.open()){
            qDebug()<<("failed");
            return false;


        }
        else{
            qDebug()<<("connected...");
            return true;
        }
    }

public:
    explicit HOD(QWidget *parent = nullptr);
    ~HOD();

private slots:
    void on_pushButton_clicked();
    void on_comboBox_textActivated( QString);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_3_currentTextChanged(const QString &arg1);

private:
    Ui::HOD *ui;



};

#endif // HOD_H
