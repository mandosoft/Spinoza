include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runTests main_check.cpp)
target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests myco_cv)