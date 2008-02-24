#include "SlinkerGrid.h"

#ifndef __1203871626__
#define __1203871626__

#include <vector>
using std::vector;

vector<SlinkerGrid::TRule> GetSolvingRules4()
{
	vector<SlinkerGrid::TRule> rules;

	{
		// ---------- Rule 1: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         0                                            0  x              
			+     +     +     +     +         =>         +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 2: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +  x  +     +     +  
			      |  1                                         |  1  x              
			+     +     +     +     +         =>         +     +  x  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 3: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,-1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +  x  +     +     +                    +     +  x  +     +     +  
			         1  x                                      |  1  x              
			+     +  x  +     +     +         =>         +     +  x  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 4: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,2));
		r.required.push_back(SlinkerGrid::TElement(-1,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +  -  +     +     +                    +     +  -  +     +     +  
			      |  2                                         |  2  x              
			+     +     +     +     +         =>         +     +  x  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 5: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,-1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.implied.push_back(SlinkerGrid::TElement(2,1,1));
		r.implied.push_back(SlinkerGrid::TElement(3,0,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +  x  +     +     +                    +     +  x  +     +     +  
			      x  2                                         x  2  |              
			+     +     +     +     +         =>         +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 6: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.required.push_back(SlinkerGrid::TElement(3,0,0));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +  -  +     +     +  
			      x  2  x                                      x  2  x              
			+     +     +     +     +         =>         +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 7: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.required.push_back(SlinkerGrid::TElement(3,0,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +  x  +     +     +  
			      |  2  |                                      |  2  |              
			+     +     +     +     +         =>         +     +  x  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 8: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +  x  +     +     +                    +     +  x  +     +     +  
			         3                                         |  3  |              
			+     +     +     +     +         =>         +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 9: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            |                                            |              
			+     +     +     +     +         =>         +     +  x  +  x  +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 10: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(1,-2,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                         x              
			+     +     +  -  +     +         =>         +     +  x  +  -  +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 11: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,1,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +     +  -  +     +         =>         +     +  -  +  -  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 12: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +     +  x  +     +         =>         +     +  -  +  x  +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 13: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +     +  x  +     +         =>         +     +  x  +  x  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 14: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		r.implied.push_back(SlinkerGrid::TElement(0,3,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +  x  +  -  +  x  +     +  
			               3                        =>                        3                 
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 15: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +     +     +     +     +                    +     +  x  +  -  +     +     +  
			               3                        =>                     |  3                 
			+     +     +     +     +     +                    +     +     +     +  x  +     +  
			                  |                                                  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 16: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +  
			               3                                                     |  3                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     3                                                        3  |              
			+     +     +     +     +     +     +                    +     +     +     +  -  +  x  +     +  
			                                                                                 x              
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 17: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +  x  +     +         =>         +     +  x  +  x  +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 18: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			         3                              =>                  3  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 19: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3     1                        =>                  3     1  x              
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 20: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1  x              
			+     +     +  x  +     +         =>         +     +  x  +  x  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 21: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,1,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			            x                           =>                     x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 22: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,3,0));
		r.implied.push_back(SlinkerGrid::TElement(-2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +  x  +     +  x  +     +  
			               2                        =>                        2                 
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 23: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                        =>               x        3                 
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 24: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                        =>               x        3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 25: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3  |              
			+     +     +  x  +     +         =>         +     +  -  +  x  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 26: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +  
			               3                                                     |  3                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2                                                        2  |              
			+     +     +     +  x  +     +     +                    +     +     +     +  x  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 27: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +  
			               3                                                     |  3                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2                                                        2                 
			+     +     +     +     +     +     +                    +     +     +     +     +  x  +     +  
			                        |                                                        |              
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 28: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,3));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(4,5,1));
		r.implied.push_back(SlinkerGrid::TElement(5,4,1));
		r.implied.push_back(SlinkerGrid::TElement(5,6,0));
		r.implied.push_back(SlinkerGrid::TElement(6,5,0));
		/*
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                           x                                
			+     +     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +     +  
			               3                                                           |  3                             
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                     2                              =>                              2                       
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                           3                                                              3  |              
			+     +     +     +     +     +     +     +                    +     +     +     +     +  -  +  x  +     +  
			                                                                                             x              
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 29: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			         2                                               |  2                       
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			            |                           =>                     |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 30: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			         2                                               |  2                       
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                        =>                     x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 31: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +  -  +     +     +                    +     +  -  +     +     +  
			            |                                      x     |              
			+     +  -  +     +     +         =>         +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 32: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			               3                                         x        3                 
			+     +  -  +     +     +     +         =>         +     +  -  +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 33: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +     +     +                    +     +     +     +  x  +     +  
			                  |                                                  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 34: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,3,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(3,4,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +  -  +     +                    +     +     +     +  -  +     +  
			                                                                     x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 35: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +  x  +     +     +  
			         1     1                  =>                  1     1           
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 36: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +  x  +     +     +  
			         1     1                  =>                  1     1           
			+     +     +     +     +                    +     +     +     +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 37: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +  x  +     +     +  
			         1     1                  =>                  1     1           
			+     +     +     +     +                    +     +     +     +     +  
			               3                                            3           
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 38: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,3,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         2     1                        =>                  2     1  x              
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 39: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +  x  +     +                    +     +  x  +  x  +     +  
			         2                        =>                  2                 
			+     +  -  +     +     +                    +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 40: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         2     1                        =>                  2     1  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 41: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,5,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +  x  +     +                    +     +     +  x  +     +  
			         2                                            2                 
			+     +     +     +     +         =>         +     +     +  x  +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 42: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +     +     +     +  
			         2     1                  =>                  2     1           
			+     +     +     +     +                    +     +     +  x  +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 43: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         2     1                        =>                  2     1  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 44: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +  x  +     +                    +     +     +  x  +     +  
			         2                        =>                  2                 
			+     +     +     +     +                    +     +     +  x  +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 45: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +     +     +                    +     +     +     +     +  
			         2     1                  =>                  2     1           
			+     +     +     +     +                    +     +     +  x  +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 46: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         1                                            1                 
			+     +     +  x  +     +                    +     +     +  x  +     +  
			         2                        =>                  2                 
			+     +     +  -  +     +                    +     +     +  -  +     +  
			                                                         x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 47: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.implied.push_back(SlinkerGrid::TElement(2,5,1));
		r.implied.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(3,6,0));
		r.implied.push_back(SlinkerGrid::TElement(4,5,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			         2                                                  2                       
			+     +     +     +     +     +         =>         +     +     +     +     +     +  
			               3                                                  3  |              
			+     +     +     +     +     +                    +     +     +  -  +  x  +     +  
			                                                                     x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 48: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.implied.push_back(SlinkerGrid::TElement(2,5,1));
		r.implied.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(3,6,0));
		r.implied.push_back(SlinkerGrid::TElement(4,5,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         2     1                                            2     1                 
			+     +     +     +     +     +         =>         +     +     +     +     +     +  
			               3                                                  3  |              
			+     +     +     +     +     +                    +     +     +  -  +  x  +     +  
			                                                                     x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 49: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3        |                     =>                  3        |              
			+     +  -  +     +     +     +                    +     +  -  +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 50: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3           3                  =>                  3           3           
			+     +  -  +     +     +     +                    +     +  -  +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 51: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(0,4,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3        |                     =>                  3  |     |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 52: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(0,4,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3           3                  =>                  3  |        3           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 53: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3        |                     =>                  3  |     |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 54: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                                                  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3           3                  =>                  3  |        3           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 55: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,2,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3     2  |                     =>                  3     2  |              
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 56: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1  x                     =>                        1  x              
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 57: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3  |                     =>                        3  |              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 58: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1     1                        =>               x  1     1  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 59: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1        |                     =>               x  1        |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 60: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			         3                                                        3                             
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			         1           3                        =>               x  1           3                 
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			         3                                                        3                             
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 61: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(0,3,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			         1     1                  =>                  1     1           
			+     +     +     +     +                    +     +  x  +  x  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 62: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +     +     +     +     +                    +     +  x  +  -  +     +     +  
			               3                                               |  3                 
			+     +     +     +     +     +         =>         +     +     +     +     +     +  
			               1     2                                            1     2           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                  x                                                  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 63: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1     1                        =>               x  1     1  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            |                                                  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 64: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1     1                        =>               x  1     1  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                               |  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 65: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			         2                              =>               x  2                       
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 66: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3  |              
			+     +     +     +     +                    +     +     +  x  +     +  
			         2     1                  =>                  2     1           
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 67: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                         x              
			+     +     +     +     +                    +     +  -  +  x  +     +  
			         3                                            3  |              
			+     +     +     +     +         =>         +     +     +  x  +     +  
			         2                                            2                 
			+     +     +  x  +     +                    +     +     +  x  +     +  
			            x                                            x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 68: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(-2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +  -  +     +     +     +  
			               3                                                        3                       
			+     +     +     +     +     +     +                    +     +  x  +     +     +     +     +  
			               2     2                                                  2     2  |              
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                  |                                                        |                    
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 69: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.implied.push_back(SlinkerGrid::TElement(-2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,5,1));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +  -  +     +     +     +  
			               3                                                        3                       
			+     +     +     +     +     +     +                    +     +  x  +     +     +     +     +  
			               2     2                                                  2     2                 
			+     +     +     +     +     +     +         =>         +     +     +     +     +  x  +     +  
			                     3                                                        3                 
			+     +     +     +     +     +     +                    +     +     +     +  -  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 70: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,3,0));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +     +     +     +     +                    +     +  x  +  -  +     +     +  
			               3                                               |  3                 
			+     +     +     +     +     +         =>         +     +     +     +     +     +  
			                     2                                                  2           
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                  x                                                  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 71: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +  
			               3                                                     |  3                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     1  x                                                     1  x              
			+     +     +     +  x  +     +     +                    +     +     +     +  x  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 72: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,4,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		r.implied.push_back(SlinkerGrid::TElement(2,5,0));
		r.implied.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(5,2,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			         3                                                        3                             
			+     +     +     +     +     +     +                    +     +     +     +  x  +     +     +  
			               2     1                                                  2     1  x              
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			               1                                                     x  1                       
			+     +     +     +     +     +     +                    +     +     +  x  +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 73: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,4,1));
		r.required.push_back(SlinkerGrid::TElement(4,3,0));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		r.implied.push_back(SlinkerGrid::TElement(2,5,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               2                                                  2  |              
			+     +     +     +  x  +     +         =>         +     +     +     +  x  +     +  
			               1                                               x  1                 
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 74: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,0));
		r.required.push_back(SlinkerGrid::TElement(4,3,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         3                                                  3  |                    
			+     +     +     +     +     +                    +     +  -  +  x  +     +     +  
			               2                        =>                     x  2  |              
			+     +     +     +  x  +     +                    +     +     +  -  +  x  +     +  
			                  x                                                  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 75: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.implied.push_back(SlinkerGrid::TElement(0,3,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			         2     1                                            2     1  x              
			+     +     +     +     +     +                    +     +  -  +     +     +     +  
			            x                           =>                     x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 76: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(0,3,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			         2                                               x  2  |                    
			+     +     +  x  +     +     +                    +     +  -  +  x  +     +     +  
			            x                           =>                     x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 77: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,4,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,5,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			         2                                               |  2                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               2  x                     =>                        2  x              
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 78: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(0,3,1));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +  x  +     +     +                    +     +  x  +     +     +  
			               2                  =>                        2           
			+     +  -  +     +     +                    +     +  -  +     +     +  
			                                                         x              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 79: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(1,4,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(0,3,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			            x                                            x              
			+     +  x  +     +     +                    +     +  x  +     +     +  
			               2                  =>                        2           
			+     +     +     +     +                    +     +  x  +     +     +  
			            |                                            |              
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 80: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			               2                        =>                     x  2  |              
			+     +     +  -  +     +     +                    +     +     +  -  +  x  +     +  
			                                                                     x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 81: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +  -  +     +     +  
			               2                        =>                     |  2  x              
			+     +     +     +     +     +                    +     +     +  x  +  -  +     +  
			                  |                                                  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 82: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,3,0));
		r.implied.push_back(SlinkerGrid::TElement(3,4,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +  x  +     +                    +     +     +     +  x  +     +  
			                                                                     x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 83: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,1));
		r.implied.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +     +     +                    +     +     +     +  x  +     +  
			                     1                                               x  1           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 84: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,3));
		r.required.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               3                        =>                        3                 
			+     +     +     +     +     +                    +     +     +     +  -  +     +  
			                  x                                                  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 85: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                  |                     =>                     x     |              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 86: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                     3                  =>                     x        3           
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 87: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x                                                  x                    
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                     3                  =>                     x        3           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 88: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            |                                                  |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                        2  x              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 89: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            |                                                  |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2  |                     =>                        2  |              
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 90: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,0));
		r.implied.push_back(SlinkerGrid::TElement(4,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            |                                                  |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +     +     +                    +     +     +     +  -  +     +  
			                  x                                                  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 91: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,3,0));
		r.implied.push_back(SlinkerGrid::TElement(3,4,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            |                                                  |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                        2                 
			+     +     +     +  x  +     +                    +     +     +     +  x  +     +  
			                                                                     |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 92: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(1,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,1));
		r.implied.push_back(SlinkerGrid::TElement(4,5,0));
		r.implied.push_back(SlinkerGrid::TElement(5,4,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			            |                                                        |                          
			+     +  x  +     +     +     +     +                    +     +  x  +     +     +     +     +  
			               2                                                        2                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     1                                                        1  x              
			+     +     +     +     +     +     +                    +     +     +     +  x  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 93: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(4,1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                               x  1                 
			+     +  x  +     +  -  +     +         =>         +     +  x  +     +  -  +     +  
			               1                                               x  1                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 94: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +     +     +         =>         +     +  x  +  x  +     +     +  
			               2  |                                               2  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 95: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(3,4,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(3,0,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			               1                                                  1  x              
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                                               |  2                 
			+     +     +     +     +     +         =>         +     +     +     +     +     +  
			                  |                                                  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 96: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			               1                                                  1                 
			+     +  x  +     +  x  +     +                    +     +  x  +  x  +  x  +     +  
			               2                        =>                        2                 
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 97: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,1,1));
		r.implied.push_back(SlinkerGrid::TElement(3,0,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1  x              
			+     +  x  +     +  -  +     +         =>         +     +  x  +     +  -  +     +  
			               2                                                  2                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 98: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,3,1));
		r.implied.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(3,0,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			               1                                                  1  x              
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2                        =>                     |  2                 
			+     +     +     +  -  +     +                    +     +     +     +  -  +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 99: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                  |                     =>                           |              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 100: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +  x  +     +                    +     +  x  +  x  +  x  +     +  
			                                        =>                                          
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 101: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                     3                  =>                              3           
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 102: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                  |                     =>                           |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 103: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +  x  +     +                    +     +  x  +  x  +  x  +     +  
			                                        =>                                          
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 104: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(4,2,3));
		r.implied.push_back(SlinkerGrid::TElement(2,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               1                                                  1                 
			+     +  x  +     +     +     +                    +     +  x  +  x  +     +     +  
			                     3                  =>                              3           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 105: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,0,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3  |                                               3  |              
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			                                        =>                           x              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 106: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +  x  +     +  x  +     +                    +     +  x  +  -  +  x  +     +  
			                                        =>                                          
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 107: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(3,0,1));
		r.implied.push_back(SlinkerGrid::TElement(3,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3  |                                               3  |              
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			                                        =>                           x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 108: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,4,3));
		r.required.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,1,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +  x  +     +  x  +     +                    +     +  x  +  -  +  x  +     +  
			                                        =>                                          
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               3                                                  3                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 109: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               1  x                     =>                        1  x              
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 110: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2  |                     =>                        2  |              
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 111: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,3,1));
		r.required.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               |                    
			+     +  x  +     +     +     +                    +     +  x  +     +     +     +  
			               2  x                     =>                        2  x              
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 112: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(4,1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			               1                                                  1                 
			+     +  -  +     +  -  +     +                    +     +  -  +     +  -  +     +  
			               1                        =>                        1                 
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 113: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(2,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			               2                                                  2                 
			+     +  -  +     +  -  +     +                    +     +  -  +     +  -  +     +  
			               2                        =>                        2                 
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 114: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,1));
		r.required.push_back(SlinkerGrid::TElement(2,3,0));
		r.required.push_back(SlinkerGrid::TElement(3,2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +  -  +     +     +     +                    +     +  -  +     +     +     +  
			               1  x                     =>                        1  x              
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 115: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(2,4,1));
		r.required.push_back(SlinkerGrid::TElement(4,2,1));
		r.implied.push_back(SlinkerGrid::TElement(1,4,0));
		r.implied.push_back(SlinkerGrid::TElement(2,5,0));
		r.implied.push_back(SlinkerGrid::TElement(4,1,0));
		r.implied.push_back(SlinkerGrid::TElement(5,2,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +  -  +     +     +     +     +                    +     +  -  +     +  x  +     +     +  
			               2     1                                                  2     1  x              
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			               1                              =>                     x  1                       
			+     +     +     +     +     +     +                    +     +     +  x  +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 116: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,-1,1));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.required.push_back(SlinkerGrid::TElement(4,0,3));
		r.implied.push_back(SlinkerGrid::TElement(2,3,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +  -  +     +     +                    +     +     +  -  +     +     +  
			         3     1     3                                      3     1     3           
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                        =>                                          
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 117: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(2,-3,0));
		r.required.push_back(SlinkerGrid::TElement(2,-2,2));
		r.required.push_back(SlinkerGrid::TElement(3,-2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +  x  +     +     +                    +     +     +  x  +     +     +  
			               2  |                                               2  |              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			         1                              =>               x  1                       
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 118: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(4,5,0));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(5,4,1));
		/*
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                           x                                
			+     +     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +     +  
			               3                                                           |  3                             
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                     2                              =>                              2                       
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                           2                                                              2  |              
			+     +     +     +     +  x  +     +     +                    +     +     +     +     +  x  +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 119: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(5,6,1));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(6,5,0));
		/*
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                           x                                
			+     +     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +     +  
			               3                                                           |  3                             
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                     2                              =>                              2                       
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                           2                                                              2                 
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +  x  +     +  
			                              |                                                              |              
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
			                                                                                                            
			+     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 120: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(6,6,3));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(6,7,1));
		r.implied.push_back(SlinkerGrid::TElement(7,6,1));
		r.implied.push_back(SlinkerGrid::TElement(7,8,0));
		r.implied.push_back(SlinkerGrid::TElement(8,7,0));
		/*
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
			                                                                                                                        
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
			                                                                                 x                                      
			+     +     +     +     +     +     +     +     +                    +     +  x  +  -  +     +     +     +     +     +  
			               3                                                                 |  3                                   
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
			                     2                                                                    2                             
			+     +     +     +     +     +     +     +     +         =>         +     +     +     +     +     +     +     +     +  
			                           2                                                                    2                       
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
			                                 3                                                                    3  |              
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +  -  +  x  +     +  
			                                                                                                         x              
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
			                                                                                                                        
			+     +     +     +     +     +     +     +     +                    +     +     +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 121: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(4,5,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(5,4,1));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +  -  +     +     +     +     +                    +     +  -  +     +     +     +     +  
			               2                                                        2                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2                                                        2  |              
			+     +     +     +  x  +     +     +                    +     +     +     +  x  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 122: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(5,4,0));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(4,5,1));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +  -  +     +     +     +     +                    +     +  -  +     +     +     +     +  
			               2                                                        2                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2  x                                                     2  x              
			+     +     +     +     +     +     +                    +     +     +     +  -  +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 123: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(5,6,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(6,5,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +  -  +     +     +     +     +                    +     +  -  +     +     +     +     +  
			               2                                                        2                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2                                                        2                 
			+     +     +     +     +     +     +                    +     +     +     +     +  x  +     +  
			                        |                                                        |              
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 124: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,1,1));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.required.push_back(SlinkerGrid::TElement(4,4,2));
		r.required.push_back(SlinkerGrid::TElement(6,5,1));
		r.implied.push_back(SlinkerGrid::TElement(1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(5,6,0));
		/*
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                     x                          
			+     +  -  +     +     +     +     +                    +     +  -  +     +     +     +     +  
			               2                                                        2                       
			+     +     +     +     +     +     +         =>         +     +     +     +     +     +     +  
			                     2                                                        2                 
			+     +     +     +     +  -  +     +                    +     +     +     +     +  -  +     +  
			                                                                                 x              
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
			                                                                                                
			+     +     +     +     +     +     +                    +     +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 125: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(1,0,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.required.push_back(SlinkerGrid::TElement(4,2,2));
		r.required.push_back(SlinkerGrid::TElement(5,2,0));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,1));
		r.implied.push_back(SlinkerGrid::TElement(4,3,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  -  +     +     +     +  
			      x  2                                               x  2                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               2  x                     =>                        2  x              
			+     +     +     +     +     +                    +     +     +  -  +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 126: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(-1,0,0));
		r.required.push_back(SlinkerGrid::TElement(0,0,2));
		r.required.push_back(SlinkerGrid::TElement(1,2,0));
		r.required.push_back(SlinkerGrid::TElement(2,0,1));
		r.implied.push_back(SlinkerGrid::TElement(0,1,1));
		r.implied.push_back(SlinkerGrid::TElement(1,-2,1));
		r.implied.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(3,0,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               |                    
			+     +     +     +     +     +                    +     +     +  x  +     +     +  
			      x  2     1                        =>               x  2     1  x              
			+     +     +     +     +     +                    +     +  -  +     +     +     +  
			            x                                                  x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 127: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(-1,0,0));
		r.required.push_back(SlinkerGrid::TElement(0,0,2));
		r.required.push_back(SlinkerGrid::TElement(2,0,2));
		r.required.push_back(SlinkerGrid::TElement(3,0,0));
		r.implied.push_back(SlinkerGrid::TElement(1,-2,0));
		r.implied.push_back(SlinkerGrid::TElement(1,2,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			      x  2     2  x                     =>               x  2     2  x              
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                               x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 128: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(-1,-2,0));
		r.required.push_back(SlinkerGrid::TElement(0,0,2));
		r.required.push_back(SlinkerGrid::TElement(1,-2,0));
		r.required.push_back(SlinkerGrid::TElement(2,-1,0));
		r.implied.push_back(SlinkerGrid::TElement(-2,-1,1));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			            x     x                                            x     x              
			+     +     +     +  x  +     +         =>         +     +  -  +     +  x  +     +  
			               2                                                  2                 
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 129: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,1));
		r.required.push_back(SlinkerGrid::TElement(0,3,0));
		r.required.push_back(SlinkerGrid::TElement(1,4,0));
		r.required.push_back(SlinkerGrid::TElement(2,2,2));
		r.implied.push_back(SlinkerGrid::TElement(-1,0,0));
		r.implied.push_back(SlinkerGrid::TElement(0,-1,0));
		/*
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +  x  +     +     +     +  
			         1                                               x  1                       
			+     +     +     +     +     +                    +     +     +     +     +     +  
			               2                                                  2                 
			+     +  x  +     +     +     +         =>         +     +  x  +     +     +     +  
			            x                                                  x                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
			                                                                                    
			+     +     +     +     +     +                    +     +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	return rules;
}

#endif
