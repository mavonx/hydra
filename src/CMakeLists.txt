FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v7.0.3
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE CORE_SOURCES "*.cpp")
set(MAIN_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
list(REMOVE_ITEM CORE_SOURCES "${MAIN_SOURCE}")

add_library(hydra_core ${CORE_SOURCES})
target_include_directories(hydra_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(hydra_core PRIVATE ftxui::ftxui)

add_executable(hydra main.cpp)
target_link_libraries(hydra PRIVATE hydra_core)
