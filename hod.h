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
