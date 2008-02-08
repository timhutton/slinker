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

// SlinkerGrid.cpp

#include "next_combination.h"

#include "SlinkerGrid.h"

#include <sstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

// for debugging
#include <fstream>

#include "wxWidgets_standard_headers.h"

/// ---------- statics -------------

const int SlinkerGrid::NHOOD[4][2] = { {-1,0}, { 0,-1}, {1,0}, {0,1} };

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

bool SlinkerGrid::IsOdd(int a) { return (a&1)==1; }
bool SlinkerGrid::IsEven(int a) { return (a&1)==0; } 
bool SlinkerGrid::IsDot(int x,int y) { return( IsEven(x) && IsEven(y) ); }
bool SlinkerGrid::IsBorder(int x,int y) { return( IsEven(x)^IsEven(y) ); }
bool SlinkerGrid::IsCell(int x,int y) { return( IsOdd(x) && IsOdd(y) ); }
bool SlinkerGrid::IsHorizontalBorder(int x,int y) { return( IsOdd(x) && IsEven(y) ); }
bool SlinkerGrid::IsVerticalBorder(int x,int y) { return( IsEven(x) && IsOdd(y) ); }

// ---------------------------

SlinkerGrid::SlinkerGrid(int x,int y,TGridShape gs) 
	: X(x), Y(y), 
	cells(2*X+1,vector<int>(2*Y+1,UNKNOWN)), // init array of values all filled with UNKNOWN
	grid_shape(gs)
{
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

bool SlinkerGrid::IsOnGrid(int x,int y) const
{
	// even non-rectangular grids are embedded in a rectangular area
	if(!(x>=0 && x<2*X+1 && y>=0 && y<2*Y+1))
		return false;

	switch(this->grid_shape)
	{
		case Rectangle:
			{
				return true; // plain rectangle
			}
		case MissingCentre:
			{
				// rectangle with missing central ninth
				// (looks best if X and Y are divisible by 3)
				return (x<2*int(X/3)+1 || x>2*(2*int(X/3)-1)+1 || y<2*int(Y/3)+1 || y>2*(2*int(Y/3)-1)+1);
			}
		case Circle:
			{
				if(X!=Y) throw(runtime_error("IsOnGrid: X and Y must be equal."));
				//if(2*int(X/2)!=X) throw(runtime_error("IsOnGrid: X must be even."));
				int mid = (2*X+1)/2;
				int r = (2*X+1)/2; // radius of inset circle
				if(IsCell(x,y))
					return(hypot(mid-x,mid-y)<=r);
				else if(IsHorizontalBorder(x,y))
					return(hypot(mid-x,mid-(y-1))<=r || hypot(mid-x,mid-(y+1))<=r);
				else if(IsVerticalBorder(x,y))
					return(hypot(mid-(x-1),mid-y)<=r || hypot(mid-(x+1),mid-y)<=r);
				else if(IsDot(x,y))
					return(hypot(mid-(x-1),mid-(y-1))<=r || hypot(mid-(x+1),mid-(y-1))<=r ||
						hypot(mid-(x+1),mid-(y+1))<=r || hypot(mid-(x-1),mid-(y+1))<=r);
			}
	}
	throw(runtime_error("Internal error: unknown grid type in IsOnGrid."));
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
		throw(out_of_range("out of range exception in SlinkerGrid::cellValue"));
	return this->cells[2*x+1][2*y+1];
}

int& SlinkerGrid::gridValue(int x,int y)
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
	vector<TRule> growth_rules;
	ReadRulesFromFile("growth_rules.txt",growth_rules);

	int x,y,tx,ty,iSymm,iRule;
	bool can_apply;
	vector<TElement>::const_iterator it;
	// start with a grid full of offs
	this->Clear();
	this->MarkUnknownBordersAsOff();
	// start with a single cell loop
	do {
		x = 2*(rand()%X) + 1;
		y = 2*(rand()%Y) + 1;
	} while(!IsOnGrid(x,y)); // (need this test for non-rectangular grids)
	this->cells[x-1][y]=this->cells[x+1][y]=this->cells[x][y-1]=this->cells[x][y+1]=1;

	// here's a nice feature - you can choose what the loop should feel like:

	// (over 0,100 what proportions do you want the three rules in?)
	//const int prob_divs[2]={50,100}; // just use first two rules; for thin corridors, maximally-filled grid (usually unsatisfactory since predictable)
	//const int prob_divs[2]={33,66}; // for thick corridors, casually-filled grid (can leave empty areas but perhaps least predictable, and may be to your taste)
	const int prob_divs[2]={50,80}; // seems to be a reasonable balance, perhaps

	// search at random for possible applications of these rules, until bored
	int its=0;
	while(++its<X*Y*1000) // there might be a more elegant method than just running for a while, but it works quickly and well
	{
		// look in a random cell at a random orientation, for a random rule
		x = 2*(rand()%X) + 1;
		y = 2*(rand()%Y) + 1;
		iSymm = rand()%N_SYMMETRIES;
		int rand_p = rand()%100;
		iRule = (rand_p<prob_divs[0])?0:((rand_p<prob_divs[1])?1:2);
		// can this rule apply?
		can_apply = true;
		for(it=growth_rules[iRule].required.begin();it!=growth_rules[iRule].required.end() && can_apply;it++)
		{
			tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
			ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
			// check that this cell entry matches the required list
			if( !( (it->val==0 && !IsOnGrid(tx,ty)) || 	(IsOnGrid(tx,ty) && cells[tx][ty]==it->val) ) )
				can_apply = false;
		}
		// also check that all our implieds are actually on the grid
		for(it = growth_rules[iRule].implied.begin();it!=growth_rules[iRule].implied.end() && can_apply;it++)
		{
			tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
			ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
			if(!IsOnGrid(tx,ty))
				can_apply=false;
		}
		if(can_apply)
		{
			for(it = growth_rules[iRule].implied.begin();it!=growth_rules[iRule].implied.end();it++)
			{
				tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
				ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
				if(IsOnGrid(tx,ty) && cells[tx][ty] != it->val)
					cells[tx][ty] = it->val;
			}
		}
		// N.B. this is not quite the same search as ApplyRules()  - we don't worry about inconsistency, 
		// and we must search at random, and while we still treat off-grid borders as equivalent to off borders, 
		// we also have to check that we're not trying to set an off-grid border to on.
	}

	// fill in the cell counts
	int minc,maxc;
	for(x=0;x<X;x++)
	{
		for(y=0;y<Y;y++)
		{
			GetBorderCountAroundCell(x*2+1,y*2+1,minc,maxc);
			cellValue(x,y) = minc;
		}
	}
}

