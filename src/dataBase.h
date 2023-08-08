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

    uint calculateAge(const QVariant &_dateOfBirth);

public:
    explicit DataBase(const QString &name);

    ~DataBase();

    void createTable();

    void createRecord(const Person &person);

    void outputAllRecord();

    void autoFillingRecord();

    void selectionTable();

    void optimizationSelectionTable();
};


#endif //SQLREQUESTINCONSOLEAPPQT6_DATABASE_H
