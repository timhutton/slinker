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

#include "DrawSlinkerGrid.h"

#include <algorithm>


void ComputeDrawingCoordinates(const SlinkerGrid& g,const wxRect& r,wxPoint& origin,int& cell_size)
{
	const int BORDER = 10;
	const int X = g.GetX();
	const int Y = g.GetY();
	cell_size = tjh_min((r.GetWidth()-BORDER*2)/X,(r.GetHeight()-BORDER*2)/Y);
	origin.x = (r.GetRight()+r.GetLeft())/2 - (cell_size * X)/2;
	origin.y = (r.GetBottom()+r.GetTop())/2 - (cell_size * Y)/2;
}

void DrawCross(wxDC& dc,wxPoint p,int cell_size)
{
	wxPen offPen(wxColour(255,200,200),2);
	dc.SetPen(offPen);
	int r = cell_size/10;
	dc.DrawLine(p.x-r,p.y-r,p.x+r,p.y+r);
	dc.DrawLine(p.x-r,p.y+r,p.x+r,p.y-r);
	dc.SetPen(wxNullPen);
}

int wxRound(float f) { return (f-floor(f)>=0.5f)?int(ceil(f)):int(floor(f)); }

void DrawGrid(const SlinkerGrid& g,wxDC& dc,wxPoint origin,int cell_size)
{
	// compute the location and size of the grid to be drawn
	const int X = g.GetX();
	const int Y = g.GetY();
	// draw the grid in light grey
	const int grid_lightness = 200;
	dc.SetPen(wxPen(wxColour(grid_lightness,grid_lightness,grid_lightness)));
	int x,y;
	for(x=0;x<=X;x++)
	{
		for(y=0;y<=Y;y++)
		{
			if(g.IsOnGrid(2*x+1,2*y+1))
			{
				dc.DrawRectangle(origin.x + cell_size*x,
					origin.y + cell_size*y,
					cell_size+1,cell_size+1);
			}
		}
	}
	// draw the borders
	wxPen onPen(wxColour(100,100,255),3);
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(g.IsOnGrid(x,y) && g.IsBorder(x,y) && g.gridValue(x,y)!=SlinkerGrid::UNKNOWN)
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
	for(x=0;x<X;x++) // note that here x and y are cell coordinates [0,X) not grid coordinates [0,2X+1)
	{
		for(y=0;y<Y;y++)
		{
			if(g.IsOnGrid(2*x+1,2*y+1) && g.cellValue(x,y)!=SlinkerGrid::UNKNOWN)
			{
				char c = '0'+g.cellValue(x,y);
				wxString str(&c,wxConvUTF8,1);
				wxSize s;
				dc.GetTextExtent(str,&s.x,&s.y);
				dc.DrawText(str,wxRound(origin.x+cell_size*(x+0.5)-s.x/2),wxRound(origin.y+cell_size*(y+0.5)-s.y/2));
			}
		}
	}
	dc.SetBrush(wxNullBrush);
}

