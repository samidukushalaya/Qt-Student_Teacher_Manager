#include "hod.h"
#include "ui_hod.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include "DatabaseManager.h"

HOD::HOD(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HOD)
{
    ui->setupUi(this);

    setupConnections();
}

HOD::~HOD()
{
    delete ui;
}

void HOD::onAddStudentButtonClicked()
{
    QString name = ui->studentNameLineEdit->text();
    QString nic = ui->studentNicLineEdit->text();
    int age = ui->studentAgeLineEdit->text().toInt();
    QString birthdate = ui->studentBirthdateLineEdit->text();
    QString email = ui->studentEmailLineEdit->text();
    QString department = ui->studentDepartmentComboBox->currentText();
    QString course = ui->studentCourseComboBox->currentText();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("INSERT INTO students(name, nic, age, birthdate, email, department, course)"
                "VALUES(:name, :nic, :age, :birthdate, :email, :department, :course)");

    qry.bindValue(":name", name);
    qry.bindValue(":nic", nic);
    qry.bindValue(":age", age);
    qry.bindValue(":birthdate", birthdate);
    qry.bindValue(":email", email);
    qry.bindValue(":department", department);
    qry.bindValue(":course", course);

    if (qry.exec())
    {
        qDebug() << "Student saved";
    }
    else
    {
        qDebug() << "Student NOT saved";
    }
}

void HOD::onDepartmentStudentComboBoxChanged()
{
    QString department = ui->studentDepartmentComboBox->currentText();
    ui->studentCourseComboBox->clear();

    if (department.compare(QString("Computing")) == 0)  // 'compare' returns 0 if the QStrings are equal
    {
        ui->studentCourseComboBox->addItem("Software Engineering");
        ui->studentCourseComboBox->addItem("Information Tecnology");
    }
    else
    {
        ui->studentCourseComboBox->addItem("Management");
        ui->studentCourseComboBox->addItem("Human Resources");
    }
}

void HOD::onClearStudentButtonClicked()
{
    ui->studentIdLineEdit->clear();
    ui->studentNameLineEdit->clear();
    ui->studentNicLineEdit->clear();
    ui->studentAgeLineEdit->clear();
    ui->studentBirthdateLineEdit->clear();
    ui->studentEmailLineEdit->clear();
    ui->studentDepartmentComboBox->currentText();
    ui->studentCourseComboBox->currentText();
}

void HOD::onModifyStudentButtonClicked()
{
    int id = ui->studentIdLineEdit->text().toInt();
    QString name = ui->studentNameLineEdit->text();
    QString nic = ui->studentNicLineEdit->text();
    int age = ui->studentAgeLineEdit->text().toInt();
    QString birthdate = ui->studentBirthdateLineEdit->text();
    QString email = ui->studentEmailLineEdit->text();
    QString department = ui->studentDepartmentComboBox->currentText();
    QString course = ui->studentCourseComboBox->currentText();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("UPDATE students SET name=:name, nic=:nic, age=:age, birthdate=:birthdate, email=:email, department=:department, course=:course where id=:id");
    qry.bindValue(":id", id);
    qry.bindValue(":name", name);
    qry.bindValue(":nic", nic);
    qry.bindValue(":age", age);
    qry.bindValue(":birthdate", birthdate);
    qry.bindValue(":email", email);
    qry.bindValue(":department", department);
    qry.bindValue(":course", course);

    if (qry.exec())
    {
        qDebug()<<"Student updated";
    }
    else
    {
        qDebug()<<"Student NOT updated";
    }
}

void HOD::onRemoveStudentButtonClicked()
{
    int id = ui->removeStudentLineEdit->text().toInt();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("DELETE FROM students WHERE id=:id");
    qry.bindValue(":id", id);

    if (qry.exec())
    {
        qDebug() << "Student deleted";
    }
    else
    {
        qDebug() << "Student NOT deleted";
    }
}

void HOD::onStudentTableViewActivated(const QModelIndex &index)
{
    QString val = ui->studentTableView->model()->data(index).toString();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare(R"(
        SELECT * FROM students
        WHERE id = :val OR name = :val OR nic = :val
              OR age = :val OR birthdate = :val OR email = :val
              OR department = :val OR course = :val
    )");
    qry.bindValue(":val", val);

    if (qry.exec())
    {
        if (qry.next()) // Only one row selected
        {
            ui->studentIdLineEdit->setText(qry.value(0).toString());
            ui->studentNameLineEdit->setText(qry.value(1).toString());
            ui->studentNicLineEdit->setText(qry.value(2).toString());
            ui->studentAgeLineEdit->setText(qry.value(3).toString());
            ui->studentBirthdateLineEdit->setText(qry.value(4).toString());
            ui->studentEmailLineEdit->setText(qry.value(5).toString());
            ui->studentDepartmentComboBox->setCurrentText(qry.value(6).toString());
            ui->studentDepartmentComboBox->setCurrentText(qry.value(7).toString());
        }
    }
    else
    {
        qDebug() << "Query failed:" << qry.lastError().text();
    }
}


void HOD::onLoadTableStudentButtonClicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlDatabase db = DatabaseManager::instance().db();
    model->setQuery("SELECT * FROM students", db);

    ui->studentTableView->setModel(model);
}

void HOD::onAddTeacherButtonClicked()
{
    QString teacherName = ui->teacherNameLineEdit->text();
    QString teacherNic = ui->teacherNicLineEdit->text();
    int teacherAge = ui->teacherAgeLineEdit->text().toInt();
    QString department = ui->teacherDepartmentComboBox->currentText();
    QString course = ui->teacherCourseComboBox->currentText();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("INSERT INTO teachers (name, nic, age, department, course)"
                "values(:name, :nic, :age, :department, :course)");

    qry.bindValue(":name", teacherName);
    qry.bindValue(":nic", teacherNic);
    qry.bindValue(":age", teacherAge);
    qry.bindValue(":department", department);
    qry.bindValue(":course", course);

    if (qry.exec())
    {
        qDebug()<<"Teacher saved";
    }
    else
    {
        qDebug() << "Teacher NOT saved";
    }
}

void HOD::onLoadTableTeacherButtonClicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlDatabase db = DatabaseManager::instance().db();
    model->setQuery("SELECT * FROM teachers", db);

    ui->teacherTableView->setModel(model);
}

void HOD::onTeacherTableViewActivated(const QModelIndex &index)
{
    QString val = ui->teacherTableView->model()->data(index).toString();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("SELECT * FROM teachers WHERE id=:val OR name=:val OR nic=:val OR age=:val OR department=:val OR course=:val");
    qry.bindValue(":val", val);

    if (qry.exec())
    {
        while (qry.next())
        {
            ui->teacherIdLineEdit->setText(qry.value(0).toString());
            ui->teacherNameLineEdit->setText(qry.value(1).toString());
            ui->teacherNicLineEdit->setText(qry.value(2).toString());
            ui->teacherAgeLineEdit->setText(qry.value(3).toString());
            ui->teacherDepartmentComboBox->setCurrentText(qry.value(4).toString());
            ui->teacherCourseComboBox->setCurrentText(qry.value(5).toString());
        }
    }
}

void HOD::onClearTeacherButtonClicked()
{
    ui->teacherIdLineEdit->clear();
    ui->teacherNameLineEdit->clear();
    ui->teacherNicLineEdit->clear();
    ui->teacherAgeLineEdit->clear();
    ui->teacherDepartmentComboBox->currentText();
    ui->teacherCourseComboBox->currentText();

}

void HOD::onRemoveTeacherButtonClicked()
{
    int id = ui->removeTeacherLineEdit->text().toInt();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("DELETE FROM teachers WHERE id=:id");
    qry.bindValue(":id", id);

    if (qry.exec())
    {
        qDebug() << "Teacher deleted";
    }
    else
    {
        qDebug() << "Teacher NOT deleted";
    }
}

void HOD::onModifyTeacherButtonClicked()
{
    int teacherId = ui->teacherIdLineEdit->text().toInt();
    QString teacherName=ui->teacherNameLineEdit->text();
    QString teacherNic = ui->teacherNicLineEdit->text();
    int teacherAge = ui->teacherAgeLineEdit->text().toInt();
    QString department = ui->teacherDepartmentComboBox->currentText();
    QString course = ui->teacherCourseComboBox->currentText();

    QSqlDatabase db = DatabaseManager::instance().db();
    QSqlQuery qry(db);
    qry.prepare("UPDATE teachers SET name=:name, nic=:nic, age=:age, department=:department, course=:course WHERE id=:id");
    qry.bindValue(":id", teacherId);
    qry.bindValue(":name", teacherName);
    qry.bindValue(":nic", teacherNic);
    qry.bindValue(":age", teacherAge);
    qry.bindValue(":department", department);
    qry.bindValue(":course", course);

    if (qry.exec())
    {
        qDebug() << "Teacher updated";
    }
    else
    {
        qDebug() << "Teacher NOT updated";
    }
}

void HOD::onDepartmentTeacherComboBoxChanged()
{
    QString department = ui->teacherDepartmentComboBox->currentText();
    ui->teacherCourseComboBox->clear();

    if (department.compare(QString("Computing")) == 0)  // 'compare' returns 0 if the QStrings are equal
    {
        ui->teacherCourseComboBox->addItem("Software Engineering");
        ui->teacherCourseComboBox->addItem("Information Tecnology");
    }
    else
    {
        ui->teacherCourseComboBox->addItem("Management");
        ui->teacherCourseComboBox->addItem("Human Resources");
    }
}

void HOD::setupConnections()
{
    // Students connections
    connect(ui->addStudentButton, &QPushButton::clicked, this, &HOD::onAddStudentButtonClicked);
    connect(ui->modifyStudentButton, &QPushButton::clicked, this, &HOD::onModifyStudentButtonClicked);
    connect(ui->removeStudentButton, &QPushButton::clicked, this, &HOD::onRemoveStudentButtonClicked);
    connect(ui->clearStudentButton, &QPushButton::clicked, this, &HOD::onClearStudentButtonClicked);
    connect(ui->studentDepartmentComboBox, &QComboBox::currentTextChanged, this, &HOD::onDepartmentStudentComboBoxChanged);
    connect(ui->loadTableStudentButton, &QPushButton::clicked, this, &HOD::onLoadTableStudentButtonClicked);
    connect(ui->studentTableView, &QTableView::activated, this, &HOD::onStudentTableViewActivated);

    // Teachers connections
    connect(ui->addTeacherButton, &QPushButton::clicked, this, &HOD::onAddTeacherButtonClicked);
    connect(ui->modifyTeacherButton, &QPushButton::clicked, this, &HOD::onModifyTeacherButtonClicked);
    connect(ui->removeTeacherButton, &QPushButton::clicked, this, &HOD::onRemoveTeacherButtonClicked);
    connect(ui->clearTeacherButton, &QPushButton::clicked, this, &HOD::onClearTeacherButtonClicked);
    connect(ui->teacherDepartmentComboBox, &QComboBox::currentTextChanged, this, &HOD::onDepartmentTeacherComboBoxChanged);
    connect(ui->loadTableTeacherButton, &QPushButton::clicked, this, &HOD::onLoadTableTeacherButtonClicked);
    connect(ui->teacherTableView, &QTableView::activated, this, &HOD::onTeacherTableViewActivated);
}
