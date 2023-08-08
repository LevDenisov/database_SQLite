#include <QCoreApplication>
#include <QDebug>
#include "../src/dataBase.h"


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

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    std::shared_ptr<DataBase> db(std::make_unique<DataBase>("myDB"));

    db->optimizationSelectionTable();

    return 0;
}
