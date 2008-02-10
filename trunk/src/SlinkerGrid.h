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

#include <vector>
#include <string>

/// This class represents a slitherlink grid, and implements algorithms for solving puzzles and making them.
class SlinkerGrid
{
	public: // public static data

		/// special value for unknown cells/borders, otherwise for cells allowed values are 0,1,2,3; for borders: 0,1 for off/on
		static const int UNKNOWN = -1;

	public: // public type declarations

		/// the different shapes that can be embedded in the rectangle
		enum TGridShape
		{
			Rectangle, ///< default is to use the whole rectangle
			MissingCentre, ///< the central third is off-limits, giving a sort of donut shape
			Circle ///< (for square grids only) a circle is inscribed
		};
		/// an element is a value in an x,y location - used in rules
		struct TElement
		{
			int x,y; ///< a location on the grid (here a relative location)
			int val; ///< the value in that location
			TElement ( int xp,int yp,int value ) : x ( xp ),y ( yp ),val ( value ) {}
		};
		/// a rule says that if certain conditions are met, certain things must be true
		struct TRule
		{
			std::vector<TElement> required; ///< if these elements are present...
			std::vector<TElement> implied;  ///<   ...then these elements can be set
		};

	public: // public methods

		/// constructor
		/** @param x grid width (4+)
		* @param y grid height (4+)
		* @param gs shape of the grid
		*/
		SlinkerGrid ( int x,int y,TGridShape gs=Rectangle );

		SlinkerGrid ( const SlinkerGrid& g );
		SlinkerGrid& operator= ( const SlinkerGrid& g );

		/// equality operator checks whether two grids have the same size, shape and entries
		bool operator== ( const SlinkerGrid& g ) const;

		/// read/write cell value - valid range from (0,0) to (width-1,height-1) inclusive
		int& cellValue ( int x,int y );

		/// read/write border/cell value - valid range from (0,0) to (2*width,2*height) inclusive
		/** the grid is stored in the following way:
				\verbatim
					   0 1 2 3 4 5 6
					0  + - +   +   +
					1  | 3 |
					2  +   + - +   +    This is a 3x2 grid, stored in a 7x5 array.
					3  |       |
					4  + - + - +   +
				\endverbatim

			For cell entries (e.g. 1,1): value is 0,1,2,3 or UNKNOWN (shown blank).
			For border entries (eg. 1,0): value is 0,1 for off/on, or UNKNOWN.
			Dot ('+') entries are ignored.														*/
		int& gridValue ( int x,int y );

		/// retrieve a string representation of the grid, with newlines, for easy printing
		std::string GetPrintOut() const;

		///  Given a set of numbers entered into the grid, return the solutions (if any).
		/**  Will use the grid as-is - set all borders to UNKNOWN if you just want to find solutions given the numbers.
		*    @param guessing_allowed if false then only those solutions that can be found through simple rules are found; if true then recursion is also used to explore pathways
		*    @param max_n_wanted_solutions set this to limit the number of solutions that are needed - e.g. 2 if you want to know  whether multiple solutions exist, or 1 if you know a solution exists.
		*    @return the unique solutions that were found for the puzzle
		*/
		std::vector<SlinkerGrid> FindSolutions ( bool guessing_allowed,int max_n_wanted_solutions );

		/// given the grid size and shape, make a puzzle with a unique solution
		void MakePuzzle();

		/// sets all borders and cell entries to UNKNOWN
		void Clear();

		/// given the elementary slitherlink rules, search for new ones involving more elements
		static void FindNewRules();

		/// get the solving rules necessary to give us most of the rules of slitherlink
		static void GetElementarySolvingRules ( std::vector<TRule> &rules );

		/// get a hand-written list of solving rules
		static void GetSolvingRules ( std::vector<TRule> &rules );

		/// checks whether the (sub-)grid is in a plausible state, or has contradictions with the solving rules
		/** note that this function ignores edge borders and considers loops illegal and so is not for
			evaluating puzzles, just sub-grid rule-candidates (see FindNewRules)
			@param solving_rules the rules that will be used to check consistency
			@param SEARCH_BORDER this many entries around the edge are ignored 
			@param depth if zero then just applies local rules, else recurses down onto possibilities depth times
			@return returns whether a contradiction was found (false) or not (true)
		*/
		bool IsConsistent ( const std::vector<TRule> &solving_rules,const int& SEARCH_BORDER,int depth);

