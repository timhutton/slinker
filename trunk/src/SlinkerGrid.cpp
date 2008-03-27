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

// if you want to use SlinkerGrid with your own interface then you can remove all wxWidgets specific things, including
// this include and all calls to wxLogStatus and wxMessageBox, etc. (were only there for debugging)
#include "wxWidgets_standard_headers.h"

// local:
#include "SlinkerGrid.h"
#include "next_combination.h"
#include "IndexedComparison.h"

// STL:
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <fstream>
using namespace std;

// these things here only because on MSVC5 w/ wxWidgets 2.6.2 we had compilation issues
int tjh_max(int a,int b) { return (a>b)?a:b; }
int tjh_min(int a,int b) { return (a<b)?a:b; }
int tjh_wxRound(float f) { return (f-floor(f)>=0.5f)?int(ceil(f)):int(floor(f)); }

/// ---------- statics -------------

const int SlinkerGrid::UNKNOWN = -1;
// (we should be able to put this value in the header file but gcc doesn't like it)

const int SlinkerGrid::NHOOD[4][2] = { {-1,0}, { 0,-1}, {1,0}, {0,1} };

const int SlinkerGrid::N_SYMMETRIES = 8;

const SlinkerGrid::TMatrix SlinkerGrid::SYMMETRIES[N_SYMMETRIES] = {
	TMatrix(1,0,0,1), // identity
	TMatrix(0,-1,1,0), // rotation by 90 degrees ccwise
	TMatrix(-1,0,0,-1), // rotation by 180 degrees
	TMatrix(0,1,-1,0), // rotation by 270 degrees ccwise
	TMatrix(-1,0,0,1), // reflection in x
	TMatrix(0,1,1,0), // reflection in x then 90 degrees ccwise
	TMatrix(1,0,0,-1), // reflection in x then 180 degrees
	TMatrix(0,-1,-1,0) // reflection in x then 270 degrees ccwise
};

bool SlinkerGrid::IsOdd(int a) { return (abs(a)&1)==1; } // abs here to extend test to negative numbers safely
bool SlinkerGrid::IsEven(int a) { return (abs(a)&1)==0; } 
bool SlinkerGrid::IsDot(int x,int y) { return( IsEven(x) && IsEven(y) ); }
bool SlinkerGrid::IsBorder(int x,int y) { return( IsEven(x)^IsEven(y) ); }
bool SlinkerGrid::IsCell(int x,int y) { return( IsOdd(x) && IsOdd(y) ); }
bool SlinkerGrid::IsHorizontalBorder(int x,int y) { return( IsOdd(x) && IsEven(y) ); }
bool SlinkerGrid::IsVerticalBorder(int x,int y) { return( IsEven(x) && IsOdd(y) ); }

// ---------------------------

SlinkerGrid::SlinkerGrid() : X(0),Y(0),grid_shape(RectangleShape)
{
}

SlinkerGrid::SlinkerGrid(int x,int y,TGridShape gs) 
	: X(x), Y(y), 
	grid_shape(gs)
{
	cells.assign(2*X+1,vector<int>(2*Y+1,UNKNOWN)); // init array of values all filled with UNKNOWN
}

SlinkerGrid::SlinkerGrid(const SlinkerGrid& g)
	: X(g.X),Y(g.Y),cells(g.cells),grid_shape(g.grid_shape)
{
}

SlinkerGrid& SlinkerGrid::operator=(const SlinkerGrid& g)
{
	X = g.X;
	Y = g.Y;
	cells = g.cells;
	grid_shape = g.grid_shape;
	return *this;
}

bool SlinkerGrid::operator==(const SlinkerGrid& g) const
{
	return(X==g.X && Y==g.Y && grid_shape==g.grid_shape && cells==g.cells);
}

int max(int a,int b) { return (a>b)?a:b; }
int min(int a,int b) { return (a<b)?a:b; }

bool SlinkerGrid::IsOnGrid(int x,int y) const
{
	// even non-rectangular grids are embedded in a rectangular area
	if(!(x>=0 && x<2*X+1 && y>=0 && y<2*Y+1))
		return false;

	switch(this->grid_shape)
	{
		case RectangleShape:
			{
				return true; // plain rectangle
			}
		case MissingCentre:
			{
				// rectangle with missing central ninth
				// (looks best if X and Y are divisible by 3)
				return (x<2*int(X/3)+1 || x>2*(2*int(X/3)-1)+1 || y<2*int(Y/3)+1 || y>2*(2*int(Y/3)-1)+1);
			}
		case CircleShape:
			{
				// TODO: make a test x and y, based on a square (an oval is a flattened circle)
				int tx=x,ty=y;
				//if(X<Y) tx = tx*Y/X; // TODO: this isn't quite right, we want symmetrical ovals
				//else if(Y<X) ty = ty*X/Y;
				int mid = (2*max(X,Y)+1)/2;
				int r = mid; // radius of inset circle
				
				if(false)
				{ // DEBUG
					ostringstream oss;
					oss << X << "," << Y << " grid:\n\n" << x << "," << y << " becomes " << tx << "," 
						<< ty << "\n\nmid=r=" << mid;
					wxMessageBox(wxString(oss.str().c_str(),wxConvUTF8));
				}
				if(IsCell(x,y))
					return(hypot(mid-tx,mid-ty)<=r);
				else if(IsHorizontalBorder(x,y))
					return(hypot(mid-tx,mid-(ty-1))<=r || hypot(mid-tx,mid-(ty+1))<=r);
				else if(IsVerticalBorder(x,y))
					return(hypot(mid-(tx-1),mid-ty)<=r || hypot(mid-(tx+1),mid-ty)<=r);
				else if(IsDot(x,y))
					return(hypot(mid-(tx-1),mid-(ty-1))<=r || hypot(mid-(tx+1),mid-(ty-1))<=r ||
						hypot(mid-(tx+1),mid-(ty+1))<=r || hypot(mid-(tx-1),mid-(ty+1))<=r);
			}
	}
	throw(runtime_error("Internal error: unknown grid type in IsOnGrid."));
	return false;
}

bool SlinkerGrid::IsLegal() const
{
	// test 1: does the border count match the cell value for every cell?
	int x,y;
	int cell_val,min_borders,max_borders;
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(!IsOnGrid(x,y) || !IsCell(x,y)) continue;
			cell_val = cells[x][y];
			// is cell value is unknown then this square is legal by this test
			if(cell_val == UNKNOWN) continue;
			// retrieve the possible range (given unknowns) of borders this cell might have
			GetBorderCountAroundCell(x,y,min_borders,max_borders);
			if(cell_val<min_borders || cell_val>max_borders)
				return false;
		}
	}
	// test 2: does any dot have the wrong number of borders joining it?
	for(x=0;x<2*X+1;x+=2)
	{
		for(y=0;y<2*Y+1;y+=2)
		{
			if(!IsOnGrid(x,y)) continue;
			GetBorderCountAroundDot(x,y,min_borders,max_borders);
			if(min_borders>2) // too many borders joining!
				return false;
			if(min_borders>0 && max_borders<2) // only one border comes here!
				return false;
		}
	}
	// test 3: all borders are connected
	{
		// count how many borders there are, and pick a dot that has a border
		int n_borders=0;
		vector< pair<int,int> > dots;
		for(x=0;x<2*X+1;x++)
		{
			for(y=0;y<2*Y+1;y++)
			{
				if(!IsOnGrid(x,y)) continue;
				if(IsBorder(x,y) && cells[x][y]==1) 
				{
					n_borders++;
					if(dots.empty())
					{
						if(IsHorizontalBorder(x,y))
							dots.push_back(make_pair(x-1,y));
						else
							dots.push_back(make_pair(x,y-1));
					}
				}
			}
		}
		if(n_borders==0) 
			return false; // a grid with no borders could pass tests 1 and 2 but we disallow it here
		CollectJoinedDots(dots);
		if(dots.size()!=n_borders)
			return false; // found a small loop
	}

	return true; // didn't find anything wrong
}

void SlinkerGrid::CollectJoinedDots(vector< pair<int,int> > &dots) const
{
	pair<int,int> current_dot,next_dot;
	int dir;
	int n_added;
	do
	{
		current_dot = dots.back();
		n_added=0;
		for(dir=0;dir<4;dir++)
		{
			next_dot = make_pair(current_dot.first + NHOOD[dir][0]*2,current_dot.second + NHOOD[dir][1]*2);
			if(IsOnGrid(next_dot.first,next_dot.second) && 
				cells[current_dot.first + NHOOD[dir][0]][current_dot.second + NHOOD[dir][1]]==1 &&
				find(dots.begin(),dots.end(),next_dot)==dots.end())
			{
				dots.push_back(next_dot);
				n_added++;
			}
		}
	} while(n_added>0);
}

void SlinkerGrid::MarkUnknownBordersAsOff()
{
	int x,y;
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(IsBorder(x,y) && cells[x][y]==UNKNOWN)
				cells[x][y] = 0;
		}
	}
}

