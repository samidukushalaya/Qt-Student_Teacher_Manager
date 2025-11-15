#pragma once

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
        DB.setDatabaseName("C:/Users/hp/Desktop/langages/Qt-Student_Teacher_Manager/Stu.db");

        if(!DB.open()){
            qDebug()<<("failed");
            return false;


        }
        else{
            qDebug()<<("connected...");
            return true;
        }
    }
=======
>>>>>>> 0d13cacfc16f296571096d8d1de77f0e1d1af4ec

public:
    explicit HOD(QWidget *parent = nullptr);
    ~HOD();

private slots:
    // Students slots
    void onAddStudentButtonClicked();
    void onDepartmentStudentComboBoxChanged();
    void onClearStudentButtonClicked();
    void onModifyStudentButtonClicked();
    void onRemoveStudentButtonClicked();
    void onStudentTableViewActivated(const QModelIndex &index);
    void onLoadTableStudentButtonClicked();

    // Teachers slots
    void onAddTeacherButtonClicked();
    void onLoadTableTeacherButtonClicked();
    void onTeacherTableViewActivated(const QModelIndex &index);
    void onClearTeacherButtonClicked();
    void onRemoveTeacherButtonClicked();
    void onModifyTeacherButtonClicked();
    void onDepartmentTeacherComboBoxChanged();

private:
    void setupConnections();
    Ui::HOD *ui;
};
