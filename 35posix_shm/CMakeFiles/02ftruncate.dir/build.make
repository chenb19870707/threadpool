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
CMAKE_SOURCE_DIR = /home/chen/socket_learn/35posix_shm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/socket_learn/35posix_shm

# Include any dependencies generated for this target.
include CMakeFiles/02ftruncate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/02ftruncate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02ftruncate.dir/flags.make

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o: CMakeFiles/02ftruncate.dir/flags.make
CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o: 02ftruncate.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chen/socket_learn/35posix_shm/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o -c /home/chen/socket_learn/35posix_shm/02ftruncate.cpp

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02ftruncate.dir/02ftruncate.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chen/socket_learn/35posix_shm/02ftruncate.cpp > CMakeFiles/02ftruncate.dir/02ftruncate.cpp.i

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02ftruncate.dir/02ftruncate.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chen/socket_learn/35posix_shm/02ftruncate.cpp -o CMakeFiles/02ftruncate.dir/02ftruncate.cpp.s

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.requires:
.PHONY : CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.requires

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.provides: CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.requires
	$(MAKE) -f CMakeFiles/02ftruncate.dir/build.make CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.provides.build
.PHONY : CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.provides

CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.provides.build: CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o

# Object files for target 02ftruncate
02ftruncate_OBJECTS = \
"CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o"

# External object files for target 02ftruncate
02ftruncate_EXTERNAL_OBJECTS =

02ftruncate: CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o
02ftruncate: CMakeFiles/02ftruncate.dir/build.make
02ftruncate: CMakeFiles/02ftruncate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable 02ftruncate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/02ftruncate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02ftruncate.dir/build: 02ftruncate
.PHONY : CMakeFiles/02ftruncate.dir/build

CMakeFiles/02ftruncate.dir/requires: CMakeFiles/02ftruncate.dir/02ftruncate.cpp.o.requires
.PHONY : CMakeFiles/02ftruncate.dir/requires

CMakeFiles/02ftruncate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/02ftruncate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/02ftruncate.dir/clean

CMakeFiles/02ftruncate.dir/depend:
	cd /home/chen/socket_learn/35posix_shm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/socket_learn/35posix_shm /home/chen/socket_learn/35posix_shm /home/chen/socket_learn/35posix_shm /home/chen/socket_learn/35posix_shm /home/chen/socket_learn/35posix_shm/CMakeFiles/02ftruncate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02ftruncate.dir/depend
