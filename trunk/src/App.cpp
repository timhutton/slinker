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

#include "App.h"
#include "MainFrame.h"

#include <exception>
using namespace std;

// some things for random number generation
#include <stdlib.h>
#include <time.h>

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. App and
// not wxApp)
IMPLEMENT_APP(App)

// 'Main program' equivalent: the program execution "starts" here
bool App::OnInit()
{
	// call the base class initialization method, currently it only parses a
	// few common command-line options but it could be do more in the future
	if ( !wxApp::OnInit() )
		return false;

	// create the main application window
	MainFrame *frame = new MainFrame(_T("Slinker"));

	// and show it (the frames, unlike simple controls, are not shown when
	// created initially)
	frame->Show(true);
	
	// seed a pseudo random number generator so we get different puzzles
	srand((unsigned int)time(NULL));

	// success: App::OnRun() will be called which will enter the main message
	// loop and the application will run. If we returned false here, the
	// application would exit immediately.
	return true;
}

int App::OnRun()
{
	try { 
		return wxApp::OnRun(); 
	}
	catch(const exception &e)
	{
		wxMessageBox(wxString(e.what(),wxConvUTF8),
			wxT("Exception thrown:"),
			wxICON_EXCLAMATION);
		return -1;
	}
	catch(...)
	{
		wxMessageBox(_T("Unknown exception."),
			wxT("Exception thrown:"),
			wxICON_EXCLAMATION);		
		return -1;
	}
}
