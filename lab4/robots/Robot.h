/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:

    /* Konstruktor */
    Robot();

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
    * Create Robot at given point
    */
    Robot(const Point& p): Unit(p){}

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
    virtual bool justCrashed() const;

    Robot* clone() const override{ return new Robot{*this};};

    /* Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
};

#endif // ROBOT_H
