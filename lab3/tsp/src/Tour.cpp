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
    firstNode = new Node(a, nullptr); // skapar första nod
    Node* current = firstNode; // current pekar på förstanod
    current->next = new Node(b, nullptr); // första nod pekar på andra
    current = current->next;
    current->next = new Node(c, nullptr); // andra nod pekar på tredje
    current = current->next;
    current->next = new Node(d, firstNode); // fjärde noden pekar på första
}

Tour::~Tour()
{
    Node* current = firstNode;
    while(current != nullptr){
        Node* temp = current;
        current = current->next;
        delete temp;
        if (current == firstNode){
            current = nullptr;
        }
    }
}

void Tour::show()
{
    Node* currentNode = this->firstNode;
    while (currentNode != nullptr) {
        string pointOutput = currentNode->point.toString(); // utskrift för punkt
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
        Point pointToDraw = currentNode->point; // hämtar ut den punk det ska ritas ett sträck ifrån
        pointToDraw.drawTo(currentNode->next->point, scene); // kallar på draw metoden
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
        tourSize++; // ökar storleken med ett
        currentNode = currentNode->next; // går till nästa nod
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
    double smallestDistance = 1.7976931348623157E+308; // sätter största vä'rdet för double
    Node* nearestNode = nullptr; // sparar undan noden som är närmast p
    Node* currentNode = firstNode; // pekar på noden vi för tillfället kollar på
    if (currentNode == nullptr){ // om tour är tom, sätt p som firstnode
        firstNode = new Node(p,  nullptr);
        firstNode->next = firstNode;
    }else{
        while (currentNode != nullptr) {
            double distance = p.distanceTo(currentNode->point); // räknar ut avståndet mellan punkterna
            if (distance < smallestDistance){ // om vi har ny nod som är närmare punkten
                smallestDistance = distance;
                nearestNode = currentNode;
            }
            currentNode = currentNode->next; // hoppar till nästa nod
            if (currentNode == firstNode){
                currentNode = nullptr; //sätter till brytvillkoret
            }
        }
        Node* nextNode = nearestNode->next; // stopppar in noden p i tour vid den nod som är närmast p
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
        firstNode = pNode; //första noden är punkten som ska sättas in
        firstNode->next = firstNode; // den pekar på sig själv
    }else{
        while (currentNode != nullptr) {
            Point nextpoint = currentNode->next->point; // punkten efter currrentPoint
            double currentDistance = currentNode->point.distanceTo(nextpoint); // nuvarande distans mellan punkterna
            double newdistance = currentNode->point.distanceTo(pNode->point) +
                    pNode->point.distanceTo(nextpoint); // distans när vi lägger till punkt p

            double distanceDifference = newdistance - currentDistance; // räknar ut distansskillnaden
            if (smallestDistance > distanceDifference){ // om vi hittat ny kortast sträcka
               smallestDistance = distanceDifference; // ny kortast sträcka
               nearestNode = currentNode; // sparar var insättning av noden gav kortast sträcka
            }
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

bool Tour::intersect(const double& kTestPoint, const double& mTestPoint, const double& kCurr,
                     const double& mCurr, const double x1, const double x2){
    if (kTestPoint == kCurr){ //parallella
        return false;
    }
    /*cout << "kCurr :" + to_string(kCurr) << endl;
    cout << "mCurr :" << mCurr << endl;
    cout << "kTest :" + to_string(kTestPoint) << endl;
    cout << "mTest :" + to_string(mTestPoint) << endl; */
    double intersectionX = (mTestPoint - mCurr) / (kCurr - kTestPoint); //hittar en skärningspunkt
    cout << "intersection :" + to_string(intersectionX) << endl;
    cout << "x1 :" + to_string(x1) << endl;
    cout << "x2 :" + to_string(x2) << endl;
    if (x1 < x2){
        if (intersectionX >= x1 && intersectionX <= x2){
            cout << "intersect" << endl;
            return true; //inom linjernas intervall, en giltig skärningspunkt!

        }
    }
    else{
        if (intersectionX <= x1 && intersectionX >= x2){
            cout << "intersect" << endl;
            return true; //inom linjernas intervall, en giltig skärningspunkt!
        }
    }
    cout << "no intersection" <<endl;
    return false;
}

bool Tour::isCrossing(const Node* insertNode, const Node* testNode){ //kolla om p dragen till nästa nod skapar en korsning till någon annan dragen linje
    Node* currentNode = firstNode; // håller koll på nuvarande noden när vi itererar
    Point insertPoint = insertNode->point;
    Point testPoint = testNode->point; //testa om p->testNode skapar en korsning
    while (currentNode != nullptr) {
        if (currentNode != insertNode){ // om vi är på den nod vi kollar om den korsar någon
            Point currP = currentNode->point; //denna punkt och nästa bildar den linje
            Point currPNext = currentNode->next->point; //vi vill kolla om pPoint->nextP korsar
          //räta linjens ekvation kolla om skär varandra
            double kCurr = (currP.y - currPNext.y)/(currP.x - currPNext.x);
            double kTestPoint = (insertPoint.y - testPoint.y)/(insertPoint.x - testPoint.x);
            double mCurr = currP.y - (kCurr*currP.x); //hittar räta linjens ekvation
            double mTestPoint = insertPoint.y - (kTestPoint*insertPoint.x); //hittar räta linjens ekvation
            if (intersect(kTestPoint, mTestPoint, kCurr, mCurr, insertPoint.x, testPoint.x)){ //skär de varandra?
                return true;
            }
        }
        currentNode = currentNode->next; // hoppar till nästa nod
        if (currentNode == firstNode){
            currentNode = nullptr; //sätter till brytvillkoret
        }

    }
    return false;
}

void Tour::avoidCrossings(Tour& crossedTour){
    double smallestDistance = 1.7976931348623157E+308; // sätter största vä'rdet för double
    Node* nearestNode = nullptr; // sparar undan noden som är närmast p
    Node* currentNode = firstNode; // pekar på noden vi för tillfället kollar på
    Node* pNode = new Node(p, nullptr);
    if (currentNode == nullptr){ // om tour är tom, sätt p som firstnode
        firstNode = pNode;
        firstNode->next = firstNode;
    }else{
        while (currentNode != nullptr) {
            double distance = p.distanceTo(currentNode->point); // räknar ut avståndet mellan punkterna
            if (distance < smallestDistance && !isCrossing(pNode, currentNode)){ // om vi har ny nod som är närmare punkten
                    smallestDistance = distance;
                    nearestNode = currentNode;
                }


            currentNode = currentNode->next; // hoppar till nästa nod
            if (currentNode == firstNode){
                currentNode = nullptr; //sätter till brytvillkoret
            }
        Node* nextNode = nearestNode->next; // stopppar in noden p i tour vid den nod som är närmast p
        nearestNode->next = new Node(p, nextNode);
    }
}
}


