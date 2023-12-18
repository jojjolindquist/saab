/* johli622 stias606
 *
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"

/*
 * Genomför en depth-first search, dvs traverserar grafens noder genom att traversera från nodens billigaste
 * grannen först, innan nästa granne traverseras. Använder sedan backtracking för att rekonstruera vägen till
 * slutnoden.
 */
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Genomför en breadth-first search, dvs traverserar grafens noder genom att traversera alla grannar till en nod
 * före grannens grannar. Håller koll på detta genom en kö, och rekonstruerar vägen till slutnoden genom att
 * använda nodernas fält "previous".
 */
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Genomför en traversal enligt Dijkstras algoritm. Använder en prioritetskö och väljer den nod som har lägst prioritet.
 * Prioriteten bestäms av det kortaste nuvarande avståndet till en nod.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);

/*
 * Genomför en traversal enligt Dijkstras algoritm. Använder en prioritetskö och väljer den nod som har lägst prioritet.
 * Prioriteten bestäms av det kortaste nuvarande avståndet till en nod plus heuristiken från den noden till slutnoden.
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

#endif
