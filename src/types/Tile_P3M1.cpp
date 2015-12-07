/*
 *  Tile_P3M1.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_P3M1.h"


Tile_P3M1::Tile_P3M1():Tile() {
    
    
}

void Tile_P3M1::setCellStructure(int structure){
    cellType = 0;
    latticeType = ORNAMENT_HEXAGONAL;
    
    updateTile();
}


void Tile_P3M1::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ofVec2f p1p2 = p1 + (p2-p1)/2;
    ornamentBase.push_back(p1p2 + (p3-p1p2)/3);
    ofVec2f p1p4 = p1 + (p4-p1)/2;
    ornamentBase.push_back(p1p4 + (p3-p1p4)/3);
    
}
