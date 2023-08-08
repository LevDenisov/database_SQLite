#include "dataBase.h"

DataBase::DataBase(const QString& name) {
    db = std::make_unique<QSqlDatabase>(QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", name)));
    db->setDatabaseName("./" + name + ".sqlite");
    db->open();
}

DataBase::~DataBase() {
    if (db != nullptr && db->open()) {
        db->close();
    }
}

void DataBase::createTable() {
    QSqlQuery query(*db);

    query.prepare("CREATE TABLE People("
                        "  first_name VARCHAR(100),"
                        "  last_name VARCHAR(100),"
                        "  patronymic VARCHAR(100),"
                        "  date_of_birth DATE,"
                        "  gender CHAR"
                        "  )");

    bool ok = query.exec();

    if (!ok) {
        QTextStream(stdout) << query.lastError().text() << '\n';
    }
}

void DataBase::createRecord(const Person &person) {
    QSqlQuery query("INSERT INTO People(first_name, last_name, patronymic, date_of_birth, gender) "
                  "VALUES (?, ?, ?, ?, ?)", *db);

    query.bindValue(0, person.getName());
    query.bindValue(1, person.getSurname());
    query.bindValue(2, person.getPatronymic());
    query.bindValue(3, person.getDateOfBirth());
    query.bindValue(4, person.getGender());

    bool ok = query.exec();

    if (!ok) {
        QTextStream(stdout) << query.lastError().text() << '\n';
    }
} // myApp 2 Petr Vasiliy Ivanovich 12/12/2002 w

void DataBase::outputAllRecord() {
    QSqlQuery query("SELECT \n"
                    "    last_name,\n"
                    "    first_name,\n"
                    "    patronymic,\n"
                    "    date_of_birth,\n"
                    "    gender\n"
                    "FROM\n"
                    "    People\n"
                    "GROUP BY\n"
                    "\tlast_name,\n"
                    "    first_name,\n"
                    "    patronymic,\n"
                    "    date_of_birth\n"
                    "ORDER BY\n"
                    "    last_name,\n"
                    "    first_name,\n"
                    "    patronymic", *db);

    if (!query.isActive()) {
        QTextStream(stdout) << query.lastError().text() << '\n';
        return;
    }

    while (query.next()) {
        QTextStream(stdout) << query.value(0).toString() << ' '
            << query.value(1).toString() << ' '
            << query.value(2).toString() << ' '
            << query.value(3).toString() << ' '
            << query.value(4).toString() << ' '
            << calculateAge(query.value(3)) << '\n';
    }
}

uint DataBase::calculateAge(const QVariant& _dateOfBirth) {
    QDate currentDate = QDate::currentDate();
    QDate dateOfBirth = _dateOfBirth.toDate();
    uint age = currentDate.year() - dateOfBirth.year();

    if (currentDate.month() < dateOfBirth.month() ||
        (currentDate.month() == dateOfBirth.month() && currentDate.day() < dateOfBirth.day())) {
        age--;
    }

    return age;
}

void DataBase::bulkInsertRecords(const QVector<Person>& people) {
    if (people.isEmpty())
        return;

    db->transaction();

    QSqlQuery query(*db);

    query.prepare("INSERT INTO People(first_name, last_name, patronymic, date_of_birth, gender) "
                  "VALUES (?, ?, ?, ?, ?)");

    QVariantList names;
    QVariantList surnames;
    QVariantList patronymics;
    QVariantList dates;
    QVariantList genders;

    for (const auto& person: people) {
        names << person.getName();
        surnames << person.getSurname();
        patronymics << person.getPatronymic();
        dates << person.getDateOfBirth();
        genders << person.getGender();
    }

    query.addBindValue(names);
    query.addBindValue(surnames);
    query.addBindValue(patronymics);
    query.addBindValue(dates);
    query.addBindValue(genders);

    if (!query.execBatch()) {
        QTextStream(stdout) << query.lastError().text() << '\n';
        db->rollback();
        return;
    }

    db->commit();
}

void DataBase::autoFillingRecord() {
    QVector<Person> people;
    const uint sizePeople = 1000000;

    people.reserve(sizePeople);

    for (uint i = 0; i < sizePeople; i++) {
        people.push_back(PersonGenerator::randomPerson());
    }

    bulkInsertRecords(people);
}

void DataBase::selectionTable() {
    QSqlQuery query("SELECT * FROM People WHERE gender = 'm' AND first_name LIKE 'F%'", *db);

    if (!query.isActive()) {
        QTextStream(stdout) << query.lastError().text() << '\n';
        return;
    }

    while (query.next()) {
        QTextStream(stdout) << query.value(0).toString() << ' '
                            << query.value(1).toString() << ' '
                            << query.value(2).toString() << ' '
                            << query.value(3).toString() << ' '
                            << query.value(4).toString() << '\n';
    }
}

void DataBase::optimizationSelectionTable() {
    QSqlQuery createIndexQuery(*db);
    createIndexQuery.exec("CREATE INDEX idx_gender ON People (gender)");
    createIndexQuery.exec("CREATE INDEX idx_first_name ON People (first_name)");

    QSqlQuery query("SELECT * FROM People WHERE gender = 'm' AND first_name LIKE 'F%'", *db);

    if (!query.isActive()) {
        QTextStream(stdout) << query.lastError().text() << '\n';
        return;
    }

    while (query.next()) {
        QTextStream(stdout) << query.value(0).toString() << ' '
                            << query.value(1).toString() << ' '
                            << query.value(2).toString() << ' '
                            << query.value(3).toString() << ' '
                            << query.value(4).toString() << '\n';
    }

}