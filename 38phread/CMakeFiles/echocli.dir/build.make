# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chen/socket_learn/38phread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/socket_learn/38phread

# Include any dependencies generated for this target.
include CMakeFiles/echocli.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echocli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echocli.dir/flags.make

CMakeFiles/echocli.dir/echocli.cpp.o: CMakeFiles/echocli.dir/flags.make
CMakeFiles/echocli.dir/echocli.cpp.o: echocli.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chen/socket_learn/38phread/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/echocli.dir/echocli.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echocli.dir/echocli.cpp.o -c /home/chen/socket_learn/38phread/echocli.cpp

CMakeFiles/echocli.dir/echocli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echocli.dir/echocli.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chen/socket_learn/38phread/echocli.cpp > CMakeFiles/echocli.dir/echocli.cpp.i

CMakeFiles/echocli.dir/echocli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echocli.dir/echocli.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chen/socket_learn/38phread/echocli.cpp -o CMakeFiles/echocli.dir/echocli.cpp.s

CMakeFiles/echocli.dir/echocli.cpp.o.requires:
.PHONY : CMakeFiles/echocli.dir/echocli.cpp.o.requires

CMakeFiles/echocli.dir/echocli.cpp.o.provides: CMakeFiles/echocli.dir/echocli.cpp.o.requires
	$(MAKE) -f CMakeFiles/echocli.dir/build.make CMakeFiles/echocli.dir/echocli.cpp.o.provides.build
.PHONY : CMakeFiles/echocli.dir/echocli.cpp.o.provides

CMakeFiles/echocli.dir/echocli.cpp.o.provides.build: CMakeFiles/echocli.dir/echocli.cpp.o

# Object files for target echocli
echocli_OBJECTS = \
"CMakeFiles/echocli.dir/echocli.cpp.o"

# External object files for target echocli
echocli_EXTERNAL_OBJECTS =

echocli: CMakeFiles/echocli.dir/echocli.cpp.o
echocli: CMakeFiles/echocli.dir/build.make
echocli: CMakeFiles/echocli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable echocli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echocli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echocli.dir/build: echocli
.PHONY : CMakeFiles/echocli.dir/build

CMakeFiles/echocli.dir/requires: CMakeFiles/echocli.dir/echocli.cpp.o.requires
.PHONY : CMakeFiles/echocli.dir/requires

CMakeFiles/echocli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echocli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echocli.dir/clean

CMakeFiles/echocli.dir/depend:
	cd /home/chen/socket_learn/38phread && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/socket_learn/38phread /home/chen/socket_learn/38phread /home/chen/socket_learn/38phread /home/chen/socket_learn/38phread /home/chen/socket_learn/38phread/CMakeFiles/echocli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echocli.dir/depend

