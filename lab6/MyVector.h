// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:
    unsigned capacity; // arrayens storlek
    unsigned numberOfElements; // antal element arrayen har för tillfället
    T* elementsArray;
    void checkCapacity();
    void resetOrInitialize();

};

template<typename T>
MyVector<T>::MyVector(){
    resetOrInitialize();
}

template<typename T>
MyVector<T>::~MyVector(){
    delete [] elementsArray;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    elementsArray = new T[capacity];
    std::copy(other.elementsArray, other.elementsArray + other.capacity, elementsArray);

}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    delete [] elementsArray;
    elementsArray = new T[capacity];
    for (int i =0; i < numberOfElements; ++i){
        elementsArray[i] = other.elementsArray[i];
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    checkCapacity(); // måste vi ändra på arrayens storlek?
    elementsArray[numberOfElements] = e; // lägger till värdet längst bak i arrayen
    numberOfElements ++;
}

template<typename T>
void MyVector<T>::pop_back(){
    numberOfElements --;
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return elementsArray[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return elementsArray[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete [] elementsArray; // kallar på destruktorn
    resetOrInitialize(); // skapar tom array med kapacitet 1
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return &elementsArray[0];
}

template<typename T>
T* MyVector<T>::end(){
    return &elementsArray[numberOfElements];
  }

template<typename T>
void MyVector<T>::checkCapacity(){
    if (numberOfElements == capacity){
        // slut utrymme
        if (capacity > 0){
            capacity*= 2; // ökar kapacitet med 2* kapacitet
        }else{
            capacity = 1; // inga elements i arrayen, capacity = 0
        }
        T* new_elements = new T[capacity]; // skapar array med nya capaciteten
        for (int i = 0; i < numberOfElements; i ++){
            // kopierar över elementen som fanns i förra arrayen
            new_elements[i] = elementsArray[i];
        }
        delete [] elementsArray; // frigör minne
        elementsArray = new_elements;
    }
}
template<typename T>
void MyVector<T>::resetOrInitialize(){
    elementsArray = new T[1];
    capacity = 1;
    numberOfElements = 0;
}

#endif // MY_VECTOR_H
