// johli622, stias606
// En vektor som implementeras med hjälp av en array. Den har variabler som har koll på storlek
// samt antalet element i arrayen för tillfället. Vektorn kan lagra element av valfri typ.

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    /*
     * Konstruktor som initierar kapacitet till 1, antal element till 0
     * samt initierar en tom array
     */
    MyVector();

    /*
     * Frigör utrymmet för alla element
     */
    ~MyVector();

    /*
     * En copy-konstruktor, initierar denna MyVector till en given MyVector
     */
    MyVector(const MyVector& other);

    /*
     * Tilldelningsoperator som kopierar över innheållet från en given Myvector
     * till en annan MyVector
     */
    MyVector& operator =(const MyVector& other);

    /*
     * Lägger till ett element längst bak i vektorn
     */
    void push_back(const T&);

    /*
     * Tar bort sista elementet i vektorn
     */
    void pop_back();

    /*
     * Returnerar ett element med ett givet index
     */
    T& operator[](unsigned i);

    /*
     * Returnerar ett element med ett givet index
     */
    const T& operator[](unsigned i)const;

    /*
     * Returnerar true om vektorn är tom
     */
    bool empty()const;

    /*
     * Returnerar en pekare till första elementet i vektorn
     */
    T* begin();

    /*
     * Returnerar en pekare till sista elementet i vektorn
     */
    T* end();

    /*
     * Frigör minne från nuvarande MyVector samt initierar en ny
     */
    void clear();

    /*
     * Returnerar antalet element i vektorn
     */
    unsigned size()const;

private:
    unsigned capacity; // arrayens storlek
    unsigned numberOfElements; // antal element arrayen har för tillfället
    T* elementsArray;

    /*
     * Kollar om arrayen kapacitet måste utökas och gör det i sånna fall
     */
    void checkCapacity();

    /*
     * Initierar en ny vektor med kapacitet 1 och antal element 0.
     */
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
    elementsArray = new T[capacity]; // initierar array
    std::copy(other.elementsArray, other.elementsArray + other.capacity, elementsArray); // kopierar elementen till nya arrayen

}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    delete [] elementsArray;
    elementsArray = new T[capacity];
    for (int i =0; i < numberOfElements; ++i){ // kopierar över alla elementen från other
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
