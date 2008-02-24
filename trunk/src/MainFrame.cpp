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

// wxWidgets:
#include "wxWidgets_standard_headers.h"
#include <wx/choicdlg.h>
#include <wx/numdlg.h>

// local:
#include "MainFrame.h"
#include "IDs.h"
#include "RuleDepictionDialog.h"
#include "DrawSlinkerGrid.h"

// STL:
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(MainFrame, wxFrame)

	// application events
	EVT_MENU(ID::Minimal_Quit,  MainFrame::OnQuit)
	EVT_MENU(ID::Minimal_About, MainFrame::OnAbout)
	EVT_PAINT( MainFrame::OnPaint)
	EVT_SIZE( MainFrame::OnSize)

	// mouse events
	EVT_LEFT_UP(MainFrame::OnLeftClick)
	EVT_RIGHT_UP(MainFrame::OnRightClick)
	
	// file menu
	EVT_MENU(ID::ExportLoopyPuzzleString,MainFrame::OnExportLoopyPuzzleString)
	EVT_MENU(ID::ImportLoopyPuzzleString,MainFrame::OnImportLoopyPuzzleString)
	
	// puzzle menu
	EVT_MENU(ID::MakeAPuzzle,MainFrame::OnMakeAPuzzle)
	EVT_MENU(ID::GiveAHint,MainFrame::OnGiveAHint)
	EVT_MENU(ID::Clear,MainFrame::OnClear)

	// actions menu
	EVT_MENU(ID::DemonstrateLoopGrowthRules,MainFrame::OnDemonstrateLoopGrowthRules)
	EVT_MENU(ID::AnalyzePuzzleDifficulty,MainFrame::OnAnalyzePuzzleDifficulty)
	EVT_MENU(ID::SearchForNewRules, MainFrame::OnSearchForNewRules)
	
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
	: working(false),
	  wxFrame(NULL, wxID_ANY, title),
	  the_solution(40,30),main_grid(40,30),
	  has_solved(true)
{
#if wxUSE_MENUS
	// create a menu bar
	wxMenuBar *menuBar = new wxMenuBar();
	
	{
		wxMenu *fileMenu = new wxMenu;
		fileMenu->Append(ID::ExportLoopyPuzzleString,_T("Export puzzle as a Loopy format string"));
		fileMenu->Append(ID::ImportLoopyPuzzleString,_T("Import a puzzle from a Loopy format string"));
		fileMenu->AppendSeparator();
		fileMenu->Append(ID::Minimal_Quit, _T("E&xit\tAlt-X"), _T("Quit this program"));
		menuBar->Append(fileMenu, _T("&File"));
	}
	
	{
		wxMenu *puzzleMenu = new wxMenu;
		puzzleMenu->Append(ID::MakeAPuzzle,_T("Make a puzzle"));
		puzzleMenu->Append(ID::Clear,_T("Clear the grid borders"));
		puzzleMenu->AppendSeparator();
		puzzleMenu->Append(ID::GiveAHint,_T("Give a hint\tF2"),_T("Show a rule that can be applied"));
		menuBar->Append(puzzleMenu, _T("&Puzzle"));
	}

	{
		wxMenu *analysisMenu = new wxMenu;
		analysisMenu->Append(ID::DemonstrateLoopGrowthRules,_T("Demonstrate the growth rules"));
		analysisMenu->Append(ID::AnalyzePuzzleDifficulty,_T("Analyze the current puzzle's difficulty"));
		analysisMenu->Append(ID::SearchForNewRules,_T("Search for new rules.."),_T("Given the existing rules, searches for more complex ones"));
		menuBar->Append(analysisMenu,_T("&Analysis"));
	}
	
	// the "About" item should be in the help menu
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(ID::Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

	// now append the freshly created menu to the menu bar...
	menuBar->Append(helpMenu, _T("&Help"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
	// create a status bar just for fun (by default with 1 pane only)
	CreateStatusBar(1);
#endif // wxUSE_STATUSBAR

}

void MainFrame::UpdateEnabledState()
{
	wxMenuBar *menu = GetMenuBar();
	if(menu==NULL) return;
	int n_menus = menu->GetMenuCount();
	for(int i=0;i<n_menus;i++)
		menu->EnableTop(i,!working);
	Update();
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

void MainFrame::OnSearchForNewRules(wxCommandEvent &event)
{
	wxBusyCursor b;
	SlinkerGrid::FindNewRules();
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	
	// recompute the drawing parameters (could store until resize or init, or perhaps a toolbar change, best to be safe?)
	wxRect r(0,0,dc.GetSize().x,dc.GetSize().y);
	ComputeDrawingCoordinates(this->main_grid,r,this->origin,this->cell_size);
	// (we store origin and size so that mouse clicks can be related to the as-last-drawn grid easily)
	
	// blank the area
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0,0,dc.GetSize().x,dc.GetSize().y);
	
	// draw the grid
	DrawGrid(this->main_grid,dc,this->origin,this->cell_size);
}

void MainFrame::OnDemonstrateLoopGrowthRules(wxCommandEvent& event)
{
	working = true;
	UpdateEnabledState();
	
	// pick a random shape
	SlinkerGrid::TGridShape gs;
	switch(rand()%3) {case 0: gs=SlinkerGrid::RectangleShape; break; case 1: gs=SlinkerGrid::MissingCentre; break; case 2: default: gs=SlinkerGrid::CircleShape; break; }
	this->main_grid = SlinkerGrid(15,21,gs);
	this->main_grid.InitGridWithSeedLoop();
	wxLogStatus(wxT("Starting with a single-cell loop..."));
	Refresh(false);
	Update();
	//wxYield();
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
		//wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT("3 rules in balance : a looser, more interesting loop..."));
	prob_divs[1]=80; // looser grid
	for(int i=0;i<N*2;i++)
	{
		this->main_grid.GrowLoop(growth_rules,prob_divs);
		Refresh(false);
		Update();
		//wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT("Rules 1 and 3 only : loop adopts minimal curvature and shrinks..."));
	prob_divs[1]=50; // shrinkage only
	for(int i=0;i<N*8;i++)
	{
		if(!this->main_grid.GrowLoop(growth_rules,prob_divs)) break;
		Refresh(false);
		Update();
		//wxMilliSleep(1);
		wxYield();
	}
	wxLogStatus(wxT(""));
	
	working = false;
	UpdateEnabledState();
}

bool MainFrame::AskUserForSolvingRulesFile()
{
	wxString filename = wxFileSelector(_T("Specify the solving rules file to use:"),_T(""),_T("*.txt"),_T("txt"),
		_T("*.txt"),wxOPEN|wxFILE_MUST_EXIST);
	if(filename.empty()) return false;
	try {
		this->solving_rules.clear();
		SlinkerGrid::ReadRulesFromFile(string(filename.fn_str()),this->solving_rules);
		return true;
	}
	catch(exception e)
	{
		wxMessageBox(wxString(e.what(),wxConvUTF8));
		return false;
	}
}

// (code from wxWidgets)
// convert wxArrayString into a wxString[] which must be delete[]d by caller
int ConvertWXArrayToC(const wxArrayString& aChoices, wxString **choices)
{
    int n = aChoices.GetCount();
    *choices = new wxString[n];

    for ( int i = 0; i < n; i++ )
    {
        (*choices)[i] = aChoices[i];
    }

    return n;
}

void MainFrame::OnMakeAPuzzle(wxCommandEvent& event)
{
	// ask user for the desired size
	wxPoint size;
	{
		const int N_SIZES=7;
		const int sizes[N_SIZES][2] = { {4,4},{5,5},{7,7},{9,9},{11,11},{15,15},{20,14} };
		wxArrayString size_choices;
		for(int i=0;i<N_SIZES;i++)
		{
			ostringstream oss;
			oss << sizes[i][0] << "x" << sizes[i][1];
			size_choices.Add(wxString(oss.str().c_str(),wxConvUTF8));
		}
		//size_choices.Add(_T("Custom")); TODO
		int iSizeChoice = wxGetSingleChoiceIndex(_T("What size of puzzle do you want?"),_T("Specify size:"),size_choices);
		if(iSizeChoice==-1) return; // user cancelled
		//if(iSizeChoice<N_SIZES)
			size = wxPoint(sizes[iSizeChoice][0],sizes[iSizeChoice][1]);
		//else {
			// TODO: support custom size
		//}
	}
	SlinkerGrid::TGridShape grid_shape;
	{
		wxArrayString choices;
		choices.Add(_T("rectangle - the standard shape"));
		choices.Add(_T("missing centre - a rectangle with a missing central area"));
		choices.Add(_T("disk - the grid squares lie inside a circle"));
		wxString *strings;
		int n = ConvertWXArrayToC(choices, &strings);
		wxSingleChoiceDialog dialog(this, _T("Select the puzzle shape:"), _T("Select from:"), n, strings);
		dialog.SetSize(400,200);
		if ( dialog.ShowModal() == wxID_OK )
		{
			switch(dialog.GetSelection())
			{
				default:
				case 0: grid_shape = SlinkerGrid::RectangleShape; break;
				case 1: grid_shape = SlinkerGrid::MissingCentre; break;
				case 2: grid_shape = SlinkerGrid::CircleShape; break;
			}
		}
		else
			return; // user cancelled
		delete []strings;
		// (wxGetSingleChoiceIndex ignores the size parameters passed)
    }
	// ask user for the ruleset (or just use the current one)
	if(!AskUserForSolvingRulesFile()) return;
	// ask user whether brute-force solving is also allowed
	bool guessing_allowed;
	{
		wxArrayString choices;
		choices.Add(_T("no brute force - puzzles will be fully deducible, and easier"));
		choices.Add(_T("brute-force used - puzzles will be harder to solve and may require back-tracking"));
		wxString *strings;
		int n = ConvertWXArrayToC(choices, &strings);
		wxSingleChoiceDialog dialog(this, _T("Select the puzzle type:"), _T("Select from:"), n, strings);
		dialog.SetSize(600,200);
		if ( dialog.ShowModal() == wxID_OK )
			guessing_allowed = (dialog.GetSelection()==1);
		else
			return; // user cancelled
		delete []strings;
		// (wxGetSingleChoiceIndex ignores the size parameters passed)
    }

	wxLogStatus(_T("Working... (may take some time for larger puzzles)"));
	wxBusyCursor busy;
	working=true;
	UpdateEnabledState();
	
	SlinkerGrid g(size.x,size.y,grid_shape);
	g.MakePuzzle(this->solving_rules,guessing_allowed);
	this->the_solution = g;
	g.ClearBorders();
	this->main_grid = g;
	this->has_solved=false;
	
	wxLogStatus(_T(""));
	Refresh(false);
	working=false;
	UpdateEnabledState();
}

wxPoint MainFrame::GetGridCoords(wxPoint p)
{
	// convert pixels to grid coordinates, using the origin and cell_size as last drawn
	double px,py;
	px = 2.0 * (p.x - this->origin.x ) / this->cell_size;
	py = 2.0 * (p.y - this->origin.y ) / this->cell_size;
	wxPoint gp = wxPoint(wxRound(px),wxRound(py));
	return gp;
}

void MainFrame::OnLeftClick(wxMouseEvent& event)
{
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
	if(this->the_solution.GetX()!=X || this->the_solution.GetY()!=Y) return; // we haven't been given the solution
	int x,y;
	for(x=0;x<2*X+1 && all_correct;x++)
	{
		for(y=0;y<2*Y+1 && all_correct;y++)
		{
			if(this->main_grid.IsOnGrid(x,y) && this->main_grid.IsBorder(x,y))
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
	if(this->main_grid.GetGridShape() != SlinkerGrid::RectangleShape)
	{
		wxMessageBox(_T("Non-rectangular puzzles not supported."));
		return;
	}
	
	// (we don't want to get any text but this dialog allows them to copy out the string
	wxGetTextFromUser(_T("(copy and paste this text into Loopy)"),_T("Puzzle as a Loopy format string:"),
		wxString(this->main_grid.GetPuzzleInLoopyFormat().c_str(),wxConvUTF8));
}

void MainFrame::OnAnalyzePuzzleDifficulty(wxCommandEvent& event)
{
	this->solving_rules.clear();
	AskUserForSolvingRulesFile(); // (they can cancel, and we will try to solve without rules, which might be slow)
	
	wxBusyCursor busy;
	wxLogStatus(wxT("Working..."));
	working=true;
	UpdateEnabledState();
	
	wxMessageBox(wxString(this->main_grid.GetPuzzleAnalysis(this->solving_rules).c_str(),wxConvUTF8));
	
	wxLogStatus(wxT(""));
	working=false;
	UpdateEnabledState();
}

void MainFrame::OnClear(wxCommandEvent &event)
{
	this->main_grid.ClearBorders();
	Refresh();
}

void MainFrame::OnGiveAHint(wxCommandEvent& event)
{
	if(this->solving_rules.empty() && !AskUserForSolvingRulesFile()) return;
	int iRule,iSymmetry;
	wxPoint pos;
	bool found_one = this->main_grid.GetAValidMove(this->solving_rules,iRule,pos,iSymmetry);
	if(found_one)
	{
		if(false)
		{
			// apply the rule
			this->main_grid.ApplyRule(this->solving_rules[iRule],pos,iSymmetry);
			Refresh(false);
			Update();
		}
		if(true) // show the user the rule we used
		{
			SlinkerGrid req,impl;
			SlinkerGrid::GetBeforeAndAfterGridsForRule(this->solving_rules[iRule],req,impl);
			if(false)
			{
				ostringstream oss;
				oss << req.GetPrintOut() << "\n\n (" << pos.x << "," << pos.y << "\nsymm:" << iSymmetry;
				wxMessageBox(wxString(oss.str().c_str(),wxConvUTF8)); // TODO: not much use in a proportional font...
			}
			else
			{
				RuleDepictionDialog dlg(this,wxID_ANY,_T("Rule:"),req,impl);
				dlg.ShowModal();
			}
		}
	}
	else
		wxMessageBox(_T("Found no rule that could be applied."));
}

void MainFrame::OnImportLoopyPuzzleString(wxCommandEvent& event)
{
	wxString s = wxGetTextFromUser(_T("(paste the Loopy puzzle string here)"),_T("Import puzzle from a Loopy format string:"),
		_T(""));
	if(s.empty()) return; // user cancelled
	this->main_grid = SlinkerGrid::ReadFromLoopyFormat(string(s.fn_str()));
	this->the_solution = SlinkerGrid(); // just so we know it is empty
	Refresh(false);
}
