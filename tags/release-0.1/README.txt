Hello,


Contents:
=========
A. Platform-specific build instructions
B. Initial thoughts and motivation



A. Platform-specific build instructions:
========================================

To compile Slinker, you need wxWidgets and CMake. It should run on any platform supported by these tools, which is many.

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
2) Build wxWidgets with your compiler. Please consult the wxWidgets documentation. For Microsoft Visual Studio,
   we only need the Debug and Release builds.
3) Run CMakeSetup.exe, and specify the source and target folders (make a 'bin' one).
4) Having specified your target compiler, keep hitting configure until done. It should find everything you need.
5) Hit 'OK' to generate the project files for your compiler.
6) Build Slinker.

Please contact tim.hutton@gmail with any problems compiling Slinker.


B. Initial thoughts and motivation:
===================================

slitherlink:

2d square lattice of values: 0,1,2,3 (usually provided at start of puzzle and fixed)
borders of squares take values: 0,1 (unbonded or bonded)
also a special value for each: -1 (entry unknown)
borders are linked in one continuous loop, with no crossovers

slitherlink is NP-complete: checking that problems have unique solutions gets very expensive with
increasing size. but for a given size, e.g. 7x7, we should be able to find enough optimisations
to be able to find unique-solution puzzles

problem 1: given a blank world, with N numbers near the middle/corners/sides, 
what 'rules' are there for 0, 1, 2, 3 entries provided?
(e.g. 3 above 3 means we know there are 3 horizontal borders turned on)

problem 2: can we solve all published worlds by exhaustive search in reasonable time? 
can we use the rules to speed up the search? (up to ~20x20;yes)

problem 4: can we generate puzzles that have unique solutions? yes

problem 5: can we generate puzzles with a minimal number of entries provided for the size? well, for a given loop, yes.

problem 6: can we generate puzzles that are directly solvable without having to follow alternatives? yes, by simply turning
           off recursion in our solver - this yields nicer puzzles without increasing the number of entries required, intriguingly. 
           => the 'unwritten' rules of slitherlink: 0) each puzzle has a unique solution. -1) each puzzle is solvable 
           without having to explore possibilities (by deduction alone)

problem: can we cast the search problem as a CA? (yes, by having transition rules apply, for directly-solvable puzzles
			we get a solution)

problem: any even-number-sized square grid with a full diagonal of 2's with all their border-pairs pointing the same way 
         has at least one other solution (with border-pairs pointing the other way), hence don't make good puzzles.
         (BTW, any *odd*-number-sized square grid with a full diagonal of 2's has no solutions.) 
         What other such quirks exist? 

