// next_combination Template
// Written by Thomas Draper
//
// Designed after next_permutation in STL
// Inspired by Mark Nelson's article http://www.dogma.net/markn/articles/Permutations/
// 
// Start with a sorted container with thee iterators -- first, k, last
// After each iteration, the first k elements of the container will be 
// a combination. When there are no more combinations, the container
// will return to sorted order.

template <class BidirectionalIterator>
bool next_combination(BidirectionalIterator first, BidirectionalIterator k,
                      BidirectionalIterator last) {
   if ((first == last) || (k == first) || (k == last)) return false;
   BidirectionalIterator i = first;
   BidirectionalIterator ii = last;
   
   ++i;
   if (i == last) return false;
   i = last;
   --i;
   
   i = k;
   --ii;
   while (i != first){ 
      if (*--i < *ii){ // Search down to find first comb entry less than final entry
         BidirectionalIterator j = k;
         while(!(*i < *j)) j++; // Find swap position [good-1-high|good-2-low]
         iter_swap(i,j); // Swap [good-2-high|good-1-low]
         i++;j++;ii=k; // Move to rotation positions
         rotate(i,j,last); // Rotate [good-2-low-high-good-1]
         while(j!=last){ ++j; ++ii;} // Find high good position
         rotate(k,ii,last); // Rotate [good-2-(low/high>|good-1-<low/high)]
         return true;
      }
   }
   rotate (first,k,last);
   return false;
   
    
}
