/*
 *  Tile_P6.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 08.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_P6.h"


Tile_P6::Tile_P6():Tile() {
    
    
}

void Tile_P6::setCellStructure(int structure){
    cellType = 0;
    latticeType = ORNAMENT_HEXAGONAL;
    
    updateTile();
}

void Tile_P6::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ornamentBase.push_back(p3);
    ofVec2f p1p4 = p1 + (p4-p1)/2;
    ornamentBase.push_back(p1p4 + (p3-p1p4)/3);
    
}
