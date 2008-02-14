/*
	Slinker - Copyright (C) 2008 Tim Hutton, tim.hutton@gmail.com, http://www.sq3.org.uk

	This file is part of Slinker.

	Slinker is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Slinker is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Slinker.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MainFrame.h"
#include "IDs.h"

#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

#include <math.h>

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MainFrame, wxFrame)

	// application events
	EVT_MENU(ID::Minimal_Quit,  MainFrame::OnQuit)
	EVT_MENU(ID::Minimal_About, MainFrame::OnAbout)
	EVT_PAINT( MainFrame::OnPaint)
	EVT_SIZE( MainFrame::OnSize)

	// file menu
	EVT_MENU(ID::ExportLoopyPuzzleString,MainFrame::OnExportLoopyPuzzleString)
	
	// tools menu
	EVT_MENU(ID::DemonstrateLoopGrowthRules,MainFrame::OnDemonstrateLoopGrowthRules)
	EVT_MENU(ID::MakeAnEasyPuzzle,MainFrame::OnMakeAnEasyPuzzle)

	// actions menu
	EVT_MENU(ID::SearchForSolutions, MainFrame::OnSearchForSolutions)
	EVT_MENU(ID::SearchForPuzzles, MainFrame::OnSearchForPuzzles)
	EVT_MENU(ID::SearchForNewRules, MainFrame::OnSearchForNewRules)
	
	// mouse events
	EVT_LEFT_UP(MainFrame::OnLeftClick)
	EVT_RIGHT_UP(MainFrame::OnRightClick)
	
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title),the_solution(40,30),main_grid(40,30),
	has_solved(true)
{
#if wxUSE_MENUS
	// create a menu bar
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(ID::ExportLoopyPuzzleString,_T("Export puzzle as a Loopy format string"));
	fileMenu->AppendSeparator();
	fileMenu->Append(ID::Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

	wxMenu *actionsMenu = new wxMenu;
	actionsMenu->Append(ID::SearchForSolutions,_T("Search for solutions.."),_T("Searches for solutions"));
	actionsMenu->Append(ID::SearchForPuzzles,_T("Search for puzzles.."),_T("Searches for puzzles with unique solutions"));
	actionsMenu->Append(ID::SearchForNewRules,_T("Search for new rules.."),_T("Given the existing rules, searches for more complex ones"));
	
	wxMenu *toolsMenu = new wxMenu;
	toolsMenu->Append(ID::MakeAnEasyPuzzle,_T("Make an easy puzzle"));
	toolsMenu->Append(ID::DemonstrateLoopGrowthRules,_T("Demonstrate the growth rules"));
	
	// the "About" item should be in the help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(ID::Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, _T("&File"));
	menuBar->Append(toolsMenu,_T("&Tools"));
	menuBar->Append(actionsMenu, _T("&Actions"));
	menuBar->Append(helpMenu, _T("&Help"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(1);
#endif // wxUSE_STATUSBAR

}


// event handlers

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format(
					_T("Uses: %s\n")
					_T("\n")
					_T("Currently running under: %s.")
					_T("\n\nSlinker is free software, released under GPLv3.")
					_T("\n\nhttp://code.google.com/p/slinker/"),
					wxVERSION_STRING,
					wxGetOsDescription().c_str()
				),
				_T("About Slinker"),
				wxOK | wxICON_INFORMATION,
				this);
}

	// slitherlink:
	// 2d square lattice of values: 0,1,2,3 (usually provided at start of puzzle and fixed)
	// borders of squares take values: 0,1 (unbonded or bonded)
	// also a special value for each: -1 (entry unknown)
	// borders are linked in one continuous loop, with no crossovers

	// slitherlink is NP-complete: checking that problems have unique solutions gets very expensive with
	// increasing size. but for a given size, e.g. 7x7, we should be able to find enough optimisations
	// to be able to find unique-solution puzzles

	// problem 1: given a blank world, with N numbers near the middle/corners/sides, 
	// what 'rules' are there for 0, 1, 2, 3 entries provided?
	// (e.g. 3 above 3 means we know there are 3 horizontal borders turned on)

	// problem 2: can we solve all published worlds by exhaustive search in reasonable time? 
	// can we use the rules to speed up the search? so far;yes

	// problem 4: can we generate puzzles that have unique solutions? yes

	// problem 5: can we generate puzzles with a minimal number of entries provided for the size? well, for a given loop, yes.

	// problem 6: can we generate puzzles that are directly solvable without having to follow alternatives? yes, by simply turning
	//            off recursion in our solver - this yields nicer puzzles without increasing the number of entries required, intriguingly. 
	//            => the 'unwritten' rules of slitherlink: 0) each puzzle has a unique solution. -1) each puzzle is solvable 
	//            without having to explore possibilities.

	// problem: can we cast the search problem as a CA?

	// problem: any even-number-sized square grid with a full diagonal of 2's with all their border-pairs pointing the same way 
	//          has at least one other solution (with border-pairs pointing the other way), hence don't make good puzzles.
	//          (BTW, any *odd*-number-sized square grid with a full diagonal of 2's has no solutions.) 
	//          What other such quirks exist?

/* the first locally minimal 10x10 found with this program (~30mins): (back-tracking necessary to solve)

+     +     +     +     +  -  +     +     +  -  +     +     +  
1           1        |  3  |        1  |  3  |        1     
+  -  +     +  -  +  -  +     +     +     +     +  -  +  -  +  
|     |     |  2     1     2  |           |                 |  
+     +  -  +     +     +  -  +     +     +  -  +  -  +     +  
|              1        |                          3  |     |  
+     +     +  -  +  -  +     +  -  +  -  +  -  +  -  +     +  
|        1  |                 |  2     1     2              |  
+     +     +  -  +  -  +  -  +     +     +  -  +  -  +  -  +  
|              1                       2  |        2     1     
+  -  +     +     +     +     +  -  +  -  +     +  -  +     +  
3  |  1           1     1  |                 |     |        
+  -  +     +  -  +  -  +     +  -  +     +  -  +     +  -  +  
|           |           |  1     3  |     |        0     2  |  
+     +     +     +  -  +     +  -  +     +  -  +     +     +  
|  1        |     |  3        |  3           3  |  1        |  
+     +     +     +  -  +     +  -  +  -  +  -  +     +     +  
|           |  1        |  1           2     1           2  |  
+     +  -  +     +     +     +  -  +  -  +     +     +  -  +  
|  3  |                 |  3  |  2        |           |  2     
+  -  +     +     +     +  -  +     +     +  -  +  -  +     +  
(but this is *hard* for humans since it requires extensive back-tracking)

A 30x30 grid that the computer can solve by just applying rules: (otherwise locally minimal)
+     +  -  +  -  +  -  +  -  +  -  +     +  -  +     +     +     +     +     +     +     +     +  -  +  -  +  -  +  -  +     +  -  +     +  -  +     +     +     +  -  +  -  +     +  
	|  3     1           2        |     |     |                          0                 1  |  2                 2  |     |     |     |  3  |                 |        2  |  2     
+     +  -  +     +  -  +  -  +     +     +     +  -  +     +  -  +     +     +  -  +     +     +     +  -  +  -  +     +     +     +  -  +     +  -  +     +  -  +     +     +  -  +  
			|  3  |        3  |     |  2  |  1     2  |     |  3  |        2  |     |           |  2  |        3  |  2  |     |  1           1     3  |  2  |  2           1     2  |  
+     +     +  -  +     +  -  +     +     +     +     +  -  +     +  -  +  -  +     +  -  +     +     +     +  -  +     +     +     +  -  +  -  +  -  +     +     +     +  -  +     +  
					1  |        2  |  2  |  2                 0                       2  |     |     |  2  |        1  |     |     |              1        |        2  |     |     |  
+     +  -  +     +     +     +  -  +     +  -  +     +     +     +     +  -  +  -  +     +     +  -  +     +     +     +     +     +  -  +  -  +     +     +  -  +  -  +     +     +  
	|  3  |  1        |     |              2  |  2                 1  |  2        |     |        1     2  |        2  |  2  |  2     2        |                    2     2  |  2  |  
+     +     +     +  -  +     +  -  +  -  +     +  -  +  -  +  -  +     +     +     +     +  -  +     +  -  +     +  -  +     +  -  +  -  +     +     +  -  +     +  -  +  -  +     +  
	|     |  3  |        1           2  |  2                 2  |  2  |           |  1     2  |  2  |  2        |  3                    |     |     |  3  |     |        1     1  |  
+     +     +  -  +     +  -  +     +     +  -  +  -  +  -  +     +     +  -  +     +     +     +     +     +     +  -  +     +  -  +     +     +  -  +     +     +     +     +     +  
1  |                 |  3  |  2     1                    |  2  |  2     3  |     |  1        |     |        0        |  2  |  3  |  3  |  1              |  3  |  1              |  
+     +     +  -  +  -  +     +  -  +  -  +     +     +  -  +     +  -  +  -  +     +     +     +     +  -  +     +  -  +     +     +  -  +     +     +     +  -  +     +     +  -  +  
1  |     |        1           1        |  1        |  3     1     2           1  |        1  |  1     2  |     |           |  1           0           1                    |  3     
+     +  -  +     +     +     +     +  -  +     +     +  -  +  -  +  -  +     +     +     +     +     +     +     +     +  -  +     +     +     +     +  -  +     +     +     +  -  +  
			1           0        |                          1     2  |  1        |        1  |  1        |  2  |     |        1           0        |     |  1                 3  |  
+  -  +  -  +  -  +     +     +     +     +  -  +  -  +  -  +     +     +     +     +     +     +     +     +     +     +  -  +  -  +  -  +     +     +     +     +  -  +     +  -  +  
|  2              |                 |     |        1     2  |           |        1  |  1        |        1  |  2  |                    3  |  1     2  |     |  3  |     |  2  |        
+     +     +  -  +     +     +  -  +     +     +     +     +     +  -  +     +     +     +  -  +     +     +     +  -  +     +  -  +  -  +     +  -  +     +  -  +     +     +     +  
|  1        |  2     0        |  3     1  |              1  |     |              2  |  2  |                 |  1     2  |     |        1        |              1     2  |  2  |        
+     +     +     +     +     +  -  +     +  -  +  -  +     +  -  +     +     +  -  +     +  -  +  -  +     +     +     +     +     +     +     +     +     +     +  -  +     +  -  +  
|  2     1  |                       |        1        |        2     1        |  3     1     1     2  |     |        2  |     |        1        |  2     1        |  2     1     3  |  
+  -  +     +  -  +  -  +  -  +  -  +     +     +  -  +     +  -  +  -  +     +  -  +  -  +     +     +  -  +     +  -  +     +  -  +  -  +     +  -  +  -  +     +     +  -  +  -  +  
	|        1     1     1           1     2  |  2        |        2  |  2              |  2     0              |  2           2        |                 |  2  |     |              
+     +     +     +     +     +  -  +  -  +  -  +     +  -  +     +     +  -  +     +     +  -  +     +  -  +  -  +     +     +  -  +     +  -  +  -  +     +     +     +  -  +  -  +  
	|  2     0              |        2     2        |  3     1           2  |        0        |     |              1        |  3  |  2     1        |     |  2  |  2           2  |  
+     +  -  +     +     +     +  -  +  -  +  -  +     +  -  +  -  +  -  +     +     +     +  -  +     +     +     +  -  +     +     +  -  +     +     +     +     +  -  +  -  +     +  
0        |                          2     2  |  2     1     1        |  2  |  1        |        1  |  1        |  3  |     |  1        |           |  2  |  1           3  |     |  
+     +     +     +  -  +     +     +  -  +     +  -  +     +     +     +     +     +     +     +     +     +  -  +     +  -  +     +     +  -  +  -  +     +     +  -  +  -  +     +  
		1  |     |  3  |  2        |  3  |           |        1        |  2  |  1     2  |  1        |     |        0           1                 1        |     |  3           2  |  
+     +     +  -  +     +  -  +  -  +     +     +     +  -  +  -  +  -  +     +     +  -  +     +     +  -  +     +     +  -  +  -  +  -  +     +     +  -  +     +  -  +  -  +  -  +  
					0     1           1  |        1           2           1  |  2  |              0           1        |  2           2  |  1        |  3           2           2     
+     +     +     +     +     +  -  +     +  -  +  -  +  -  +  -  +  -  +     +     +  -  +  -  +     +  -  +  -  +  -  +     +     +     +     +     +  -  +  -  +  -  +  -  +  -  +  
0     0                 2  |     |        1     2                 3  |     |              2  |     |        1     1     1           2  |  1     0           2                 3  |  
+     +     +  -  +  -  +  -  +     +     +     +  -  +  -  +  -  +  -  +     +  -  +  -  +     +     +     +     +     +  -  +     +  -  +     +     +  -  +  -  +  -  +  -  +  -  +  
		1  |        1              |        1  |  2           1           0              |     |     |        1     2  |  3  |     |        0     1  |        1     1           1     
+     +     +  -  +     +     +  -  +     +     +     +     +     +     +     +  -  +     +  -  +     +  -  +  -  +  -  +     +     +     +     +     +     +     +     +  -  +     +  
0              |        1  |        1        |  2                       1  |  3  |              1     1     1              |     |  1           1  |  2     1        |     |        
+     +  -  +     +  -  +     +  -  +  -  +     +  -  +     +  -  +     +     +     +  -  +  -  +  -  +     +     +     +     +     +     +  -  +     +  -  +  -  +  -  +     +     +  
	|  3  |           |              2  |  2        |     |  3  |  1        |                    2  |  2           0        |     |  2  |  3  |  2                       2  |  1     
+     +     +  -  +     +     +     +     +  -  +  -  +     +     +     +     +  -  +  -  +  -  +     +  -  +  -  +     +  -  +     +     +     +  -  +  -  +  -  +     +  -  +     +  
	|  1        |     |  1     1     1                    |     |  1           2     2        |        1        |  2  |        1  |     |  2     2           3  |     |  3           
+     +     +     +     +     +  -  +  -  +  -  +  -  +     +     +     +  -  +  -  +  -  +     +     +     +     +     +     +     +     +  -  +  -  +     +  -  +     +  -  +     +  
	|        1  |     |     |  2     1     2     2  |  3  |     |  2  |  3     2     2  |     |  1     1        |  2  |           |  1              |     |        0        |        
+     +     +     +     +  -  +     +     +  -  +     +  -  +     +     +  -  +  -  +     +  -  +     +  -  +  -  +     +  -  +     +     +     +     +     +  -  +     +     +  -  +  
2  |  1        |  2                    |  3  |                 |              3  |        1        |                       |  2  |  2     0        |  1        |              2  |  
+  -  +     +     +  -  +  -  +     +  -  +     +     +     +  -  +     +     +  -  +     +     +     +     +  -  +  -  +  -  +     +  -  +     +     +     +     +     +  -  +     +  
|  3     1           2     2  |     |        2  |           |              1  |  3                    |     |  3                          |           |  2     1  |  2  |  3  |     |  
+  -  +  -  +  -  +  -  +     +  -  +     +  -  +     +  -  +     +  -  +     +  -  +  -  +  -  +     +     +  -  +     +  -  +  -  +  -  +     +     +  -  +     +     +     +     +  
		1           3  |                 |  3        |  3     2  |  3  |        1              |  2  |        3  |     |  3     1     1                    |     |     |     |  3  |  
+     +     +     +  -  +     +     +     +  -  +     +  -  +  -  +     +     +     +     +     +     +  -  +  -  +     +  -  +     +     +  -  +  -  +     +     +  -  +     +  -  +  
				|        0     0     0     2  |        1     1        |                    2  |  1                 1        |        1  |  2        |     |  1     2     0           
+     +  -  +     +     +     +     +     +     +  -  +     +     +  -  +     +  -  +  -  +  -  +     +  -  +  -  +  -  +  -  +     +     +     +     +     +     +  -  +     +     +  
1  |  3  |     |                          1        |  2     2  |  2        |  2           1        |  3                       0        |           |     |  3  |  3  |        0     
+     +     +  -  +     +     +  -  +  -  +  -  +     +  -  +  -  +     +  -  +     +  -  +     +     +  -  +  -  +     +  -  +     +  -  +     +     +     +  -  +     +  -  +     +  
1  |        1     1        |              2  |  2                 1  |           |  3  |              1     2  |  3  |     |     |  3           1  |  2           0        |        
+     +     +     +  -  +     +  -  +  -  +     +  -  +  -  +  -  +     +  -  +  -  +     +     +  -  +     +     +  -  +     +     +  -  +     +     +  -  +     +     +     +     +  
	|           |  3  |        2        |        1           3  |  1     1           1  |     |  3  |        1              |  1        |              3  |              1  |        
+  -  +     +  -  +     +  -  +  -  +     +  -  +     +  -  +  -  +     +     +     +     +  -  +     +  -  +  -  +     +     +     +     +  -  +     +  -  +     +  -  +     +     +  
|  3        |  2     0     1     2  |           |  2  |        2     1     1                       1           3  |  1        |        1     3  |     |        2  |     |  3  |        
+  -  +  -  +     +     +     +     +  -  +  -  +     +  -  +  -  +  -  +  -  +  -  +  -  +  -  +  -  +  -  +  -  +     +     +  -  +  -  +  -  +     +  -  +  -  +     +  -  +     +  

*/

