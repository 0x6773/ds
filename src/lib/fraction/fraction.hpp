/*
 *
 * Made By : Govind Sahai
 * Licensed under MIT License
 * CopyRight 2015
 *
 * fraction.hpp
 *
 */


#pragma once

#ifndef _FRACTION_HPP_

#define _FRACTION_HPP_

#include "../stdafx.h"
#include "../first.hpp"

namespace fract
{
    template<typename T>
        auto gcd(const T&, const T&);
    template<typename T>
        auto lcm(const T&, const T&);

    template<typename T=long,bool S=true>
    class fraction
    {
        private:
            T numerator;
            T denominator;

 
            void shortener()
            {
                if(S)
                {
                    auto _gg=gcd(abs(this->numerator),abs(this->denominator));
                    if(_gg==0)
                    {
                        this->numerator=0;
                        this->denominator=1;
                    }
                    else
                    {
                        this->numerator=this->numerator/_gg;
                        this->denominator=this->denominator/_gg;
                    }
                }
                if(this->denominator<0)
                {
                    this->numerator*=-1;
                    this->denominator*=-1;
                }
                return;
            }

        public:
            fraction(T _num = 0,T _deno = 1)
                :   numerator(_num),denominator(_deno)
            {
                static_assert(is_integral<T>::value,"Template Type must be int, long, or long long");
                static_assert(!is_unsigned<T>::value,"Unsigned types not allowed. Only use signed types");
                assert(this->denominator!=0 && "Denominator cannot be zero.");
                this->shortener();
            }

            void operator()(std::pair<T,T> _pair)
            {
                this->numerator=_pair.first;
                this->denominator=_pair.second;

                this->shortener();
            }

            void operator()(std::initializer_list<T> _ilist)
            {
                size_t _ilsize=_ilist.size();
                assert(std::less_equal<size_t>()(_ilsize,2) && "Size of initializer list must be less than 3");
                if(_ilsize==2)
                {
                    this->numerator=*(_ilist.begin());
                    this->denominator=*(next(_ilist.begin()));
                }
                else if(_ilsize==1)
                {
                    this->numerator=*(_ilist.begin());
                    this->denominator=1;
                }
                else
                {
                    this->numerator=0;
                    this->denominator=1;
                }
            }

            ~fraction()
            {
                //  Destructor
            }

            auto getNumerator() const
            {
                return this->numerator;
            }

            auto getDenominator() const
            {
                return this->denominator;
            }

            auto getValue() const
            {
                return static_cast<long double>(this->numerator)/static_cast<long double>(this->denominator);
            }

            void setNumerator(T _num)
            {
                this->numerator=_num;
                this->shortener();
            }

            void setDenominator(T _deno)
            {
                this->denominator=_deno;
                this->shortener();
            }
            
            void inverse()
            {
                assert(this->numerator!=0 && "To inverse a fraction Numerator must be non-Zero");
                swap(this->numerator,this->denominator);
                this->shortener();
            }

            void info()
            {
                cout<<this->numerator<<"/"<<this->denominator<<endl;
            }

    };
    
     template<typename T>
     auto gcd(const T& _value1, const T& _value2)
     {
          return mydetails::gcd(_value1,_value2);
     }

    template<typename T>
     auto lcm(const T& _value1,const T& _value2)
     {
        return std::multiplies<T>()(_value1,_value2)/gcd(_value1,_value2);
     }
    /*
     *  Tests Done
     */
    template<typename T,bool S>
    auto& operator<<(std::ostream& strmo,fraction<T,S>& fract)
    {
        auto _num=fract.getNumerator();
        auto _deno=fract.getDenominator();

        strmo<<_num<<"/"<<_deno;

        return strmo;
    }

    /*
     *  Tests Done
     */
    template<typename T,bool S>
    auto& operator<<(std::ostream& strmo,fraction<T,S>&& fract)
    {
        auto _num=fract.getNumerator();
        auto _deno=fract.getDenominator();

        strmo<<_num<<"/"<<_deno;

        return strmo;
    }

    /*
     *  Tests Done
     */
    template<typename T,bool S>
    auto& operator>>(std::istream& strmi,fraction<T,S>& fract)
    {
        T _temp;
        strmi>>_temp;
        fract.setNumerator(_temp);
        strmi.ignore();
        strmi>>_temp;
        fract.setDenominator(_temp);           
        return strmi;
    }

