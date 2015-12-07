/*
 *  Tile_P4M.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_P4M.h"


Tile_P4M::Tile_P4M():Tile() {
    
    
}

void Tile_P4M::setCellStructure(int structure){
    cellType = 0;
    latticeType = ORNAMENT_SQUARE;
    
    updateTile();
}

void Tile_P4M::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ornamentBase.push_back(p1 + (p3-p1)/2);
    ornamentBase.push_back(p1 + (p4-p1)/2);
    
}
