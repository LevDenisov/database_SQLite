#ifndef SQLREQUESTINCONSOLEAPPQT6_COMMAND_H
#define SQLREQUESTINCONSOLEAPPQT6_COMMAND_H

#include "dataBase.h"

class Command {
protected:
    std::shared_ptr<DataBase> db;
public:
    explicit Command(const std::shared_ptr<DataBase>& db) : db(db) {}
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class CreateTableCmd : public Command {
public:
    explicit CreateTableCmd(const std::shared_ptr<DataBase>& db) : Command(db) {}

    void execute() override {
        db->createTable();
    }
};

class CreateRecordCmd : public Command {
    Person person;
public:
    CreateRecordCmd(const std::shared_ptr<DataBase>& db, const Person& person)
        : Command(db), person(person) {}
    CreateRecordCmd(const std::shared_ptr<DataBase>& db, const Person&& person)
        : Command(db), person(person) {}

    void execute() override {
        db->createRecord(person);
    }
};

class OutputAllRecordCmd : public Command {
public:
    explicit OutputAllRecordCmd(const std::shared_ptr<DataBase>& db) : Command(db) {}

    void execute() override {
        db->outputAllRecord();
    }
};

class AutoFillingRecordCmd : public Command {
public:
    explicit AutoFillingRecordCmd(const std::shared_ptr<DataBase>& db) : Command(db) {}

    void execute() override {
        db->autoFillingRecord();
    }
};

class SelectionTableCmd : public Command {
public:
    explicit SelectionTableCmd(const std::shared_ptr<DataBase>& db) : Command(db) {}

    void execute() override {
        db->selectionTable();
    }
};

class Invoker {
    std::shared_ptr<DataBase> db;
    std::unique_ptr<Command> cmd;

public:
    explicit Invoker(const std::shared_ptr<DataBase>& db) : db(db), cmd(nullptr) {}

    void createTable() {
        cmd = std::make_unique<CreateTableCmd>(db);
        cmd->execute();
    }

    void insertRecord(const Person& person) {
        cmd = std::make_unique<CreateRecordCmd>(db, person);
        cmd->execute();
    }

    void outputRecords() {
        cmd = std::make_unique<OutputAllRecordCmd>(db);
        cmd->execute();
    }

    void autoFilling() {
        cmd = std::make_unique<AutoFillingRecordCmd>(db);
        cmd->execute();
    }

    void selectionTable() {
        cmd = std::make_unique<SelectionTableCmd>(db);
        cmd->execute();
    }
};


#endif //SQLREQUESTINCONSOLEAPPQT6_COMMAND_H
