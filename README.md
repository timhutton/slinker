Summary
=======

Slinker is an attempt to capture the best way to generate slitherlink-type puzzles. 

(Slitherlink is probably a trademark of [Nikoli](http://www.nikoli.co.jp) who invented the puzzle, so go to them if you want to buy genuine quality puzzles.)

Downloads
=========

The current version of Slinker is 0.1. The following downloads are available:

  * [Windows executable](https://github.com/timhutton/slinker/releases/download/release-0.1/Slinker-0.1.1-win32.exe) (417KB)
  * [Linux executable](https://github.com/timhutton/slinker/releases/download/release-0.1/Slinker-0.1.0-Linux.sh) (112KB)
  * [source code](https://github.com/timhutton/slinker/releases/download/release-0.1/Slinker-0.1.0-Source.tar.gz) (59KB) - for all popular platforms, see the [](README.txt) for build requirements and instructions.

Slinker works on Mac too: MacBuild.md 

Changes since earlier revisions: ChangeList.md

Screenshots
===========

[Slinker 0.1 under Linux](https://github.com/timhutton/slinker/releases/download/release-0.1/slinker-0.1_screenshot1_linux.png)


Status
======

Slinker can:
  * create and solve puzzles of different difficulties using a set of rules
  * verify that puzzles have a unique solution
  * decide whether a puzzle can be directly solved with a given ruleset.
  * can offer useful hints for when you get stuck
  * import/export puzzles as a Loopy string
  * compute more rules, if `SlinkerGrid::FindNewRules()` makes sense to you

Future work
===========

  * Undo/redo, fix position.
  * Puzzle creation should be faster - can we derive 'number removal' rules that tell us which numbers can be removed for a given local situation, given a set of solving rules?
  * Puzzle solving should be faster - solving a 40x30 takes a _long_ time, even with a 4-element ruleset.
  * Puzzles should make more use of the harder rules - rather than removing numbers at random, can we remove those that leave the puzzle only solvable using more complex rules?
  * Export/import as full Loopy format.
  * Need to add option to make a puzzle that would require highlander rules, and also make a list of highlander rules (how?).
  * May want to make 'special situation' puzzles - e.g. those involving only '2's, or those with certain areas empty. How to allow the user to do this? Or provide the programmer with tools to do this?
  * Analysis of puzzle difficulty - max/average level of rules required to solve, need for highlander, etc.? Ideally we'd like to be able to rate every puzzle as scientifically as possible, and seek consensus on the method. 

Links
=====

  * [Kwon-Tom Loop](http://www.kwontomloop.com) - an amazing community of Slitherlink-obsessed geniuses.
  * Other Slitherlink puzzle generators: (please tell me of any more you know)
    * [Loopy](http://www.chiark.greenend.org.uk/~sgtatham/puzzles/)
    * [KrazyDad](http://www.krazydad.com/slitherlink/) (Loopy code adapted for hexagonal and Penrose grids)
    * [Loop-de-Loop](http://www.deadofnight.org/?x=other)

