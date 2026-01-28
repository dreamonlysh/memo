include(${CMAKE_SOURCE_DIR}/cmake/fetch_content_googletest.cmake)

add_executable(trial_gtest googletest.cpp)

target_link_libraries(trial_gtest PRIVATE GTest::gtest_main)

# auto find gtest in trial_gtest
gtest_discover_tests(trial_gtest)
