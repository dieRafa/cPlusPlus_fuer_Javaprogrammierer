#include "fix_point.h"
#include <math.h>

/*Math-Operations*/
fix_point add(fix_point lhs,fix_point rhs){
    fix_point result;
    result.data = lhs.data + rhs.data;
    return result;
}

fix_point sub(fix_point lhs,fix_point rhs){
   fix_point result;
   result.data = lhs.data - rhs.data;
    return result;
}

fix_point mul(fix_point lhs,fix_point rhs){

    fix_point result;

    result.data = (static_cast<long>(lhs.data) * rhs.data) >> 16;

    return result;
}

fix_point div(fix_point lhs,fix_point rhs){
    fix_point result;
    result.data = (static_cast<long>(lhs.data)<<16)/rhs.data;
    return result;
}
