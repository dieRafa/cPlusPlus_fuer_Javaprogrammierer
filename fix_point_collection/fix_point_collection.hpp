#ifndef FIXPOINT_COLLECTION_H
#define FIXPOINT_COLLECTION_H

#include "fixpoint_oo.hpp"
//for unique_ptr
#include <memory>

class fix_point_collection {
public:

    fix_point_collection();
    //~fix_point_collection();

    void push_back(fix_point fp);
    fix_point pop_back();
    size_t size() const;
    fix_point sum() const;
    size_t count_value(fix_point fp);
    const fix_point& operator[](unsigned int index) const;
    fix_point& operator[](unsigned int index);
    fix_point operator[](fix_point index) const;

private:

    //std::array<fix_point, 0> myArray;   //nich dynamisch, Größe muss feststehen --> Buuh!
    //fix_point[3] myArray;    //oldschool c-style array

    //http://www.bromeon.ch/articles/raii.html
    //no need for destructor
    std::unique_ptr<fix_point []> myCollection;    //smartpointer, objekt hält zeiger auf fixpointarray
    unsigned int m_size;
};

size_t count_value(fix_point_collection &collection, fix_point fp);
fix_point sum(fix_point_collection &collection);


#endif // FIXPOINT_COLLECTION_H
