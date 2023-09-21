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
   firstNode = nullptr;
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
    while(firstNode != nullptr){
        Node* temp = firstNode;
        firstNode = firstNode->next;
        delete temp;
    }
}

void Tour::show()
{
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
    Node* currentNode = firstNode;
    while (currentNode != nullptr) {
        Point pointToDraw = currentNode->point;
        pointToDraw.drawTo(currentNode->next->point, scene);
        currentNode = currentNode->next; // hoppar till nästa nod
        if (currentNode == firstNode){
            currentNode = nullptr; //sätter till brytvillkoret
        }
    }
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
    double smallestDistance = 1.7976931348623157E+308;
    Node* nearestNode = nullptr;
    Node* currentNode = firstNode;
    if (currentNode == nullptr){
        firstNode = new Node(p,  nullptr);
        firstNode->next = firstNode;
    }else{
        while (currentNode != nullptr) {
            double distance = p.distanceTo(currentNode->point);
            if (distance < smallestDistance){
                smallestDistance = distance;
                nearestNode = currentNode;
            }
            currentNode = currentNode->next; // hoppar till nästa nod
            if (currentNode == firstNode){
                currentNode = nullptr; //sätter till brytvillkoret
            }
        }
        Node* nextNode = nearestNode->next;
        nearestNode->next = new Node(p, nextNode);
    }
}

void Tour::insertSmallest(Point p)
{
    double smallestDistance = 1.7976931348623157E+308;
    Node* nearestNode = nullptr; // den nod som gav kortast sträcka
    Node* currentNode = firstNode; // håller koll på nuvarande noden när vi itererar
    Node* pNode = new Node(p, nullptr); // skapar nod för punkten p
    if (currentNode == nullptr){ // det är en tom tour
        firstNode = new Node(p,  nullptr); //första noden är punkten som ska sättas in
        firstNode->next = firstNode; // den pekar på sig själv
    }else{
        while (currentNode != nullptr) {
            Node* nextNode = currentNode->next; // pekar på noden som kommer efter currentnode
            pNode->next = nextNode; // sätter att P pekar på det som currentnode pekade på
            currentNode->next = pNode; // currentnode pekar på p
            double currentDistance = this->distance(); // räknar ut sträckan på tour
            if (smallestDistance > currentDistance){ // om vi hittat ny kortast sträcka
               smallestDistance = currentDistance; // ny kortast sträcka
               nearestNode = currentNode; // sparar var insättning av noden gav kortast sträcka
            }
            currentNode->next = nextNode; // ändrar tillbaka som det var
            currentNode = currentNode->next; // hoppar till nästa nod
            if (currentNode == firstNode){
                currentNode = nullptr; //sätter till brytvillkoret
            }
        }
        Node* temp = nearestNode->next; // sätter in punkten p där den gav kortast sträcka
        pNode->next = temp;
        nearestNode->next = pNode;
    }
}
