#pragma once

#include "stdafx.h"
#include "first.hpp"

//  Ref : https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/

namespace SparseTableNS
{
  template<typename T,typename Comp=std::less<T>>
  class SparseTable
  {
  public:
    std::vector<std::vector<T>> ar;

    Comp _comp;

    void build(const std::vector<T>& mnciitbhuar)
    {
      ar.resize(mnciitbhuar.size());
      for(auto& x : ar)
        x.resize(log2(mnciitbhuar.size())+1);

      T N = mnciitbhuar.size();

      for(T i=0;i<N;++i)
        ar[i][0]=i;

      for(T j=1;1<<j <=N;++j)
      {
        for(T i=0;i+(1<<j)-1<N;i++)
        {
          if(_comp(mnciitbhuar[ar[i][j-1]],mnciitbhuar[ar[i + (1<<(j-1))][j-1]]))
            ar[i][j]=ar[i][j-1];
          else
            ar[i][j]=ar[i+ (1<<(j-1))][j-1];
        }
      }
    }

    T query(const vector<T>& mnciitbhuar,const T& i,const T& j)
    {
      T k=log2(j-i+1);
      if(_comp(mnciitbhuar[ar[i][k]],mnciitbhuar[ar[j-pow(2,k)+1][k]]) ||
        (mnciitbhuar[ar[i][k]]==mnciitbhuar[ar[j-pow(2,k)+1][k]]))
        return ar[i][k];
      else
        return ar[j-pow(2,k)+1][k];
    }
  };
}
