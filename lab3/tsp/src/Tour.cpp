// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <QLinkedList>

Tour::Tour()
{
   //initierar vår första pekare till null
}

Tour::Tour(Point a, Point b, Point c, Point d){
    firstNode = new Node(a, nullptr);
    Node* current = firstNode;
    current->next = new Node(b, nullptr);
    current = current->next;
    current->next = new Node(c, nullptr);
    current = current->next;
    current->next = new Node(d, firstNode);
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{
    cout <<  firstNode->toString() << endl;
    Node* currentNode = this->firstNode;
    while (currentNode != nullptr) {
        string pointOutput = currentNode->point.toString();
        cout << pointOutput << endl;
        currentNode = currentNode->next; // hoppar till nästa nod
        if (currentNode == firstNode){
            currentNode = nullptr; //sätter till brytvillkoret
        }
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    int tourSize = 0; // sätter räknare
    Node* currentNode = firstNode;
    while (currentNode != nullptr){
        tourSize++;
        currentNode = currentNode->next;
        if (currentNode == firstNode){ // vi har gått ett varv
            currentNode = nullptr; // sätter till brytvillkoret
        }
    }
    return tourSize;
}

double Tour::distance()
{
    double euclideanDistance = 0; // sätter räknare
    Node* previousNode = firstNode; // första noden
    Node* currentNode = firstNode->next; // nästa nod
    while (previousNode != nullptr){
        Point previousPoint = previousNode->point; // hämtar punkten till första noden
        Point currentPoint = currentNode->point; // hämtar punkten till nästa nod
        euclideanDistance += previousPoint.distanceTo(currentPoint); // adderar avståndet till räknaren
        previousNode = currentNode; // Går till nästa nod
        currentNode = currentNode->next; // går till nästa nod
        if (previousNode == firstNode){ // vi har gått ett varv
            previousNode = nullptr; // sätter till brytvillkoret
        }
    }
    return euclideanDistance;
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