		/// Loopy has a simple format for puzzles, e.g. "4x4:a33a12032f3"
		static SlinkerGrid ReadFromLoopyFormat ( const std::string &string );
		std::string GetPuzzleInLoopyFormat();

		/// for nicer printing: set all off borders to UNKNOWN, which prints as a blank
		void MarkOffBordersAsUnknown();

	private: // private classes

		/// a 2x2 integer matrix for reflections and quarter rotations
		class TMatrix
		{
			public:
				TMatrix ( int i,int j,int k,int l ) : a ( i ),b ( j ),c ( k ),d ( l ) {}
				int mX ( int x,int y ) const { return a*x+b*y; }
				int mY ( int x,int y ) const { return c*x+d*y; }
			private:
				int a,b,c,d;
		};

	private: // private data

		/// the dimensions of the rectangular area under consideration
		int X,Y;

		/// [2X+1][2Y+1] where entries are for cells and borders, as in the diagram above
		std::vector< std::vector<int> > cells;

		/// the shape of the grid
		TGridShape grid_shape;

	private: // private static data

		/// an encoding of the von Neumann neighbourhood
		static const int NHOOD[4][2];

		/// the 8 symmetries (reflections and rotations)
		static const int N_SYMMETRIES = 8;
		static const TMatrix SYMMETRIES[N_SYMMETRIES];

	private: // private methods

		/// are the grid coordinates supplied valid?
		bool IsOnGrid ( int x,int y ) const;

		/// helper functions to identify where in the grid we are
		static bool IsOdd ( int a );
		static bool IsEven ( int a );
		static bool IsDot ( int x,int y );
		static bool IsBorder ( int x,int y );
		static bool IsCell ( int x,int y );
		static bool IsHorizontalBorder ( int x,int y );
		static bool IsVerticalBorder ( int x,int y );

		/// retrieves the number of set borders around this cell : x in [0,2*X+1), y in [0,2*Y+1)
		void GetBorderCountAroundCell ( int x,int y,int &min,int &max ) const;

		/// retrieves the number of set borders around this dot : x in [0,2*X+1), y in [0,2*Y+1)
		void GetBorderCountAroundDot ( int x,int y,int &min,int &max ) const;

		/// rule-assisted search for solutions : if guessing is on then recursion is used
		void FollowPossibilities ( const std::vector<TRule> &solving_rules,std::vector<SlinkerGrid> &solutions,
								bool guessing_allowed,unsigned int max_n_wanted_solutions );

		/// rules can be written to disk for sharing
		static void WriteRulesToFile ( const std::vector<TRule> &rules,const std::string &filename );
		static void ReadRulesFromFile ( const std::string &filename,std::vector<TRule> &rules );

		/// apply whatever local implication rules are valid
		/** @param rules the local solving rules that we use
			@param changed on return, gets pointers of the entries that were changed from UNKNOWN, can be passed into SlinkerGrid::UndoChanges()
			@return returns false when a grid is inconsistent, else true
		*/
		bool ApplyRules ( const std::vector<TRule>& rules,std::vector<int*> &changed );

		/// given a set of rules, find those which are not specified by the others
		static void FindNonRedundantRules ( const std::vector<TRule> &rules,std::vector<TRule>& nonredundant_rules );

		/// changes must have been made on this grid
		void UndoChanges ( const std::vector<int*> &changed );

		/// is this grid finished - is every border assigned a yes or no answer?
		bool IsFinished() const;

		/// does this grid break any rules, as it stands? (allowing for unknown entries)
		bool IsLegal() const;

		/// extract all dots that are connected to the one passed at the head of the array
		void CollectJoinedDots ( std::vector< std::pair<int,int> > &dots ) const;

		/// given an empty grid, generate a long wiggly loop line
		void FillGridWithRandomLoop();

		/// we've finished a grid, fill all the unknown borders with definite off state
		void MarkUnknownBordersAsOff();

		/// would turning this border on make a loop?
		bool WouldMakeALoop ( int x,int y ) const;

		/// does this grid contain any loops?
		bool HasLoop(); // (actually const but makes temporary changes...)
};
