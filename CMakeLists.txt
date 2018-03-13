cmake_minimum_required(VERSION 3.5)
project(mdv)

# The version number.
set (MDV_VERSION_MAJOR 1)
set (MDV_VERSION_MINOR 0)

# does this system provide the getline functions?
include (CheckFunctionExists)
check_function_exists (getline HAVE_GETLINE)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/src/MdvConfig.h.in" 
	"${PROJECT_SOURCE_DIR}/src/MdvConfig.h"
	)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
set(SOURCE_FILES 
	src/main.c 
	src/display.c 
	src/display.h 
	src/file.c 
	src/file.h 
	src/fallback.c 
	src/fallback.h 
	src/parser.c 
	src/parser.h 
	src/headers.c 
	src/headers.h 
	src/lists.c 
	src/lists.h 
	src/hr.c 
	src/hr.h 
	src/span.c 
	src/span.h
	)
add_executable(mdv ${SOURCE_FILES})
target_link_libraries(mdv ${CURSES_LIBRARIES})