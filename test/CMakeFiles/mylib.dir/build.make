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
CMAKE_SOURCE_DIR = /home/teshager/Dev/cpp/Sudoku_SDL2/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/teshager/Dev/cpp/Sudoku_SDL2/test

# Include any dependencies generated for this target.
include CMakeFiles/mylib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mylib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mylib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mylib.dir/flags.make

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.s

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.s

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.s

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.s

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.s

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o: CMakeFiles/mylib.dir/flags.make
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o: /home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp
CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o: CMakeFiles/mylib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o -MF CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o.d -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o -c /home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp > CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.i

CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp -o CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.s

# Object files for target mylib
mylib_OBJECTS = \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o" \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o" \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o" \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o" \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o" \
"CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o"

# External object files for target mylib
mylib_EXTERNAL_OBJECTS =

libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/model.cpp.o
libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/solver.cpp.o
libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/window.cpp.o
libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/texture.cpp.o
libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/AssetManager.cpp.o
libmylib.a: CMakeFiles/mylib.dir/home/teshager/Dev/cpp/Sudoku_SDL2/GameEntity.cpp.o
libmylib.a: CMakeFiles/mylib.dir/build.make
libmylib.a: CMakeFiles/mylib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libmylib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mylib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mylib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mylib.dir/build: libmylib.a
.PHONY : CMakeFiles/mylib.dir/build

CMakeFiles/mylib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mylib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mylib.dir/clean

CMakeFiles/mylib.dir/depend:
	cd /home/teshager/Dev/cpp/Sudoku_SDL2/test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/teshager/Dev/cpp/Sudoku_SDL2/test /home/teshager/Dev/cpp/Sudoku_SDL2/test /home/teshager/Dev/cpp/Sudoku_SDL2/test /home/teshager/Dev/cpp/Sudoku_SDL2/test /home/teshager/Dev/cpp/Sudoku_SDL2/test/CMakeFiles/mylib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mylib.dir/depend

