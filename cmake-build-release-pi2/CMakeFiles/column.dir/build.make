# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /tmp/tmp.n6jBnPQEUa

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2

# Include any dependencies generated for this target.
include CMakeFiles/column.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/column.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/column.dir/flags.make

CMakeFiles/column.dir/src/I2CDevice.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/I2CDevice.cpp.o: ../src/I2CDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/column.dir/src/I2CDevice.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/I2CDevice.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/I2CDevice.cpp

CMakeFiles/column.dir/src/I2CDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/I2CDevice.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/I2CDevice.cpp > CMakeFiles/column.dir/src/I2CDevice.cpp.i

CMakeFiles/column.dir/src/I2CDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/I2CDevice.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/I2CDevice.cpp -o CMakeFiles/column.dir/src/I2CDevice.cpp.s

CMakeFiles/column.dir/src/I2CDevice.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/I2CDevice.cpp.o.requires

CMakeFiles/column.dir/src/I2CDevice.cpp.o.provides: CMakeFiles/column.dir/src/I2CDevice.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/I2CDevice.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/I2CDevice.cpp.o.provides

CMakeFiles/column.dir/src/I2CDevice.cpp.o.provides.build: CMakeFiles/column.dir/src/I2CDevice.cpp.o


CMakeFiles/column.dir/src/group.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/group.cpp.o: ../src/group.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/column.dir/src/group.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/group.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/group.cpp

CMakeFiles/column.dir/src/group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/group.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/group.cpp > CMakeFiles/column.dir/src/group.cpp.i

CMakeFiles/column.dir/src/group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/group.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/group.cpp -o CMakeFiles/column.dir/src/group.cpp.s

CMakeFiles/column.dir/src/group.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/group.cpp.o.requires

CMakeFiles/column.dir/src/group.cpp.o.provides: CMakeFiles/column.dir/src/group.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/group.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/group.cpp.o.provides

CMakeFiles/column.dir/src/group.cpp.o.provides.build: CMakeFiles/column.dir/src/group.cpp.o


CMakeFiles/column.dir/src/main.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/column.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/main.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/main.cpp

CMakeFiles/column.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/main.cpp > CMakeFiles/column.dir/src/main.cpp.i

CMakeFiles/column.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/main.cpp -o CMakeFiles/column.dir/src/main.cpp.s

CMakeFiles/column.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/main.cpp.o.requires

CMakeFiles/column.dir/src/main.cpp.o.provides: CMakeFiles/column.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/main.cpp.o.provides

CMakeFiles/column.dir/src/main.cpp.o.provides.build: CMakeFiles/column.dir/src/main.cpp.o


CMakeFiles/column.dir/src/node.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/node.cpp.o: ../src/node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/column.dir/src/node.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/node.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/node.cpp

CMakeFiles/column.dir/src/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/node.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/node.cpp > CMakeFiles/column.dir/src/node.cpp.i

CMakeFiles/column.dir/src/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/node.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/node.cpp -o CMakeFiles/column.dir/src/node.cpp.s

CMakeFiles/column.dir/src/node.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/node.cpp.o.requires

CMakeFiles/column.dir/src/node.cpp.o.provides: CMakeFiles/column.dir/src/node.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/node.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/node.cpp.o.provides

CMakeFiles/column.dir/src/node.cpp.o.provides.build: CMakeFiles/column.dir/src/node.cpp.o


CMakeFiles/column.dir/src/objectHandler.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/objectHandler.cpp.o: ../src/objectHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/column.dir/src/objectHandler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/objectHandler.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/objectHandler.cpp

CMakeFiles/column.dir/src/objectHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/objectHandler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/objectHandler.cpp > CMakeFiles/column.dir/src/objectHandler.cpp.i

CMakeFiles/column.dir/src/objectHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/objectHandler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/objectHandler.cpp -o CMakeFiles/column.dir/src/objectHandler.cpp.s

CMakeFiles/column.dir/src/objectHandler.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/objectHandler.cpp.o.requires

CMakeFiles/column.dir/src/objectHandler.cpp.o.provides: CMakeFiles/column.dir/src/objectHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/objectHandler.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/objectHandler.cpp.o.provides

CMakeFiles/column.dir/src/objectHandler.cpp.o.provides.build: CMakeFiles/column.dir/src/objectHandler.cpp.o


CMakeFiles/column.dir/src/pin.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/pin.cpp.o: ../src/pin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/column.dir/src/pin.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/pin.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/pin.cpp

CMakeFiles/column.dir/src/pin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/pin.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/pin.cpp > CMakeFiles/column.dir/src/pin.cpp.i

CMakeFiles/column.dir/src/pin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/pin.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/pin.cpp -o CMakeFiles/column.dir/src/pin.cpp.s

