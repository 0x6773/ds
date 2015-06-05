#include "/home/mnciitbhu/Codes/stdafx.h"
#include "/home/mnciitbhu/Codes/first.hpp"
#include "fraction.hpp"

using namespace std;
using namespace mydetails;
using namespace fract;
using namespace std::rel_ops;

#define T long
auto ff(T a=0,T b=1)
{
    return fraction<T>(a,b);
}

void addition_tests()
{
    assert(ff(2)+ff(3,2)==ff(7,2));
    assert(ff(-10)+ff(5,2)==ff(-15,2));
    assert(ff(-5)+ff()==ff(-5));
    assert(ff(-23,4)+ff(-34,2)==ff(-91,4));

    cout<<"Addition tests passed"<<endl;
}

void addition_number_tests()
{
    assert(ff(2)+2==ff(4));
    assert(ff(3,2)+5==ff(13,2));
    assert(ff(-5,6)+20==ff(115,6));

    assert(2+ff(2)==ff(4));
    assert(5+ff(3,2)==ff(13,2));
    assert(20+ff(-5,6)==ff(115,6));

    cout<<"Addition Number Test Passed"<<endl;
}

void substraction_tests()
{
    assert(ff(2)-ff(3,2)==ff(1,2));
    assert(ff(-10)-ff(5,2)==ff(-25,2));
    assert(ff(-5)-ff()==ff(-5));
    assert(ff(-23,4)-ff(-34,2)==ff(45,4));

    cout<<"Substraction test passed"<<endl;
}

void substraction_number_test()
{
    assert(ff(2)-2==ff());
    assert(ff(3,2)-5==ff(-7,2));
    assert(ff(-5,6)-20==ff(-125,6));

    assert(2-ff(2)==ff());
    assert(5-ff(3,2)==ff(7,2));
    assert(20-ff(-5,6)==ff(125,6));

    cout<<"Substraction Number Test Passed"<<endl;
}

void multiplication_tests()
{
    assert(ff(2)*ff(3,2)==ff(3));
    assert(ff(-10)*ff(5,2)==ff(-25));
    assert(ff(-5)*ff()==ff());
    assert(ff(-23,4)*ff(-34,2)==ff(782,8));

    cout<<"Multiplication tests passed"<<endl;
}

void multiplication_number_tests()
{
    assert(ff(2)*2==ff(4));
    assert(ff(3,2)*5==ff(15,2));
    assert(ff(-5,6)*20==ff(-50,3));

    assert(2*ff(2)==ff(4));
    assert(5*ff(3,2)==ff(15,2));
    assert(20*ff(-5,6)==ff(-50,3));

    cout<<"Multiplication Number Test Passed"<<endl;
}

void division_tests()
{
    assert(ff(2)/ff(3,2)==ff(4,3));
    assert(ff(-10)/ff(5,2)==ff(-4));
    assert(ff(-5)/ff(1)==ff(-5));
    assert(ff(-23,4)/ff(-34,2)==ff(23,68));

    cout<<"Division tests passed"<<endl;
}

void division_number_tests()
{
    assert(ff(2)/2==ff(1));
    assert(ff(3,2)/5==ff(3,10));
    assert(ff(-5,6)/20==ff(-5,120));

    assert(2/ff(2)==ff(1));
    assert(5/ff(3,2)==ff(10,3));
    assert(20/ff(-5,6)==ff(-24));

    cout<<"Division Number Test Passed"<<endl;
}

void pow_tests()
{
    auto foo=[](fraction<T> fs,T _val)
    {
        pow(fs,_val);
        return fs;
    };
    
    assert(foo(ff(2),3)==ff(8));
    assert(foo(ff(3,2),3)==ff(27,8));
    assert(foo(ff(-5,6),5)==ff(-3125,7776));
    assert(foo(ff(),5)==ff());

    cout<<"pow Test Passed"<<endl;
}

void stream_tests()
{
    auto foo=[](fraction<T> fs)
    {
       stringstream ss(ios::in|ios::out);
       ss<<fs;
        auto fr=ff();
        ss>>fr;
        return fr;        
    };
    
    assert(foo(ff(23,2))==ff(23,2));
    assert(foo(ff(-10))==ff(-10));
    assert(foo(ff(-23,4))==ff(-23,4));
    assert(foo(ff(23,-8))==ff(23,-8));

    cout<<"Stream test passed"<<endl;
}

void tests()
{
    addition_tests();
    addition_number_tests();
    substraction_tests();
    substraction_number_test();
    multiplication_tests();
    multiplication_number_tests();
    division_tests();
    division_number_tests();
    pow_tests();
    stream_tests();
}

int main()
{   
    tests();

    return 0;
}
