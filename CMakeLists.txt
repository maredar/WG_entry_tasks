cmake_minimum_required(VERSION 3.14)
project(wg_entry_tasks)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES 
        main.cpp 
        src/first_task/is_even.hpp 
        src/second_task/cyclic_buffer_array.hpp
        src/second_task/cyclic_buffer_list.hpp
        src/third_task/merge_sort.hpp)

add_executable(wg_entry_tasks ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(wg_entry_tasks_tests wg_entry_tasks_tests.cpp)
target_link_libraries(wg_entry_tasks_tests gtest_main)
add_test(NAME tests COMMAND wg_entry_tasks_tests)