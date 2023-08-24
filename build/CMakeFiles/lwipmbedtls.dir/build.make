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

# Include any dependencies generated for this target.
include CMakeFiles/lwipmbedtls.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lwipmbedtls.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lwipmbedtls.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lwipmbedtls.dir/flags.make

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj: CMakeFiles/lwipmbedtls.dir/flags.make
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj: ../pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj: CMakeFiles/lwipmbedtls.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/f/pico-webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj -MF CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj.d -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj -c /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.i"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c > CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.i

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.s"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.s

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj: CMakeFiles/lwipmbedtls.dir/flags.make
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj: ../pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj: CMakeFiles/lwipmbedtls.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/f/pico-webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj -MF CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj.d -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj -c /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.i"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c > CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.i

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.s"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.s

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj: CMakeFiles/lwipmbedtls.dir/flags.make
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj: ../pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c
CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj: CMakeFiles/lwipmbedtls.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/f/pico-webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj -MF CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj.d -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj -c /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.i"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c > CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.i

CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.s"
	/usr/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/f/pico-webserver/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c -o CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.s

# Object files for target lwipmbedtls
lwipmbedtls_OBJECTS = \
"CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj" \
"CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj" \
"CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj"

# External object files for target lwipmbedtls
lwipmbedtls_EXTERNAL_OBJECTS =

liblwipmbedtls.a: CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls.c.obj
liblwipmbedtls.a: CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/altcp_tls/altcp_tls_mbedtls_mem.c.obj
liblwipmbedtls.a: CMakeFiles/lwipmbedtls.dir/pico-sdk/lib/lwip/src/apps/snmp/snmpv3_mbedtls.c.obj
liblwipmbedtls.a: CMakeFiles/lwipmbedtls.dir/build.make
liblwipmbedtls.a: CMakeFiles/lwipmbedtls.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/f/pico-webserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library liblwipmbedtls.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lwipmbedtls.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lwipmbedtls.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lwipmbedtls.dir/build: liblwipmbedtls.a
.PHONY : CMakeFiles/lwipmbedtls.dir/build

CMakeFiles/lwipmbedtls.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lwipmbedtls.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lwipmbedtls.dir/clean

CMakeFiles/lwipmbedtls.dir/depend:
	cd /mnt/f/pico-webserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/f/pico-webserver /mnt/f/pico-webserver /mnt/f/pico-webserver/build /mnt/f/pico-webserver/build /mnt/f/pico-webserver/build/CMakeFiles/lwipmbedtls.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lwipmbedtls.dir/depend