void SlinkerGrid::MarkOffBordersAsUnknown()
{
	int x,y;
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(IsBorder(x,y) && cells[x][y]==0)
				cells[x][y] = UNKNOWN;
		}
	}
}

bool SlinkerGrid::IsFinished() const
{
	// not finished if any border is marked as UNKNOWN
	int x,y;
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(IsOnGrid(x,y) && IsBorder(x,y) && cells[x][y]==UNKNOWN)
				return false;
		}
	}
	return true;
} 

int& SlinkerGrid::cellValue(int x,int y)
{
	if(x<0 || x>=X || y<0 || y>=Y)
	{
		ostringstream oss;
		oss << "out of range exception in SlinkerGrid::cellValue : " << x << "," << y;
		throw(out_of_range(oss.str().c_str()));
	}
	return this->cells[2*x+1][2*y+1];
}

const int& SlinkerGrid::cellValue(int x,int y) const
{
	if(x<0 || x>=X || y<0 || y>=Y)
	{
		ostringstream oss;
		oss << "out of range exception in SlinkerGrid::cellValue : " << x << "," << y;
		throw(out_of_range(oss.str().c_str()));
	}
	return this->cells[2*x+1][2*y+1];
}

int& SlinkerGrid::gridValue(int x,int y)
{
	if(!IsOnGrid(x,y))
	{
		ostringstream oss;
		oss << "out of range exception in SlinkerGrid::gridValue : " << x << "," << y;
		throw(out_of_range(oss.str().c_str()));
	}
	return this->cells[x][y];
}

const int& SlinkerGrid::gridValue(int x,int y) const
{
	if(!IsOnGrid(x,y))
		throw(out_of_range("out of range exception in SlinkerGrid::gridValue"));
	return this->cells[x][y];
}

void SlinkerGrid::GetBorderCountAroundCell(int x,int y,int &min,int &max) const
{
	if(x<1 || x>=2*X || y<1 || y>=2*Y)
		throw(out_of_range("out of range exception in SlinkerGrid::GetBorderCountAroundCell"));
	if(!IsCell(x,y))
		throw(out_of_range("non-cell coords in SlinkerGrid::GetBorderCountAroundCell"));
	min = 0;
	max = 4;
	int b;
	for(int dir=0;dir<4;dir++)
	{
		b = cells[x+NHOOD[dir][0]][y+NHOOD[dir][1]];
		if(b==1)
			min++;
		if(b==0)
			max--;
	}
}

void SlinkerGrid::GetBorderCountAroundDot(int x,int y,int &min,int &max) const
{
	if(!IsOnGrid(x,y))
		throw(out_of_range("out of range exception in SlinkerGrid::GetBorderCountAroundDot"));
	if(!IsDot(x,y))
		throw(out_of_range("non-dot coordinates in SlinkerGrid::GetBorderCountAroundDot"));
	min = 0;
	max = 4;
	int tx,ty,b;
	for(int dir=0;dir<4;dir++)
	{
		tx = x+NHOOD[dir][0];
		ty = y+NHOOD[dir][1];
		// this location might be off the grid
		if(!IsOnGrid(tx,ty))
			max--;
		else {
			b = cells[tx][ty];
			if(b==1) 
				min++;
			else if(b==0)
				max--;
		}
	}
}

string SlinkerGrid::GetPrintOut() const
{
	ostringstream oss;
	int x,y,v;
	// make a text representation (looks best rendered in a fixed-width font)
	for(y=0;y<2*Y+1;y++)
	{
		for(x=0;x<2*X+1;x++)
		{
			if(!IsOnGrid(x,y)) // allowing for non-rectangular grids
			{
				oss << "#";
			}
			else
			{
				v = cells[x][y];
				if(IsDot(x,y))
					oss << "+";
				else if(v==UNKNOWN) // unknowns we leave blank
					oss << " ";
				else if(IsHorizontalBorder(x,y))
				{
					if(v)
						oss << "-";
					else
						oss << "x";
				}
				else if(IsVerticalBorder(x,y))
				{
					if(v)
						oss << "|";
					else
						oss << "x";
				}
				else // is a known cell entry
					oss << v; 
			}
			oss << "  ";
		}
		oss << "\n";
	}
	return oss.str();
}

void SlinkerGrid::FillGridWithRandomLoop()
{
	// method: starting with a 1-cell loop, expand using growth rules at random until satisfied
	// (the rules maintain the single loop property without having to search for it)

	InitGridWithSeedLoop();

	vector<TRule> growth_rules = GetGrowthRules();
	
	// here's a nice feature - you can choose what the loop should feel like:
	// (over 0,100 what proportions do you want the three rules in?)
	//const int prob_divs[2]={50,100}; // just use first two rules; for thin corridors, maximally-filled grid (usually unsatisfactory since predictable)
	//const int prob_divs[2]={33,66}; // for thick corridors, casually-filled grid (can leave empty areas but perhaps least predictable, and may be to your taste)
	const int prob_divs[2]={50,80}; // seems to be a reasonable balance, perhaps

	// search at random for possible applications of these rules, until bored
	int its=0;
	while(++its<X*Y*20) // there might be a more elegant method than just running for a while, but it works well and quickly enough
		GrowLoop(growth_rules,prob_divs);

	// fill in the cell counts
	int minc,maxc,x,y;
	for(x=0;x<X;x++)
	{
		for(y=0;y<Y;y++)
		{
			GetBorderCountAroundCell(x*2+1,y*2+1,minc,maxc);
			cellValue(x,y) = minc;
		}
	}
}

void SlinkerGrid::InitGridWithSeedLoop()
{
	// start with a grid full of offs
	this->Clear();
	//this->MarkUnknownBordersAsOff();
	// start with a single cell loop
	int x,y;
	do {
		x = 2*(rand()%X) + 1;
		y = 2*(rand()%Y) + 1;
	} while(!IsOnGrid(x,y)); // (need this test for non-rectangular grids)
	this->cells[x-1][y]=this->cells[x+1][y]=this->cells[x][y-1]=this->cells[x][y+1]=1;
}

bool SlinkerGrid::GrowLoop(const vector<TRule>& growth_rules,const int* prob_divs)
{
	// look in a random cell at a random orientation, for a random rule
	int n_tries=0;
	while(n_tries++<1000)
	{
		int x = 2*(rand()%X) + 1;
		int y = 2*(rand()%Y) + 1;
		int tx,ty;
		int iSymm = rand()%N_SYMMETRIES;
		int rand_p = rand()%100;
		int iRule = (rand_p<prob_divs[0])?0:((rand_p<prob_divs[1])?1:2);
		// can this rule apply?
		bool can_apply = true;
		vector<TElement>::const_iterator it;
		for(it=growth_rules[iRule].required.begin();it!=growth_rules[iRule].required.end() && can_apply;it++)
		{
			tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
			ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
			// check that this cell entry matches the required list
			if( !( (it->val==0 && !IsOnGrid(tx,ty)) || 	
				(IsOnGrid(tx,ty) && (cells[tx][ty]==it->val || (it->val==0 && cells[tx][ty]==UNKNOWN))) ) )
					can_apply = false;
		}
		// also check that all our implieds are actually on the grid
		for(it = growth_rules[iRule].implied.begin();it!=growth_rules[iRule].implied.end() && can_apply;it++)
		{
			tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
			ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
			if(!IsOnGrid(tx,ty)) // (could just check that 'on' borders are on the grid)
				can_apply=false;
		}
		if(can_apply)
		{
			for(it = growth_rules[iRule].implied.begin();it!=growth_rules[iRule].implied.end();it++)
			{
				tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
				ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
				if(IsOnGrid(tx,ty) && cells[tx][ty] != it->val)
				{
					cells[tx][ty] = (it->val==1)?1:UNKNOWN;
				}
			}
			return true;
		}
		// N.B. this is not quite the same search as ApplyRules()  - we don't worry about inconsistency, 
		// and we must search at random, and while we still treat off-grid borders as equivalent to off borders, 
		// we also have to check that we're not trying to set an off-grid border to on.
	}
	return false;
}

void SlinkerGrid::Clear()
{
	int x;
	for(x=0;x<2*X+1;x++)
	{
		fill(cells[x].begin(),cells[x].end(),UNKNOWN); 
	}
}

void SlinkerGrid::ClearBorders()
{
	int x,y;
	for(x=0;x<2*X+1;x++)
	{
		for(y=0;y<2*Y+1;y++)
		{
			if(IsOnGrid(x,y) && IsBorder(x,y))
				this->cells[x][y] = UNKNOWN;
		}
	}
}

