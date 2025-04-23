cmake_minimum_required(VERSION 3.30)
project(cpp-project)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    main
    src/main.cpp
    )

target_compile_options(main PRIVATE)
