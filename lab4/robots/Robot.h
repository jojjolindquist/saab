/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Robot, en subklass till Unit som består av flera metoder som
 * överskriver Units, så att de beter sig som en robot (levande och rörliga).
 * Robotar är spelarens (Hero's) motståndare. Robotar blir till Junk
 * vid kollision med Junk eller andra robotar.
 *
 * johli622 stias606
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool toBeJunked = false;

public:

    /*
     * did not crash yet
     */
    bool isAlive() const override;
    
    /*
     * Kopieringskonstruktor
     */
    Robot* clone() const override;

    /*
     * Crashes and remembers it
     */
    void doCrash() override;

    /*
     * Return whether the robot crashed
     */
    bool isToBeJunked() const override;


    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;


};

#endif // ROBOT_H
