# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yakub/Projects/C++/golf_game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yakub/Projects/C++/golf_game/build

# Include any dependencies generated for this target.
include CMakeFiles/golf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/golf.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/golf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/golf.dir/flags.make

CMakeFiles/golf.dir/src/main.cpp.o: CMakeFiles/golf.dir/flags.make
CMakeFiles/golf.dir/src/main.cpp.o: /home/yakub/Projects/C++/golf_game/src/main.cpp
CMakeFiles/golf.dir/src/main.cpp.o: CMakeFiles/golf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/yakub/Projects/C++/golf_game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/golf.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/golf.dir/src/main.cpp.o -MF CMakeFiles/golf.dir/src/main.cpp.o.d -o CMakeFiles/golf.dir/src/main.cpp.o -c /home/yakub/Projects/C++/golf_game/src/main.cpp

CMakeFiles/golf.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/golf.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yakub/Projects/C++/golf_game/src/main.cpp > CMakeFiles/golf.dir/src/main.cpp.i

CMakeFiles/golf.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/golf.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yakub/Projects/C++/golf_game/src/main.cpp -o CMakeFiles/golf.dir/src/main.cpp.s

# Object files for target golf
golf_OBJECTS = \
"CMakeFiles/golf.dir/src/main.cpp.o"

# External object files for target golf
golf_EXTERNAL_OBJECTS =

golf: CMakeFiles/golf.dir/src/main.cpp.o
golf: CMakeFiles/golf.dir/build.make
golf: _deps/raylib-build/raylib/libraylib.a
golf: /usr/lib/x86_64-linux-gnu/libOpenGL.so
golf: /usr/lib/x86_64-linux-gnu/libGLX.so
golf: /usr/lib/x86_64-linux-gnu/libGLU.so
golf: _deps/raylib-build/raylib/external/glfw/src/libglfw3.a
golf: /usr/lib/x86_64-linux-gnu/librt.a
golf: /usr/lib/x86_64-linux-gnu/libm.so
golf: CMakeFiles/golf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/yakub/Projects/C++/golf_game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable golf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/golf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/golf.dir/build: golf
.PHONY : CMakeFiles/golf.dir/build

CMakeFiles/golf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/golf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/golf.dir/clean

CMakeFiles/golf.dir/depend:
	cd /home/yakub/Projects/C++/golf_game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yakub/Projects/C++/golf_game /home/yakub/Projects/C++/golf_game /home/yakub/Projects/C++/golf_game/build /home/yakub/Projects/C++/golf_game/build /home/yakub/Projects/C++/golf_game/build/CMakeFiles/golf.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/golf.dir/depend
