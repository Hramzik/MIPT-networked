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
CMAKE_BINARY_DIR = /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked

# Include any dependencies generated for this target.
include w10/CMakeFiles/w10.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include w10/CMakeFiles/w10.dir/compiler_depend.make

# Include the progress variables for this target.
include w10/CMakeFiles/w10.dir/progress.make

# Include the compile flags for this target's objects.
include w10/CMakeFiles/w10.dir/flags.make

w10/CMakeFiles/w10.dir/codegen:
.PHONY : w10/CMakeFiles/w10.dir/codegen

w10/CMakeFiles/w10.dir/main.cpp.o: w10/CMakeFiles/w10.dir/flags.make
w10/CMakeFiles/w10.dir/main.cpp.o: w10/main.cpp
w10/CMakeFiles/w10.dir/main.cpp.o: w10/CMakeFiles/w10.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object w10/CMakeFiles/w10.dir/main.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w10/CMakeFiles/w10.dir/main.cpp.o -MF CMakeFiles/w10.dir/main.cpp.o.d -o CMakeFiles/w10.dir/main.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/main.cpp

w10/CMakeFiles/w10.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w10.dir/main.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/main.cpp > CMakeFiles/w10.dir/main.cpp.i

w10/CMakeFiles/w10.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w10.dir/main.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/main.cpp -o CMakeFiles/w10.dir/main.cpp.s

w10/CMakeFiles/w10.dir/protocol.cpp.o: w10/CMakeFiles/w10.dir/flags.make
w10/CMakeFiles/w10.dir/protocol.cpp.o: w10/protocol.cpp
w10/CMakeFiles/w10.dir/protocol.cpp.o: w10/CMakeFiles/w10.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object w10/CMakeFiles/w10.dir/protocol.cpp.o"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT w10/CMakeFiles/w10.dir/protocol.cpp.o -MF CMakeFiles/w10.dir/protocol.cpp.o.d -o CMakeFiles/w10.dir/protocol.cpp.o -c /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/protocol.cpp

w10/CMakeFiles/w10.dir/protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/w10.dir/protocol.cpp.i"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/protocol.cpp > CMakeFiles/w10.dir/protocol.cpp.i

w10/CMakeFiles/w10.dir/protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/w10.dir/protocol.cpp.s"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/protocol.cpp -o CMakeFiles/w10.dir/protocol.cpp.s

# Object files for target w10
w10_OBJECTS = \
"CMakeFiles/w10.dir/main.cpp.o" \
"CMakeFiles/w10.dir/protocol.cpp.o"

# External object files for target w10
w10_EXTERNAL_OBJECTS =

w10/w10: w10/CMakeFiles/w10.dir/main.cpp.o
w10/w10: w10/CMakeFiles/w10.dir/protocol.cpp.o
w10/w10: w10/CMakeFiles/w10.dir/build.make
w10/w10: 3rdParty/raylib/raylib/libraylib.a
w10/w10: 3rdParty/enet/libenet.a
w10/w10: /usr/lib/x86_64-linux-gnu/libOpenGL.so
w10/w10: /usr/lib/x86_64-linux-gnu/libGLX.so
w10/w10: /usr/lib/x86_64-linux-gnu/libGLU.so
w10/w10: /usr/lib/x86_64-linux-gnu/librt.a
w10/w10: /usr/lib/x86_64-linux-gnu/libm.so
w10/w10: w10/CMakeFiles/w10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable w10"
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/w10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
w10/CMakeFiles/w10.dir/build: w10/w10
.PHONY : w10/CMakeFiles/w10.dir/build

w10/CMakeFiles/w10.dir/clean:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 && $(CMAKE_COMMAND) -P CMakeFiles/w10.dir/cmake_clean.cmake
.PHONY : w10/CMakeFiles/w10.dir/clean

w10/CMakeFiles/w10.dir/depend:
	cd /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10 /home/hramzik_pro/Desktop/coding/1-multiplayer/MIPT-networked/w10/CMakeFiles/w10.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : w10/CMakeFiles/w10.dir/depend

