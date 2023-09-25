/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:

    /*
     * Create a GameState with randomly placed, but not
     * overlapping hero and numberOfRobots robots
     */
    GameState(int numberOfRobots);

    ~GameState() = default;


    /*
     * Clear and redraw entire playing field
     */
    void draw(QGraphicsScene* scene) const;	// Clear and redraw entire playing field

    /*
     * Teleport hero to random location
     */
    void teleportHero();

    /*
     * Move robots one step towards hero
     */
    void moveRobots();

    /*
     * Identify crashed robots
     */
    void updateCrashes();

    /*
     * Count identified crashed robots
     */
    int countJustCrashed()const;

    /*
     * Replace each identified crashed robot with a junk
     */
    void junkTheCrashed();

    /*
     * Are there still robots that did not crash?
     */
    bool stillLiveRobots() const;

    /*
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /*
     * Move hero towards dir
     */
    void moveHeroTowards (const Point& dir);

    /*
     * Return hero
     */
    Point getHeroAsPoint () const;

private:
    std::vector<Robot> robots;  // the robots
    std::vector<Junk> junks;    // robots that have turned to junk
    Hero hero;                  // the hero

    // private helpers
    bool isEmpty(const Unit& unit) const;

};

#endif // GAMESTATE_H
