#ifndef FIX_POINT_HPP
#define FIX_POINT_HPP
#include <cstdint>
#include <cmath>

template <int Data>
struct make_type
{

};
template<> struct make_type<8>{using type = std::int8_t;};
template<> struct make_type<16>{using type = std::int16_t;};
template<> struct make_type<32>{using type = std::int32_t;};
template<> struct make_type<64>{using type = std::int64_t;};

template <int rafa, int ela >
class fix_point {

public:

    const int rafa_bits = rafa;
    static const int post_point_bits = ela;
    static const int rafaela_bits = rafa + ela;

    using IntType = typename make_type<rafaela_bits>::type;

     IntType data;

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

    //Klassenfrac
    float frac() const;
    //Klassenfloor
    float floor() const;

   //Vergleichsoperatoren
   bool operator == (fix_point rhs) const;
   bool operator != (fix_point rhs) const;
   bool operator > (fix_point rhs) const;
   bool operator >= (fix_point rhs) const;
   bool operator < (fix_point rhs) const;
   bool operator <= (fix_point rhs) const;

   //arithmetische Operatoren
   fix_point operator + (fix_point rhs) const;
   fix_point operator - (fix_point rhs) const;
   fix_point operator / (fix_point rhs) const;
   fix_point operator * (fix_point rhs) const;

   fix_point operator += (fix_point rhs);
   fix_point operator -= (fix_point rhs);
   fix_point operator /= (fix_point rhs);
   fix_point operator *= (fix_point rhs);


    //Cast
   float toFloat();

   fix_point to_fix_point (float value){
       return {(int)(value * pow(2,16))};
   }

    operator float() {
       return toFloat();
   }

};

float frac (fix_point<16,16> value);
float floor (fix_point<16,16> value);


#endif