bool SlinkerGrid::ApplyRules(const vector<TRule>& rules,vector<int*> &changed)
{
	int x,y;
	unsigned int iSymm;
	bool can_apply,did_something;
	vector<TElement>::const_iterator it;
	vector<TRule>::const_iterator rule_it;
	int tx,ty;
	changed.clear(); // don't want any previous entries
	int *pEntry;
	do 
	{
		did_something = false;
		for(rule_it = rules.begin();rule_it!=rules.end();rule_it++)
		{
			for(x=-1;x<2*X+1+1;x++) // consider rule applications to the cells around the edge too (see the elementary rules)
			{
				for(y=-1;y<2*Y+1+1;y++)
				{
					if(!IsCell(x,y)) continue;
					// does the rule apply here (centred on cell x,y) in any orientation?
					for(iSymm=0;iSymm<N_SYMMETRIES;iSymm++)
					{
						can_apply = true;
						for(it=rule_it->required.begin();it!=rule_it->required.end() && can_apply;it++)
						{
							tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
							ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
							if( !( (it->val==0 && IsBorder(tx,ty) && !IsOnGrid(tx,ty)) || 
								(IsOnGrid(tx,ty) && cells[tx][ty]==it->val) ) )
									can_apply = false;
						}
						if(!can_apply) continue;
						for(it = rule_it->implied.begin();it!=rule_it->implied.end();it++)
						{
							tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
							ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
							if(!IsOnGrid(tx,ty)) continue;
							pEntry = &cells[tx][ty];
							if(*pEntry != it->val)
							{
								if(*pEntry != UNKNOWN)
								{
									// We've found a contradiction! this means the grid was inconsistent.
									// In FollowPossibilities this means we can abandon this search avenue.
									// In FindNewRules this means we may have found a rule.
									return false; 
								}
								*pEntry = it->val;
								changed.push_back(pEntry);
								did_something = true;
							}
						}
					}
				}
			}
		}
	} while(did_something);
	
	return true; // no contradiction found
}

void SlinkerGrid::FollowPossibilities(const std::vector<TRule> &solving_rules, vector<SlinkerGrid> &solutions,
									bool guessing_allowed,unsigned int max_n_wanted_solutions)
{
	vector<int*> changed;

	// first apply whatever local rules we can
	bool grid_ok = ApplyRules(solving_rules,changed);

	if(grid_ok) // (otherwise the grid had contradictions => no solutions down this path)
	{
		if(IsFinished())
		{
			if(IsLegal() && find(solutions.begin(),solutions.end(),*this)==solutions.end())
			{
				// we have found a solution not previously found, add it to the list
				solutions.push_back(*this);
			}
		}
		else if(solutions.size()<max_n_wanted_solutions && guessing_allowed) 
			// if there are multiple valid solutions then just finding N is enough 
			// (also guessing (exploration of possibilities) must be allowed)
		{
			int x,y,onoff;
			// follow on/off possibilities for the first unassigned border we find
			bool found_one=false;
			for(x=0;(x<2*X+1 && !found_one);x++)
			{
				for(y=0;(y<2*Y+1 && !found_one);y++)
				{
					if(!IsBorder(x,y) || !IsOnGrid(x,y) || cells[x][y]!=UNKNOWN) 
						continue;
					found_one=true;
					for(onoff=0;onoff<=1;onoff++)
					{
						// a special consideration for speedup: can reject this move 
						// if it would make a loop and not a solution
						if(onoff==1 && WouldMakeALoop(x,y))
						{
							// would this move make a solution?
							SlinkerGrid test(*this);
							test.cells[x][y]=1;
							test.MarkUnknownBordersAsOff();

							if(!test.IsLegal()) // this function is slow but doing this means we can avoid a potentially enormous search avenue
								continue;
							// (if it *is* legal then we will recurse down onto this option and it will be logged as a solution)
						}
						cells[x][y]=onoff;
						FollowPossibilities(solving_rules,solutions,guessing_allowed,max_n_wanted_solutions);
					}
					// revert the test change
					cells[x][y] = UNKNOWN;
				}
			}
		}
	}

	// revert the changes made by applying the rules
	UndoChanges(changed);
}

void SlinkerGrid::UndoChanges(const vector<int*> &changed)
{
	for(vector<int*>::const_iterator it=changed.begin();it!=changed.end();it++)
		**it = UNKNOWN;
}

bool SlinkerGrid::WouldMakeALoop(int x,int y) const
{
	vector<pair<int,int> > dots;
	// add the left/above dot of this border as a starting point
	dots.push_back(IsHorizontalBorder(x,y)?make_pair(x-1,y):make_pair(x,y-1));
	CollectJoinedDots(dots);
	// if the right/below dot is already connected (N.B. border is currently off) then we have a loop
	return(find(dots.begin(),dots.end(),
		IsHorizontalBorder(x,y)?make_pair(x+1,y):make_pair(x,y+1))!=dots.end());
}

bool SlinkerGrid::HasLoop()
{
	// collect connected border into sets
	// if turning any border off leaves its dots connected then return true
	bool found_a_loop=false;
	int x,y;
	for(x=0;x<2*X+1 && !found_a_loop;x++)
	{
		for(y=0;y<2*Y+1 && !found_a_loop;y++)
		{
			if(IsBorder(x,y) && cells[x][y]==1)
			{
				// disable the border temporarily	
				cells[x][y]=0;
				// are the end dots still connected?
				if(WouldMakeALoop(x,y))
					found_a_loop = true;
				// re-enable the border
				cells[x][y]=1;
			}
		}
	}
	return found_a_loop;
}

std::vector<SlinkerGrid> SlinkerGrid::FindSolutions(const vector<TRule> &rules,bool guessing_allowed,int max_n_wanted_solutions) const
{
	// find some solutions
	vector<SlinkerGrid> solutions;
	SlinkerGrid g(*this);
	g.FollowPossibilities(rules,solutions,guessing_allowed,max_n_wanted_solutions);
	return solutions;
}

void SlinkerGrid::MakePuzzleByRemovingRandomClues(const vector<TRule>& rules,bool guessing_allowed)
{
	bool no_unique_solutions = false;
	do
	{
		// first fill the grid with a nice loop
		FillGridWithRandomLoop();
	
		// now try removing numbers one by one, as long as they still give us a unique solution
	
		vector<SlinkerGrid> solutions;
		vector< pair< pair<int,int>, int> > entries,test_entries; // x,y,value
		SlinkerGrid puzzle_solution(*this);
	
		// retrieve the entries from the grid
		int x,y;
		for(x=0;x<X;x++)
			for(y=0;y<Y;y++)
				if(cellValue(x,y)!=UNKNOWN)
					entries.push_back(make_pair(make_pair(x,y),cellValue(x,y)));
		int n_original_entries = entries.size();
	
		SlinkerGrid pad(*this);
		bool still_looking=true;
		unsigned int iRemove,iEntry;
		while(still_looking)
		{
			still_looking = false; 
			// shuffle the entries (don't want to have all the numbers on one side; and first few entries are likely necessary from previous rounds)
			random_shuffle(entries.begin(),entries.end());
			// try removing each one in turn, if it still gives a unique solution then we're done at this level
			for(iRemove=0;(iRemove<entries.size() && !still_looking);iRemove++)
			{
				// collect all-but-one of the entries into the test_entries list
				test_entries.clear();
				for(iEntry=0;iEntry<entries.size();iEntry++)
				{
					if(iEntry != iRemove)
						test_entries.push_back(entries[iEntry]);
				}
				// write these test_entries to a blank grid
				pad.Clear();
				for(vector<pair<pair<int,int>,int> >::const_iterator it=test_entries.begin();it!=test_entries.end();it++)
					pad.cellValue(it->first.first,it->first.second)=it->second;
				// do these test_entries still give us a unique solution?
				solutions = pad.FindSolutions(rules,guessing_allowed,2);
				if(solutions.size()==1)
				{
					// this'll do! (could search other avenues too but no real need unless you want to be sure it's a global minimum)
					entries = test_entries;
					puzzle_solution = solutions.front();
					still_looking=true;
				}
			}
		}
		if(entries.size()==n_original_entries)
		{
			// we've just hit on a rare case where even with all numbers there are no unique solutions.
			// we just set this flag to try again
			no_unique_solutions = true;
		}
		else
		{
			// ok, we're done, lets take a copy of the solution and go
			*this = puzzle_solution;
			MarkOffBordersAsUnknown(); // for pretty printing
			no_unique_solutions = false;
		}
	} while(no_unique_solutions);
}

