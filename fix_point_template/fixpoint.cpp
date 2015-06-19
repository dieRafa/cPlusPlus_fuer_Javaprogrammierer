#include "fixpoint.hpp"

#include <iostream>
#include <cmath>


//Konstruktoren
fix_point::fix_point() : data(0)
{

}
//nicht optimal, Nachkommazeug wird nur abgeschnitten, nicht korrekt gerundet
fix_point::fix_point(float value) : data(static_cast<std::int32_t>(value * 65536))
{

}
fix_point::fix_point(double value) : data(static_cast<float>(value * 65536))
{

}
fix_point::fix_point(std::int32_t value) : data(value)
{

}

//Zuweisungsoperator
fix_point& fix_point::operator = (float value)  //funzt nicht ohne Zeiger
{
    data = static_cast<std::int32_t>(value * 65536);
    return *this;
}

//Cast
float fix_point::toFloat (){

}
//Vergleichoperatoren
bool fix_point::operator == (fix_point rhs) const
{
    return (data == rhs.data);
}

bool fix_point::operator != (fix_point rhs) const
{
    return (data != rhs.data);
}

bool fix_point::operator > (fix_point rhs) const
{
    return (data > rhs.data);
}

bool fix_point::operator >= (fix_point rhs) const
{
    return (data >= rhs.data);
}

bool fix_point::operator < (fix_point rhs) const
{
    return (data < rhs.data);
}

bool fix_point::operator <= (fix_point rhs) const
{
    return (data <= rhs.data);
}
/arithmetische Operatoren
fix_point fix_point::operator + (fix_point rhs) const
{
    const std::int32_t sum = data + rhs.data;
    return fix_point(sum);   //Konstruktoraufruf
}
fix_point fix_point::operator - (fix_point rhs) const
{
    const std::int32_t dif = data - rhs.data;
    return fix_point(dif);
}
fix_point fix_point::operator / (fix_point rhs) const   //aus 1.1
{
    fix_point result;
    result.data = (static_cast<std::int64_t>(data)<<16)/rhs.data;
    return result;

}
fix_point fix_point::operator * (fix_point rhs) const
{
    fix_point result;
    result.data = (static_cast<std::int64_t>(data) * rhs.data) >> 16;
    return result;
}
//+,-,/,% sind jetzt schon daa :)
fix_point fix_point::operator += (fix_point rhs)
{
    *this = *this + rhs;
    return *this;
    //return fix_point(data) = data + rhs.data;
}
fix_point fix_point::operator -= (fix_point rhs)
{
    *this = *this - rhs;
    return *this;
}
fix_point fix_point::operator /= (fix_point rhs)
{
    *this = *this / rhs;
    return *this;
}
fix_point fix_point::operator *= (fix_point rhs)
{
    *this = *this * rhs;
    return *this;
}
