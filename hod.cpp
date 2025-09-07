#include "hod.h"
#include "ui_hod.h"
#include<QSqlQuery>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>




HOD::HOD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HOD)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("    Student ID");
    ui->lineEdit_2->setPlaceholderText("    Student Name");
    ui->lineEdit_3->setPlaceholderText("    NIC");
    ui->lineEdit_4->setPlaceholderText("    Age");
    ui->lineEdit_5->setPlaceholderText("    Birthday");
    ui->lineEdit_6->setPlaceholderText("    E-mail");
    ui->comboBox->setPlaceholderText("    Deparment");
    ui->comboBox_2->setPlaceholderText("    Course");
    ui->lineEdit_9->setPlaceholderText("    Enter the Student ID..");
    ui->lineEdit_7->setPlaceholderText("    Teacher ID");
    ui->lineEdit_8->setPlaceholderText("    Teacher Name");
    ui->lineEdit_10->setPlaceholderText("   NIC");
    ui->lineEdit_11->setPlaceholderText("    Age");
    ui->comboBox_3->setPlaceholderText("    Deparment");
    ui->comboBox_4->setPlaceholderText("    Course");
    ui->lineEdit_12->setPlaceholderText("    Enter the Teacher ID..");

    if (!connopen()){
        qDebug()<<"Not connected..";

    }

    else {
           qDebug()<<"connected..";
    }








}

HOD::~HOD()
{
    delete ui;
}

void HOD::on_pushButton_clicked()
{


   QString Name,email,departments,course, id,nic,age,bday;

    id=ui->lineEdit->text();
    Name=ui->lineEdit_2->text();
    nic=ui->lineEdit_3->text();
    age=ui->lineEdit_4->text();
    bday=ui->lineEdit_5->text();
    email=ui->lineEdit_6->text();
    departments=ui->comboBox->currentText();
    course=ui->comboBox_2->currentText();

    if (!connopen()){
        qDebug()<<"failed";
            return;
    }

    connopen();

    QSqlQuery qry;
    qry.prepare("insert into table_1(ID,name,nic,age,bday,email,department,course)"
                "values(:ID,:name,:nic,:age,:bday,:email,:department,:course)");

    qry.bindValue(":ID",id);
    qry.bindValue(":name",Name);
    qry.bindValue(":nic",nic);
    qry.bindValue(":age",age);
    qry.bindValue(":bday",bday);
    qry.bindValue(":email",email);
    qry.bindValue(":department",departments);
    qry.bindValue(":course",course);

    if (qry.exec()){
        qDebug()<<"Saved";
    }
    else{
        qDebug()<<"Not Saved..";
    }
    connclose();









}




void HOD::on_comboBox_textActivated(QString)
{
    QString department;
    department=ui->comboBox->currentText();
    if (department=="Computing"){
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("software Enginerning");
        ui->comboBox_2->addItem("Information Tecnology");
    }
    else{
        ui->comboBox_2->clear();
        ui->comboBox_2->addItem("Managment");
        ui->comboBox_2->addItem("Human Resoures");
    }


}


void HOD::on_pushButton_4_clicked()
{

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->comboBox->currentText();
    ui->comboBox_2->currentText();

}


void HOD::on_pushButton_2_clicked()
{
    QString Name,email,departments,course, id,nic,age,bday;

    id=ui->lineEdit->text();
    Name=ui->lineEdit_2->text();
    nic=ui->lineEdit_3->text();
    age=ui->lineEdit_4->text();
    bday=ui->lineEdit_5->text();
    email=ui->lineEdit_6->text();
    departments=ui->comboBox->currentText();
    course=ui->comboBox_2->currentText();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }

    connopen();
    QSqlQuery qry;
    qry.prepare("update  table_1 set ID=:id,name=:name,nic=:nic, age=:age,bday=:bday, email=:email, department=:departments, course=:course where ID=:id");
                qry.bindValue(":id",id);
                qry.bindValue(":name",Name);
                qry.bindValue(":nic",nic);
                qry.bindValue(":age",age);
                qry.bindValue(":bday",bday);
                qry.bindValue(":email",email);
                qry.bindValue(":departments",departments);
                qry.bindValue(":course",course);
        if (qry.exec()){
        qDebug()<<"Updated";
    }
    else{
        qDebug()<<"Not Updated";
    }
    connclose();
}


void HOD::on_pushButton_3_clicked()
{
    QString id;

    id=ui->lineEdit_9->text();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }

    connopen();
    QSqlQuery qry;
    qry.prepare("Delete from table_1 where ID=:id");
    qry.bindValue(":id",id);

    if (qry.exec()){
        qDebug()<<"DELETE";
    }
    else{
        qDebug()<<"not delete";
    }
    connclose();
}


