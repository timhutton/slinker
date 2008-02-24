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
#include <wx/artprov.h>

// local
#include "RuleDepictionDialog.h"
#include "DrawSlinkerGrid.h"

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(RuleDepictionDialog, wxDialog)

	EVT_PAINT( RuleDepictionDialog::OnPaint)
	EVT_SIZE( RuleDepictionDialog::OnSize)

END_EVENT_TABLE()

const wxSize RuleDepictionDialog::initial_size(450,200);

RuleDepictionDialog::RuleDepictionDialog(wxWindow* parent, wxWindowID id, const wxString& title,
	const SlinkerGrid& before,const SlinkerGrid& after)
		: wxDialog(parent,id,title,wxPoint(0,0),initial_size,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER),
		  req(before),impl(after)
{
}
		
void RuleDepictionDialog::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	// blank the area
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawRectangle(0,0,dc.GetSize().x,dc.GetSize().y);
	// draw the two grids
	wxPoint origin;
	int cell_size;
	int one_side_size = dc.GetSize().x*initial_size.GetHeight()/initial_size.GetWidth();
	wxRect r1(0,0,one_side_size,dc.GetSize().y);
	ComputeDrawingCoordinates(req,r1,origin,cell_size);
	DrawGrid(req,dc,origin,cell_size);
	wxPoint o2(origin.x+(dc.GetSize().x-one_side_size),origin.y);
	DrawGrid(impl,dc,o2,cell_size);
	// draw an arrow in between
	wxBitmap bmp = wxArtProvider::GetBitmap(wxART_GO_FORWARD);
	dc.DrawBitmap(bmp,dc.GetSize().x/2-bmp.GetWidth()/2,dc.GetSize().y/2-bmp.GetHeight()/2);
}

void RuleDepictionDialog::OnSize(wxSizeEvent& event)
{
	this->Refresh(false);
	event.Skip();
}
