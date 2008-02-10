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
#include "SlinkerGrid.h"

#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID::Minimal_Quit,  MainFrame::OnQuit)
	EVT_MENU(ID::Minimal_About, MainFrame::OnAbout)

	EVT_MENU(ID::SearchForSolutions, MainFrame::OnSearchForSolutions)
	EVT_MENU(ID::SearchForPuzzles, MainFrame::OnSearchForPuzzles)
	EVT_MENU(ID::SearchForNewRules, MainFrame::OnSearchForNewRules)
	EVT_MENU(ID::TestLoopyFormat, MainFrame::OnTestLoopyFormat)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
#if wxUSE_MENUS
	// create a menu bar
	wxMenu *fileMenu = new wxMenu;

	wxMenu *actionsMenu = new wxMenu;
	actionsMenu->Append(ID::SearchForSolutions,_T("Search for solutions.."),_T("Searches for solutions"));
	actionsMenu->Append(ID::SearchForPuzzles,_T("Search for puzzles.."),_T("Searches for puzzles with unique solutions"));
	actionsMenu->Append(ID::SearchForNewRules,_T("Search for new rules.."),_T("Given the existing rules, searches for more complex ones"));
	actionsMenu->Append(ID::TestLoopyFormat,_T("Test the Loopy format code..."),_T(""));

	// the "About" item should be in the help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(ID::Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

	fileMenu->Append(ID::Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, _T("&File"));
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

	vector<SlinkerGrid> solutions;
	solutions = g.FindSolutions(true,2); // allow guessing

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
	g.MakePuzzle();
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

void MainFrame::OnTestLoopyFormat(wxCommandEvent& event)
{
	//SlinkerGrid g = SlinkerGrid::ReadFromLoopyFormat("40x30:23b3a202a33b2a3a2b3a3a3b13a333a2b21b3a1d0b22c23b21c21b1d2a3d2d131102b2h2b103131d2b22a2a2g210a211222a111g1a2a212a2a1121a2b21a012d101a13b1a1112a1a3a222b23f20b2b1b03f11b312c11b3a1a323c31a22a23c311a2a1b32b3b12e20a21c1b3c01a13e22b1a11b222g01b21b33g120b31a33a12a23312a21a2312222122a32a21213a22a23c13a2b2a23f12f11a1b2a21c22c1a2a22c31a0d3a31c00a1a2c22a2a1b12a3a21c01222012c21a1a22b2a3b1a2e1b3a2b1d2b3a3b3e1a2b1a223231a3b0b2b23b1b1b1a211131a2b3a132223a2b2b0b01b2b3b1a101232a2b2a1e0b1a2b3d2b2a2b2e2a1b3a2b13a1a12c13131212c33a1a33b1a2a31c3a3a33c12a3d2a11c10a1a1c21c11a1b2a12f32f23a3b1a22c32a21a12032a22a1131213232a31a22110a22a12a21b212g22b23b21g232b12a2b22e23a32c2b1c11a10e32b2b22b2a1a020c22a20a11c121a3a2b23c222b22f13b1b3b22f01b222a2a2a1213a1b31a132d322a21b3a1220a1a231a2a2g011a112112a222g1a1a32b3d322223b2h0b323313d2d1a3d3b22c20b21c12b2d2a3b22b3a123a13b2a2a2b3a3a1b22a012a2b12");
	SlinkerGrid g = SlinkerGrid::ReadFromLoopyFormat("10x10:1a1a3a13a1b212g1e3b1c212d1c2a2131a11i13b021b3a3a31c1a1a21a23c32c2");
	wxBusyCursor busy;
	vector<SlinkerGrid> solutions = g.FindSolutions(true,1);
	if(!solutions.empty())
	{
		ofstream out("from_loopy.txt");
		solutions.front().MarkOffBordersAsUnknown();
		out << solutions.front().GetPrintOut() << "\n\n";
		wxMessageBox(wxT("Success!"));
	}
	else
		wxMessageBox(wxT("Failed to find a solution."));
	
}
