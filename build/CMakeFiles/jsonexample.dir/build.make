# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build

# Include any dependencies generated for this target.
include CMakeFiles/jsonexample.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/jsonexample.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/jsonexample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsonexample.dir/flags.make

CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o: CMakeFiles/jsonexample.dir/flags.make
CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o: ../examples/jsonExample.cpp
CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o: CMakeFiles/jsonexample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o -MF CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o.d -o CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o -c /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/examples/jsonExample.cpp

CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/examples/jsonExample.cpp > CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.i

CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/examples/jsonExample.cpp -o CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.s

# Object files for target jsonexample
jsonexample_OBJECTS = \
"CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o"

# External object files for target jsonexample
jsonexample_EXTERNAL_OBJECTS =

jsonexample: CMakeFiles/jsonexample.dir/examples/jsonExample.cpp.o
jsonexample: CMakeFiles/jsonexample.dir/build.make
jsonexample: CMakeFiles/jsonexample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jsonexample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsonexample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsonexample.dir/build: jsonexample
.PHONY : CMakeFiles/jsonexample.dir/build

CMakeFiles/jsonexample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jsonexample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jsonexample.dir/clean

CMakeFiles/jsonexample.dir/depend:
	cd /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build /Users/mariasliacka/computer_graphics/cw2/raytracer_A2_CG2021/RayTracer/build/CMakeFiles/jsonexample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsonexample.dir/depend
