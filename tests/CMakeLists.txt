add_executable(SystemTest
        "JSONTest.cpp"
        "MacrosTest.cpp"
        "MathTest.cpp")
target_link_libraries(SystemTest PRIVATE
        GTest::gtest_main
        System)
