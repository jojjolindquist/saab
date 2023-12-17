// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <algorithm>
// TODO: include any other headers you need; remove this comment
using namespace std;

void swap(vector<Vertex*>& neighbors,const int& vertex1, const int& vertex2){
    Vertex* temp = (neighbors.at(vertex1)); // sparar ena punkten temporärt
    neighbors.at(vertex1) = neighbors.at(vertex2);
    neighbors.at(vertex2) = temp;
}

int partition(vector<Vertex*>& neighbors, int left, int right, Vertex*& pivot, Vertex*& startNode, BasicGraph& graph) {
    // inspiration ifrån https://www.ida.liu.se/opendsa/Books/TDDD86F23/html/Quicksort.html
    while (left <= right) { // flyttar på bounds till de möts
        while ((graph.getArc(neighbors[left], startNode))->cost < (graph.getArc(pivot, startNode))->cost) left++; // om vinkeln för punkten är mindre än pivotelementets vinkel
        while ((right >= left)  && ((graph.getArc(neighbors[right], startNode))->cost >=
                                    (graph.getArc(pivot, startNode))->cost)) right--; // så länge bounds inte möts
        if (right > left){
            swap(neighbors, left, right);  // Byt plats på värden som inte är i rätt ordning
        }
    }
    return left; // returnerar första positionen i högra partitionen
}

/*
* quicksort, använder rekursion samt en partition-metod för att sortera vår vektor av värden.
* Denna version av quicksort har inspirerats från openDSA
*/
void quickSort(vector<Vertex*>& neighbors, int start,  int end, Vertex*& startNode, BasicGraph& graph){
    // inspiration ifrån https://www.ida.liu.se/opendsa/Books/TDDD86F23/html/Quicksort.html
    int pivotIndex = (start + end)/2;
    swap(neighbors, pivotIndex, end); // byt plats på sista elementet och pivotelementet
    int newPivot = partition(neighbors, start, end-1, neighbors[end], startNode, graph);
    swap(neighbors, newPivot, end); // sätter nya pivotelementet på rätt plats
    if ((newPivot-start) > 1) quickSort(neighbors, start, newPivot -1, startNode, graph); // sortera vänstra partitionen
    if ((end - newPivot) > 1) quickSort(neighbors, newPivot +1, end, startNode, graph); // sortera högra partitionen
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    start->setColor(GREEN);
    start->visited = true;
    vector<Vertex*> path;
    Set<Vertex*> neighborsSet= graph.getNeighbors(start);
    vector<Vertex*> neighbors(neighborsSet.begin(), neighborsSet.end()); // skapar vektor av set
    quickSort(neighbors, 0, neighbors.size() -1, start, graph); // sortera grannar efter kostnad

      for (int i=0; i< neighbors.size(); i++){
        if (!(neighbors[i]->visited)){
            if (neighbors[i] == end){
                end->visited= true;
                end->setColor(GREEN);
                neighbors[i]->setColor(GREEN);
                path.push_back(end);
                path.push_back(neighbors[i]);
                return path;
            }
            neighbors[i]->visited = true; // markera noden som visited
            vector<Vertex*> subPath = depthFirstSearch(graph, neighbors[i], end);
            if (!subPath.empty()){ // vi hittade en väg till slutnoden
                neighbors[i]->setColor(GREEN);
                path.push_back(start); // lägg till startnoden
                path.push_back(neighbors[i]);
                path.insert(path.end() , subPath.begin()+1, subPath.end()); // lägger till subPath i slutet av path
                return path;

            }else{
                neighbors[i]->setColor(GRAY);
            }
        }
      }
      return path; // ingen väg hittades, returnera tom vektor
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
