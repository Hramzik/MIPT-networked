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
include w2/CMakeFiles/game_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include w2/CMakeFiles/game_server.dir/compiler_depend.make

# Include the progress variables for this target.
include w2/CMakeFiles/game_server.dir/progress.make

# Include the compile flags for this target's objects.
include w2/CMakeFiles/game_server.dir/flags.make

w2/CMakeFiles/game_server.dir/codegen:
.PHONY : w2/CMakeFiles/game_server.dir/codegen

w2/CMakeFiles/game_server.dir/GameServer.cpp.o: w2/CMakeFiles/game_server.dir/flags.make
w2/CMakeFiles/game_server.dir/GameServer.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w2/GameServer.cpp
w2/CMakeFiles/game_server.dir/GameServer.cpp.o: w2/CMakeFiles/game_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object w2/CMakeFiles/game_server.dir/GameServer.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w2/CMakeFiles/game_server.dir/GameServer.cpp.o -MF CMakeFiles/game_server.dir/GameServer.cpp.o.d -o CMakeFiles/game_server.dir/GameServer.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w2/GameServer.cpp

w2/CMakeFiles/game_server.dir/GameServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/game_server.dir/GameServer.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w2/GameServer.cpp > CMakeFiles/game_server.dir/GameServer.cpp.i

w2/CMakeFiles/game_server.dir/GameServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/game_server.dir/GameServer.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w2/GameServer.cpp -o CMakeFiles/game_server.dir/GameServer.cpp.s

# Object files for target game_server
game_server_OBJECTS = \
"CMakeFiles/game_server.dir/GameServer.cpp.o"

# External object files for target game_server
game_server_EXTERNAL_OBJECTS =

w2/game_server: w2/CMakeFiles/game_server.dir/GameServer.cpp.o
w2/game_server: w2/CMakeFiles/game_server.dir/build.make
w2/game_server: 3rdParty/enet/libenet.a
w2/game_server: w2/CMakeFiles/game_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable game_server"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
w2/CMakeFiles/game_server.dir/build: w2/game_server
.PHONY : w2/CMakeFiles/game_server.dir/build

w2/CMakeFiles/game_server.dir/clean:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 && $(CMAKE_COMMAND) -P CMakeFiles/game_server.dir/cmake_clean.cmake
.PHONY : w2/CMakeFiles/game_server.dir/clean

w2/CMakeFiles/game_server.dir/depend:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w2 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w2/CMakeFiles/game_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : w2/CMakeFiles/game_server.dir/depend

