# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/padi/clion-2016.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/padi/clion-2016.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/padi/ClionProjects/mdv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/padi/ClionProjects/mdv/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mdv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mdv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mdv.dir/flags.make

CMakeFiles/mdv.dir/src/main.c.o: CMakeFiles/mdv.dir/flags.make
CMakeFiles/mdv.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mdv.dir/src/main.c.o"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mdv.dir/src/main.c.o   -c /home/padi/ClionProjects/mdv/src/main.c

CMakeFiles/mdv.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mdv.dir/src/main.c.i"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/padi/ClionProjects/mdv/src/main.c > CMakeFiles/mdv.dir/src/main.c.i

CMakeFiles/mdv.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mdv.dir/src/main.c.s"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/padi/ClionProjects/mdv/src/main.c -o CMakeFiles/mdv.dir/src/main.c.s

CMakeFiles/mdv.dir/src/main.c.o.requires:

.PHONY : CMakeFiles/mdv.dir/src/main.c.o.requires

CMakeFiles/mdv.dir/src/main.c.o.provides: CMakeFiles/mdv.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/mdv.dir/build.make CMakeFiles/mdv.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/mdv.dir/src/main.c.o.provides

CMakeFiles/mdv.dir/src/main.c.o.provides.build: CMakeFiles/mdv.dir/src/main.c.o


CMakeFiles/mdv.dir/src/display.c.o: CMakeFiles/mdv.dir/flags.make
CMakeFiles/mdv.dir/src/display.c.o: ../src/display.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mdv.dir/src/display.c.o"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mdv.dir/src/display.c.o   -c /home/padi/ClionProjects/mdv/src/display.c

CMakeFiles/mdv.dir/src/display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mdv.dir/src/display.c.i"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/padi/ClionProjects/mdv/src/display.c > CMakeFiles/mdv.dir/src/display.c.i

CMakeFiles/mdv.dir/src/display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mdv.dir/src/display.c.s"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/padi/ClionProjects/mdv/src/display.c -o CMakeFiles/mdv.dir/src/display.c.s

CMakeFiles/mdv.dir/src/display.c.o.requires:

.PHONY : CMakeFiles/mdv.dir/src/display.c.o.requires

CMakeFiles/mdv.dir/src/display.c.o.provides: CMakeFiles/mdv.dir/src/display.c.o.requires
	$(MAKE) -f CMakeFiles/mdv.dir/build.make CMakeFiles/mdv.dir/src/display.c.o.provides.build
.PHONY : CMakeFiles/mdv.dir/src/display.c.o.provides

CMakeFiles/mdv.dir/src/display.c.o.provides.build: CMakeFiles/mdv.dir/src/display.c.o


CMakeFiles/mdv.dir/src/file.c.o: CMakeFiles/mdv.dir/flags.make
CMakeFiles/mdv.dir/src/file.c.o: ../src/file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/mdv.dir/src/file.c.o"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mdv.dir/src/file.c.o   -c /home/padi/ClionProjects/mdv/src/file.c

CMakeFiles/mdv.dir/src/file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mdv.dir/src/file.c.i"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/padi/ClionProjects/mdv/src/file.c > CMakeFiles/mdv.dir/src/file.c.i

CMakeFiles/mdv.dir/src/file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mdv.dir/src/file.c.s"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/padi/ClionProjects/mdv/src/file.c -o CMakeFiles/mdv.dir/src/file.c.s

CMakeFiles/mdv.dir/src/file.c.o.requires:

.PHONY : CMakeFiles/mdv.dir/src/file.c.o.requires

CMakeFiles/mdv.dir/src/file.c.o.provides: CMakeFiles/mdv.dir/src/file.c.o.requires
	$(MAKE) -f CMakeFiles/mdv.dir/build.make CMakeFiles/mdv.dir/src/file.c.o.provides.build
.PHONY : CMakeFiles/mdv.dir/src/file.c.o.provides

CMakeFiles/mdv.dir/src/file.c.o.provides.build: CMakeFiles/mdv.dir/src/file.c.o


CMakeFiles/mdv.dir/src/fallback.c.o: CMakeFiles/mdv.dir/flags.make
CMakeFiles/mdv.dir/src/fallback.c.o: ../src/fallback.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/mdv.dir/src/fallback.c.o"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mdv.dir/src/fallback.c.o   -c /home/padi/ClionProjects/mdv/src/fallback.c

CMakeFiles/mdv.dir/src/fallback.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mdv.dir/src/fallback.c.i"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/padi/ClionProjects/mdv/src/fallback.c > CMakeFiles/mdv.dir/src/fallback.c.i