void MainFrame::OnSearchForSolutions(wxCommandEvent &event)
{
	wxBusyCursor busy;

	/* the first published puzzle solved with this program, from puzzle-loop */
	SlinkerGrid g1(5,5);
	g1.cellValue(1,0)=2;
	g1.cellValue(4,0)=3;
	g1.cellValue(1,1)=2;
	g1.cellValue(2,1)=2;
	g1.cellValue(2,2)=0;
	g1.cellValue(3,2)=3;
	g1.cellValue(0,3)=1;
	g1.cellValue(4,3)=2;

	// early CG puzzle : hard
	SlinkerGrid g2(6,5);
	g2.cellValue(0,0)=g2.cellValue(1,0)=g2.cellValue(2,0)=g2.cellValue(4,0)=g2.cellValue(5,0)=2;
	g2.cellValue(4,1)=3;
	g2.cellValue(0,2)=1;
	g2.cellValue(1,2)=0;
	g2.cellValue(4,2)=1;
	g2.cellValue(2,3)=2;
	g2.cellValue(4,3)=2;
	g2.cellValue(5,3)=3;
	g2.cellValue(0,4)=g2.cellValue(2,4)=g2.cellValue(4,4)=1;

	// early CG puzzle: medium
	SlinkerGrid g3(6,5);
	g3.cellValue(1,0)=3;
	g3.cellValue(2,0)=3;
	g3.cellValue(4,0)=1;
	g3.cellValue(0,1)=2;
	g3.cellValue(4,1)=1;
	g3.cellValue(0,2)=2;
	g3.cellValue(3,2)=2;
	g3.cellValue(5,2)=1;
	g3.cellValue(2,3)=3;
	g3.cellValue(4,3)=2;
	g3.cellValue(5,3)=1;
	g3.cellValue(0,4)=3;
	g3.cellValue(2,4)=1;
	g3.cellValue(3,4)=2;
	g3.cellValue(4,4)=3;
	g3.cellValue(5,4)=1;

	// CG puzzle
	SlinkerGrid g4(7,7);
	g4.cellValue(0,0)=2;
	g4.cellValue(3,0)=2;
	g4.cellValue(1,1)=2;
	g4.cellValue(4,1)=3;
	g4.cellValue(6,1)=3;
	g4.cellValue(3,2)=1;
	g4.cellValue(5,2)=1;
	g4.cellValue(2,3)=1;
	g4.cellValue(4,3)=1;
	g4.cellValue(5,3)=0;
	g4.cellValue(6,3)=2;
	g4.cellValue(0,4)=2;
	g4.cellValue(5,4)=1;
	g4.cellValue(6,4)=3;
	g4.cellValue(2,5)=1;
	g4.cellValue(4,5)=3;
	g4.cellValue(5,5)=1;
	g4.cellValue(1,6)=3;
	g4.cellValue(2,6)=1;
	g4.cellValue(5,6)=1;

	SlinkerGrid g5(3,3);
	//g5.cellValue(0,0)=3;
	//g5.cellValue(1,0)=2;

	SlinkerGrid g6(5,5); // first no-guessing solution created with this program
	g6.cellValue(0,0)=2;
	g6.cellValue(1,0)=1;
	g6.cellValue(4,0)=1;
	g6.cellValue(3,1)=2;
	g6.cellValue(4,1)=1;
	g6.cellValue(0,2)=1;
	g6.cellValue(1,2)=2;
	g6.cellValue(2,2)=2;
	g6.cellValue(4,2)=1;
	g6.cellValue(0,3)=2;
	g6.cellValue(2,4)=1;
	g6.cellValue(3,4)=3;
	g6.cellValue(4,4)=1;

	SlinkerGrid g(g6);
	
	vector<SlinkerGrid::TRule> rules;

	vector<SlinkerGrid> solutions;
	solutions = g.FindSolutions(rules,true,2); // allow guessing

	if(solutions.size()==1)
	{
		wxMessageBox(wxT("Found unique solution - see log.txt"));
		ofstream out("log.txt");
		out << solutions.front().GetPrintOut();
	}
	else if(solutions.size()>1)
	{
		ostringstream oss;
		oss << "Found " << solutions.size() << " solutions - see log.txt";
		wxMessageBox(wxString(oss.str().c_str(),wxConvUTF8));
		ofstream out("log.txt");
		for(vector<SlinkerGrid>::iterator it = solutions.begin();it!=solutions.end();it++)
		{
			out << it->GetPrintOut() << "\n\n-------\n\n";
		}
	}
	else
	{
		wxMessageBox(wxT("Found no solutions"));
	}
}