    /*
     *  Checking Equality
     *  Tests Done All tests are using this :p
     */
    template<typename T1,bool S1,typename T2,bool S2>
    bool operator==(const fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
    {
        static_assert(std::is_same<T1,T2>::value, "Both fractions should be of same first type");
            
        return fract1.getNumerator()==fract2.getNumerator()&&
            fract1.getDenominator()==fract2.getDenominator();
    }

    /*
     *  Checking which is bigger
     */
    template<typename T1,bool S1,typename T2,bool S2>
    bool operator<(const fraction<T1,S1>& fract1, const fraction<T2,S2>& fract2)
    {
        static_assert(std::is_same<T1,T2>::value,"Both fractions should have same type");
        return fract1.getValue()<fract2.getValue();
    }


    /*
     *  Adding two fractions
     *  Tests Done
     */
    template<typename T1,bool S1,typename T2,bool S2,bool S3=S1||S2>
    auto operator+(const fraction<T1,S1>& fract1, const fraction<T2,S2>& fract2)
    {
       static_assert(std::is_same<T1,T2>::value, "Both fractions should be of similar data type");

       auto n1=fract1.getNumerator();
       auto n2=fract2.getNumerator();
       auto d1=fract1.getDenominator();
       auto d2=fract2.getDenominator();

       auto d=lcm(d1,d2);
       auto n=n1*(d/d1)+n2*(d/d2);

       return move(fraction<T1,S3>(n,d));        
    }

     /*
      *  operator+=
      */
     template<typename T1,bool S1,typename T2,bool S2>
     void operator+=(fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
     {
         fract1=(fract1+fract2);
     }   

     /*
      *  Adding number from/to fraction
      */
     template<typename T1,bool S1,typename T>
     auto operator+(const fraction<T1,S1>& fract, T _value)
     {
         return (fract+fraction<T1,S1>(_value));
     }

     template<typename T1,bool S1,typename T>
     auto operator+(T _value, const fraction<T1,S1>& fract)
     {
         return (fract + _value);
     }

    /*
     *  Substracting two fractions
     *  Tests Done
     */
    template<typename T1,bool S1,typename T2,bool S2,bool S3=S1||S2>
    auto operator-(const fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
    {
        static_assert(std::is_same<T1,T2>::value,"Both fractions should be of similar data type");
        
        auto n1=fract1.getNumerator();
        auto n2=fract2.getNumerator();
        auto d1=fract1.getDenominator();
        auto d2=fract2.getDenominator();

        auto d=lcm(d1,d2);
        auto n=n1*(d/d1)-n2*(d/d2);

        return move(fraction<T1,S3>(n,d));
    } 

    /*
     *  operator-=
     */
    template<typename T1,bool S1,typename T2,bool S2>
    void operator-=(fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
    {
        fract1=(fract1-fract2);
    }

    /*
     *  Substracting number from/to fraction
     */
    template<typename T1,bool S1,typename T>
    auto operator-(const fraction<T1,S1>& fract, T _value)
    {
        return (fract-fraction<T1,S1>(_value));
    }

    template<typename T1,bool S1,typename T>
    auto operator-(T _value, const fraction<T1,S1>& fract)
    {
        return -1*(fract - _value);
    }

    /*
     *  Multiples two fraction
     */
    template<typename T1,bool S1,typename T2,bool S2,bool S3=S1||S2>
    auto operator*(const fraction<T1,S1>& fract1, const fraction<T2,S2>& fract2)
    {
        static_assert(std::is_same<T1,T2>::value,"Both fractions should be of similar data type"); 

        auto n1=fract1.getNumerator();
        auto n2=fract2.getNumerator();
        auto d1=fract1.getDenominator();
        auto d2=fract2.getDenominator();

        auto d=d1*d2;
        auto n=n1*n2;

        return move(fraction<T1,S3>(n,d));
    }

    /*
     *  operator*=
     */
    template<typename T1,bool S1,typename T2,bool S2>
    void operator*=(fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
    {
        fract1=(fract1*fract2);
    }

    /*
     *  Multipling number from fraction
     */
    template<typename T1,bool S1,typename T>
    auto operator*(const fraction<T1,S1>& fract, T _value)
    {
        return (fract*fraction<T1,S1>(_value));
    }

    template<typename T1,bool S1,typename T>
    auto operator*(T _value, const fraction<T1,S1>& fract)
    {
        return (fract * _value);
    }
    

    /*
     *  Divides two fraction
     */
    template<typename T1,bool S1,typename T2,bool S2,bool S3=S1||S2>
    auto operator/(const fraction<T1,S1>& fract1, fraction<T2,S2> fract2)
    {
        static_assert(std::is_same<T1,T2>::value,"Both fractions should be of similar data type"); 
        
        assert(fract2.getNumerator()!=0 && "Cannot divide by zero");
        
        fract2.inverse();
        return (fract1*fract2);
    }

    /*
     *  operator/=
     */
    template<typename T1,bool S1,typename T2,bool S2>
    void operator/=(fraction<T1,S1>& fract1,const fraction<T2,S2>& fract2)
    {
        fract1=(fract1/fract2);
    }

    /*
     *  Dividing number from/to fraction
     */
    template<typename T1,bool S1,typename T>
    auto operator/(const fraction<T1,S1>& fract, T _value)
    {
        return (fract/fraction<T1,S1>(_value));
    }

    template<typename T1,bool S1,typename T>
    auto operator/(T _value, const fraction<T1,S1>& fract)
    {
        if(_value==0)
            return fraction<T1,S1>();
        else
        {
            fraction<T1,S1> fract1=fract/_value;
            fract1.inverse();
            return move(fract1);
        }
    }

    /*
     *  pow(fraction<>, _value)
     */
    template<typename T1,bool S1,typename T>
    void pow(fraction<T1,S1>& fract,T _value)
    {
        static_assert(is_integral<T>::value,"Power must be integral");
       T1 n=std::pow(fract.getNumerator(),_value);
       T1 d=std::pow(fract.getDenominator(),_value);

       fract.setNumerator(n);
       fract.setDenominator(d);
    }
}

#endif //   _FRACTION_HPP_
