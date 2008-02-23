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

// wxWidgets
#include "wxWidgets_standard_headers.h"

// local
#include "SlinkerGrid.h"

class RuleDepictionDialog : public wxDialog
{
	public:
	
		RuleDepictionDialog(wxWindow* parent, wxWindowID id, const wxString& title,const SlinkerGrid& before,
			const SlinkerGrid& after);
		
		void OnPaint(wxPaintEvent& event);
		
	protected:
	
		const SlinkerGrid &req;
		const SlinkerGrid &impl;

		// any class wishing to process wxWidgets events must use this macro
		DECLARE_EVENT_TABLE()
};
