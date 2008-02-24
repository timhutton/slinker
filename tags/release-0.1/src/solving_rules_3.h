#include "SlinkerGrid.h"

#ifndef __1203871633__
#define __1203871633__

#include <vector>
using std::vector;

vector<SlinkerGrid::TRule> GetSolvingRules3()
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
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			            |                     =>               x     |              
			+     +  -  +     +     +                    +     +  -  +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 24: --------------
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
		// ---------- Rule 25: --------------
		SlinkerGrid::TRule r;
		r.required.push_back(SlinkerGrid::TElement(0,0,3));
		r.required.push_back(SlinkerGrid::TElement(0,4,3));
		r.required.push_back(SlinkerGrid::TElement(1,2,1));
		r.implied.push_back(SlinkerGrid::TElement(-1,2,0));
		/*
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			            |                     =>               x     |              
			+     +     +     +     +                    +     +     +     +     +  
			         3                                            3                 
			+     +     +     +     +                    +     +     +     +     +  
			                                                                        
			+     +     +     +     +                    +     +     +     +     +  
		*/
		rules.push_back(r);
	}
	{
		// ---------- Rule 26: --------------
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
		// ---------- Rule 27: --------------
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
		// ---------- Rule 28: --------------
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
		// ---------- Rule 29: --------------
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
		// ---------- Rule 30: --------------
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
		// ---------- Rule 31: --------------
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
		// ---------- Rule 32: --------------
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
		// ---------- Rule 33: --------------
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
		// ---------- Rule 34: --------------
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
		// ---------- Rule 35: --------------
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
		// ---------- Rule 36: --------------
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
	return rules;
}

#endif
