cmake_minimum_required(VERSION 3.24)
project(sqlRequestInConsoleAppQT6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        REQUIRED)

find_package(Qt6Sql
        REQUIRED)

add_executable(sqlRequestInConsoleAppQT6 main.cpp src/dataBase.cpp src/dataBase.h src/person.cpp src/person.h src/command.cpp src/command.h)
target_link_libraries(sqlRequestInConsoleAppQT6
        Qt::Core Qt6::Sql
        )
add_subdirectory(TEST)

