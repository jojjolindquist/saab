/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot* pRobot = new Robot();
        while(!isEmpty(*pRobot)){ //kollar om en robot ligger på en annan robot
            delete pRobot;
            pRobot = new Robot();
        }
        robots.push_back(pRobot);
    }
    teleportHero();
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const auto robot: robots){ //tar auto för att få korrekt typ (junk eller robot)
        robot->draw(scene);
    }
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(auto robot : robots){
        robot->moveTowards(hero);
    }
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        //for(unsigned j=0; j < junks.size(); ++j){
           // if(robots[i].at(junks[j])){
            //    robots[i].doCrash();
           // }
      //  }
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(*robots[o])){
                robots[i]->doCrash(); //om Junk kommer inget hända, annars blir båda junk
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            Junk* newJunk = new Junk(robots[i]->asPoint());
            delete robots[i];
            robots[i] = newJunk; //genom att ändra i pekaren slipper vi ta bort/lägga till objekt i vektorn
            //robots.push_back(Junk(robots[i]->asPoint()));
            //robots[i] = robots[robots.size()-1];
            //robots.pop_back();
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot : robots){
        if(hero.at(*robot)){ //OBS
            return true;
        }
    }
    /*for(const Junk& junk: junks){
        if(hero.at(junk)){
            return true;
        }
    } */
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    /*for(const Junk& junk: junks)
        if(junk.at(unit))
            return false; */
    return true;
}

