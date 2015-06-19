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

float fix_point::toFloat (){

}
//Vergleichoperatoren
