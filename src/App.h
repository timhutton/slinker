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

/// the main application class for Slinker's GUI
class App : public wxApp
{
public:
	
	/// when the application is initialized the wxWidgets framework calls this function
	virtual bool OnInit();

	/// this function creates the message-processing loop for the application
	virtual int OnRun();
	
	/// testing something
	int dummy;
};

