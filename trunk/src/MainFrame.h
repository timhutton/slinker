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

#include "wxWidgets_standard_headers.h"

#include "SlinkerGrid.h"

/// the main window of the application
class MainFrame : public wxFrame
{
public:
	/// ctor(s)
	MainFrame(const wxString& title);

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	
	// actions menu
	void OnSearchForSolutions(wxCommandEvent& event);
	void OnSearchForPuzzles(wxCommandEvent& event);
	void OnSearchForNewRules(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
	
	// tools menu
	void OnDemonstrateLoopGrowthRules(wxCommandEvent& event);
	void OnMakeAnEasyPuzzle(wxCommandEvent& event);
	
	// mouse handling
	void OnLeftClick(wxMouseEvent& event);
	void OnRightClick(wxMouseEvent& event);
	
private: // private data

	/// the grid that is drawn on the screen and worked on by the user
	SlinkerGrid main_grid;
	
	/// the grid that contains the solution to main_grid (if applicable) for quick comparison
	SlinkerGrid the_solution;
	
	/// we make a note if the current grid is solved once, to prevent multiple alerts
	bool has_solved;
	
	/// the top-left corner of the grid, in pixels
	wxPoint origin;
	int cell_size;
	
private: // private methods
	
	void DrawGrid(const SlinkerGrid& g,wxPaintDC& dc);
	void ComputeDrawingCoordinates(const SlinkerGrid& g,wxPaintDC& dc);
	wxPoint GetGridCoords(wxPoint p);
	void CheckForSuccess();

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};