void MainFrame::OnSearchForPuzzles(wxCommandEvent &event)
{
	wxBusyCursor b;
	SlinkerGrid g(10,10);
	vector<SlinkerGrid::TRule> rules;
	SlinkerGrid::ReadRulesFromFile("solving_rules_3.txt",rules);
	g.MakePuzzle(rules,false);
	string loopy = g.GetPuzzleInLoopyFormat();
	ofstream out("loopy.txt");
	out << loopy;
	wxMessageBox(wxString((loopy+"\n\n(also saved to loopy.txt)").c_str(),wxConvUTF8));
}

void MainFrame::OnSearchForNewRules(wxCommandEvent &event)
{
	wxBusyCursor b;
	SlinkerGrid::FindNewRules();
}

void MainFrame::ComputeDrawingCoordinates(const SlinkerGrid& g,wxPaintDC& dc)
{
	const int BORDER = 10;
	const int X = g.GetX();
	const int Y = g.GetY();
	this->cell_size = min((dc.GetSize().x-BORDER*2)/X,(dc.GetSize().y-BORDER*2)/Y);
	this->origin.x = dc.GetSize().x/2 - (cell_size * X)/2;
	this->origin.y = dc.GetSize().y/2 - (cell_size * Y)/2;
}

void DrawCross(wxPaintDC& dc,wxPoint p,int cell_size)
{
	wxPen offPen(wxColour(255,200,200),2);
	dc.SetPen(offPen);
	int r = cell_size/10;
	dc.DrawLine(p.x-r,p.y-r,p.x+r,p.y+r);
	dc.DrawLine(p.x-r,p.y+r,p.x+r,p.y-r);
	dc.SetPen(wxNullPen);
}