void SlinkerGrid::MakePuzzleByAddingClues(const vector<TRule>& rules,bool guessing_allowed)
{
	SlinkerGrid the_solution;

	// first find a loop that gives a unique solution if all clues are given
	while(true)
	{
		// first fill the grid with a nice loop
		FillGridWithRandomLoop();
	
		ClearBorders();
		vector<SlinkerGrid> solutions = FindSolutions(rules,true,2);
		if(solutions.size()==1) 
		{
			the_solution = solutions.front();
			break;
		}
	}
	
	// compute the difficulty of each rule and sort them
	vector<TRule> sorted_rules(rules);
	vector<double> sorted_rule_difficulty;
	SortRulesByIncreasingDifficulty(sorted_rules,sorted_rule_difficulty);
	
	// now add clues one by one until the solution is implied (hence unique)
	Clear();
	bool all_done;
	vector<int*> changed;
	int n_added=0;
	int x,y;
	int tx,ty;
	while(true)
	{
		{
			ostringstream oss;
			oss << "Added " << n_added++ << " clues...";
			wxLogStatus(wxString(oss.str().c_str(),wxConvUTF8));
		}
		// collect a list of clues we could add that give us something useful
		vector<wxPoint> candidates;
		for(x=0;x<X;x++)
		{
			for(y=0;y<Y;y++)
			{
				if(!IsOnGrid(2*x+1,2*y+1) || cellValue(x,y)!=UNKNOWN) continue;
				// would this clue give us something useful?
				cellValue(x,y) = the_solution.cellValue(x,y);
				ApplyRules(sorted_rules,changed);
				if(!changed.empty())
				{
					UndoChanges(changed);
					candidates.push_back(wxPoint(x,y));
				}
				cellValue(x,y) = UNKNOWN;
			}
		}
		
		if(candidates.empty())
			break; // no clues would help - we're done (though might not be solvable...!)
		
		{
			// simply take one at random (until we find a better one)
			int i = rand() % candidates.size();
			x = candidates[i].x;
			y = candidates[i].y;
		}
		
		// decide which clue to add
		{
			// compute the max difficulty level of the rules that can be applied for each candidate clue
			double greatest_diff=0.0,diff;
			// take the clue that calls for the most difficult rules
			vector<TRule> ruleset;
			for(vector<wxPoint>::const_iterator cand_it=candidates.begin();cand_it!=candidates.end();cand_it++)
			{
				ruleset.clear();
				for(vector<TRule>::const_iterator r_it=sorted_rules.begin();r_it!=sorted_rules.end();r_it++)
				{
					ruleset.push_back(*r_it);
					ApplyRules(ruleset,changed);
					if(!changed.empty())
					{
						diff = sorted_rule_difficulty[r_it-sorted_rules.begin()];
						if(diff>greatest_diff)
						{
							greatest_diff = diff;
							x = cand_it->x;
							y = cand_it->y;
						}
						UndoChanges(changed);
					}
				}
			}
		}
		
		// add the clue and see how far it gets us
		cellValue(x,y) = the_solution.cellValue(x,y);
		ApplyRules(rules,changed);
		// if every "on" border of the_solution is now present, we're done
		all_done=true;
		for(tx=0;tx<2*X+1 && all_done;tx++)
		{
			for(ty=0;ty<2*Y+1 && all_done;ty++)
			{
				if(IsBorder(tx,ty) && IsOnGrid(tx,ty) && the_solution.gridValue(tx,ty)==1 && gridValue(tx,ty)!=1)
					all_done = false;
			}
		}
		if(all_done) break;
	}
}

// compute the binomial coefficient "m choose n" (e.g. 100 choose 2 = 4950; 6 choose 4 = 15)
// (isn't there a function for this?)
unsigned choose(unsigned long m, unsigned long n) 
{
	unsigned long r = 1l;
	unsigned long d;
	if (n > m) return 0l;
	for (d=1l; d <= n; d++) {
		r *= m--;
		r /= d;
	}
	return r;
}

