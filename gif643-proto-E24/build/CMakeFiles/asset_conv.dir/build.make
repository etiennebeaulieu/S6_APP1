# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /workspaces/gif643-proto-E24

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspaces/gif643-proto-E24/build

# Include any dependencies generated for this target.
include CMakeFiles/asset_conv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/asset_conv.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/asset_conv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/asset_conv.dir/flags.make

CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o: CMakeFiles/asset_conv.dir/flags.make
CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o: /workspaces/gif643-proto-E24/src/asset_conv.cpp
CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o: CMakeFiles/asset_conv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspaces/gif643-proto-E24/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o -MF CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o.d -o CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o -c /workspaces/gif643-proto-E24/src/asset_conv.cpp

CMakeFiles/asset_conv.dir/src/asset_conv.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/asset_conv.dir/src/asset_conv.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /workspaces/gif643-proto-E24/src/asset_conv.cpp > CMakeFiles/asset_conv.dir/src/asset_conv.cpp.i

CMakeFiles/asset_conv.dir/src/asset_conv.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/asset_conv.dir/src/asset_conv.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /workspaces/gif643-proto-E24/src/asset_conv.cpp -o CMakeFiles/asset_conv.dir/src/asset_conv.cpp.s

# Object files for target asset_conv
asset_conv_OBJECTS = \
"CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o"

# External object files for target asset_conv
asset_conv_EXTERNAL_OBJECTS =

asset_conv: CMakeFiles/asset_conv.dir/src/asset_conv.cpp.o
asset_conv: CMakeFiles/asset_conv.dir/build.make
asset_conv: libnanosvg.a
asset_conv: libstb_image.a
asset_conv: CMakeFiles/asset_conv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspaces/gif643-proto-E24/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable asset_conv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/asset_conv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/asset_conv.dir/build: asset_conv
.PHONY : CMakeFiles/asset_conv.dir/build

CMakeFiles/asset_conv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/asset_conv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/asset_conv.dir/clean

CMakeFiles/asset_conv.dir/depend:
	cd /workspaces/gif643-proto-E24/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspaces/gif643-proto-E24 /workspaces/gif643-proto-E24 /workspaces/gif643-proto-E24/build /workspaces/gif643-proto-E24/build /workspaces/gif643-proto-E24/build/CMakeFiles/asset_conv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/asset_conv.dir/depend

