project(test)

add_subdirectory(MS_Test)


add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_test
        ${MS_TEST_SOURCE_FILES}
        )

target_link_libraries(run_test gtest gtest_main)