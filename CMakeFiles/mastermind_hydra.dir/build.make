# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /theia/home/apps/CO7/skylake/software/CMake/3.15.3-GCCcore-8.3.0/bin/cmake

# The command to remove a file.
RM = /theia/home/apps/CO7/skylake/software/CMake/3.15.3-GCCcore-8.3.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /sulb0/rcostari/rtos_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /sulb0/rcostari/rtos_2

# Include any dependencies generated for this target.
include CMakeFiles/mastermind_hydra.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mastermind_hydra.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mastermind_hydra.dir/flags.make

CMakeFiles/mastermind_hydra.dir/main.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mastermind_hydra.dir/main.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/main.cpp.o -c /sulb0/rcostari/rtos_2/main.cpp

CMakeFiles/mastermind_hydra.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/main.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/main.cpp > CMakeFiles/mastermind_hydra.dir/main.cpp.i

CMakeFiles/mastermind_hydra.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/main.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/main.cpp -o CMakeFiles/mastermind_hydra.dir/main.cpp.s

CMakeFiles/mastermind_hydra.dir/Guess.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Guess.cpp.o: Guess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mastermind_hydra.dir/Guess.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Guess.cpp.o -c /sulb0/rcostari/rtos_2/Guess.cpp

CMakeFiles/mastermind_hydra.dir/Guess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Guess.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Guess.cpp > CMakeFiles/mastermind_hydra.dir/Guess.cpp.i

CMakeFiles/mastermind_hydra.dir/Guess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Guess.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Guess.cpp -o CMakeFiles/mastermind_hydra.dir/Guess.cpp.s

CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o: Challenger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o -c /sulb0/rcostari/rtos_2/Challenger.cpp

CMakeFiles/mastermind_hydra.dir/Challenger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Challenger.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Challenger.cpp > CMakeFiles/mastermind_hydra.dir/Challenger.cpp.i

CMakeFiles/mastermind_hydra.dir/Challenger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Challenger.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Challenger.cpp -o CMakeFiles/mastermind_hydra.dir/Challenger.cpp.s

CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o: Gamemaster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o -c /sulb0/rcostari/rtos_2/Gamemaster.cpp

CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Gamemaster.cpp > CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.i

CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Gamemaster.cpp -o CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.s

CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o: Evaluation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o -c /sulb0/rcostari/rtos_2/Evaluation.cpp

CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Evaluation.cpp > CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.i

CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Evaluation.cpp -o CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.s

CMakeFiles/mastermind_hydra.dir/Utils.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Utils.cpp.o: Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mastermind_hydra.dir/Utils.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Utils.cpp.o -c /sulb0/rcostari/rtos_2/Utils.cpp

CMakeFiles/mastermind_hydra.dir/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Utils.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Utils.cpp > CMakeFiles/mastermind_hydra.dir/Utils.cpp.i

CMakeFiles/mastermind_hydra.dir/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Utils.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Utils.cpp -o CMakeFiles/mastermind_hydra.dir/Utils.cpp.s

CMakeFiles/mastermind_hydra.dir/Range.cpp.o: CMakeFiles/mastermind_hydra.dir/flags.make
CMakeFiles/mastermind_hydra.dir/Range.cpp.o: Range.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mastermind_hydra.dir/Range.cpp.o"
	mpiCC  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mastermind_hydra.dir/Range.cpp.o -c /sulb0/rcostari/rtos_2/Range.cpp

CMakeFiles/mastermind_hydra.dir/Range.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mastermind_hydra.dir/Range.cpp.i"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /sulb0/rcostari/rtos_2/Range.cpp > CMakeFiles/mastermind_hydra.dir/Range.cpp.i

CMakeFiles/mastermind_hydra.dir/Range.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mastermind_hydra.dir/Range.cpp.s"
	mpiCC $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /sulb0/rcostari/rtos_2/Range.cpp -o CMakeFiles/mastermind_hydra.dir/Range.cpp.s

# Object files for target mastermind_hydra
mastermind_hydra_OBJECTS = \
"CMakeFiles/mastermind_hydra.dir/main.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Guess.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Utils.cpp.o" \
"CMakeFiles/mastermind_hydra.dir/Range.cpp.o"

# External object files for target mastermind_hydra
mastermind_hydra_EXTERNAL_OBJECTS =

mastermind_hydra: CMakeFiles/mastermind_hydra.dir/main.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Guess.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Challenger.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Gamemaster.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Evaluation.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Utils.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/Range.cpp.o
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/build.make
mastermind_hydra: CMakeFiles/mastermind_hydra.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/sulb0/rcostari/rtos_2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable mastermind_hydra"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mastermind_hydra.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mastermind_hydra.dir/build: mastermind_hydra

.PHONY : CMakeFiles/mastermind_hydra.dir/build

CMakeFiles/mastermind_hydra.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mastermind_hydra.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mastermind_hydra.dir/clean

CMakeFiles/mastermind_hydra.dir/depend:
	cd /sulb0/rcostari/rtos_2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /sulb0/rcostari/rtos_2 /sulb0/rcostari/rtos_2 /sulb0/rcostari/rtos_2 /sulb0/rcostari/rtos_2 /sulb0/rcostari/rtos_2/CMakeFiles/mastermind_hydra.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mastermind_hydra.dir/depend