void SlinkerGrid::FindNewRules() // static
{
	// for a test grid NxN, find layouts of M cell/border entries (bounded by UNKNOWNS) that
	// don't allow any existing rules to be applied, and then:
	
	// approach 1: for each UNKNOWN border, try on/off and see if applying all the other rules leads to a contradiction.
	// if so, then we have a simple rule. complete for all borders, report our new found rule. This works extremely well,
	// apart from missing certain (rare?) rules that need a depth of recursion, eg:
	
	/*         +   +   +   +           +   +   +   +
					2                       2
			+   +   + x +    =>     + - +   + x +
				x   x                   x   x
			+   +   +               +   +   +
			
		Trying a 'x' in that place does not immediately lead to contradiction, hence this isn't spotted as a rule. Here 
		we would need approach 2.
	*/
	
	// approach 2: recurse down all (or depth R) possibilities for the local area. if a border has the same on/off state in 
	// all non-contradictive possibilities then this becomes part of the rule. (more expensive but more productive)
	
	// questions: how can we discover highlander rules? should we use highlander rules in puzzle construction?
	
	
	
	// we start with some set of rules that include the elementary rules - without these the very rules of slitherlink might be broken
	vector<TRule> rules;
	//GetElementarySolvingRules(rules);
	try {
		SlinkerGrid::ReadRulesFromFile("solving_rules_3.txt",rules);
	}
	catch(const exception &e)
	{
		wxMessageBox(wxString(e.what(),wxConvUTF8));
		return;
	}

	const int RECURSION_DEPTH = 0; // increase to catch more rules (but slow)

	const bool SEARCH_FOR_NEAR_DIAGONAL_RULES_ONLY = false; // if true: larger grids take less time (but only a subset of rules are searched)

	// TODO: instead of ranking rules by number of entries (M) - consider using number of cells. This might
	//       match better with people's expectations, and might reduce some of our rendundancy/zero issues - 
	//       e.g. zero won't appear because crosses will be more general for a given number of cells;
	
	// we work through the number of entries (M), from the bottom up
	for(int M=4;M<=4;M++)
	{
		const int N_BORDER_CELLS=2; // just to make sure that we don't see edge effects
		const int N=min(7,M+N_BORDER_CELLS*2); // size of the grid: need enough room to draw out the largest possible rule, with a border
		const int INPUT_BORDER=N_BORDER_CELLS*2+1; // we leave a border of INPUT_BORDER entries thick of UNKNOWNs around the edge of the input
		const int SEARCH_BORDER=N_BORDER_CELLS*2-1; // rule entries can't go near the edge of the grid
				
		SlinkerGrid g(N,N);
		vector<int*> changed;
		int left = INPUT_BORDER;
		int top = INPUT_BORDER;
		int right = 2*N+1-INPUT_BORDER-1; // inclusive
		int bottom = 2*N+1-INPUT_BORDER-1; // inclusive
		
		SlinkerGrid required(g);
		int x,y;
		
		// make a list of the possible entries, with the value each would take.
		// then, taking any M (non-colliding) of these makes a candidate set of requirements for a new rule
		vector< TElement > possible_entries;
		for(x=left;x<=right;x++)
		{
			for(y=top;y<=bottom;y++)
			{
				if(SEARCH_FOR_NEAR_DIAGONAL_RULES_ONLY && abs(x-y)>1) 
					continue;

				if(g.IsBorder(x,y))
				{
					possible_entries.push_back(TElement(x,y,0));
					possible_entries.push_back(TElement(x,y,1));
				}
				else if(g.IsCell(x,y))
				{
					possible_entries.push_back(TElement(x,y,1));
					possible_entries.push_back(TElement(x,y,2));
					possible_entries.push_back(TElement(x,y,3));

					// We exclude zero from rules because it only ever gives non-minimal rules - those
					// that would be more generally applicable if represented with 'x's. The zero rules would be 
					// removed at a later stage when discovered to be redundant (see below) but only if you process
					// the M+K level completely, so you'll always be left with some for a given M. Excluding zero 
					// from the rules gives us a large speedup since there are fewer rule candidates, and fewer 
					// ongoing rules to search them against. The downside is that technically this function won't 
					// find all rules for M elements, and may even exclude your favourite rule. Consider:
					//
					//                    +     +     +     +               +     +     +     +
					//                       0           0                     0           0
					//                    +     +     +     +               +     +  x  +     +
					//                                             =>             x     x
					//                    +     +     +     +               +     +  x  +     +
					//                       0                                 0
					//                    +     +     +     +               +     +     +     +
					//
					// Under our scheme this wouldn't appear for M=3 - you'd have to wait until M=6 before seeing 
					// this rule (using 'x's instead of '0's).
				}
			}
		}

		unsigned long iCase,n_cases; // things for reporting progress
		
		// Below we use next_combination() to work through the possibilities. This function needs a sorted 
		// container of sortable items, which TRule's aren't, so we use a list of indices for indirection. 
		// They start off sorted because we create them that way.
		vector<unsigned int> indices;
		{
			int n_entries = possible_entries.size();
			for(int i=0;i<n_entries;i++)
				indices.push_back(i);
			n_cases = choose(n_entries,M);
		}
		vector<unsigned int>::const_iterator indices_it;

		bool is_consistent;
		bool found_one,added_something;
		
		iCase=1;
		
		// work through all the possibilities
		do // while(next_combination)
		{
			// report progress
			{
				ostringstream oss;
				oss << "For " << M << " entries: case " << iCase << " of " << n_cases << ", " << rules.size() << " rules so far";
				wxLogStatus(wxString(oss.str().c_str(),wxConvUTF8));
				wxYield();
			}
			iCase++;
			// take the first M entries of indices array (reordered by next_combination so the first M are the ones we want)
			// but ignoring those combinations that collide (2+ possible_entries refer to the same border or cell)
			g.Clear();
			bool entries_collide = false;
			for(indices_it = indices.begin();indices_it!=indices.begin()+M;indices_it++)
			{
				const TElement& el = possible_entries[*indices_it];
				int& entry = g.cells[el.x][el.y];
				if(entry!=UNKNOWN)
				{
					entries_collide=true;
					break;
				}
				entry = el.val;
			}
			if(entries_collide) continue; // move straight onto the next combination - this one is duff
			
			required = g; // take a note of the input, in case this turns out to be a rule
			// see if this set of inputs leads to any new rules
			is_consistent = g.ApplyRules(rules,changed);
			if(!is_consistent) continue; // this set of inputs is not possible, no new rules to find here
			if(g.HasLoop()) continue; // this set of inputs is not possible since it leads directly (using the existing rules) to a loop

			// We _could_ also continue here if !changed.empty() since an existing rule can be applied to this
			// rule candidate. But in certain cases there is something implied *after* the existing rules have
			// been applied - e.g.:  
			//                          +     +     +          +     +     +
			//                             3                      3
			//                          +     +     +          +     +     +
			//                                   3       =>    x        3
			//                          +     +     +          +     +     +
			//                             3                      3 
			//                          +     +     +          +     +     +
			//
			// The version of this rule with everything filled out first has 19 elements, not 3, so unless we 
			// were searching up to M=19 we would never see this rule.
			// 
			// The downside of this is that sometimes redundant rules are found, because the more general case
			// hasn't been encountered yet. e.g.:
			//                                             +     +     +           +     +     +
			//                                                1                       1
			//                                             +  -  +     +     =>    +  -  +     +
			//                                                      1                       1  x
			//                                             +     +     +           +     +  x  +
			//
			// And so we include a redundant rules removal step at the end of each M level, to remove those rules
			// that are fully implied by the others. Overall the approach seems to work well.


			// test each border in turn, adding the opposite if exactly one possibility leads to inconsistency
			int on_off;
			int n_inconsistent,implied;
			bool grid_is_inconsistent = false;
			found_one = false;
			do 
			{
				added_something = false;

				for(x=SEARCH_BORDER;x<2*N+1-SEARCH_BORDER && !grid_is_inconsistent;x++)
				{
					for(y=SEARCH_BORDER;y<2*N+1-SEARCH_BORDER && !grid_is_inconsistent;y++)
					{
						int& entry = g.cells[x][y];
						if(IsBorder(x,y) && entry==UNKNOWN)
						{
							n_inconsistent=0;
							for(on_off=0;on_off<=1 && !added_something;on_off++)
							{
								entry = on_off;
								// with this change, is the grid still consistent, or now in a contradictory state?
								is_consistent = g.IsConsistent(rules,SEARCH_BORDER,RECURSION_DEPTH);
								entry = UNKNOWN; // undo our test change
								if(!is_consistent)
								{
									n_inconsistent++;
									implied = (1-on_off);
								}
							}
							if(n_inconsistent==1)
							{
								// we have found a rule!
								// apply the opposite case to the border state that led to a contradiction
								entry = implied;
								found_one = true;
								added_something = true;
								// N.B. this can't be an old rule in a new orientation because ApplyRules 
								// would have tried that already and if we perform an exhaustive search 
								// up from small M, this rule must be minimal, since
								// any simpler form of it would have been identified previously
							}
							else if(n_inconsistent==2)
							{
								grid_is_inconsistent = true;
							}
						}
					}
				}
			} while(!grid_is_inconsistent && added_something);
			// if we found a new rule then add to our list of rules, for use in finding more complex ones
			if(!grid_is_inconsistent && found_one)
			{
				g.UndoChanges(changed); // remove the parts of the result that we already knew from previous rules
				// add the rule to our list
				TRule r;
				int cx,cy;
				bool found_starting_place=false;
				for(x=INPUT_BORDER;x<2*N+1-INPUT_BORDER && !found_starting_place;x++)
				{
					for(y=INPUT_BORDER;y<2*N+1-INPUT_BORDER && !found_starting_place;y++)
					{
						if(required.cells[x][y]!=UNKNOWN)
						{
							cx=x;
							cy=y;
							if(required.IsHorizontalBorder(cx,cy))
							{
								if(cy>1) cy--; else cy++;
							}
							else if(required.IsVerticalBorder(cx,cy))
							{
								if(cx>1) cx--; else cx++;
							}
							found_starting_place = true;
						}
					}
				}
				if(!found_starting_place || !required.IsCell(cx,cy))
					wxMessageBox(wxT("Failed to find an entry in rule input - unexpected behaviour."));
				for(x=SEARCH_BORDER;x<2*N+1-SEARCH_BORDER;x++)
				{
					for(y=SEARCH_BORDER;y<2*N+1-SEARCH_BORDER;y++)
					{
						if(!IsDot(x,y))
						{
							if(required.cells[x][y]!=UNKNOWN)
							{
								r.required.push_back(TElement(x-cx,y-cy,required.cells[x][y]));
							}
							else if(g.cells[x][y]!=UNKNOWN)
							{
								r.implied.push_back(TElement(x-cx,y-cy,g.cells[x][y]));
							}
						}
					}
				}
				rules.push_back(r);
				WriteRulesToFile(rules,"rules_temp.txt");	
			}
		} while(next_combination(indices.begin(),indices.begin()+M,indices.end()));

		// Some of the rules may be redundant, given rules that were found later. (ideally this wouldn't happen but how?)
		// So we need a pass to work out which rules wouldn't be needed if all the others were provided - which
		// rule's implieds are now all given by other rules? As we extend the number of entries we may find 
		// more general rules, e.g. all the rules featuring '0' will be more generally represented with rules that
		// use 'x's.
		wxLogStatus(wxT("Removing rules later found to be redundant..."));
		vector<TRule> nonredundant_rules;
		FindNonRedundantRules(rules,nonredundant_rules);
		rules.clear();
		rules.assign(nonredundant_rules.begin(),nonredundant_rules.end());
		WriteRulesToFile(rules,"rules_temp.txt");	

	} // for(M)

	WriteRulesToFile(rules,"rules.txt");	

	// report completion
	{
		ostringstream oss;
		oss << "Done. "  << rules.size() << " rules in total.";
		wxLogStatus(wxString(oss.str().c_str(),wxConvUTF8));
		wxYield();
	}
}

void SlinkerGrid::FindNonRedundantRules(const std::vector<TRule> &rules,vector<TRule>& nonredundant_rules)
{
	nonredundant_rules.clear(); // don't want to leave any in there

	vector<TRule> test_set;
	const int N=10;// size not really important here as long as it's big enough
	SlinkerGrid g(N,N); 
	int spx = N/2,spy=N/2;
	if(IsDot(spx,spy)) spx=spy=spy+1;
	else if(IsHorizontalBorder(spx,spy)) spy++;
	else if(IsVerticalBorder(spx,spy)) spx++;
	vector<int*> changed;
	for(vector<TRule>::const_iterator it1=rules.begin();it1!=rules.end();it1++)
	{
		// copy all but this rule into our test set
		test_set.clear();
		for(vector<TRule>::const_iterator it2=rules.begin();it2!=rules.end();it2++)
		{
			if(it2!=it1)
				test_set.push_back(*it2);
		}
		
		// make a test grid of the input
		g.Clear();
		vector<TElement>::const_iterator rule_it;
		for(rule_it = it1->required.begin();rule_it!=it1->required.end();rule_it++)
		{
			g.cells[rule_it->x+spx][rule_it->y+spy] = rule_it->val;
		}
			
		// apply the test set of rules
		g.ApplyRules(test_set,changed);
		
		// is there any implied that isn't present? if so then we keep this rule
		bool done=false;
		for(rule_it = it1->implied.begin();rule_it!=it1->implied.end() && !done;rule_it++)
		{
			if(g.cells[rule_it->x+spx][rule_it->y+spy]==UNKNOWN)
			{
				nonredundant_rules.push_back(*it1);
				done=true;
			}
		}
	}
}

