#ifndef SQLREQUESTINCONSOLEAPPQT6_PERSON_H
#define SQLREQUESTINCONSOLEAPPQT6_PERSON_H

#include <QString>
#include <QDate>
#include <QRandomGenerator>

class Person {
    QString name;
    QString surname;
    QString patronymic;
    QDate date_of_birth;
    QChar gender;
public:
    Person() = default;

    Person(const QString &name, const QString &surname, const QString &patronymic, const QDate &date_of_birth,
           const QChar &gender)
            : name(name), surname(surname), patronymic(patronymic), date_of_birth(date_of_birth), gender(gender) {}

    Person(const QString &&name, const QString &&surname, const QString &&patronymic, const QDate &&date_of_birth,
           const QChar &gender)
            : name(name), surname(surname), patronymic(patronymic), date_of_birth(date_of_birth), gender(gender) {}



    [[nodiscard]] QString getName() const {
        return name;
    }

    [[nodiscard]] QString getSurname() const {
        return surname;
    }

    [[nodiscard]] QString getPatronymic() const {
        return patronymic;
    }

    [[nodiscard]] QDate getDateOfBirth() const {
        return date_of_birth;
    }

    [[nodiscard]] QChar getGender() const {
        return gender;
    }

    void setName(const QString &_name) {
        this->name = _name;
    }

    void setSurname(const QString &_surname) {
        this->surname = _surname;
    }

    void setPatronymic(const QString &_patronymic) {
        this->patronymic = _patronymic;
    }

    void setDateOfBirth(const QDate &_date_of_birth) {
        this->date_of_birth = _date_of_birth;
    }

    void setGender(const QChar &_gender) {
        this->gender = _gender;
    }
};

class PersonGenerator {
public:
    static Person randomPerson() {
        return {randomName(), randomSurname(), randomPatronymic(), randomDate(), randomGender()};
    }

private:
    PersonGenerator() = default;

    static inline std::mt19937 &generator() {
        static thread_local std::mt19937 gen(std::random_device{}());
        return gen;
    }

    template<typename T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
    static T my_rand(T min, T max) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(generator());
    }

    static QString randomName() {
        const QVector<QString> names = {
                "Alice", "Bob", "Charlie", "David", "Emma",
                "Frank", "Grace", "Henry", "Isabella", "Jack"
        };

        return names[my_rand(qsizetype(0), names.size() - 1)];
    }

    static QString randomSurname() {
        const QVector<QString> surnames = {
                "Smith", "Johnson", "Williams", "Jones", "Brown",
                "Davis", "Miller", "Wilson", "Taylor", "Anderson",
                "Foster", "Ferguson", "Franklin", "Fletcher", "Buffalo",
                "Ruffalo", "Rafferty"
        };

        return surnames[my_rand(qsizetype(0), surnames.size() - 1)];
    }

    static QString randomPatronymic() {
        const QVector<QString> patronymics = {
                "Michaelovich", "Alexandrovna", "Petrovich", "Ivanovna", "Sergeevich",
                "Anatolyevna", "Andreevich", "Vladimirovna", "Nikolaevich", "Dmitrievna"
        };

        return patronymics[my_rand(qsizetype(0), patronymics.size() - 1)];
    }

    static QChar randomGender() {
        const QVector<QChar> genders = {'m', 'w'};

        return genders[my_rand(0, 1)];
    }

    static QDate randomDate() {
        return {my_rand(2000, 2022), my_rand(1, 12), my_rand(1, 25)};
    }
};

namespace {
    bool isEnglishSymbol(QChar ch) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            return true;
        } else {
            return false;
        }
    }

    bool containsOnlyEnglishCharacters(const QString &str) {
        if (std::all_of(str.begin(), str.end(), isEnglishSymbol)) {
            return true;
        }

        return false;
    }
}

#endif //SQLREQUESTINCONSOLEAPPQT6_PERSON_H
