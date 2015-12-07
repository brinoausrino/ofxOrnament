/*
 *  Tile_PGG.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_PGG.h"


Tile_PGG::Tile_PGG():Tile() {
    
    
}

void Tile_PGG::setCellStructure(int structure){
    cellType = structure%2;
    switch (structure%2) {
        case 0:
            latticeType = ORNAMENT_RECTANGLE;
            break;
        case 1:
            latticeType = ORNAMENT_SQUARE;
            break;
    }
    updateTile();
}

void Tile_PGG::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1 + (p2-p1)/2);
    ornamentBase.push_back(p2 + (p3-p2)/2);
    ornamentBase.push_back(p1 + (p4-p1)/2);
    
}
