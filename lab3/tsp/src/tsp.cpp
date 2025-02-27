/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Tour.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    string filename = "tsp5.txt";
    ifstream input;
    input.open(filename);

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    //TEST

    // define 4 points forming a square
    /*Point p(100.0, 100.0);
    Point q(500.0, 100.0);
    Point r(500.0, 500.0);
    Point s(100.0, 500.0);
            // Set up a Tour with those four points
            // The constructor should link p->q->r->s->p
    Tour squareTour(p, q, r, s);
            // Output the Tour
    squareTour.show();
    cout << squareTour.size() << endl;
    cout << squareTour.distance() << endl;
    squareTour.draw(scene);*/

    // run insertion heuristic
    Tour tour;
    double x;
    double y;
    while (input >> x >> y) {
        Point p(x, y);
        tour.insertSmallest(p);
        //uncomment the 4 lines below to animate
        //tour.draw(scene);
        //std::chrono::milliseconds dura(50);
        //std::this_thread::sleep_for(dura);
        //a.processEvents();
    }
    input.close();

    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    cout << "Number of points: " << tour.size() << endl;
   // tour.show();

    // draw tour
    tour.draw(scene);
    //return a.exec(); // start Qt event loop
    return 0;
}