CMakeFiles/mdv.dir/src/fallback.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mdv.dir/src/fallback.c.s"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/padi/ClionProjects/mdv/src/fallback.c -o CMakeFiles/mdv.dir/src/fallback.c.s

CMakeFiles/mdv.dir/src/fallback.c.o.requires:

.PHONY : CMakeFiles/mdv.dir/src/fallback.c.o.requires

CMakeFiles/mdv.dir/src/fallback.c.o.provides: CMakeFiles/mdv.dir/src/fallback.c.o.requires
	$(MAKE) -f CMakeFiles/mdv.dir/build.make CMakeFiles/mdv.dir/src/fallback.c.o.provides.build
.PHONY : CMakeFiles/mdv.dir/src/fallback.c.o.provides

CMakeFiles/mdv.dir/src/fallback.c.o.provides.build: CMakeFiles/mdv.dir/src/fallback.c.o


CMakeFiles/mdv.dir/src/parser.c.o: CMakeFiles/mdv.dir/flags.make
CMakeFiles/mdv.dir/src/parser.c.o: ../src/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/mdv.dir/src/parser.c.o"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mdv.dir/src/parser.c.o   -c /home/padi/ClionProjects/mdv/src/parser.c

CMakeFiles/mdv.dir/src/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mdv.dir/src/parser.c.i"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/padi/ClionProjects/mdv/src/parser.c > CMakeFiles/mdv.dir/src/parser.c.i

CMakeFiles/mdv.dir/src/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mdv.dir/src/parser.c.s"
	/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/padi/ClionProjects/mdv/src/parser.c -o CMakeFiles/mdv.dir/src/parser.c.s

CMakeFiles/mdv.dir/src/parser.c.o.requires:

.PHONY : CMakeFiles/mdv.dir/src/parser.c.o.requires

CMakeFiles/mdv.dir/src/parser.c.o.provides: CMakeFiles/mdv.dir/src/parser.c.o.requires
	$(MAKE) -f CMakeFiles/mdv.dir/build.make CMakeFiles/mdv.dir/src/parser.c.o.provides.build
.PHONY : CMakeFiles/mdv.dir/src/parser.c.o.provides

CMakeFiles/mdv.dir/src/parser.c.o.provides.build: CMakeFiles/mdv.dir/src/parser.c.o


# Object files for target mdv
mdv_OBJECTS = \
"CMakeFiles/mdv.dir/src/main.c.o" \
"CMakeFiles/mdv.dir/src/display.c.o" \
"CMakeFiles/mdv.dir/src/file.c.o" \
"CMakeFiles/mdv.dir/src/fallback.c.o" \
"CMakeFiles/mdv.dir/src/parser.c.o"

# External object files for target mdv
mdv_EXTERNAL_OBJECTS =

mdv: CMakeFiles/mdv.dir/src/main.c.o
mdv: CMakeFiles/mdv.dir/src/display.c.o
mdv: CMakeFiles/mdv.dir/src/file.c.o
mdv: CMakeFiles/mdv.dir/src/fallback.c.o
mdv: CMakeFiles/mdv.dir/src/parser.c.o
mdv: CMakeFiles/mdv.dir/build.make
mdv: /usr/lib64/libcurses.so
mdv: /usr/lib64/libform.so
mdv: CMakeFiles/mdv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable mdv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mdv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mdv.dir/build: mdv

.PHONY : CMakeFiles/mdv.dir/build

CMakeFiles/mdv.dir/requires: CMakeFiles/mdv.dir/src/main.c.o.requires
CMakeFiles/mdv.dir/requires: CMakeFiles/mdv.dir/src/display.c.o.requires
CMakeFiles/mdv.dir/requires: CMakeFiles/mdv.dir/src/file.c.o.requires
CMakeFiles/mdv.dir/requires: CMakeFiles/mdv.dir/src/fallback.c.o.requires
CMakeFiles/mdv.dir/requires: CMakeFiles/mdv.dir/src/parser.c.o.requires

.PHONY : CMakeFiles/mdv.dir/requires

CMakeFiles/mdv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mdv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mdv.dir/clean

CMakeFiles/mdv.dir/depend:
	cd /home/padi/ClionProjects/mdv/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/padi/ClionProjects/mdv /home/padi/ClionProjects/mdv /home/padi/ClionProjects/mdv/cmake-build-debug /home/padi/ClionProjects/mdv/cmake-build-debug /home/padi/ClionProjects/mdv/cmake-build-debug/CMakeFiles/mdv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mdv.dir/depend

