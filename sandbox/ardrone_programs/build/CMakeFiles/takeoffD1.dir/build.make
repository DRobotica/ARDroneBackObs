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
CMAKE_SOURCE_DIR = /home/jesus/ros_workspace/sandbox/ardrone_programs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jesus/ros_workspace/sandbox/ardrone_programs/build

# Include any dependencies generated for this target.
include CMakeFiles/takeoffD1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/takeoffD1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/takeoffD1.dir/flags.make

CMakeFiles/takeoffD1.dir/src/takeoffD1.o: CMakeFiles/takeoffD1.dir/flags.make
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: ../src/takeoffD1.cpp
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: ../manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/roslang/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/roscpp/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/std_msgs/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/geometry_msgs/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/sensor_msgs/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/bullet/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/rosconsole/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/geometry/angles/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/rospy/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/rostest/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/roswtf/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/message_filters/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/geometry/tf/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/ros/core/rosbuild/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/roslib/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/pluginlib/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/image_common/image_transport/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/share/std_srvs/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/common_rosdeps/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/image_common/camera_calibration_parsers/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/image_common/camera_info_manager/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/ardrone_autonomy/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/serial/cereal_port/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/sandbox/serial_port/manifest.xml
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/geometry/tf/msg_gen/generated
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /opt/ros/fuerte/stacks/geometry/tf/srv_gen/generated
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/ardrone_autonomy/msg_gen/generated
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/ardrone_autonomy/srv_gen/generated
CMakeFiles/takeoffD1.dir/src/takeoffD1.o: /home/jesus/ros_workspace/sandbox/serial_port/msg_gen/generated
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jesus/ros_workspace/sandbox/ardrone_programs/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/takeoffD1.dir/src/takeoffD1.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -o CMakeFiles/takeoffD1.dir/src/takeoffD1.o -c /home/jesus/ros_workspace/sandbox/ardrone_programs/src/takeoffD1.cpp

CMakeFiles/takeoffD1.dir/src/takeoffD1.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/takeoffD1.dir/src/takeoffD1.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -E /home/jesus/ros_workspace/sandbox/ardrone_programs/src/takeoffD1.cpp > CMakeFiles/takeoffD1.dir/src/takeoffD1.i

CMakeFiles/takeoffD1.dir/src/takeoffD1.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/takeoffD1.dir/src/takeoffD1.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DBT_USE_DOUBLE_PRECISION -DBT_EULER_DEFAULT_ZYX -W -Wall -Wno-unused-parameter -fno-strict-aliasing -pthread -S /home/jesus/ros_workspace/sandbox/ardrone_programs/src/takeoffD1.cpp -o CMakeFiles/takeoffD1.dir/src/takeoffD1.s

CMakeFiles/takeoffD1.dir/src/takeoffD1.o.requires:
.PHONY : CMakeFiles/takeoffD1.dir/src/takeoffD1.o.requires

CMakeFiles/takeoffD1.dir/src/takeoffD1.o.provides: CMakeFiles/takeoffD1.dir/src/takeoffD1.o.requires
	$(MAKE) -f CMakeFiles/takeoffD1.dir/build.make CMakeFiles/takeoffD1.dir/src/takeoffD1.o.provides.build
.PHONY : CMakeFiles/takeoffD1.dir/src/takeoffD1.o.provides

CMakeFiles/takeoffD1.dir/src/takeoffD1.o.provides.build: CMakeFiles/takeoffD1.dir/src/takeoffD1.o

# Object files for target takeoffD1
takeoffD1_OBJECTS = \
"CMakeFiles/takeoffD1.dir/src/takeoffD1.o"

# External object files for target takeoffD1
takeoffD1_EXTERNAL_OBJECTS =

../bin/takeoffD1: CMakeFiles/takeoffD1.dir/src/takeoffD1.o
../bin/takeoffD1: CMakeFiles/takeoffD1.dir/build.make
../bin/takeoffD1: CMakeFiles/takeoffD1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/takeoffD1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/takeoffD1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/takeoffD1.dir/build: ../bin/takeoffD1
.PHONY : CMakeFiles/takeoffD1.dir/build

CMakeFiles/takeoffD1.dir/requires: CMakeFiles/takeoffD1.dir/src/takeoffD1.o.requires
.PHONY : CMakeFiles/takeoffD1.dir/requires

CMakeFiles/takeoffD1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/takeoffD1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/takeoffD1.dir/clean

CMakeFiles/takeoffD1.dir/depend:
	cd /home/jesus/ros_workspace/sandbox/ardrone_programs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jesus/ros_workspace/sandbox/ardrone_programs /home/jesus/ros_workspace/sandbox/ardrone_programs /home/jesus/ros_workspace/sandbox/ardrone_programs/build /home/jesus/ros_workspace/sandbox/ardrone_programs/build /home/jesus/ros_workspace/sandbox/ardrone_programs/build/CMakeFiles/takeoffD1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/takeoffD1.dir/depend

