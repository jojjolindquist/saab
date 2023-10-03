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
        Unit* pUnit = new Robot(); //skapar en ny robot
        while(!isEmpty(*pUnit)){
            delete pUnit;
            pUnit = new Robot();
        }
        units.push_back(pUnit);
    }
    teleportHero();
}

GameState::~GameState(){
    for (auto unit: units){
        delete unit;
    }
}

GameState::GameState(const GameState& state){
    copyOther(state);
}

void GameState::copyOther(const GameState& state){
    std::vector<Unit*> newUnits;
    for (auto unit : state.units){ //för varje unit anropas dess egen clone-metod
        newUnits.push_back(unit->clone()); //och läggs till i nya vektorn
    }
    hero = state.hero;
    units = newUnits;
}

GameState& GameState::operator= (const GameState& other) {
    if (this != &other) {
        for (auto unit: units){ //frigör utrymme utan att radera pekaren this
            delete unit;
        }
        copyOther(other); //anropar kopiering
    }
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const auto unit: units) //tar auto för att få korrekt draw-metod för objektet
        unit->draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(auto unit: units)
        unit->moveTowards(hero.asPoint());
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); ++i){
        for(unsigned o=i+1; o < units.size(); ++o){
            if(units[i]->at(*units[o])){
                units[i]->doCrash(); //om Junk kommer inget hända för den ena, annars blir båda Junk.
                units[o]->doCrash();
            }
        }
    }
}

int GameState::countToBeJunked()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isToBeJunked())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i]->isToBeJunked()) {
            Junk* newJunk = new Junk(units[i]->asPoint());
            delete units[i];
            units[i] = newJunk; //genom att ändra i pekaren slipper vi ta bort och lägga in units
        }
    }
}

bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i)
        if(units[i]->isAlive())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Unit* unit: units){
        if(hero.at(*unit)){
            return true;
        }
    }
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
    for(const Unit* everyUnit: units)
        if(everyUnit->at(unit))
            return false;
    return true;
}

