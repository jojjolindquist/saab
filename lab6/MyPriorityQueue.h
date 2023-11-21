// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <algorithm>


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

  unsigned size() const;

private:
    void upHeapBubbling();
    int parent(int pos);
    void downHeapBubbling();
    bool isLeaf(int pos);
    int leftChild(int pos);
    void swap(int pos1, int pos2);
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
   vector_array = MyVector<T>(); // skapar tom vektor med kapacitet 1
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){

}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
   vector_array.push_back(t);
   upHeapBubbling(); // ändrar så att elementen är ordnade
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    if (vector_array.size() != 0){
        swap(0, vector_array.size()-1); // byt plats på rot och sista lövet
        vector_array.pop_back(); // ta bort sista elementet (roten)
        downHeapBubbling();
    }
}


template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}
template <typename T, typename C>
void MyPriorityQueue<T,C>::upHeapBubbling(){
    int curr = vector_array.size() - 1; // börjar i slutet av arrayen
    // skifta upp tills currs parents priritet > currs prioritet
    if (!(parent(curr) != -1)) { // om noden inte har någon förälder
        while ((curr != 0) &&(strictly_larger_operator(vector_array[curr], vector_array[parent(curr)]))) {
              swap(curr, parent(curr)); // byt plats på curr och currparent
              curr = parent(curr);
            }
    }
}
template <typename T, typename C>
int MyPriorityQueue<T,C>::parent(int pos){
    if (pos <= 0){
        return -1;
    }
    return (pos-1)/2;
}
template <typename T, typename C>
void MyPriorityQueue<T,C>::downHeapBubbling(){
    int pos = 0;
    while (!isLeaf(pos) && leftChild(pos) != -1) { // gåt igenom hela trädet
          int childValue = leftChild(pos); // hämtar värdet för vänstra barnet
          if ((childValue<(vector_array.size()-1)) &&
                  (strictly_larger_operator(vector_array[childValue],vector_array[childValue+1])))
            childValue++; // childvalue är nu indexet av barnet med större värde
          if (!strictly_larger_operator(vector_array[pos], vector_array[childValue])) return;
          swap(pos, childValue);
          pos = childValue;  // Gå neråt till vänstra barnet
        }
}
template <typename T, typename C>
bool MyPriorityQueue<T,C>::isLeaf(int pos){
    return (pos >= vector_array.size()/2) && (pos < vector_array.size());
}
template <typename T, typename C>
int MyPriorityQueue<T,C>::leftChild(int pos){
    if (pos >= vector_array.size()/2) return -1;
        return 2*pos + 1;
}
template <typename T, typename C>
void MyPriorityQueue<T,C>::swap(int pos1, int pos2){
    T temp = vector_array[pos1];
    vector_array[pos1] = vector_array[pos2];
    vector_array[pos2] = temp;

}

#endif // MY_PRIORITY_QUEUE_H
