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
CMAKE_SOURCE_DIR = /home/chen/socket_learn/18epoll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/socket_learn/18epoll

# Include any dependencies generated for this target.
include CMakeFiles/epollsvr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/epollsvr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/epollsvr.dir/flags.make

CMakeFiles/epollsvr.dir/epollsvr.cpp.o: CMakeFiles/epollsvr.dir/flags.make
CMakeFiles/epollsvr.dir/epollsvr.cpp.o: epollsvr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chen/socket_learn/18epoll/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/epollsvr.dir/epollsvr.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/epollsvr.dir/epollsvr.cpp.o -c /home/chen/socket_learn/18epoll/epollsvr.cpp

CMakeFiles/epollsvr.dir/epollsvr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/epollsvr.dir/epollsvr.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chen/socket_learn/18epoll/epollsvr.cpp > CMakeFiles/epollsvr.dir/epollsvr.cpp.i

CMakeFiles/epollsvr.dir/epollsvr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/epollsvr.dir/epollsvr.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chen/socket_learn/18epoll/epollsvr.cpp -o CMakeFiles/epollsvr.dir/epollsvr.cpp.s

CMakeFiles/epollsvr.dir/epollsvr.cpp.o.requires:
.PHONY : CMakeFiles/epollsvr.dir/epollsvr.cpp.o.requires

CMakeFiles/epollsvr.dir/epollsvr.cpp.o.provides: CMakeFiles/epollsvr.dir/epollsvr.cpp.o.requires
	$(MAKE) -f CMakeFiles/epollsvr.dir/build.make CMakeFiles/epollsvr.dir/epollsvr.cpp.o.provides.build
.PHONY : CMakeFiles/epollsvr.dir/epollsvr.cpp.o.provides

CMakeFiles/epollsvr.dir/epollsvr.cpp.o.provides.build: CMakeFiles/epollsvr.dir/epollsvr.cpp.o

# Object files for target epollsvr
epollsvr_OBJECTS = \
"CMakeFiles/epollsvr.dir/epollsvr.cpp.o"

# External object files for target epollsvr
epollsvr_EXTERNAL_OBJECTS =

epollsvr: CMakeFiles/epollsvr.dir/epollsvr.cpp.o
epollsvr: CMakeFiles/epollsvr.dir/build.make
epollsvr: CMakeFiles/epollsvr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable epollsvr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/epollsvr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/epollsvr.dir/build: epollsvr
.PHONY : CMakeFiles/epollsvr.dir/build

CMakeFiles/epollsvr.dir/requires: CMakeFiles/epollsvr.dir/epollsvr.cpp.o.requires
.PHONY : CMakeFiles/epollsvr.dir/requires

CMakeFiles/epollsvr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/epollsvr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/epollsvr.dir/clean

CMakeFiles/epollsvr.dir/depend:
	cd /home/chen/socket_learn/18epoll && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/socket_learn/18epoll /home/chen/socket_learn/18epoll /home/chen/socket_learn/18epoll /home/chen/socket_learn/18epoll /home/chen/socket_learn/18epoll/CMakeFiles/epollsvr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/epollsvr.dir/depend

