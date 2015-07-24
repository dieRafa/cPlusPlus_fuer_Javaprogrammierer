#include <iostream>
#include "fix_point_oo.hpp"
#include <cmath>

//Konstruktoren
//Initialisierung von data geht nur in ctors im "Methodenkopf"
fix_point::fix_point() : data(0)
{

}
//nicht optimal, Nachkommazeuch wird nur abgeschnitten, nicht korrekt gerundet
fix_point::fix_point(float value) : data(static_cast<std::int32_t>(value * 65536))
{

}
fix_point::fix_point(double value) : data(static_cast<float>(value * 65536))
{

}
fix_point::fix_point(std::int32_t value) : data(value)
{

}

//Klassenoperatoren
//Zuweisungsoperator
fix_point& fix_point::operator = (float value)  //funzt nicht ohne Zeiger
{
    data = static_cast<std::int32_t>(value * 65536);
    return *this;
}

//Vergleichsoperatoren

bool fix_point::operator == (fix_point rhs) const
{
    return (data == rhs.data);
}

/*bool fix_point::operator != (fix_point rhs) const
{
    return (data != rhs.data);
}*/

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

//arithmetische Operatoren
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

fix_point fix_point::operator%(fix_point rhs) const {
    return fix_point(data % rhs.data);
}

//+,-,/,% sind jetzt schon daa :) -> Rafa fragt: der % war schon da?!
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

//Typkonvertierungsoperatoren
fix_point::operator float() const
{
    return to_float(*this);
}
fix_point::operator int() const
{
    return static_cast<int>(floor());
}

//Inkrement/Dekrement
fix_point fix_point::operator ++ ()
{
    data += 65536;   //int32-äquivalent von 1
    return *this;
}
fix_point fix_point::operator -- ()
{
    data -= 65536;
    return *this;
}
fix_point fix_point::operator ++ (int)
{
    fix_point result(data);
    ++(*this);  //funzt, weil es als pre bereits implementiert ist
    return result;
}
fix_point fix_point::operator -- (int)
{
    fix_point result(data);
    --(*this);  //funzt, weil es als pre bereits implementiert ist
    return result;
}

//Klassenfrac
float fix_point::frac() const
{
    float temp = 0;
    for (int i = 0; i<16; ++i){
        if(1 == ((data >> (15-i)) & 1))
            temp+= pow(2,-1-i);
    }
    return temp;
}
//Klassenfloor
float fix_point::floor() const{
    return  data >> 16;
}


//freistehende Funktionen
fix_point to_fix_point (float value){
    return fix_point((int)(value * pow(2,16)));
}
float to_float(fix_point value){
    return floor(value) + frac(value);
}

float frac(fix_point value)
{
    return value.frac();
}

float floor(fix_point value){
    return  value.floor();
}

fix_point sin(fix_point x)
{
    return (x - x*x*x / fix_point(6.f) + x*x*x*x*x / fix_point(120.f));

}

fix_point cos(fix_point x)
{
    return(fix_point(1.f) - x*x / fix_point(2.f) + x*x*x*x / fix_point(24.f) - x*x*x*x*x*x / fix_point(720.f));
}
