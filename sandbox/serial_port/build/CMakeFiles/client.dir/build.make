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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jesus/ros_workspace/sandbox/serial_port

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jesus/ros_workspace/sandbox/serial_port/build

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/src/client.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/client.o: ../src/client.cpp
CMakeFiles/client.dir/src/client.o: ../manifest.xml
CMakeFiles/client.dir/src/client.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/client.dir/src/client.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/client.dir/src/client.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/client.dir/src/client.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/client.dir/src/client.o: /home/jesus/ros_workspace/serial/cereal_port/manifest.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jesus/ros_workspace/sandbox/serial_port/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/client.dir/src/client.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/client.dir/src/client.o -c /home/jesus/ros_workspace/sandbox/serial_port/src/client.cpp

CMakeFiles/client.dir/src/client.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/jesus/ros_workspace/sandbox/serial_port/src/client.cpp > CMakeFiles/client.dir/src/client.i

CMakeFiles/client.dir/src/client.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/jesus/ros_workspace/sandbox/serial_port/src/client.cpp -o CMakeFiles/client.dir/src/client.s

CMakeFiles/client.dir/src/client.o.requires:
.PHONY : CMakeFiles/client.dir/src/client.o.requires

CMakeFiles/client.dir/src/client.o.provides: CMakeFiles/client.dir/src/client.o.requires
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/src/client.o.provides.build
.PHONY : CMakeFiles/client.dir/src/client.o.provides

CMakeFiles/client.dir/src/client.o.provides.build: CMakeFiles/client.dir/src/client.o

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: CMakeFiles/client.dir/src/client.o
../bin/client: CMakeFiles/client.dir/build.make
../bin/client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: ../bin/client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/requires: CMakeFiles/client.dir/src/client.o.requires
.PHONY : CMakeFiles/client.dir/requires

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/jesus/ros_workspace/sandbox/serial_port/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jesus/ros_workspace/sandbox/serial_port /home/jesus/ros_workspace/sandbox/serial_port /home/jesus/ros_workspace/sandbox/serial_port/build /home/jesus/ros_workspace/sandbox/serial_port/build /home/jesus/ros_workspace/sandbox/serial_port/build/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend
