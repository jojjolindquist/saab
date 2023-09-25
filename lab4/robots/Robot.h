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

    /*
     * did not crash yet
     */
    bool canMove() const;

    /*
     * Crashes and remembers it
     */
    void doCrash();

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;


};

#endif // ROBOT_H