bool SlinkerGrid::IsConsistent(const std::vector<TRule> &solving_rules,const int& SEARCH_BORDER,int depth)
{
	// first apply the local solving rules - if this grid is inconsistent then we're done
	vector<int*> changed;
	bool is_cons = ApplyRules(solving_rules,changed);

	// if the grid contains any loop at all then this is forbidden (remember this function only used with rule candidates, not whole puzzles)
	if(is_cons && HasLoop())
		is_cons = false;
	
	// otherwise, try a border and recurse down as necessary
	if(is_cons && depth>0)
	{
		int x,y;
		// if both border states give an inconsistent grid (for any border), then the current grid is inconsistent
		bool test_is_cons;
		int n_inconsistent,on_off;
		for(x=SEARCH_BORDER;x<2*X+1-SEARCH_BORDER && is_cons;x++) // for every non-edge entry (don't want off-grid effects here, see FindNewRules)
		{
			for(y=SEARCH_BORDER;y<2*Y+1-SEARCH_BORDER && is_cons;y++)
			{
				int &entry = cells[x][y];
				if(IsBorder(x,y) && entry==UNKNOWN)
				{
					n_inconsistent=0;
					for(on_off=0;on_off<=1;on_off++)
					{
						entry=on_off;
						// with this change, is the grid still consistent, or now in a contradictory state?
						test_is_cons = IsConsistent(solving_rules,SEARCH_BORDER,depth-1); // keep track of recursion depth
						entry=UNKNOWN; // undo our test change
						if(!test_is_cons)
							n_inconsistent++;
						else 
							break; // don't need to check the other possibility: the current grid is consistent
					}
					if(n_inconsistent==2)
						is_cons = false; // the current grid state is inconsistent! (this is a good thing - we have found a rule)
				}
			}
		}
	}
	
	UndoChanges(changed);
	
	return is_cons;
}

void SlinkerGrid::GetElementarySolvingRules(vector<TRule> &rules)
{
	// This is a compressed set of rules - using contradictions to reduce the number of rules to
	// a minimum (8). You can use this set with FindNewRules to find more, and FindNewRules forbids small loops, 
	// so together with that heuristic, these 8 rules give you the seed to find *all* slitherlink rules, up to
	// whatever rule size you like. (Not including highlander rules, which make an extra assumption that a unique
	// solution exists.)
	
	// FindNewRules will give you the more familiar forms of these rules, without contradictions, a set of 13. 
	// These 13 are the ones we include in our elementary_rules.txt, simply because they are easier to understand.
	{
		TRule a; 
		a.required.push_back(TElement(0,0,0)); // a 0 ...
		a.implied.push_back(TElement(1,0,0)); // has all borders off (by symmetry)
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,0,1)); // a 1 ...
		a.required.push_back(TElement(-1,0,1)); // with one border on ...
		a.implied.push_back(TElement(0,-1,0)); // .. has all other borders off
		a.implied.push_back(TElement(1,0,0));
		a.implied.push_back(TElement(0,1,0));
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,0,1)); // a 1 ...
		a.required.push_back(TElement(0,-1,0)); // with three borders off ...
		a.required.push_back(TElement(1,0,0));
		a.required.push_back(TElement(0,1,0));
		a.implied.push_back(TElement(-1,0,1)); // .. has one border on
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,0,2)); // a 2 ...
		a.required.push_back(TElement(-1,0,1)); // with three borders on ...
		a.required.push_back(TElement(0,-1,1));
		a.required.push_back(TElement(1,0,1));
		a.implied.push_back(TElement(1,0,0)); // .. is a contradiction
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,0,2)); // a 2 ... 
		a.required.push_back(TElement(-1,0,0)); // with three borders off ...
		a.required.push_back(TElement(0,-1,0));
		a.required.push_back(TElement(1,0,0));
		a.implied.push_back(TElement(1,0,1)); // .. is a contradiction
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,0,3)); // a 3 ...
		a.required.push_back(TElement(0,-1,0)); // with one border off ...
		a.implied.push_back(TElement(0,1,1)); // .. has the other borders on
		a.implied.push_back(TElement(-1,0,1));
		a.implied.push_back(TElement(1,0,1));
		rules.push_back(a);
		// ("three ons around a cell imply an off" is given by the more general no-small-loops heuristic)
	}
	{
		TRule a;
		a.required.push_back(TElement(0,1,0)); // where three offs join at a dot..
		a.required.push_back(TElement(2,1,0));
		a.required.push_back(TElement(1,2,0));
		a.implied.push_back(TElement(1,0,0)); // .. the fourth border must also be off
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,1,1)); // where three lines join at a dot..
		a.required.push_back(TElement(2,1,1));
		a.required.push_back(TElement(1,2,1));
		a.implied.push_back(TElement(0,1,0)); // .. there is a contradiction
		rules.push_back(a);
	}
}

void SlinkerGrid::GetBeforeAndAfterGridsForRule(const TRule& r,SlinkerGrid& req,SlinkerGrid& impl)
{
	// first work out the bounding box for the rule
	int left=INT_MAX,right=-INT_MAX,top=INT_MAX,bottom=-INT_MAX;
	vector<TElement>::const_iterator it;
	for(it=r.required.begin();it!=r.required.end();it++)
	{
		if(it->x<left) left=it->x;
		if(it->y<top) top=it->y;
		if(it->x>right) right=it->x;
		if(it->y>bottom) bottom=it->y;
	}
	for(it=r.implied.begin();it!=r.implied.end();it++)
	{
		if(it->x<left) left=it->x;
		if(it->y<top) top=it->y;
		if(it->x>right) right=it->x;
		if(it->y>bottom) bottom=it->y;
	}
	int width = (right-left-1)/2+4;
	int height = (bottom-top-1)/2+4;
	int cx = 2-left;
	int cy = 2-top;
	if(IsDot(cx,cy)) { cx++; cy++; }
	else if(IsHorizontalBorder(cx,cy)) { cy++; }
	else if(IsVerticalBorder(cx,cy)) { cx++; }
	req = SlinkerGrid(width,height);
	impl = SlinkerGrid(width,height);
	for(it=r.required.begin();it!=r.required.end();it++)
	{
		req.cells[cx+it->x][cy+it->y]=it->val; 
		impl.cells[cx+it->x][cy+it->y]=it->val;
	}
	for(it=r.implied.begin();it!=r.implied.end();it++)
	{
		impl.cells[cx+it->x][cy+it->y]=it->val;
	}
}

void SlinkerGrid::WriteRulesToFile(const vector<TRule> &rules,const string &filename) // static
{
	/* File format example:
	
			#--------------
			required:
			0,0,0
			implied:
			-1,0,0
			0,-1,0
			1,0,0
			0,1,0
			
			# this is the elementary rule for zero in a cell
			#
			#             +   +        + x +
			#               0     =>   x 0 x
			#             +   +        + x +
			#
			#-------------- 
			
		Description:
		'#' character at the start of a line means a comment; that line is ignored (also blank lines)
		'required:' string at the start of a line begins a rule, following lines are elements.
		Each element is three integers, comma delimited: "<x>,<y>,<value>\n" for the border and cell values.
		'implied:' string at the start of a line begins the implied section, following lines are more elements.
		
		Rules are applied with 0,0 centred on a cell entry (not a border or a dot)
		Rules are applied in any orientation and reflection, thus need only be given in one of them.
		(N.B. Technically only one of the 'implied' lines in the example above is needed, since the rule will
		be applied in the other orientations.)
	*/
	
	// we should use xml for this? but this is far more human readable?
	
	ofstream out(filename.c_str());
	vector<TRule>::const_iterator rules_it;
	vector<TElement>::const_iterator it;
	SlinkerGrid req(4,4),impl(4,4);
	for(rules_it=rules.begin();rules_it!=rules.end();rules_it++)
	{
		SlinkerGrid::GetBeforeAndAfterGridsForRule(*rules_it,req,impl);
		// write out the rule in machine-readable format (and draw the rule onto two grids)
		out << "#---------- Rule " << rules_it-rules.begin()+1 << ": --------------\nrequired:\n";
		for(it=rules_it->required.begin();it!=rules_it->required.end();it++)
			out << it->x << "," << it->y << "," << it->val << "\n";
		out << "implied:\n";
		for(it=rules_it->implied.begin();it!=rules_it->implied.end();it++)
			out << it->x << "," << it->y << "," << it->val << "\n";
		// draw a visual depiction of the rule for humans
		{
			istringstream req_text(req.GetPrintOut()),impl_text(impl.GetPrintOut());
			out << "\n";
			int y;
			string s;
			for(y=0;y<2*req.GetY()+1;y++)
			{
				out << "#         ";
				getline(req_text,s);
				out << s;
				if(y==req.GetY()) out << "       =>         ";
				else out << "                  ";
				getline(impl_text,s);
				out << s << "\n";
			}
			out << "\n";
		}
	}
}

