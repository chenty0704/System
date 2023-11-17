find_package(GTest REQUIRED CONFIG)

add_executable(SystemTest
        JSONTest.cpp)
target_link_libraries(SystemTest PRIVATE
        GTest::gtest_main
        System)
