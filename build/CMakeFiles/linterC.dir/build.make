# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\projets ESGI\Linter-C"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\projets ESGI\Linter-C\build"

# Include any dependencies generated for this target.
include CMakeFiles/linterC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linterC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linterC.dir/flags.make

CMakeFiles/linterC.dir/sources/main.c.obj: CMakeFiles/linterC.dir/flags.make
CMakeFiles/linterC.dir/sources/main.c.obj: CMakeFiles/linterC.dir/includes_C.rsp
CMakeFiles/linterC.dir/sources/main.c.obj: ../sources/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\projets ESGI\Linter-C\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/linterC.dir/sources/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\linterC.dir\sources\main.c.obj   -c "D:\projets ESGI\Linter-C\sources\main.c"

CMakeFiles/linterC.dir/sources/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linterC.dir/sources/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\projets ESGI\Linter-C\sources\main.c" > CMakeFiles\linterC.dir\sources\main.c.i

CMakeFiles/linterC.dir/sources/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linterC.dir/sources/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\projets ESGI\Linter-C\sources\main.c" -o CMakeFiles\linterC.dir\sources\main.c.s

CMakeFiles/linterC.dir/sources/config.c.obj: CMakeFiles/linterC.dir/flags.make
CMakeFiles/linterC.dir/sources/config.c.obj: CMakeFiles/linterC.dir/includes_C.rsp
CMakeFiles/linterC.dir/sources/config.c.obj: ../sources/config.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\projets ESGI\Linter-C\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/linterC.dir/sources/config.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\linterC.dir\sources\config.c.obj   -c "D:\projets ESGI\Linter-C\sources\config.c"

CMakeFiles/linterC.dir/sources/config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linterC.dir/sources/config.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\projets ESGI\Linter-C\sources\config.c" > CMakeFiles\linterC.dir\sources\config.c.i

CMakeFiles/linterC.dir/sources/config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linterC.dir/sources/config.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\projets ESGI\Linter-C\sources\config.c" -o CMakeFiles\linterC.dir\sources\config.c.s

CMakeFiles/linterC.dir/sources/logger.c.obj: CMakeFiles/linterC.dir/flags.make
CMakeFiles/linterC.dir/sources/logger.c.obj: CMakeFiles/linterC.dir/includes_C.rsp
CMakeFiles/linterC.dir/sources/logger.c.obj: ../sources/logger.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\projets ESGI\Linter-C\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/linterC.dir/sources/logger.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\linterC.dir\sources\logger.c.obj   -c "D:\projets ESGI\Linter-C\sources\logger.c"

CMakeFiles/linterC.dir/sources/logger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linterC.dir/sources/logger.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\projets ESGI\Linter-C\sources\logger.c" > CMakeFiles\linterC.dir\sources\logger.c.i

CMakeFiles/linterC.dir/sources/logger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linterC.dir/sources/logger.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\projets ESGI\Linter-C\sources\logger.c" -o CMakeFiles\linterC.dir\sources\logger.c.s

CMakeFiles/linterC.dir/sources/linter.c.obj: CMakeFiles/linterC.dir/flags.make
CMakeFiles/linterC.dir/sources/linter.c.obj: CMakeFiles/linterC.dir/includes_C.rsp
CMakeFiles/linterC.dir/sources/linter.c.obj: ../sources/linter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\projets ESGI\Linter-C\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/linterC.dir/sources/linter.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\linterC.dir\sources\linter.c.obj   -c "D:\projets ESGI\Linter-C\sources\linter.c"

CMakeFiles/linterC.dir/sources/linter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/linterC.dir/sources/linter.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\projets ESGI\Linter-C\sources\linter.c" > CMakeFiles\linterC.dir\sources\linter.c.i

CMakeFiles/linterC.dir/sources/linter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/linterC.dir/sources/linter.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\projets ESGI\Linter-C\sources\linter.c" -o CMakeFiles\linterC.dir\sources\linter.c.s

# Object files for target linterC
linterC_OBJECTS = \
"CMakeFiles/linterC.dir/sources/main.c.obj" \
"CMakeFiles/linterC.dir/sources/config.c.obj" \
"CMakeFiles/linterC.dir/sources/logger.c.obj" \
"CMakeFiles/linterC.dir/sources/linter.c.obj"

# External object files for target linterC
linterC_EXTERNAL_OBJECTS =

linterC.exe: CMakeFiles/linterC.dir/sources/main.c.obj
linterC.exe: CMakeFiles/linterC.dir/sources/config.c.obj
linterC.exe: CMakeFiles/linterC.dir/sources/logger.c.obj
linterC.exe: CMakeFiles/linterC.dir/sources/linter.c.obj
linterC.exe: CMakeFiles/linterC.dir/build.make
linterC.exe: regex2.dll
linterC.exe: CMakeFiles/linterC.dir/linklibs.rsp
linterC.exe: CMakeFiles/linterC.dir/objects1.rsp
linterC.exe: CMakeFiles/linterC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\projets ESGI\Linter-C\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable linterC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\linterC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linterC.dir/build: linterC.exe

.PHONY : CMakeFiles/linterC.dir/build

CMakeFiles/linterC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\linterC.dir\cmake_clean.cmake
.PHONY : CMakeFiles/linterC.dir/clean

CMakeFiles/linterC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\projets ESGI\Linter-C" "D:\projets ESGI\Linter-C" "D:\projets ESGI\Linter-C\build" "D:\projets ESGI\Linter-C\build" "D:\projets ESGI\Linter-C\build\CMakeFiles\linterC.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/linterC.dir/depend

