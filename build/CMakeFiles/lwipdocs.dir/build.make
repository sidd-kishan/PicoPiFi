# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/f/pico-webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/f/pico-webserver/build

# Utility rule file for lwipdocs.

# Include any custom commands dependencies for this target.
include CMakeFiles/lwipdocs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lwipdocs.dir/progress.make

CMakeFiles/lwipdocs:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/f/pico-webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating API documentation with Doxygen"
	cd /mnt/f/pico-webserver/pico-sdk/lib/lwip/doc/doxygen && /usr/bin/cmake -E remove_directory /mnt/f/pico-webserver/pico-sdk/lib/lwip/doc/doxygen/output/html
	cd /mnt/f/pico-webserver/pico-sdk/lib/lwip/doc/doxygen && /usr/bin/doxygen /mnt/f/pico-webserver/pico-sdk/lib/lwip/doc/doxygen/lwip.Doxyfile

lwipdocs: CMakeFiles/lwipdocs
lwipdocs: CMakeFiles/lwipdocs.dir/build.make
.PHONY : lwipdocs

# Rule to build all files generated by this target.
CMakeFiles/lwipdocs.dir/build: lwipdocs
.PHONY : CMakeFiles/lwipdocs.dir/build

CMakeFiles/lwipdocs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lwipdocs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lwipdocs.dir/clean

CMakeFiles/lwipdocs.dir/depend:
	cd /mnt/f/pico-webserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/f/pico-webserver /mnt/f/pico-webserver /mnt/f/pico-webserver/build /mnt/f/pico-webserver/build /mnt/f/pico-webserver/build/CMakeFiles/lwipdocs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lwipdocs.dir/depend
