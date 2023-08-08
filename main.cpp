#include <QCoreApplication>
#include <QDebug>

#include <functional>

#include "src/command.h"

double functionExecutionTime(const std::function<void()>& f) {
    auto                  start_time      = std::chrono::steady_clock::now();
    auto                   end_time       = std::chrono::steady_clock::now();

    auto                    time            = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end_time - start_time).count();

    const uint N_RUNS = 10;

    QVector<double> test_duration(N_RUNS);

    for (uint t = 0; t < N_RUNS; t++) {
        time = 0;

        start_time = std::chrono::steady_clock::now();
        f();
        end_time = std::chrono::steady_clock::now();

        time += std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end_time - start_time).count();
        test_duration[t] = time;
    }

    return std::accumulate(test_duration.begin(), test_duration.end(), 0.0) / N_RUNS;
}

void processCommand(const QString& input, Invoker& inv) {
    QStringList parameters = input.split(' ', Qt::SkipEmptyParts);

    QString nameTable;
    bool ok;
    int command;

    if (parameters.size() < 2) {
        return;
    }

    nameTable = parameters.at(1);
    command = parameters.at(1).toInt(&ok);

    if (!ok) {
        QTextStream(stdout) << "This command does not exist\n";
    }

    switch (command) {
        case 1: {
            if (parameters.size() != 2) {
                QTextStream(stdout) << "Invalid number of arguments\n";
                return;
            }

            inv.createTable();
            break;
        }

        case 2: {
            if (parameters.size() != 7) {
                QTextStream(stdout) << "Invalid number of arguments\n";
                return;
            }

            Person person;

            if (containsOnlyEnglishCharacters(parameters.at(2))) {
                person.setName(parameters.at(2));
            } else {
                QTextStream(stdout) << "There are incorrect characters in the name\n";
                return;
            }

            if (containsOnlyEnglishCharacters(parameters.at(3))) {
                person.setSurname(parameters.at(3));
            } else {
                QTextStream(stdout) << "There are incorrect characters in the surname\n";
                return;
            }

            if (containsOnlyEnglishCharacters(parameters.at(4))) {
                person.setPatronymic(parameters.at(4));
            } else {
                QTextStream(stdout) << "There are incorrect characters in the patronymic\n";
                return;
            }

            QDate date = QDate::fromString(parameters.at(5),"dd/MM/yyyy");

            if (date.isValid()) {
                person.setDateOfBirth(date);
            } else {
                QTextStream(stdout) << "Incorrect date entered\n";
                return;
            }

            if (parameters.at(6).size() == 1 && (parameters.at(6)[0] == 'm' || parameters.at(6)[0] == 'w')) {
                person.setGender(parameters.at(6)[0]);
            } else {
                QTextStream(stdout) << "Incorrect gender of a person has been introduced\n";
                return;
            }

            inv.insertRecord(person);
            break;
        }

        case 3: {
            inv.outputRecords();
            break;
        }

        case 4: {
            inv.autoFilling();
            break;
        }

        case 5: {
            inv.selectionTable();
            break;
        }

        default: {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QString input;
    std::shared_ptr<DataBase> db(std::make_unique<DataBase>("myDB"));
    Invoker inv(db);

    while (input != "q") {
        QTextStream(stdout) << "> ";
        input = QTextStream(stdin).readLine();

        processCommand(input, inv);
    }

    return 0;
}