void HOD::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();

    if (!connopen()) {
        qDebug() << "Failed to open DB";
        return;
    }

    QSqlQuery qry(DB);
    qry.prepare(R"(
        SELECT * FROM table_1
        WHERE ID = :val OR name = :val OR nic = :val
              OR age = :val OR bday = :val OR email = :val
              OR department = :val OR course = :val
    )");
    qry.bindValue(":val", val);

    if (qry.exec()) {
        if (qry.next()) {   // only one row expected
            ui->lineEdit->setText(qry.value(0).toString());
            ui->lineEdit_2->setText(qry.value(1).toString());
            ui->lineEdit_3->setText(qry.value(2).toString());
            ui->lineEdit_4->setText(qry.value(3).toString());
            ui->lineEdit_5->setText(qry.value(4).toString());
            ui->lineEdit_6->setText(qry.value(5).toString());
            ui->comboBox->setCurrentText(qry.value(6).toString());
            ui->comboBox_2->setCurrentText(qry.value(7).toString());
        }
    } else {
        qDebug() << "Query failed:" << qry.lastError().text();
    }

    connclose();
}


void HOD::on_pushButton_9_clicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    connopen();
    modal->setQuery("SELECT * FROM table_1", DB);

    ui->tableView->setModel(modal);
    connclose();



}


void HOD::on_pushButton_5_clicked()
{
    QString id,name,nic,age,department,course;
    id=ui->lineEdit_7->text();
    name=ui->lineEdit_8->text();
    nic=ui->lineEdit_10->text();
    age=ui->lineEdit_11->text();
    department=ui->comboBox_3->currentText();
    course=ui->comboBox_4->currentText();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }
    connopen();

    QSqlQuery qry;
    qry.prepare("insert into table_2(ID,name,NIC,Age,Departments,Course)"
                "values(:ID,:name,:nic,:age,:department,:course)");

                qry.bindValue(":ID",id);
                qry.bindValue(":name",name);
                qry.bindValue(":nic",nic);
                qry.bindValue(":age",age);
                qry.bindValue(":department",department);
                qry.bindValue(":course",course);

                if (qry.exec()){
                    qDebug()<<"Saved";
                }
                else{
                    qDebug()<<"Not Saved";
                }
                connclose();








}


void HOD::on_pushButton_10_clicked()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    connopen();
    modal->setQuery("SELECT * FROM table_2", DB);

    ui->tableView_2->setModel(modal);
    connclose();

}


void HOD::on_tableView_2_activated(const QModelIndex &index)
{
    QString val=ui->tableView_2->model()->data(index).toString();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }

    connopen();
    QSqlQuery qry;
    qry.prepare("select * from table_2 where ID='"+val+"' or name='"+val+"' or NIC='"+val+"' or Age='"+val+"' or Departments='"+val+"' or Course='"+val+"'");

    if (qry.exec()){
        while (qry.next()) {

            //ui->txt_ID->setText(qry.value(0)).tostring());
            ui->lineEdit_7->setText(qry.value(0).toString());
            ui->lineEdit_8->setText(qry.value(1).toString());
            ui->lineEdit_10->setText(qry.value(2).toString());
            ui->lineEdit_11->setText(qry.value(3).toString());
            ui->comboBox_3->setCurrentText(qry.value(4).toString());
            ui->comboBox_4->setCurrentText(qry.value(5).toString());

        }
        connclose();
    }
}


void HOD::on_pushButton_7_clicked()
{
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->comboBox_3->currentText();
    ui->comboBox_4->currentText();

}


void HOD::on_pushButton_8_clicked()
{
    QString id;

    id=ui->lineEdit_12->text();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }

    connopen();
    QSqlQuery qry;
    qry.prepare("Delete from table_2 where ID=:id");
    qry.bindValue(":id",id);

    if (qry.exec()){
        qDebug()<<"DELETE";
    }
    else{
        qDebug()<<"not delete";
    }
    connclose();
}


void HOD::on_pushButton_6_clicked()
{
    QString id,name,nic,age,department,course;
    id=ui->lineEdit_7->text();
    name=ui->lineEdit_8->text();
    nic=ui->lineEdit_10->text();
    age=ui->lineEdit_11->text();
    department=ui->comboBox_3->currentText();
    course=ui->comboBox_4->currentText();

    if (!connopen()){
        qDebug()<<"failed";
        return;
    }
    connopen();
    QSqlQuery qry;
    qry.prepare("update  table_2 set ID=:id,name=:name,NIC=:nic,Age=:age,Departments=:department,Course=:course where ID=:id");
    qry.bindValue(":id",id);
    qry.bindValue(":name",name);
    qry.bindValue(":nic",nic);
    qry.bindValue(":age",age);
    qry.bindValue(":department",department);
    qry.bindValue(":course",course);

    if (qry.exec()){
        qDebug()<<"Updated";
    }
    else{
        qDebug()<<"Not Updated";
    }
    connclose();





}





void HOD::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    QString department;
    department=ui->comboBox_3->currentText();
    if (department=="Computing"){
        ui->comboBox_4->clear();
        ui->comboBox_4->addItem("software Enginerning");
        ui->comboBox_4->addItem("Information Tecnology");
    }
    else{
        ui->comboBox_4->clear();
        ui->comboBox_4->addItem("Managment");
        ui->comboBox_4->addItem("Human Resoures");
    }
}

