#include "head.h"

//----------KONSTRUKTOR----------//
Set::Set()
{
    power = 0;      //pusty uklad
    value = 0;      //--
    mayPower = 5;   //najlepszy uklad
    mayValue = 27;  //najwieksza wartosc kart
}


//----------OPERATOR >=----------//
bool Set::operator>=(Set s)
{
    if((s.power == 0) && (s.value == 0))
    {
        if((power > s.mayPower) || ((power == s.mayPower) && (value >= s.mayValue)))
            return 1;
        else
            return 0;
    }
    else
    {
        if((this->power > s.power) || ((power == s.power)&& (value >= s.value)))
            return 1;
        else
            return 0;
    }
}
