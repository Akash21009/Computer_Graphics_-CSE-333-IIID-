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
CMAKE_SOURCE_DIR = /mnt/e/OpenGl/Assign1/code/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/OpenGl/Assign1/code/code

# Include any dependencies generated for this target.
include CMakeFiles/Assignment01.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Assignment01.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment01.dir/flags.make

CMakeFiles/Assignment01.dir/src/main.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/Assignment01.dir/src/main.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Assignment01.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/src/main.cpp.o -MF CMakeFiles/Assignment01.dir/src/main.cpp.o.d -o CMakeFiles/Assignment01.dir/src/main.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/src/main.cpp

CMakeFiles/Assignment01.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/src/main.cpp > CMakeFiles/Assignment01.dir/src/main.cpp.i

CMakeFiles/Assignment01.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/src/main.cpp -o CMakeFiles/Assignment01.dir/src/main.cpp.s

CMakeFiles/Assignment01.dir/src/utils.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/src/utils.cpp.o: src/utils.cpp
CMakeFiles/Assignment01.dir/src/utils.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Assignment01.dir/src/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/src/utils.cpp.o -MF CMakeFiles/Assignment01.dir/src/utils.cpp.o.d -o CMakeFiles/Assignment01.dir/src/utils.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/src/utils.cpp

CMakeFiles/Assignment01.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/src/utils.cpp > CMakeFiles/Assignment01.dir/src/utils.cpp.i

CMakeFiles/Assignment01.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/src/utils.cpp -o CMakeFiles/Assignment01.dir/src/utils.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o: depends/imgui/imgui_impl_glfw.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_glfw.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_glfw.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_glfw.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o: depends/imgui/imgui_impl_opengl3.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_opengl3.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_opengl3.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_impl_opengl3.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o: depends/imgui/imgui.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o: depends/imgui/imgui_demo.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_demo.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_demo.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_demo.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o: depends/imgui/imgui_draw.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_draw.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_draw.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_draw.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.s

CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/Assignment01.dir/flags.make
CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o: depends/imgui/imgui_widgets.cpp
CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o: CMakeFiles/Assignment01.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o -MF CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o -c /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_widgets.cpp

CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_widgets.cpp > CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.i

CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/OpenGl/Assign1/code/code/depends/imgui/imgui_widgets.cpp -o CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.s

# Object files for target Assignment01
Assignment01_OBJECTS = \
"CMakeFiles/Assignment01.dir/src/main.cpp.o" \
"CMakeFiles/Assignment01.dir/src/utils.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o" \
"CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o"

# External object files for target Assignment01
Assignment01_EXTERNAL_OBJECTS =

Assignment01: CMakeFiles/Assignment01.dir/src/main.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/src/utils.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_glfw.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui_impl_opengl3.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui_demo.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui_draw.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/depends/imgui/imgui_widgets.cpp.o
Assignment01: CMakeFiles/Assignment01.dir/build.make
Assignment01: /usr/lib/x86_64-linux-gnu/libGL.so
Assignment01: /usr/lib/x86_64-linux-gnu/libGLU.so
Assignment01: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
Assignment01: /usr/lib/x86_64-linux-gnu/libGLEW.so
Assignment01: CMakeFiles/Assignment01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/OpenGl/Assign1/code/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Assignment01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Assignment01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment01.dir/build: Assignment01
.PHONY : CMakeFiles/Assignment01.dir/build

CMakeFiles/Assignment01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Assignment01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Assignment01.dir/clean

CMakeFiles/Assignment01.dir/depend:
	cd /mnt/e/OpenGl/Assign1/code/code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/OpenGl/Assign1/code/code /mnt/e/OpenGl/Assign1/code/code /mnt/e/OpenGl/Assign1/code/code /mnt/e/OpenGl/Assign1/code/code /mnt/e/OpenGl/Assign1/code/code/CMakeFiles/Assignment01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Assignment01.dir/depend

