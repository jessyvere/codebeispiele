//
//  canal.cpp
//  wasserbau
//
//  Created by Jessica Moll on 01.06.18.
//

#include "canals.h"


Canals::Canals(){
    init();

}

void Canals::setup(){
    for (int i = 0; i < numberOfCanals; i++){
        xPositions.push_back((((m_size.x/numberOfCanals)*i) + (m_size.x/numberOfCanals)/2) + m_pos.x);
    }
    
    cwidth = 10;
}

//--------------------------------------------------------------
void Canals::update(){

}

//--------------------------------------------------------------
void Canals::draw(){
}

float Canals::calculateNearestCanal(float x){
    minimalDistanceToCanal = m_size.x;
    int nearestCanal = 0;
    for(int i = 0; i < xPositions.size(); i++){
        if(abs(x - xPositions[i]) < minimalDistanceToCanal) {
            minimalDistanceToCanal = abs(x-xPositions[i]);
            nearestCanal = i;
        }
    }
    nearestCanalPosition = xPositions[nearestCanal];
    return nearestCanalPosition;

}



void Canals::setNumberOfCanals(int x){
    numberOfCanals = x;
}

void Canals::setYPosition(float x){
    yPosition = x;
}

void Canals::setWidth(float x){
    cwidth = x;
}

void Canals::setSortingDistance(float x){
    sortingDistance = x;
}

