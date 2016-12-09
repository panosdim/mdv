cmake_minimum_required(VERSION 3.5)
project(mdp)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOURCE_FILES src/main.c src/display.c src/display.h src/file.c src/file.h src/getline.c src/getline.h src/parser.c src/parser.h)
add_executable(mdp ${SOURCE_FILES})
target_link_libraries(mdp ${CURSES_LIBRARIES})