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
include CMakeFiles/net3drones.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/net3drones.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/net3drones.dir/flags.make

CMakeFiles/net3drones.dir/src/net3drones.o: CMakeFiles/net3drones.dir/flags.make
CMakeFiles/net3drones.dir/src/net3drones.o: ../src/net3drones.cpp
CMakeFiles/net3drones.dir/src/net3drones.o: ../manifest.xml
CMakeFiles/net3drones.dir/src/net3drones.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/net3drones.dir/src/net3drones.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/net3drones.dir/src/net3drones.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/net3drones.dir/src/net3drones.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/net3drones.dir/src/net3drones.o: /home/jesus/ros_workspace/serial/cereal_port/manifest.xml
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jesus/ros_workspace/sandbox/serial_port/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/net3drones.dir/src/net3drones.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/net3drones.dir/src/net3drones.o -c /home/jesus/ros_workspace/sandbox/serial_port/src/net3drones.cpp

CMakeFiles/net3drones.dir/src/net3drones.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net3drones.dir/src/net3drones.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/jesus/ros_workspace/sandbox/serial_port/src/net3drones.cpp > CMakeFiles/net3drones.dir/src/net3drones.i

CMakeFiles/net3drones.dir/src/net3drones.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net3drones.dir/src/net3drones.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/jesus/ros_workspace/sandbox/serial_port/src/net3drones.cpp -o CMakeFiles/net3drones.dir/src/net3drones.s

CMakeFiles/net3drones.dir/src/net3drones.o.requires:
.PHONY : CMakeFiles/net3drones.dir/src/net3drones.o.requires

CMakeFiles/net3drones.dir/src/net3drones.o.provides: CMakeFiles/net3drones.dir/src/net3drones.o.requires
	$(MAKE) -f CMakeFiles/net3drones.dir/build.make CMakeFiles/net3drones.dir/src/net3drones.o.provides.build
.PHONY : CMakeFiles/net3drones.dir/src/net3drones.o.provides

CMakeFiles/net3drones.dir/src/net3drones.o.provides.build: CMakeFiles/net3drones.dir/src/net3drones.o

# Object files for target net3drones
net3drones_OBJECTS = \
"CMakeFiles/net3drones.dir/src/net3drones.o"

# External object files for target net3drones
net3drones_EXTERNAL_OBJECTS =

../bin/net3drones: CMakeFiles/net3drones.dir/src/net3drones.o
../bin/net3drones: CMakeFiles/net3drones.dir/build.make
../bin/net3drones: CMakeFiles/net3drones.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/net3drones"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/net3drones.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/net3drones.dir/build: ../bin/net3drones
.PHONY : CMakeFiles/net3drones.dir/build

CMakeFiles/net3drones.dir/requires: CMakeFiles/net3drones.dir/src/net3drones.o.requires
.PHONY : CMakeFiles/net3drones.dir/requires

CMakeFiles/net3drones.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/net3drones.dir/cmake_clean.cmake
.PHONY : CMakeFiles/net3drones.dir/clean

CMakeFiles/net3drones.dir/depend:
	cd /home/jesus/ros_workspace/sandbox/serial_port/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jesus/ros_workspace/sandbox/serial_port /home/jesus/ros_workspace/sandbox/serial_port /home/jesus/ros_workspace/sandbox/serial_port/build /home/jesus/ros_workspace/sandbox/serial_port/build /home/jesus/ros_workspace/sandbox/serial_port/build/CMakeFiles/net3drones.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/net3drones.dir/depend