int round(float f) { return int((f-floor(f)<0.5f)?floor(f):ceil(f)); }

void MainFrame::DrawGrid(const SlinkerGrid& g,wxPaintDC& dc)
{
	// we need a better method than recomputing this each time - but how?
	this->ComputeDrawingCoordinates(g,dc);
	const int X = g.GetX();
	const int Y = g.GetY();
	// blank the area
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0,0,dc.GetSize().x,dc.GetSize().y);
	// draw the grid in light grey
	dc.SetPen(wxPen(wxColour(240,240,240)));
	int x,y;
	for(x=0;x<=X;x++)
	{
		dc.DrawLine(origin.x + cell_size*x,
			origin.y,
			origin.x + cell_size*x,
			dc.GetSize().y/2 + cell_size * Y/2+1);
	}
	for(y=0;y<=Y;y++)
	{
		dc.DrawLine(origin.x,
			origin.y + cell_size*y,
			dc.GetSize().x/2 + cell_size * X/2+1,
			origin.y + cell_size*y);
	}
	// draw the borders
	wxPen onPen(wxColour(100,100,255),3);
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(g.IsBorder(x,y) && g.gridValue(x,y)!=SlinkerGrid::UNKNOWN)
			{
				if(g.gridValue(x,y)==0)
				{
					if(g.IsHorizontalBorder(x,y))
					{
						int sx = (x-1)/2;
						int sy = y/2;
						DrawCross(dc,wxPoint(origin.x+sx*cell_size+cell_size/2,origin.y+sy*cell_size),cell_size);
					}
					else
					{
						int sx = x/2;
						int sy = (y-1)/2;
						DrawCross(dc,wxPoint(origin.x+sx*cell_size,origin.y+sy*cell_size+cell_size/2),cell_size);
					}
				}
				else
				{
					dc.SetPen(onPen);
					if(g.IsHorizontalBorder(x,y))
					{
						int sx = (x-1)/2;
						int sy = y/2;
						dc.DrawLine(origin.x+sx*cell_size,origin.y+sy*cell_size,origin.x+(sx+1)*cell_size,origin.y+sy*cell_size);
					}
					else
					{
						int sx = x/2;
						int sy = (y-1)/2;
						dc.DrawLine(origin.x+sx*cell_size,origin.y+sy*cell_size,origin.x+sx*cell_size,origin.y+(sy+1)*cell_size);
					}
				}
			}
		}
	}
	dc.SetPen(wxNullPen);
	// draw cells entries
	for(x=0;x<X;x++)
	{
		for(y=0;y<Y;y++)
		{
			if(g.cellValue(x,y)!=SlinkerGrid::UNKNOWN)
			{
				char c = '0'+g.cellValue(x,y);
				wxString str(&c,wxConvUTF8,1);
				wxSize s;
				dc.GetTextExtent(str,&s.x,&s.y);
				dc.DrawText(str,round(origin.x+cell_size*(x+0.5)-s.x/2),round(origin.y+cell_size*(y+0.5)-s.y/2));
			}
		}
	}
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	DrawGrid(this->main_grid,dc);
}

