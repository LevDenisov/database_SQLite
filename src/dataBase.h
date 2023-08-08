#ifndef SQLREQUESTINCONSOLEAPPQT6_DATABASE_H
#define SQLREQUESTINCONSOLEAPPQT6_DATABASE_H


#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

#include "person.h"

class DataBase {
    std::unique_ptr<QSqlDatabase> db;

    void bulkInsertRecords(const QVector<Person> &people);

public:
    explicit DataBase(const QString &name);

    ~DataBase();

    void createTable();

    void createRecord(const Person &person);

    std::unique_ptr<QSqlQuery> outputAllRecord();

    void autoFillingRecord();

    std::unique_ptr<QSqlQuery> selectionTable();

    std::unique_ptr<QSqlQuery> optimizationSelectionTable();

    static uint calculateAge(const QVariant &_dateOfBirth);
};

void printUniqueRecord(std::unique_ptr<QSqlQuery> query);

void printRecords(std::unique_ptr<QSqlQuery> query);

#endif //SQLREQUESTINCONSOLEAPPQT6_DATABASE_H
