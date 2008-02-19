 Hello,

To compile Slinker, you need wxWidgets 2.8 and CMake. It should run on any platform supported by these tools, which is many.


Platform-specific Build Instructions:
=====================================

Linux:

1) Your package manager (Synaptic or similar) should offer wxGTK (or similar) and cmake. Install them both.
2) Find wx-config (usually lives in /usr/bin or similar) - or wx-config-unicode.
3) Make a bin folder in the source code folder (or elsewhere).
4) From the bin folder, type "ccmake .." (or the path to the source folder)
5) ccmake may complain that wx-config was not found, if so enter the full path to the one you found, e.g. /usr/bin/wx-config-unicode
6) Keep hitting 'c' for configure until the pre-build is completed, and the 'g' option is offered.
7) Hit 'g' to generate the makefiles and exit.
8) Type 'make' to build Slinker.

Check the CMake manual for more options - you can make kdevelop projects, for example, or other IDEs.

Windows:

1) Install wxWidgets and CMake. Install in standard locations, eg. C:\wxWidgets-2.6.4 and C:\Program File\CMake2.5
2) Run CMakeSetup.exe, and specify the source and target folders (make a 'bin' one).
3) Having specified your target compiler, keep hitting configure until done. It should find everything you need.
4) Hit 'OK' to generate the project files for your compiler.
5) Compile.

Please contact tim.hutton@gmail with any problems compiling Slinker.