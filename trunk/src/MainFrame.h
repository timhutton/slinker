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

/// the main window of the application
class MainFrame : public wxFrame
{
public:
	/// ctor(s)
	MainFrame(const wxString& title);

	/// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSearchForSolutions(wxCommandEvent& event);
	void OnSearchForPuzzles(wxCommandEvent& event);
	void OnSearchForNewRules(wxCommandEvent& event);
	
	/// debug
	void OnTestLoopyFormat(wxCommandEvent& event);

private:

	// any class wishing to process wxWidgets events must use this macro
	DECLARE_EVENT_TABLE()
};

