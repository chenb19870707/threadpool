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
CMAKE_SOURCE_DIR = /home/chen/socket_learn/34posix_mq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/socket_learn/34posix_mq

# Include any dependencies generated for this target.
include CMakeFiles/03mq_getattr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/03mq_getattr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/03mq_getattr.dir/flags.make

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o: CMakeFiles/03mq_getattr.dir/flags.make
CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o: 03mq_getattr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chen/socket_learn/34posix_mq/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o -c /home/chen/socket_learn/34posix_mq/03mq_getattr.cpp

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/chen/socket_learn/34posix_mq/03mq_getattr.cpp > CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.i

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/chen/socket_learn/34posix_mq/03mq_getattr.cpp -o CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.s

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.requires:
.PHONY : CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.requires

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.provides: CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.requires
	$(MAKE) -f CMakeFiles/03mq_getattr.dir/build.make CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.provides.build
.PHONY : CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.provides

CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.provides.build: CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o

# Object files for target 03mq_getattr
03mq_getattr_OBJECTS = \
"CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o"

# External object files for target 03mq_getattr
03mq_getattr_EXTERNAL_OBJECTS =

03mq_getattr: CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o
03mq_getattr: CMakeFiles/03mq_getattr.dir/build.make
03mq_getattr: CMakeFiles/03mq_getattr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable 03mq_getattr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/03mq_getattr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/03mq_getattr.dir/build: 03mq_getattr
.PHONY : CMakeFiles/03mq_getattr.dir/build

CMakeFiles/03mq_getattr.dir/requires: CMakeFiles/03mq_getattr.dir/03mq_getattr.cpp.o.requires
.PHONY : CMakeFiles/03mq_getattr.dir/requires

CMakeFiles/03mq_getattr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/03mq_getattr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/03mq_getattr.dir/clean

CMakeFiles/03mq_getattr.dir/depend:
	cd /home/chen/socket_learn/34posix_mq && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/socket_learn/34posix_mq /home/chen/socket_learn/34posix_mq /home/chen/socket_learn/34posix_mq /home/chen/socket_learn/34posix_mq /home/chen/socket_learn/34posix_mq/CMakeFiles/03mq_getattr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/03mq_getattr.dir/depend

