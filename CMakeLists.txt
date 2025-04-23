cmake_minimum_required(VERSION 3.30)
project(cpp-project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    main
    src/main.cpp
    )

target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
