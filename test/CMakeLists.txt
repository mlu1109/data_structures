include_directories(${gtest_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR})
set(test_sources main_test.cpp avl_test.cpp helper.cpp helper.hpp)
add_executable(data_structures_tests ${test_sources})
target_link_libraries(data_structures_tests gtest)