#ifndef FIX_POINT_OO_HPP
#define FIX_POINT_OO_HPP

#include <cstdint>


class fix_point {

private:
    std::int32_t data;

public:
    //default Konstruktor
    fix_point();
    //Konstruktor mit float
    fix_point(float value);
    //Konstruktor mit double
    fix_point(double value);
    //Konstruktor mit int32
    explicit fix_point(std::int32_t value);

    //Klassen-Operatoren
    //Zuweisungsoperator
    fix_point& operator = (float value);

    //Vergleichsoperatoren
    bool operator == (fix_point rhs) const;
    bool operator != (fix_point rhs) const { return !operator==(rhs); };
    bool operator > (fix_point rhs) const;
    bool operator >= (fix_point rhs) const;
    bool operator < (fix_point rhs) const;
    bool operator <= (fix_point rhs) const;

    //arithmetische Operatoren
    fix_point operator + (fix_point rhs) const;
    fix_point operator - (fix_point rhs) const;
    fix_point operator / (fix_point rhs) const;
    fix_point operator * (fix_point rhs) const;
    fix_point operator % (fix_point rhs) const;

    fix_point operator += (fix_point rhs);
    fix_point operator -= (fix_point rhs);
    fix_point operator /= (fix_point rhs);
    fix_point operator *= (fix_point rhs);

    //Typkonvertierungsoperatoren
    //ohne explicite ambigouse geduense
    explicit operator float() const;
    explicit operator int() const;

    //Inkrement/Dekrement
    fix_point operator ++ ();   //prefix
    fix_point operator -- ();   //prefix

    fix_point operator ++ (int);    //postfix
    fix_point operator -- (int);    //postfix

    //Klassenfrac
    float frac() const;
    //Klassenfloor
    float floor() const;

};

//freistehende Funktionen
fix_point to_fix_point(float value);
float to_float(fix_point value);

float frac(fix_point value);
float floor(fix_point value);

fix_point sin(fix_point x);
fix_point cos(fix_point x);

#endif // FIX_POINT_OO_HPP


