# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build

# Include any dependencies generated for this target.
include w7/CMakeFiles/w7_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include w7/CMakeFiles/w7_server.dir/compiler_depend.make

# Include the progress variables for this target.
include w7/CMakeFiles/w7_server.dir/progress.make

# Include the compile flags for this target's objects.
include w7/CMakeFiles/w7_server.dir/flags.make

w7/CMakeFiles/w7_server.dir/codegen:
.PHONY : w7/CMakeFiles/w7_server.dir/codegen

w7/CMakeFiles/w7_server.dir/server.cpp.o: w7/CMakeFiles/w7_server.dir/flags.make
w7/CMakeFiles/w7_server.dir/server.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/server.cpp
w7/CMakeFiles/w7_server.dir/server.cpp.o: w7/CMakeFiles/w7_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object w7/CMakeFiles/w7_server.dir/server.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w7/CMakeFiles/w7_server.dir/server.cpp.o -MF CMakeFiles/w7_server.dir/server.cpp.o.d -o CMakeFiles/w7_server.dir/server.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/server.cpp

w7/CMakeFiles/w7_server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w7_server.dir/server.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/server.cpp > CMakeFiles/w7_server.dir/server.cpp.i

w7/CMakeFiles/w7_server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w7_server.dir/server.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/server.cpp -o CMakeFiles/w7_server.dir/server.cpp.s

w7/CMakeFiles/w7_server.dir/protocol.cpp.o: w7/CMakeFiles/w7_server.dir/flags.make
w7/CMakeFiles/w7_server.dir/protocol.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/protocol.cpp
w7/CMakeFiles/w7_server.dir/protocol.cpp.o: w7/CMakeFiles/w7_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object w7/CMakeFiles/w7_server.dir/protocol.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w7/CMakeFiles/w7_server.dir/protocol.cpp.o -MF CMakeFiles/w7_server.dir/protocol.cpp.o.d -o CMakeFiles/w7_server.dir/protocol.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/protocol.cpp

w7/CMakeFiles/w7_server.dir/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w7_server.dir/protocol.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/protocol.cpp > CMakeFiles/w7_server.dir/protocol.cpp.i

w7/CMakeFiles/w7_server.dir/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w7_server.dir/protocol.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/protocol.cpp -o CMakeFiles/w7_server.dir/protocol.cpp.s

w7/CMakeFiles/w7_server.dir/entity.cpp.o: w7/CMakeFiles/w7_server.dir/flags.make
w7/CMakeFiles/w7_server.dir/entity.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/entity.cpp
w7/CMakeFiles/w7_server.dir/entity.cpp.o: w7/CMakeFiles/w7_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object w7/CMakeFiles/w7_server.dir/entity.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w7/CMakeFiles/w7_server.dir/entity.cpp.o -MF CMakeFiles/w7_server.dir/entity.cpp.o.d -o CMakeFiles/w7_server.dir/entity.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/entity.cpp

w7/CMakeFiles/w7_server.dir/entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w7_server.dir/entity.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/entity.cpp > CMakeFiles/w7_server.dir/entity.cpp.i

w7/CMakeFiles/w7_server.dir/entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w7_server.dir/entity.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7/entity.cpp -o CMakeFiles/w7_server.dir/entity.cpp.s

# Object files for target w7_server
w7_server_OBJECTS = \
"CMakeFiles/w7_server.dir/server.cpp.o" \
"CMakeFiles/w7_server.dir/protocol.cpp.o" \
"CMakeFiles/w7_server.dir/entity.cpp.o"

# External object files for target w7_server
w7_server_EXTERNAL_OBJECTS =

w7/w7_server: w7/CMakeFiles/w7_server.dir/server.cpp.o
w7/w7_server: w7/CMakeFiles/w7_server.dir/protocol.cpp.o
w7/w7_server: w7/CMakeFiles/w7_server.dir/entity.cpp.o
w7/w7_server: w7/CMakeFiles/w7_server.dir/build.make
w7/w7_server: 3rdParty/enet/libenet.a
w7/w7_server: w7/CMakeFiles/w7_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable w7_server"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/w7_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
w7/CMakeFiles/w7_server.dir/build: w7/w7_server
.PHONY : w7/CMakeFiles/w7_server.dir/build

w7/CMakeFiles/w7_server.dir/clean:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 && $(CMAKE_COMMAND) -P CMakeFiles/w7_server.dir/cmake_clean.cmake
.PHONY : w7/CMakeFiles/w7_server.dir/clean

w7/CMakeFiles/w7_server.dir/depend:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w7 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w7/CMakeFiles/w7_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : w7/CMakeFiles/w7_server.dir/depend

