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
include w4/CMakeFiles/w4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include w4/CMakeFiles/w4.dir/compiler_depend.make

# Include the progress variables for this target.
include w4/CMakeFiles/w4.dir/progress.make

# Include the compile flags for this target's objects.
include w4/CMakeFiles/w4.dir/flags.make

w4/CMakeFiles/w4.dir/codegen:
.PHONY : w4/CMakeFiles/w4.dir/codegen

w4/CMakeFiles/w4.dir/client.cpp.o: w4/CMakeFiles/w4.dir/flags.make
w4/CMakeFiles/w4.dir/client.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/client.cpp
w4/CMakeFiles/w4.dir/client.cpp.o: w4/CMakeFiles/w4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object w4/CMakeFiles/w4.dir/client.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w4/CMakeFiles/w4.dir/client.cpp.o -MF CMakeFiles/w4.dir/client.cpp.o.d -o CMakeFiles/w4.dir/client.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/client.cpp

w4/CMakeFiles/w4.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w4.dir/client.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/client.cpp > CMakeFiles/w4.dir/client.cpp.i

w4/CMakeFiles/w4.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w4.dir/client.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/client.cpp -o CMakeFiles/w4.dir/client.cpp.s

w4/CMakeFiles/w4.dir/protocol.cpp.o: w4/CMakeFiles/w4.dir/flags.make
w4/CMakeFiles/w4.dir/protocol.cpp.o: /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/protocol.cpp
w4/CMakeFiles/w4.dir/protocol.cpp.o: w4/CMakeFiles/w4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object w4/CMakeFiles/w4.dir/protocol.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w4/CMakeFiles/w4.dir/protocol.cpp.o -MF CMakeFiles/w4.dir/protocol.cpp.o.d -o CMakeFiles/w4.dir/protocol.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/protocol.cpp

w4/CMakeFiles/w4.dir/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w4.dir/protocol.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/protocol.cpp > CMakeFiles/w4.dir/protocol.cpp.i

w4/CMakeFiles/w4.dir/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w4.dir/protocol.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4/protocol.cpp -o CMakeFiles/w4.dir/protocol.cpp.s

# Object files for target w4
w4_OBJECTS = \
"CMakeFiles/w4.dir/client.cpp.o" \
"CMakeFiles/w4.dir/protocol.cpp.o"

# External object files for target w4
w4_EXTERNAL_OBJECTS =

w4/w4: w4/CMakeFiles/w4.dir/client.cpp.o
w4/w4: w4/CMakeFiles/w4.dir/protocol.cpp.o
w4/w4: w4/CMakeFiles/w4.dir/build.make
w4/w4: 3rdParty/raylib/raylib/libraylib.a
w4/w4: 3rdParty/enet/libenet.a
w4/w4: /usr/lib/x86_64-linux-gnu/libOpenGL.so
w4/w4: /usr/lib/x86_64-linux-gnu/libGLX.so
w4/w4: /usr/lib/x86_64-linux-gnu/libGLU.so
w4/w4: /usr/lib/x86_64-linux-gnu/librt.a
w4/w4: /usr/lib/x86_64-linux-gnu/libm.so
w4/w4: w4/CMakeFiles/w4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable w4"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/w4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
w4/CMakeFiles/w4.dir/build: w4/w4
.PHONY : w4/CMakeFiles/w4.dir/build

w4/CMakeFiles/w4.dir/clean:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 && $(CMAKE_COMMAND) -P CMakeFiles/w4.dir/cmake_clean.cmake
.PHONY : w4/CMakeFiles/w4.dir/clean

w4/CMakeFiles/w4.dir/depend:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w4 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/build/w4/CMakeFiles/w4.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : w4/CMakeFiles/w4.dir/depend

