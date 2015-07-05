
#include "fix_point_collection.hpp"
#include <algorithm>
#include <cmath>

fix_point_collection::fix_point_collection(): m_size(0)
{

}
//fix_point_collection::~fix_point_collection()
//{

//}
//add new element at the end of the collection
void fix_point_collection::push_back(fix_point fp)
{
    //Typ, Name, Konstruktor
    std::unique_ptr<fix_point []> temp (new fix_point[m_size + 1]);

    //copies old collection -> temp
    std::copy(myCollection.get(), myCollection.get() + m_size, temp.get());

    //new element is added at the end of temp (this spot was free)
    temp[m_size] = fp;

    //temp points to adress X -> myCollection points to adress X
    myCollection = std::move(temp);
    m_size++;
}
//delete last element
fix_point fix_point_collection::pop_back()
{
    fix_point lastElement = fix_point(0.f);    //Initializing with int creates ambigous error
    if(m_size != 0){
        lastElement = myCollection[m_size - 1];
        std::unique_ptr<fix_point []> temp (new fix_point[m_size - 1]);
        //last element falls off
        std::copy(myCollection.get(), myCollection.get() + (m_size - 1), temp.get());
        myCollection = std::move(temp);
        m_size--;
    }
    return lastElement;
}
size_t fix_point_collection::size() const{
    return (size_t) m_size;   //cast to size_t
}

fix_point fix_point_collection::sum() const{
    fix_point sum = fix_point(0.f);
    for (unsigned int i = 0; i < m_size; i++){
        sum += myCollection[i];
    }
    return sum;
}

size_t fix_point_collection::count_value(fix_point fp){
    size_t count = 0;
    for(unsigned int i = 0; i < m_size; i++){
        if(myCollection[i] == fp){
            count++;
        }
    }
    return count;
}

fix_point sum(fix_point_collection &collection) {
    return collection.sum();
}

size_t count_value(fix_point_collection &collection, fix_point fp){
    return collection.count_value(fp);
}

//READ-ONLY
const fix_point& fix_point_collection::operator[](unsigned int index) const {
    if(index < m_size) {
        return myCollection[index];
    }
    fix_point fp(0.f);
    return fp;
}

fix_point& fix_point_collection::operator[](unsigned int index) {
    if(index < m_size) {
        return myCollection[index];
    }
    fix_point fp(0.f);
    return fp;

}
//Interpolation
fix_point fix_point_collection::operator[](fix_point index) const {
    int minIndex = (int) floor(to_float(index));
    int maxIndex = (int) ceil(to_float(index));
    float t = to_float(index) - minIndex;
    if(maxIndex < m_size) {
        return fix_point((1.f - t) * to_float(myCollection[minIndex]) + t * to_float(myCollection[maxIndex]));
    }
    return fix_point(0.f);
}