void MainFrame::OnDemonstrateLoopGrowthRules(wxCommandEvent& event)
{
	this->main_grid = SlinkerGrid(15,10);
	this->main_grid.InitGridWithSeedLoop();
	wxLogStatus(wxT("Starting with a single-cell loop..."));
	Refresh(false);
	Update();
	wxYield();
	wxSleep(3);
	vector<SlinkerGrid::TRule> growth_rules = SlinkerGrid::GetGrowthRules();
	const int N = this->main_grid.GetX() * this->main_grid.GetY() * 3;
	wxLogStatus(wxT("Rules 1 and 2 only : a maximally-filled grid is predictable..."));
	int prob_divs[]={50,100}; // tight grid
	for(int i=0;i<N;i++)
	{
		this->main_grid.GrowLoop(growth_rules,prob_divs);
		Refresh(false);
		Update();
		wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT("3 rules in balance : a looser, more interesting loop..."));
	prob_divs[1]=80; // looser grid
	for(int i=0;i<N*2;i++)
	{
		this->main_grid.GrowLoop(growth_rules,prob_divs);
		Refresh(false);
		Update();
		wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT("Rules 1 and 3 only : loop adopts minimal curvature and shrinks..."));
	prob_divs[1]=50; // shrinkage only
	for(int i=0;i<N*8;i++)
	{
		if(!this->main_grid.GrowLoop(growth_rules,prob_divs)) break;
		Refresh(false);
		Update();
		wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT(""));
}

void MainFrame::OnMakeAnEasyPuzzle(wxCommandEvent& event)
{
	long size = wxGetNumberFromUser(_T("What size of grid?"),_T("Size: (4-20)"),_T("hello"),7,4,20);
	wxString filename = wxFileSelector(_T("Specify the solving rules file to use:"),0,_T("solving_rules*.txt"),_T("txt"),
		_T("*.txt"),wxOPEN|wxFILE_MUST_EXIST);
	if(filename.empty()) return;

	wxLogStatus(_T("Working... (may take some time for larger puzzles)"));
	wxBusyCursor busy;

	vector<SlinkerGrid::TRule> rules;
	try {
		SlinkerGrid::ReadRulesFromFile(string(filename),rules);
	}
	catch(exception e)
	{
		wxMessageBox(wxString(e.what(),wxConvUTF8));
		return;
	}
	SlinkerGrid g(size,size);
	g.MakePuzzle(rules,false);
	this->the_solution = g;
	g.ClearBorders();
	this->main_grid = g;
	this->has_solved=false;
	wxLogStatus(_T(""));
	Refresh(false);
}

wxPoint MainFrame::GetGridCoords(wxPoint p)
{
	// work out which border was closest, if any
	double px,py;
	px = 2.0 * (p.x - this->origin.x ) / this->cell_size;
	py = 2.0 * (p.y - this->origin.y ) / this->cell_size;
	wxPoint gp = wxPoint(round(px),round(py));
	return gp;
}

