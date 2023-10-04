/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Hero, en subklass till Unit. Har en egen kopieringskonstruktor och draw-metod.
 * Representerar spelaren som användaren styr.
 */

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include <QGraphicsScene>

class Hero : public Unit {

public:

    /*
     * Kopieringskonstruktor
     */
    Hero* clone() const override;

    /*
     * did not crash yet
     */
    bool isAlive() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;

    /*
     * Return whether the unit crashed
     */
    bool isToBeJunked() const override;

    /*
    * Draws this unit onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;


};

#endif // HERO_H
