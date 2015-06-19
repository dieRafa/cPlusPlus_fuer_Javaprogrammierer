#ifndef FIX_POINT_H
#define FIX_POINT_H
#include <iostream>
#include <math.h>
/*#include<cstdint> -> c++11??*/

struct fix_point {
    signed int data;
};

/*Funktions-Deklaration*/
/*Umwandlung*/
inline fix_point to_fix_point(float value);
inline float to_float(fix_point value);
/*Vor- und Nachkommastellen*/
inline float floor(fix_point value);
inline float frac(fix_point value);
/*Gleichheit*/
inline bool equals(fix_point lhs,fix_point rhs);
inline bool less_than(fix_point lhs,fix_point rhs);
/*Math-Operations*/
fix_point add(fix_point lhs,fix_point rhs);
fix_point sub(fix_point lhs,fix_point rhs);
fix_point mul(fix_point lhs,fix_point rhs);
fix_point div(fix_point lhs,fix_point rhs);

/*Funktions-Definition- inline-Empfehlung*/
/*Convertierung*/

inline fix_point to_fix_point (float value){
    return {(int)(value * pow(2,16))};
}

inline float to_float(fix_point value){
    return floor(value) + frac(value);
}

/*Vor- und Nachkommastellen*/
inline float floor(fix_point value){
    return  value.data >> 16;
}

inline float frac(fix_point value){

    float temp = 0;
    for (int i = 0; i<=15; ++i){
        if(1 == ((value.data >> (15-i)) & 1))
            temp+= pow(2,-1-i);
    }
    return temp;
    /*
    std::cout << "value: " << value.data << std::endl;
    std::cout << (value.data << 15)<< std::endl;
    return value.data << 15;
    */
}


/*Gleichheit*/
inline bool equals(fix_point lhs,fix_point rhs){
    return (lhs.data == rhs.data);

}

inline bool less_than(fix_point lhs,fix_point rhs){
    return (lhs.data < rhs.data);
}

#endif // FIX_POINT_H

