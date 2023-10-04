/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Hero.h"
#include "constants.h"



void Hero::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addRect(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                          UNIT_WIDTH, UNIT_HEIGHT), Qt::NoPen, QBrush(HERO_COLOR));
}

Hero* Hero::clone() const{
    return new Hero{ *this }; //enligt föreläsningen
}

bool Hero::isAlive() const{
    return false;
}

void Hero::doCrash(){

}

bool Hero::isToBeJunked() const{
    return false;
}
