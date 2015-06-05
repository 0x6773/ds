// Randomized_Quick_Select.cpp
// Page : 543 : DS&A MTG
#include <iostream>
#include <algorithm>
#include <vector>
#include "/home/mnciitbhu/Codes/first.hpp"

using namespace std;
using namespace mydetails;

template<typename IT,
	 typename S = typename iterator_traits<IT>::value_type>
S quickSelect(IT _Forw,
	      IT _End,
	      size_t pos)
{
  if(_Forw == _End)
    return *_Forw;
  
  vector<S> les;
  vector<S> equ;
  vector<S> grt;

  S k = *_Forw;
  
  copy_if(_Forw, _End, back_inserter(les),
	  [=](const S& var)
	  {
	    return var < k;
	  });
  copy_if(_Forw, _End, back_inserter(equ),
	  [=](const S& var)
	  {
	    return var == k;
	  });
  copy_if(_Forw, _End, back_inserter(grt),
	  [=](const S& var)
	  {
	    return var > k;
	  });
  /* or do the following instead of above copy_if`s
  for(const auto& x : ar)
  {
    if(x < k) les.push_back(x);
    else if(x == k) equ.push_back(x);
    else grt.push_back(x);
  }*/

  if(pos < les.size())
    return quickSelect(les.begin(),
		       les.end(),
		       pos);
  else if(pos < les.size() + equ.size())
    return equ[0];
  else
    return quickSelect(grt.begin(),
		       grt.end(),
		       pos - les.size() - equ.size());
}

int main()
{
  vector<int> ar;

  for(int i = 0; i < 20; ++i)
    ar.push_back(rand() % 50);

  print(ar);
  for(int i = 0; i < 20; ++i)
    cout<<quickSelect(ar.begin(), ar.end(), i)<<" ";
  cout<<endl;
  sort(ar.begin(), ar.end());
  print(ar);
  
  return 0;
}
	      
