# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/matt/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/matt/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.126/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matt/Projects/Opera/opera_home/matan/Pass-Pass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pass_pass_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pass_pass_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pass_pass_2.dir/flags.make

CMakeFiles/pass_pass_2.dir/main.c.o: CMakeFiles/pass_pass_2.dir/flags.make
CMakeFiles/pass_pass_2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pass_pass_2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pass_pass_2.dir/main.c.o   -c /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/main.c

CMakeFiles/pass_pass_2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pass_pass_2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/main.c > CMakeFiles/pass_pass_2.dir/main.c.i

CMakeFiles/pass_pass_2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pass_pass_2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/main.c -o CMakeFiles/pass_pass_2.dir/main.c.s

# Object files for target pass_pass_2
pass_pass_2_OBJECTS = \
"CMakeFiles/pass_pass_2.dir/main.c.o"

# External object files for target pass_pass_2
pass_pass_2_EXTERNAL_OBJECTS =

pass_pass_2: CMakeFiles/pass_pass_2.dir/main.c.o
pass_pass_2: CMakeFiles/pass_pass_2.dir/build.make
pass_pass_2: CMakeFiles/pass_pass_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable pass_pass_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pass_pass_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pass_pass_2.dir/build: pass_pass_2

.PHONY : CMakeFiles/pass_pass_2.dir/build

CMakeFiles/pass_pass_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pass_pass_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pass_pass_2.dir/clean

CMakeFiles/pass_pass_2.dir/depend:
	cd /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matt/Projects/Opera/opera_home/matan/Pass-Pass /home/matt/Projects/Opera/opera_home/matan/Pass-Pass /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug /home/matt/Projects/Opera/opera_home/matan/Pass-Pass/cmake-build-debug/CMakeFiles/pass_pass_2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pass_pass_2.dir/depend