CMakeFiles/column.dir/src/pin.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/pin.cpp.o.requires

CMakeFiles/column.dir/src/pin.cpp.o.provides: CMakeFiles/column.dir/src/pin.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/pin.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/pin.cpp.o.provides

CMakeFiles/column.dir/src/pin.cpp.o.provides.build: CMakeFiles/column.dir/src/pin.cpp.o


CMakeFiles/column.dir/src/settings.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/settings.cpp.o: ../src/settings.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/column.dir/src/settings.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/settings.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/settings.cpp

CMakeFiles/column.dir/src/settings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/settings.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/settings.cpp > CMakeFiles/column.dir/src/settings.cpp.i

CMakeFiles/column.dir/src/settings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/settings.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/settings.cpp -o CMakeFiles/column.dir/src/settings.cpp.s

CMakeFiles/column.dir/src/settings.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/settings.cpp.o.requires

CMakeFiles/column.dir/src/settings.cpp.o.provides: CMakeFiles/column.dir/src/settings.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/settings.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/settings.cpp.o.provides

CMakeFiles/column.dir/src/settings.cpp.o.provides.build: CMakeFiles/column.dir/src/settings.cpp.o


CMakeFiles/column.dir/src/trigger.cpp.o: CMakeFiles/column.dir/flags.make
CMakeFiles/column.dir/src/trigger.cpp.o: ../src/trigger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/column.dir/src/trigger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/column.dir/src/trigger.cpp.o -c /tmp/tmp.n6jBnPQEUa/src/trigger.cpp

CMakeFiles/column.dir/src/trigger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/column.dir/src/trigger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /tmp/tmp.n6jBnPQEUa/src/trigger.cpp > CMakeFiles/column.dir/src/trigger.cpp.i

CMakeFiles/column.dir/src/trigger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/column.dir/src/trigger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /tmp/tmp.n6jBnPQEUa/src/trigger.cpp -o CMakeFiles/column.dir/src/trigger.cpp.s

CMakeFiles/column.dir/src/trigger.cpp.o.requires:

.PHONY : CMakeFiles/column.dir/src/trigger.cpp.o.requires

CMakeFiles/column.dir/src/trigger.cpp.o.provides: CMakeFiles/column.dir/src/trigger.cpp.o.requires
	$(MAKE) -f CMakeFiles/column.dir/build.make CMakeFiles/column.dir/src/trigger.cpp.o.provides.build
.PHONY : CMakeFiles/column.dir/src/trigger.cpp.o.provides

CMakeFiles/column.dir/src/trigger.cpp.o.provides.build: CMakeFiles/column.dir/src/trigger.cpp.o


# Object files for target column
column_OBJECTS = \
"CMakeFiles/column.dir/src/I2CDevice.cpp.o" \
"CMakeFiles/column.dir/src/group.cpp.o" \
"CMakeFiles/column.dir/src/main.cpp.o" \
"CMakeFiles/column.dir/src/node.cpp.o" \
"CMakeFiles/column.dir/src/objectHandler.cpp.o" \
"CMakeFiles/column.dir/src/pin.cpp.o" \
"CMakeFiles/column.dir/src/settings.cpp.o" \
"CMakeFiles/column.dir/src/trigger.cpp.o"

# External object files for target column
column_EXTERNAL_OBJECTS =

column: CMakeFiles/column.dir/src/I2CDevice.cpp.o
column: CMakeFiles/column.dir/src/group.cpp.o
column: CMakeFiles/column.dir/src/main.cpp.o
column: CMakeFiles/column.dir/src/node.cpp.o
column: CMakeFiles/column.dir/src/objectHandler.cpp.o
column: CMakeFiles/column.dir/src/pin.cpp.o
column: CMakeFiles/column.dir/src/settings.cpp.o
column: CMakeFiles/column.dir/src/trigger.cpp.o
column: CMakeFiles/column.dir/build.make
column: CMakeFiles/column.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable column"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/column.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/column.dir/build: column

.PHONY : CMakeFiles/column.dir/build

CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/I2CDevice.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/group.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/main.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/node.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/objectHandler.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/pin.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/settings.cpp.o.requires
CMakeFiles/column.dir/requires: CMakeFiles/column.dir/src/trigger.cpp.o.requires

.PHONY : CMakeFiles/column.dir/requires

CMakeFiles/column.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/column.dir/cmake_clean.cmake
.PHONY : CMakeFiles/column.dir/clean

CMakeFiles/column.dir/depend:
	cd /tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/tmp.n6jBnPQEUa /tmp/tmp.n6jBnPQEUa /tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2 /tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2 /tmp/tmp.n6jBnPQEUa/cmake-build-release-pi2/CMakeFiles/column.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/column.dir/depend