void MainFrame::OnLeftClick(wxMouseEvent& event)
{
	// work out which border was closest, if any
	wxPoint p(this->GetGridCoords(wxPoint(event.m_x,event.m_y)));
	if(this->main_grid.IsOnGrid(p.x,p.y) && this->main_grid.IsBorder(p.x,p.y))
	{
		int val = this->main_grid.gridValue(p.x,p.y);
		if(val==SlinkerGrid::UNKNOWN) val=1;
		else if(val==1) val=0;
		else val=SlinkerGrid::UNKNOWN;
		this->main_grid.gridValue(p.x,p.y) = val;
		Refresh(false);
		CheckForSuccess();
	}
}

void MainFrame::OnRightClick(wxMouseEvent& event)
{
	// work out which border was closest, if any
	wxPoint p(this->GetGridCoords(wxPoint(event.m_x,event.m_y)));
	if(this->main_grid.IsOnGrid(p.x,p.y) && this->main_grid.IsBorder(p.x,p.y))
	{
		int val = this->main_grid.gridValue(p.x,p.y);
		if(val==SlinkerGrid::UNKNOWN) val=0;
		else if(val==0) val=1;
		else val=SlinkerGrid::UNKNOWN;
		this->main_grid.gridValue(p.x,p.y) = val;
		Refresh(false);
		CheckForSuccess();
	}
}

void MainFrame::CheckForSuccess()
{
	if(this->has_solved) return;
	bool all_correct=true;
	const int X = this->main_grid.GetX();
	const int Y = this->main_grid.GetY();
	int x,y;
	for(x=0;x<2*X+1 && all_correct;x++)
	{
		for(y=0;y<2*Y+1 && all_correct;y++)
		{
			if(this->main_grid.IsBorder(x,y))
			{
				if(this->the_solution.gridValue(x,y)==1)
				{
					if(this->main_grid.gridValue(x,y)!=1)
						all_correct = false;
				}
				else if(this->main_grid.gridValue(x,y)==1) 
					all_correct=false;
			}
		}
	}
	if(all_correct)
	{
		wxMessageBox(wxT("Completed!"));
		this->has_solved = true;
	}
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	this->Refresh(false);
	event.Skip();
}

void MainFrame::OnExportLoopyPuzzleString(wxCommandEvent& event)
{
	wxGetTextFromUser(_T("(copy and paste this text into Loopy)"),_T("Puzzle as a Loopy format string:"),
		wxString(this->main_grid.GetPuzzleInLoopyFormat().c_str(),wxConvUTF8));
}
