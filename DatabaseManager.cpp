#include "DatabaseManager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager mgr;
    return mgr;
}

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open(const QString& path)
{
    if (m_db.isOpen())
    {
        return true;
    }

    // Create default connection only once
    if (!QSqlDatabase::contains("main"))
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "main");
    }
    else
    {
        m_db = QSqlDatabase::database("main");
    }

    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "Database opened:" << path;
    return true;
}

void DatabaseManager::close()
{
    if (!m_db.isValid())
    {
        return;
    }

    if (m_db.isOpen())
    {
        m_db.close();
    }

    QSqlDatabase::removeDatabase("main");
    qDebug() << "Database closed";
}

bool DatabaseManager::initialize()
{
    QSqlQuery query(m_db);

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            nic TEXT NOT NULL,
            age INT,
            birthdate TEXT,
            email TEXT,
            department TEXT NOT NULL,
            course TEXT NOT NULL
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS teachers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            nic TEXT NOT NULL,
            age INT,
            department TEXT NOT NULL,
            course TEXT NOT NULL
        )
    )");

    return true;
}


QSqlDatabase DatabaseManager::db() const
{
    return m_db;
}
