add_executable(SystemTest
        JSONTest.cpp
        MDArrayTest.cpp)
target_link_libraries(SystemTest PRIVATE
        GTest::gtest_main
        System)
