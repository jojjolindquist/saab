/* En klass Tour vars inre struktur är en länkad lista av noder som
* innehåller punkter och pekare till nästa nod. Klassen använder sig
* av heuristikerna insertSmallest och insertNearest för att sätta in
* nästa punkt på turen för att få kortast tur. En Tour har ett privat
* fält som är en pekare till första noden i listan. */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /* En konstruktor som tar in fyra punkter och skapar en länkad lista av noder,
     * där sista noden pekar på den första. */
    Tour(Point a, Point b, Point c, Point d);

    /* En konstruktor som inte tar in några parametrar och skapar en tom länkad
     * lista av noder */
    Tour();

    /* En destruktor som går igenom alla noder i den länkade listan och radera
     * deras minnesutrymme. */
    ~Tour();

    /* En metod som skriver ut alla punkter i turen. */
    void show();

    /* En metod som ritar ut ett streck mellan två punkter i turen. */
    void draw(QGraphicsScene* scene);

    /* En metod som itererar genom alla noder i turen och räknar upp för varje nod
     * och returnerar antalet. */
    int size();

    /* En metod som räknar ut hela turens längd genom att addera det
    * euklidiska avståndet mellan alla punkter. */
    double distance();

    /* En metod som sätter in punkt p efter den
    * nod vars punkt har kortast avstånd till p. */
    void insertNearest(Point p);

    /* En metod som sätter in punkt p efter en nod så att
    * hela turens totalsträcka blir kortast. */
    void insertSmallest(Point p);

    /* En metod som sätter in punkt p efter en nod så att
     * inga korsningar i turen kommer ske, och vi får en
     * kortare tur. */
    void avoidCrossings(Point p);

    bool isCrossing(Node* node, Node* testNode);


private:
    Node* firstNode = nullptr;
};

#endif // TOUR_H