void SlinkerGrid::ReadRulesFromFile(const string &filename,vector<TRule> &rules) // static
{
	if(!wxFileExists(wxString(filename.c_str(),wxConvUTF8)))
		throw(runtime_error("File does not exist."));
	ifstream in(filename.c_str());
	string line;
	TRule r;
	enum { starting,reading_requireds,reading_implieds } state = starting;
	int lines_read=0;
	while(!in.eof())
	{
		getline(in,line); 
		lines_read++;
		if(line.find("required:")==0 || in.eof())
		{
			// if there's a rule already read in then flush it
			if(!r.required.empty()) rules.push_back(r);
			r.required.clear();
			r.implied.clear();
			state = reading_requireds;
		}
		else if(line.find("implied:")==0)
		{
			state = reading_implieds;
		}
		else if(line[0]=='#' || line.empty()) continue; // comment or empty line, ignore
		else
		{
			// this must be an element line, read it in
			TElement el(INT_MAX,INT_MAX,INT_MAX);
			int n_read = sscanf(line.c_str(),"%d,%d,%d",&el.x,&el.y,&el.val);
			if(n_read!=3)
			{
				// something else on the line, ignore
				continue;
			}
			if(state==reading_requireds)
				r.required.push_back(el);
			else if(state==reading_implieds)
				r.implied.push_back(el);
			else throw(runtime_error("Error reading file: found element outside of required-implied blocks"));
		}
	}
}

SlinkerGrid SlinkerGrid::ReadFromLoopyFormat(const string &s)
{
	istringstream iss(s.c_str());
	char c1,c2;
	int X,Y;
	iss >> X >> c1 >> Y >> c2;
	//if(c1!='x' || c2!=':') throw(runtime_error("Error reading file - expecting the Loopy format."));
	SlinkerGrid g(X,Y);
	int x=0,y=0;
	char c;
	while(iss.good())
	{
		iss >> c;
		if(c>='0' &&c<='3' && x>=0 && x<X && y>=0 && y<Y)
			g.cellValue(x++,y) = (c-'0');
		else if(c>='a' && c<='z')
			x += (c-'a'+1);
		//else throw(runtime_error("Error reading file - unexpected character."));
		while(x>=X)
		{
			y++;
			x-=X;
		}
	}
	return g;
}

string SlinkerGrid::GetPuzzleInLoopyFormat()
{
	ostringstream oss;
	oss << X << "x" << Y << ":";
	int n_spaces_pending=0;
	for(int y=0;y<Y;y++)
	{
		for(int x=0;x<X;x++)
		{
			if(cellValue(x,y)==UNKNOWN)
				n_spaces_pending++;
			else
			{
				if(n_spaces_pending>0)
				{
					if(n_spaces_pending>26) 
						throw(runtime_error("Over 26 spaces in a row - how to deal with this in the Loopy format?"));
					oss << char('a'+n_spaces_pending-1);
					n_spaces_pending=0;
				}
				oss << char('0'+cellValue(x,y));
			}
		}
	}
	// if there are trailing spaces then we need to deal with them now
	if(n_spaces_pending>0)
		oss << char('a'+n_spaces_pending-1);
	return oss.str();
}

