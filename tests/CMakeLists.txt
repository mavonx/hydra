enable_testing()

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES "*.cpp")

add_executable(hydra_tests ${TEST_SOURCES})
target_link_libraries(hydra_tests PRIVATE hydra_core GTest::gtest_main)

gtest_discover_tests(hydra_tests)
