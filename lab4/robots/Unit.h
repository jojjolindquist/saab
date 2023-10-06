/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 *
 * (OBS: våra kommentarer är på svenska. De engelska var med från början)
 * Unit, en klass för alla spelobjekt och deras metoder. Varje Unit har en
 * x- och y-koordinat.
 *
 * johli622 stias606
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:

    /*
     * Create a unit at a random position
     */
    Unit();

    /*
    * Create unit at given point
    */
    Unit(const Point& p);

    virtual ~Unit(){}

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;

    /*
     * did not crash yet
     */
    virtual bool isAlive() const = 0;
    
    /*
     * Kopieringskonstruktor
     */
    virtual Unit* clone() const = 0;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash() = 0;

    /*
    * Take one step closer to point
    */
    virtual void moveTowards(const Point&);

    /*
     * Return whether the unit crashed
     */
    virtual bool isToBeJunked() const = 0;

    /*
    * Draws this unit onto the given QGraphicsScene.
    */
    virtual void draw(QGraphicsScene* scene) const = 0;

    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;
private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H
