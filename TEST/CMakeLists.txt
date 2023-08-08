add_executable(TEST_TEST TEST.cpp ../src/dataBase.cpp ../src/dataBase.h)
target_compile_features(TEST_TEST PRIVATE cxx_std_17)
target_link_libraries(TEST_TEST PRIVATE Qt::Core Qt6::Sql)
