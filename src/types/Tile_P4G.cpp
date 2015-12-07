/*
 *  Tile_P4MG.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_P4G.h"

Tile_P4G::Tile_P4G():Tile() {
    
    
}

void Tile_P4G::setCellStructure(int structure){
    cellType = 0;
    latticeType = ORNAMENT_SQUARE;
    
    updateTile();
}

void Tile_P4G::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1 + (p2-p1)/2);
    ornamentBase.push_back(p1 + (p3-p1)/2);
    ornamentBase.push_back(p1 + (p4-p1)/2);
    
}