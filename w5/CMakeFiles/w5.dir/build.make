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
CMAKE_SOURCE_DIR = /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked

# Include any dependencies generated for this target.
include w5/CMakeFiles/w5.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include w5/CMakeFiles/w5.dir/compiler_depend.make

# Include the progress variables for this target.
include w5/CMakeFiles/w5.dir/progress.make

# Include the compile flags for this target's objects.
include w5/CMakeFiles/w5.dir/flags.make

w5/CMakeFiles/w5.dir/main.cpp.o: w5/CMakeFiles/w5.dir/flags.make
w5/CMakeFiles/w5.dir/main.cpp.o: w5/main.cpp
w5/CMakeFiles/w5.dir/main.cpp.o: w5/CMakeFiles/w5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object w5/CMakeFiles/w5.dir/main.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w5/CMakeFiles/w5.dir/main.cpp.o -MF CMakeFiles/w5.dir/main.cpp.o.d -o CMakeFiles/w5.dir/main.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/main.cpp

w5/CMakeFiles/w5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/w5.dir/main.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/main.cpp > CMakeFiles/w5.dir/main.cpp.i

w5/CMakeFiles/w5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/w5.dir/main.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/main.cpp -o CMakeFiles/w5.dir/main.cpp.s

w5/CMakeFiles/w5.dir/protocol.cpp.o: w5/CMakeFiles/w5.dir/flags.make
w5/CMakeFiles/w5.dir/protocol.cpp.o: w5/protocol.cpp
w5/CMakeFiles/w5.dir/protocol.cpp.o: w5/CMakeFiles/w5.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object w5/CMakeFiles/w5.dir/protocol.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w5/CMakeFiles/w5.dir/protocol.cpp.o -MF CMakeFiles/w5.dir/protocol.cpp.o.d -o CMakeFiles/w5.dir/protocol.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/protocol.cpp

w5/CMakeFiles/w5.dir/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/w5.dir/protocol.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/protocol.cpp > CMakeFiles/w5.dir/protocol.cpp.i

w5/CMakeFiles/w5.dir/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/w5.dir/protocol.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/protocol.cpp -o CMakeFiles/w5.dir/protocol.cpp.s

# Object files for target w5
w5_OBJECTS = \
"CMakeFiles/w5.dir/main.cpp.o" \
"CMakeFiles/w5.dir/protocol.cpp.o"

# External object files for target w5
w5_EXTERNAL_OBJECTS =

w5/w5: w5/CMakeFiles/w5.dir/main.cpp.o
w5/w5: w5/CMakeFiles/w5.dir/protocol.cpp.o
w5/w5: w5/CMakeFiles/w5.dir/build.make
w5/w5: 3rdParty/raylib/raylib/libraylib.a
w5/w5: 3rdParty/enet/libenet.a
w5/w5: /usr/lib/x86_64-linux-gnu/libOpenGL.so
w5/w5: /usr/lib/x86_64-linux-gnu/libGLX.so
w5/w5: /usr/lib/x86_64-linux-gnu/libGLU.so
w5/w5: 3rdParty/raylib/raylib/external/glfw/src/libglfw3.a
w5/w5: /usr/lib/x86_64-linux-gnu/librt.a
w5/w5: /usr/lib/x86_64-linux-gnu/libm.so
w5/w5: w5/CMakeFiles/w5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable w5"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/w5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
w5/CMakeFiles/w5.dir/build: w5/w5
.PHONY : w5/CMakeFiles/w5.dir/build

w5/CMakeFiles/w5.dir/clean:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 && $(CMAKE_COMMAND) -P CMakeFiles/w5.dir/cmake_clean.cmake
.PHONY : w5/CMakeFiles/w5.dir/clean

w5/CMakeFiles/w5.dir/depend:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w5/CMakeFiles/w5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : w5/CMakeFiles/w5.dir/depend

