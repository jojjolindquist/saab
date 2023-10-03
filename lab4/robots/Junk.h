/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Junk, en subklass till Unit som är kraschade robotar. De är
 * orörliga och döda, samt överskrider Units metoder.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit  {
public:

    /*
     * Konstruktor
     */
    Junk(const Point& p): Unit(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;

    /*
     * did not crash yet
     */
    bool isAlive() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;
    
    /*
     * Kopieringskonstruktor
     */
     Junk* clone() const override;

    /*
    * Take one step closer to point
    */
    void moveTowards(const Point&) override;

    /*
     * Return whether the junk crashed
     */
    bool isToBeJunked() const override;

};

#endif // JUNK_H
