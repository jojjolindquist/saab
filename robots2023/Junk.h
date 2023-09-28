/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot  {
public:
    Junk(const Point& p): Robot(p){}
    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    /*
    * Take one step closer to u
    */
    void moveTowards(const Unit&) override;

    /*
     * did not crash yet
     */
    bool canMove() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const override;
};

#endif // JUNK_H
