/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 * stias606, johli622
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int slow(int argc, char *argv[]){
    QApplication a(argc, argv);

    // open file
    string filename = "mystery10089.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N-3 ; ++i) {
        for (int j = i+1 ; j < N-2 ; ++j) {
            for (int k = j+1 ; k < N-1 ; ++k) {
                //only consider fourth point if first three are collinear
                if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(k))) {
                    for (int m{k+1} ; m < N ; ++m) {
                        if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(m))) {
                            render_line(scene, points.at(i), points.at(m));
                            a.processEvents(); // show rendered line
                        }
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
/*
 * Byter plats på två par i en vektor, tar in indexet på de par som ska byta plats samt en vektor med par
 */
void swap(vector<pair<Point, double>>& kValuesToSort,const int& pivot, const int& end){
    pair<Point, double> temp = (kValuesToSort.at(pivot)); // sparar ena punkten temporärt
    kValuesToSort.at(pivot) = kValuesToSort.at(end);
    kValuesToSort.at(end) = temp;
}

/*
* Utför partitioner enligt quicksorts algoritm, i denna version utefter k-värden (lutningen)
*/
int partitionK(vector<pair<Point, double>>& kValuesToSort, int left, int right, pair<Point, double>& pivot) {
    // inspiration ifrån https://www.ida.liu.se/opendsa/Books/TDDD86F23/html/Quicksort.html
    while (left <= right) { // flyttar på bounds till de möts
        while (kValuesToSort.at(left).second < pivot.second) left++; // om vinkeln för punkten är mindre än pivotelementets vinkel
        while ((right >= left)  && (kValuesToSort[right].second >= pivot.second)) right--; // så länge bounds inte möts
        if (right > left){
            swap(kValuesToSort, left, right);  // Byt plats på värden som inte är i rätt ordning
        }
    }
    return left; // returnerar första positionen i högra partitionen
}
/*
 * Utför partitioner enligt quicksorts algoritm, i denna version utefetr punkternas psoitioner
 */
int partitionP(vector<pair<Point, double>>& kValuesToSort, int left, int right, pair<Point, double>& pivot) {
    // inspiration ifrån https://www.ida.liu.se/opendsa/Books/TDDD86F23/html/Quicksort.html
    while (left <= right) { // flyttar på bounds till de möts
        while (kValuesToSort.at(left).first < pivot.first) left++; // om vinkeln för punkten är mindre än pivotelementets vinkel
        while ((right >= left)  && !(kValuesToSort[right].first < pivot.first)) right--;
        if (right > left) {
            swap(kValuesToSort, left, right);  // Byt plats på värden som inte är i rätt ordning
        }
    }
    return left; // returnerar första positionen i högra partitionen
}

/*
* quicksort, använder rekursion samt en partition-metod för att sortera vår vektor av värden.
* Denna version av quicksort har inspirerats från openDSA
*/
void quickSort(vector<pair<Point, double>>& kValuesToSort, const int& start, const int& end, bool sortK){
    // inspiration ifrån https://www.ida.liu.se/opendsa/Books/TDDD86F23/html/Quicksort.html
    int pivotIndex = (start + end)/2;
    swap(kValuesToSort, pivotIndex, end); // byt plats på sista elementet och pivotelementet
    int newPivot;
    if(sortK){
        newPivot = partitionK(kValuesToSort, start, end-1, kValuesToSort[end]);
    }else{
        newPivot = partitionP(kValuesToSort, start, end-1, kValuesToSort[end]);
    }
    swap(kValuesToSort, newPivot, end); // sätter nya pivotelementet på rätt plats
    if ((newPivot-start) > 1) quickSort(kValuesToSort, start, newPivot -1, sortK); // sortera vänstra partitionen
    if ((end - newPivot) > 1) quickSort(kValuesToSort, newPivot +1, end, sortK); // sortera högra partitionen
}
/*
 * Ritar ut en linje mellan punkter som har samma vinkel i förhållande till en specifik punkt. Tar in punkten som används referens
 * till att beräkna vinkeln till andra punkter, en vektor med par av alla övriga punkter och deras k-värde, indexet för första punkten
 * respektive sista punkten med samma lutning. Sorterar punkterna och ritar sedan en linje från först punkten i den sorterade listan till
 * den sista.
 */
void drawLine(Point& origo, vector<pair<Point, double>>& kValuesSort, const int& start, const int& end, QGraphicsScene* scene, QApplication& a){
    auto startPair = kValuesSort.begin() + start; // hämtar iterator för första punkten som ska sorteras
    auto endPair = kValuesSort.begin() + end; //iterator för sista punkten som ska sorteras
    vector<pair<Point, double>> pointsToSort;
    for (auto i = startPair; i <= endPair; i++){ // lägger till punkterna som har samma k-värde i ny vektor
        pointsToSort.push_back(*i);
    }
    pair<Point, double> origoPair = pair<Point, double> (origo, pointsToSort[0].second);
    pointsToSort.push_back(origoPair); // lägger även till punkten vi har jämfört vinel med
    quickSort(pointsToSort, 0, pointsToSort.size()-1, false); // sorterar punkterna, skickar in false så vi ska sortera efter punkter
    render_line(scene, pointsToSort[0].first, pointsToSort[pointsToSort.size()-1].first); // ritar ut linje mellan första och sista punkten
    a.processEvents(); // visa linjen

}

/*
* Den snabba versionen av brute. Skapar en vektor av alla punkter och deras lutning relativt
* olika punkter som utsetts till origo. Först sorteras vektorn efter lutningen, för att därefter
* skicka de punkter med samma lutning till drawline(). Där sorteras punkterna efter punktens koordinat,
* därefter ritas dessa punkter ut.
*/
int fast(int argc, char *argv[]){
    QApplication a(argc, argv);

    // open file
    string filename = "input12800.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Pattern Recognition");
    view->show();
    auto begin = chrono::high_resolution_clock::now();

    for(int i = 0; i < points.size(); i ++){ // går igenom alla punkter
        Point p = points.at(i); // hämtar ut en punkt för att jämföra med andra punkter
        vector<pair<Point, double>> kValuesSort; // skapar vektor med par av punkter och deras vinkel till punkten vi jämför med

        for (int j = 0; j < N; j++){ // iterrerar över resterande punkter
            if (i != j){ //Vi vill inte lägga till punkten vi jämför med
                double kValue = p.slopeTo(points.at(j));
                pair<Point, double> pointPair(points.at(j), kValue);
                kValuesSort.push_back(pointPair);
            }
        }
        quickSort(kValuesSort, 0, kValuesSort.size()-1, true); // sorterar paren efter deras vinkel
        int sameK = 0; // initierar till index 0, räknar punkter med samma lutning
        for (int i = 0; i < kValuesSort.size(); i ++){
            if (kValuesSort[i].second == kValuesSort[i +1].second){ // två följande punkter har samma lutning
                sameK++;
            }else if (sameK>= 2){ // vill endast gå in om vi hittar 3 vektorer i samma värde ( den första räknas med)
                drawLine(p, kValuesSort, i-sameK, i, scene, a); // i-sameK = startindex, i = slutindex
                sameK = 0; // påbörjar ny räkning
            }else{
                sameK = 0; // påbörjar ny räkning
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
int main(int argc, char *argv[]) {
    fast(argc, argv);
}