void SlinkerGrid::Clear()
{
	int x;
	for(x=0;x<2*X+1;x++)
	{
		fill(cells[x].begin(),cells[x].end(),-1);//SlinkerGrid::UNKNOWN);
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
			for(x=0;x<2*X+1;x++)
			{
				for(y=0;y<2*Y+1;y++)
				{
					if(!IsCell(x,y) || !IsOnGrid(x,y)) continue;
					// does the rule apply here (centred on cell x,y) in any orientation?
					for(iSymm=0;iSymm<N_SYMMETRIES;iSymm++)
					{
						can_apply = true;
						for(it=rule_it->required.begin();it!=rule_it->required.end() && can_apply;it++)
						{
							tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
							ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
							if( !( (it->val==0 && !IsOnGrid(tx,ty)) || 
								(IsOnGrid(tx,ty) && cells[tx][ty]==it->val) ) )
									can_apply = false;
						}
						if(!can_apply) continue;
						for(it = rule_it->implied.begin();it!=rule_it->implied.end();it++)
						{
							tx = x + SYMMETRIES[iSymm].mX(it->x,it->y);
							ty = y + SYMMETRIES[iSymm].mY(it->x,it->y);
							pEntry = &cells[tx][ty];
							if(IsOnGrid(tx,ty) && *pEntry != it->val)
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
					if(!IsBorder(x,y) || cells[x][y]!=UNKNOWN) 
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

std::vector<SlinkerGrid> SlinkerGrid::FindSolutions(bool guessing_allowed,int max_n_wanted_solutions)
{
	// retrieve some solving rules from somewhere
	vector<TRule> solving_rules;
	ReadRulesFromFile("solving_rules_3.txt",solving_rules); // load the rules from file
	
	// find some solutions
	vector<SlinkerGrid> solutions;
	FollowPossibilities(solving_rules,solutions,guessing_allowed,max_n_wanted_solutions);
	return solutions;
}

void SlinkerGrid::MakePuzzle()
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
				solutions = pad.FindSolutions(false,2); // disallow back-tracking (else problems created are *hard*)
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
	const int N=20;// size not really important here as long as it's big enough
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
		for(vector<TElement>::const_iterator rule_it = it1->required.begin();rule_it!=it1->required.end();rule_it++)
			g.cells[rule_it->x+spx][rule_it->y+spy] = rule_it->val;
		// apply the test set of rules
		g.ApplyRules(test_set,changed);
		// is there any implied that isn't present? if so then we keep this rule
		bool done=false;
		for(vector<TElement>::const_iterator rule_it = it1->implied.begin();rule_it!=it1->implied.end() && !done;rule_it++)
		{
			if(g.cells[rule_it->x+spx][rule_it->y+spy]==UNKNOWN)
			{
				nonredundant_rules.push_back(*it1);
				done = true;
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
	// whatever size you like.
	
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
	for(rules_it=rules.begin();rules_it!=rules.end();rules_it++)
	{
		// first work out the bounding box for the rule
		int left=INT_MAX,right=-INT_MAX,top=INT_MAX,bottom=-INT_MAX;
		for(it=rules_it->required.begin();it!=rules_it->required.end();it++)
		{
			if(it->x<left) left=it->x;
			if(it->y<top) top=it->y;
			if(it->x>right) right=it->x;
			if(it->y>bottom) bottom=it->y;
		}
		for(it=rules_it->implied.begin();it!=rules_it->implied.end();it++)
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
		SlinkerGrid req(width,height),impl(width,height);
		// write out the rule in machine-readable format (and draw the rule onto two grids)
		out << "#---------- Rule " << rules_it-rules.begin()+1 << ": --------------\nrequired:\n";
		for(it=rules_it->required.begin();it!=rules_it->required.end();it++)
		{
			out << it->x << "," << it->y << "," << it->val << "\n";
			req.cells[cx+it->x][cy+it->y]=it->val; 
			impl.cells[cx+it->x][cy+it->y]=it->val;
		}
		out << "implied:\n";
		for(it=rules_it->implied.begin();it!=rules_it->implied.end();it++)
		{
			out << it->x << "," << it->y << "," << it->val << "\n";
			impl.cells[cx+it->x][cy+it->y]=it->val;
		}
		// draw a visual depiction of the rule for humans
		{
			istringstream req_text(req.GetPrintOut()),impl_text(impl.GetPrintOut());
			out << "\n";
			int y;
			string s;
			for(y=0;y<2*height+1;y++)
			{
				out << "#         ";
				getline(req_text,s);
				out << s;
				if(y==height) out << "       =>         ";
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
	while(!in.eof())
	{
		getline(in,line); 
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
			istringstream iss(line);
			char c;
			iss >> el.x >> c >> el.y >> c >> el.val;
			if(el.val==INT_MAX) // bad way to test read success :(
				throw(runtime_error("Error reading file: expected x,y,val"));
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
