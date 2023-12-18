// Innehåller flera olika algoritmer för att hitta den kortaste vägen från en startpunkt (nod) till en
// slutpunkt (nod). Dessa består av 4 olika algoritmer som genomför graph traversals, DFS, BFS, Dijkstras och
// A*.
// johli622 stias606

#include "costs.h"
#include "trailblazer.h"
#include <algorithm>
#include <queue>
#include <pqueue.h>

using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    start->setColor(GREEN); //gör node grön när den besöks
    start->visited = true;
    vector<Vertex*> path;
    Set<Vertex*> neighborsSet= graph.getNeighbors(start); //hämtar alla grannar till startnoden
    vector<Vertex*> neighbors(neighborsSet.begin(), neighborsSet.end()); // skapar vektor av set

      for (int i=0; i< neighbors.size(); i++){
        if (!(neighbors[i]->visited)){ //om grannen inte besökt
            if (neighbors[i] == end){ //om grannen är slutnoden
                end->visited= true;
                end->setColor(GREEN);
                neighbors[i]->setColor(GREEN);
                path.push_back(end);
                path.push_back(neighbors[i]);
                return path; //backtracking, vi lägger nu till alla noder fram tills slutnoden i path
            }
            neighbors[i]->visited = true; // markera noden som visited
            vector<Vertex*> subPath = depthFirstSearch(graph, neighbors[i], end); //hitta en väg rekursivt till slutnoden
            if (!subPath.empty()){ // vi hittade en väg till slutnoden
                neighbors[i]->setColor(GREEN); //då ska denna nod vara med, sätt till grön
                path.push_back(start); // lägg till startnoden
                path.push_back(neighbors[i]); //lägg till grannen
                path.insert(path.end() , subPath.begin()+1, subPath.end()); // lägger till subPath i slutet av path
                return path;

            }else{
                neighbors[i]->setColor(GRAY); //grannen ledde inte till slutnoden, färga grå
            }
        }
      }
      return path; // ingen väg hittades, returnera tom vektor
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData(); //återställ data både före och efter
    queue<Vertex*> nodequeue;
    nodequeue.push(start);
    start->setColor(YELLOW); //färga gul när lägger till i kön
    start->visited = true;
    vector<Vertex*> path;

      while (!nodequeue.empty()) { // medan kön inte är tom
        start = nodequeue.front(); //hämtar värdet
        nodequeue.pop(); //tar bort från kön
        start->setColor(GREEN); //färga grön när den tas ur kön

        if (start == end) { //har vi kommit till slutnoden?
            // Rekonstruera path från end till start
            start->visited = true;
            Vertex* current = end;
            while (current != nullptr) { //använd previous för att återbygga path tills vi hittar en nullptr
                path.insert(path.begin(), current);
                current = current->previous;
            }
            graph.resetData();
            return path;
        }
        Set<Vertex*> neighborsSet= graph.getNeighbors(start);
        vector<Vertex*> neighbors(neighborsSet.begin(), neighborsSet.end()); // skapar vektor av set

        for (int i=0; i < neighbors.size(); i++) //annars iterera över alla grannar
          if (!neighbors[i]->visited) {
            neighbors[i]->visited = true;
            neighbors[i]->previous = start; //sätt previous till start
            nodequeue.push(neighbors[i]); //lägg till i kön
            neighbors[i]->setColor(YELLOW); //markera gul
          }
      }
    graph.resetData();
    return path; //vi hittade ingen väg till slutnoden
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData(); //återställ data både före och efter
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    vector<int> allVertex;

    for (Vertex* node : graph.getVertexSet()){ //initiera alla noders prioritet till infinity
        pqueue.enqueue(node, INFINITY);
        node->cost = INFINITY;     //sätt kostnaden till samma för att kunna använda senare
    }
    pqueue.changePriority(start, 0); //ge startnoden prioritet 0
    start->cost = 0;

    for (int i = 0; i < graph.getVertexSet().size(); i++){
        if (pqueue.peekPriority() == INFINITY){ //om den nod med lägst prioritet har kostnad INFINITY
            return path; //returnera en empty path
        }
        Vertex* smallestNode = pqueue.dequeue(); //hämta noden med lägst prioritet

        if (!smallestNode->visited){ //kontrollera att smallestNode inte har markerats innan

            if (smallestNode == end) { //har vi hittat end-node?
                smallestNode->setColor(GREEN);
                // Rekonstruera path från end till start
                smallestNode->visited = true;

                Vertex* current = end;
                while (current != nullptr) { //använd previous för att återbygga path tills vi hittar en nullptr
                    path.insert(path.begin(), current);
                    current = current->previous;
                }
                graph.resetData();
                return path;
            }
            smallestNode->visited = true;
            smallestNode->setColor(GREEN); //nu har vi hanterat noden, markera den grön
            Set<Vertex*> neighborsSet= graph.getNeighbors(smallestNode);
            vector<Vertex*> neighbors(neighborsSet.begin(), neighborsSet.end()); // skapar vektor av set

            for (int j=0; j < neighbors.size(); j++){
                Vertex* neighbor = neighbors[j];
                if(!neighbor->visited){ //om grannen ej besökt
                    neighbors[j]->setColor(YELLOW); //färga gul
                    double newWeight = graph.getArc(smallestNode, neighbor)->cost; //nya kostnaden = den mellan smallestNode och neighbor
                    if (neighbor->cost > (smallestNode->cost + newWeight)){ //kolla om vi hittat en ny mindre kostnad
                        neighbor->cost = smallestNode->cost + newWeight; //isåfall uppdatera nodens kostnad
                        pqueue.changePriority(neighbor, neighbor->cost); //uppdatera nodens prioritet
                        neighbor->previous = smallestNode; //sätt previous till smallestNode
                }
            }
        }
    }
 }
    graph.resetData(); //återställ data både före och efter
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData(); //återställ data både före och efter
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    //pqueue.enqueue(start, 0);
    vector<int> allVertex;
    for (Vertex* node : graph.getVertexSet()){
        pqueue.enqueue(node, INFINITY);
        node->cost = INFINITY;
    }
    pqueue.changePriority(start, 0);
    start->cost = 0;
    for (int i = 0; i < graph.getVertexSet().size(); i++){
        if (pqueue.peekPriority() == INFINITY){ //om den nod med lägst prioritet har kostnad INFINITY
            return path; //returnera en empty path
        }
        Vertex* smallestNode = pqueue.dequeue();

        if (!smallestNode->visited){ //kontrollera att smallestNode inte har markerats innan

            if (smallestNode == end) { //har vi hittat end-node?
                smallestNode->setColor(GREEN);
                // Rekonstruera path från end till start
                smallestNode->visited = true;

                Vertex* current = end;
                while (current != nullptr) { //använd previous för att återbygga path tills vi hittar en nullptr
                    path.insert(path.begin(), current);
                    current = current->previous;
                }
                graph.resetData();
                return path;
            }
            smallestNode->visited = true;
            smallestNode->setColor(GREEN); //nu har vi hanterat noden, markera den grön
            Set<Vertex*> neighborsSet= graph.getNeighbors(smallestNode);
            vector<Vertex*> neighbors(neighborsSet.begin(), neighborsSet.end()); // skapar vektor av set

            for (int j=0; j < neighbors.size(); j++){
                Vertex* neighbor = neighbors[j];
                if(!neighbor->visited){ //om grannen ej besökt
                    neighbors[j]->setColor(YELLOW);
                    double newWeight = graph.getArc(smallestNode, neighbor)->cost; //nya kostnaden = den mellan smallestNode och neighbor
                    if (neighbor->cost > (smallestNode->cost + newWeight + neighbor->heuristic(end))){ //lägger till heuristikens kostnad, ny mindre kostnad?
                        neighbor->cost = smallestNode->cost + newWeight + neighbor->heuristic(end); //isåfall uppdatera nodens kostnad
                        pqueue.changePriority(neighbor, neighbor->cost); //uppdatera nodens prioritet
                        neighbor->previous = smallestNode; //sätt previous till smallestNode
                }
            }
        }
    }
 }
    graph.resetData();
    return path;
}
