# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build

# Include any dependencies generated for this target.
include CMakeFiles/your_executable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/your_executable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/your_executable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/your_executable.dir/flags.make

CMakeFiles/your_executable.dir/socket/main.cpp.o: CMakeFiles/your_executable.dir/flags.make
CMakeFiles/your_executable.dir/socket/main.cpp.o: /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/main.cpp
CMakeFiles/your_executable.dir/socket/main.cpp.o: CMakeFiles/your_executable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/your_executable.dir/socket/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/your_executable.dir/socket/main.cpp.o -MF CMakeFiles/your_executable.dir/socket/main.cpp.o.d -o CMakeFiles/your_executable.dir/socket/main.cpp.o -c /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/main.cpp

CMakeFiles/your_executable.dir/socket/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/your_executable.dir/socket/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/main.cpp > CMakeFiles/your_executable.dir/socket/main.cpp.i

CMakeFiles/your_executable.dir/socket/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/your_executable.dir/socket/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/main.cpp -o CMakeFiles/your_executable.dir/socket/main.cpp.s

CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o: CMakeFiles/your_executable.dir/flags.make
CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o: /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/websocket_session.cpp
CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o: CMakeFiles/your_executable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o -MF CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o.d -o CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o -c /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/websocket_session.cpp

CMakeFiles/your_executable.dir/socket/websocket_session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/your_executable.dir/socket/websocket_session.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/websocket_session.cpp > CMakeFiles/your_executable.dir/socket/websocket_session.cpp.i

CMakeFiles/your_executable.dir/socket/websocket_session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/your_executable.dir/socket/websocket_session.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/socket/websocket_session.cpp -o CMakeFiles/your_executable.dir/socket/websocket_session.cpp.s

CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o: CMakeFiles/your_executable.dir/flags.make
CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o: /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/app/conveyor_status.cpp
CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o: CMakeFiles/your_executable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o -MF CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o.d -o CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o -c /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/app/conveyor_status.cpp

CMakeFiles/your_executable.dir/app/conveyor_status.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/your_executable.dir/app/conveyor_status.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/app/conveyor_status.cpp > CMakeFiles/your_executable.dir/app/conveyor_status.cpp.i

CMakeFiles/your_executable.dir/app/conveyor_status.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/your_executable.dir/app/conveyor_status.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/app/conveyor_status.cpp -o CMakeFiles/your_executable.dir/app/conveyor_status.cpp.s

# Object files for target your_executable
your_executable_OBJECTS = \
"CMakeFiles/your_executable.dir/socket/main.cpp.o" \
"CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o" \
"CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o"

# External object files for target your_executable
your_executable_EXTERNAL_OBJECTS =

your_executable: CMakeFiles/your_executable.dir/socket/main.cpp.o
your_executable: CMakeFiles/your_executable.dir/socket/websocket_session.cpp.o
your_executable: CMakeFiles/your_executable.dir/app/conveyor_status.cpp.o
your_executable: CMakeFiles/your_executable.dir/build.make
your_executable: /usr/local/lib/libboost_system.dylib
your_executable: CMakeFiles/your_executable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable your_executable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/your_executable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/your_executable.dir/build: your_executable
.PHONY : CMakeFiles/your_executable.dir/build

CMakeFiles/your_executable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/your_executable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/your_executable.dir/clean

CMakeFiles/your_executable.dir/depend:
	cd /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build /Users/qiaoyu/Documents/格拉斯哥/嵌入式/Aircraft_Cargo_Blance_System/backend/build/CMakeFiles/your_executable.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/your_executable.dir/depend