vector<SlinkerGrid::TRule> SlinkerGrid::GetGrowthRules()
{
	vector<TRule> rules;
	{
		TRule a;
		a.required.push_back(TElement(1,0,1));
		a.required.push_back(TElement(0,1,1));
		a.required.push_back(TElement(-1,0,0));
		a.required.push_back(TElement(0,-1,0));
		a.required.push_back(TElement(-2,-1,0));
		a.required.push_back(TElement(-1,-2,0));
		a.implied.push_back(TElement(1,0,0));
		a.implied.push_back(TElement(0,1,0));
		a.implied.push_back(TElement(-1,0,1));
		a.implied.push_back(TElement(0,-1,1));
		/*
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                                                                                             
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                     x                                                  x                    
		#         +     +  x  +  x  +     +     +                    +     +  x  +  -  +     +     +  
		#                     x     |                     =>                     |     x              
		#         +     +     +  -  +     +     +                    +     +     +  x  +     +     +  
		#                                                                                             
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                                                                                             
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(-1,0,1));
		a.required.push_back(TElement(1,0,0));
		a.required.push_back(TElement(0,-1,0));
		a.required.push_back(TElement(0,1,0));
		a.required.push_back(TElement(1,-2,0));
		a.required.push_back(TElement(1,2,0));
		a.required.push_back(TElement(2,-1,0));
		a.required.push_back(TElement(2,1,0));
		a.implied.push_back(TElement(-1,0,0));
		a.implied.push_back(TElement(1,0,1));
		a.implied.push_back(TElement(0,-1,1));
		a.implied.push_back(TElement(0,1,1));
		/*
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                                                                                             
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                     x                                                  x                    
		#         +     +  x  +  x  +     +     +                    +     +  -  +  x  +     +     +  
		#               |     x                           =>               x     |                    
		#         +     +  x  +  x  +     +     +                    +     +  -  +  x  +     +     +  
		#                     x                                                  x                    
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		#                                                                                             
		#         +     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(a);
	}
	{
		TRule a;
		a.required.push_back(TElement(0,1,1));
		a.required.push_back(TElement(1,0,1));
		a.required.push_back(TElement(0,-1,1));
		a.required.push_back(TElement(-1,0,0));
		a.implied.push_back(TElement(-1,0,1));
		a.implied.push_back(TElement(1,0,0));
		a.implied.push_back(TElement(0,-1,0));
		a.implied.push_back(TElement(0,1,0));
		/*
		#         +     +     +     +     +                    +     +     +     +     +  
		#                                                                                 
		#         +     +  -  +     +     +                    +     +  x  +     +     +  
		#               x     |                                      |     x              
		#         +     +  -  +     +     +         =>         +     +  x  +     +     +  
		#                                                                                 
		#         +     +     +     +     +                    +     +     +     +     +  
		#                                                                                 
		#         +     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(a);
	}
	return rules;
}

string SlinkerGrid::GetPuzzleAnalysis(const std::vector<TRule>& solving_rules) const
{
	//wxMessageBox(_T("Error - function not working, see code."));
	ostringstream oss;
	SlinkerGrid g(*this);
	g.ClearBorders();
	vector<SlinkerGrid> no_guessing_solutions = g.FindSolutions(solving_rules,false,2);
	if(!no_guessing_solutions.empty())
	{
		oss << "Puzzle can be solved with the supplied rules.\n";
		if(no_guessing_solutions.size()==1)
		{
			oss << "Puzzle has a unique solution.\n\n";
			// work out the difficulty of each rule
			vector<TRule> sorted_rules(solving_rules);
			vector<double> difficulty;
			SlinkerGrid::SortRulesByIncreasingDifficulty(sorted_rules,difficulty);
			// work out the rules that need be applied
			const int MAX_ELEMENTS=6;
			vector<int> n_of_each_class(MAX_ELEMENTS,0);
			double diff,average_difficulty=0.0,max_difficulty=0.0;
			int iRule,iSymm,n_req,n_rules=0;
			wxPoint pos;
			while(g.GetAValidMove(sorted_rules,iRule,pos,iSymm))
			{
				n_req = sorted_rules[iRule].required.size();
				if(n_req<MAX_ELEMENTS)
					n_of_each_class[n_req]++;
				n_rules++;
				diff = difficulty[iRule];
				average_difficulty += diff;
				if(diff>max_difficulty)
					max_difficulty = diff;
				if(false)
				{
					ostringstream debug;
					SlinkerGrid pre,post;
					GetBeforeAndAfterGridsForRule(sorted_rules[iRule],pre,post);
					debug << "Rule " << iRule+1 << ":\n\n" << pre.GetPrintOut() << "\n\nRequired elements: "
						<< n_req << "\nDifficulty: " << diff;
					//TODO: returning incorrect index, causing error - why?
					wxMessageBox(wxString(debug.str().c_str(),wxConvUTF8));
				}
				g.ApplyRule(sorted_rules[iRule],pos,iSymm);
			}
			for(int i=2;i<MAX_ELEMENTS;i++)
				oss << "Number of " << i << "-element rule-applications needed: " << n_of_each_class[i] << "\n";
			oss << "\nAverage rule difficulty: " << average_difficulty/double(n_rules) << "\n";
			oss << "Max rule difficulty: " << max_difficulty << "\n";
		}
		else
			oss << "Puzzle has multiple solutions.\n";
	}
	else
	{
		vector<SlinkerGrid> solutions = g.FindSolutions(solving_rules,true,2);
		oss << "Puzzle cannot be solved with the supplied rules alone.\n";
		if(solutions.empty())
			oss << "Puzzle has no solutions.\n";
		else if(solutions.size()==1)
			oss << "Puzzle has a unique solution.\n";
		else
			oss << "Puzzle has multiple solutions.\n";
	}
	// TODO: more analysis: how many of each class of rule were used?
	return oss.str();
}

void SlinkerGrid::ApplyRule(const TRule& rule,wxPoint& pos,int& iSymmetry)
{
	int tx,ty;
	for(vector<TElement>::const_iterator it = rule.implied.begin();it!=rule.implied.end();it++)
	{
		tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
		ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
		if(IsOnGrid(tx,ty))
			cells[tx][ty] = it->val;
	}
}

bool SlinkerGrid::GetAValidMove(const std::vector<TRule>& rules,int& iRule,wxPoint& pos,int& iSymmetry)
{
	// TODO: should code-share with ApplyRules if can maintain efficiency
	vector<TElement>::const_iterator it;
	bool can_apply;
	int tx,ty;
	for(iRule=0;iRule<rules.size();iRule++)
	{
		const TRule& rule = rules[iRule];
		for(pos.x=-1;pos.x<(2*X+1+1);pos.x++)
		{
			for(pos.y=-1;pos.y<(2*Y+1+1);pos.y++)
			{
				if(!IsCell(pos.x,pos.y)) continue;
				// does the rule apply here (centred on cell x,y) in any orientation?
				for(iSymmetry=0;iSymmetry<N_SYMMETRIES;iSymmetry++)
				{
					can_apply = true; // until found otherwise
					for(it=rule.required.begin();it!=rule.required.end() && can_apply;it++)
					{
						tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
						ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
						if( !( (it->val==0 && IsBorder(tx,ty) && !IsOnGrid(tx,ty)) || 
							(IsOnGrid(tx,ty) && cells[tx][ty]==it->val) ) )
								can_apply = false;

					}
					if(!can_apply) continue;
					for(it = rule.implied.begin();it!=rule.implied.end();it++)
					{
						tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
						ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
						if(!IsOnGrid(tx,ty)) continue;
						if(cells[tx][ty]==UNKNOWN)
							return true; // this rule can apply and is useful (changes something)
					}
				}
			}
		}
	}
	return false; // found nothing to apply
}

void SlinkerGrid::SortRulesByIncreasingDifficulty(vector<TRule> &rules,vector<double> &difficulty)
{
	const int N_RULES = rules.size();
	
	// fill a large area with a random loop
	const int N=100;
	SlinkerGrid g(N,N);
	g.FillGridWithRandomLoop();
	g.MarkUnknownBordersAsOff();
	
	// count the number of times that each rule could apply
	vector<int> frequency(rules.size(),0);
	{
		vector<TElement>::const_iterator it;
		bool can_apply;
		int tx,ty,iRule,iSymmetry;
		wxPoint pos;
		for(iRule=0;iRule<N_RULES;iRule++)
		{
			const TRule& rule = rules[iRule];
			for(pos.x=-1;pos.x<(2*g.X+1+1);pos.x++)
			{
				for(pos.y=-1;pos.y<(2*g.Y+1+1);pos.y++)
				{
					if(!IsCell(pos.x,pos.y)) continue;
					// does the rule apply here (centred on cell x,y) in any orientation?
					for(iSymmetry=0;iSymmetry<N_SYMMETRIES;iSymmetry++)
					{
						can_apply = true; // until found otherwise
						for(it=rule.required.begin();it!=rule.required.end() && can_apply;it++)
						{
							tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
							ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
							if( !( (it->val==0 && IsBorder(tx,ty) && !g.IsOnGrid(tx,ty)) || 
								(g.IsOnGrid(tx,ty) && g.gridValue(tx,ty)==it->val) ) )
									can_apply = false;
	
						}
						if(can_apply) 
							frequency[iRule]++;
					}
				}
			}
		}
	}
	
	// now sort the rules by increasing difficulty
	vector<SlinkerGrid::TRule> sorted_rules;
	{
		difficulty.clear();
		difficulty.resize(N_RULES);
		
		vector<int> indices(N_RULES);
		
		for (int i = 0; i < indices.size(); i++)
			indices [i] = i;
		
		sort (indices.begin (), indices.end (),
			IndexedComparison<std::vector<int>::const_iterator>
				(frequency.begin (), frequency.end ()));
				
		reverse(indices.begin(),indices.end()); // because we sorted in increasing order
		
		for(int i=0;i<N_RULES;i++)
		{
			sorted_rules.push_back(rules[indices[i]]);
			difficulty[i] = max(0.0,1.0-(frequency[indices[i]]/double(N*N)));
		}
	}
	
	// copy the rules over
	rules.clear();
	rules.assign(sorted_rules.begin(),sorted_rules.end());
}

void SlinkerGrid::MakePuzzleByAddingHardClues(const vector<TRule>& rules)
{
	// N.B. this seemed like a good idea but didn't work at all. 

	// first fill a grid with a nice loop
	SlinkerGrid solution(*this);
	solution.Clear();
	solution.FillGridWithRandomLoop();
	
	ofstream debug("debug.txt");
	debug << solution.GetPrintOut();
	
	Clear();
	
	// until the puzzle is completely specified, add the numbers that are needed to provide
	// one of the hardest of rules, then apply the rules and repeat
	vector<TElement>::const_iterator it;
	vector<int*> changed1,changed2;
	bool can_apply;
	int tx,ty,iRule,iSymmetry;
	wxPoint pos;
	bool found_one;
	
	int n_clues_supplied=0;
	 
	for(int pass=0;pass<2;pass++)
	{
		do 
		{
			found_one = false;
			for(iRule=rules.size()-1;iRule>=0 && !found_one;iRule--) // start by looking for the hardest rules
			{
				const TRule& rule = rules[iRule];
				for(pos.x=-1;pos.x<(2*X+1+1) && !found_one;pos.x++)
				{
					for(pos.y=-1;pos.y<(2*Y+1+1) && !found_one;pos.y++)
					{
						if(!IsCell(pos.x,pos.y)) continue;
						for(iSymmetry=0;iSymmetry<N_SYMMETRIES && !found_one;iSymmetry++)
						{
							// could the rule apply here, if we added whatever numbers were necessary?
							// i.e. are the numbers in the solution, and the borders in the grid - if so then yes.
							
							can_apply = true; // until found otherwise
							bool has_at_least_one_number_missing=false;
							for(it=rule.required.begin();it!=rule.required.end() && can_apply;it++)
							{
								tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
								ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
								if( !( (it->val==0 && IsBorder(tx,ty) && !IsOnGrid(tx,ty)) ||  // (either off-grid and an off border
									( IsOnGrid(tx,ty) && 
										(
											(IsBorder(tx,ty) && gridValue(tx,ty)==it->val) || // or a border on this grid
											(IsCell(tx,ty) && solution.gridValue(tx,ty)==it->val)  // or a cell on the solution grid
										) 
									) ) ) 
										can_apply = false;
								if(IsOnGrid(tx,ty) && IsCell(tx,ty) && gridValue(tx,ty)==UNKNOWN)
									has_at_least_one_number_missing = true;
							}
							bool gives_us_something_we_didnt_know = false;
							for(it=rule.implied.begin();it!=rule.implied.end() && !gives_us_something_we_didnt_know;it++)
							{
								tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
								ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
								if(IsOnGrid(tx,ty) && IsBorder(tx,ty) && gridValue(tx,ty)==UNKNOWN)
									gives_us_something_we_didnt_know = true;
							}
							if(can_apply && has_at_least_one_number_missing && gives_us_something_we_didnt_know) 
							{
								if(pass==0)
								{
									// check whether with these clues we'd actually need the rule itself to find this stuff out
									SlinkerGrid g(*this);
									// add the clues required to the test grid
									for(it=rule.required.begin();it!=rule.required.end() && can_apply;it++)
									{
										tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
										ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
										if(IsCell(tx,ty) && gridValue(tx,ty)==UNKNOWN)
											g.gridValue(tx,ty)=it->val;
									}
									vector<TRule> other_rules;
									for(int ir=0;ir<rules.size();ir++)
										if(ir!=iRule) other_rules.push_back(rules[ir]);
									g.ApplyRules(other_rules,changed1);
									g.ApplyRules(rules,changed2);
									if(!changed2.empty())
									{
										found_one = true;
										*this = g;
									}
								}
								else if(pass==1) // on the second pass we relax this condition
								{
									// add the clues required to the test grid
									for(it=rule.required.begin();it!=rule.required.end() && can_apply;it++)
									{
										tx = pos.x + SYMMETRIES[iSymmetry].mX(it->x,it->y);
										ty = pos.y + SYMMETRIES[iSymmetry].mY(it->x,it->y);
										if(IsCell(tx,ty) && gridValue(tx,ty)==UNKNOWN)
											gridValue(tx,ty)=it->val;
									}
									ApplyRules(rules,changed1);
									found_one=true;
								}
							}
						}
					}
				}
			}
		} while(found_one);
	}
}

double SlinkerGrid::GetPuzzleDifficulty(const std::vector<TRule> &sorted_rules,const std::vector<double> &difficulty) const
{
	SlinkerGrid g(*this);
	g.ClearBorders();
	// work out the rules that need be applied
	double diff,average_difficulty=0.0,max_difficulty=0.0;
	int iRule,iSymm,n_rules=0;
	wxPoint pos;
	while(g.GetAValidMove(sorted_rules,iRule,pos,iSymm))
	{
		n_rules++;
		diff = difficulty[iRule];
		average_difficulty += diff;
		if(diff>max_difficulty)
			max_difficulty = diff;
		g.ApplyRule(sorted_rules[iRule],pos,iSymm);
	}
	average_difficulty /= n_rules;
	return max_difficulty; // or average difficulty? or something else?
}
