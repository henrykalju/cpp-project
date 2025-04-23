cmake_minimum_required(VERSION 3.30)
project(cpp-project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
    main
    src/main.cpp
    )

target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
