// from a Dr Dobb's Journal article in 2000
// http://www.ddj.com/cpp/184401278

template <class random_iterator>
class IndexedComparison
{
   public:
      IndexedComparison (random_iterator begin,
         random_iterator end)
         : p_begin (begin), p_end (end) {}
      bool operator () (unsigned int a, unsigned int b) const
         { return *(p_begin + a) < *(p_begin + b); }

   private:
      random_iterator const p_begin;
      random_iterator const p_end;
};

