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
    firstNode; //initierar vår första pekare till null
}

Tour::Tour(Point a, Point b, Point c, Point d){
    Node first = Node(a);
    Node* firstP = &first;
    Node second = Node(b);
    Node* secondP = &second;
    Node third = Node(c);
    Node* thirdP = &third;
    Node fourth = Node(d);
    Node* fourthP = &fourth;
    first.next = secondP;
    second.next = thirdP;
    third.next = fourthP;
    fourth.next = firstP;
    this->firstNode = &first; //sätter pekaren till vår första nod till den första nod vi skapade
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
    // TODO: write this member
}

double Tour::distance()
{
    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
