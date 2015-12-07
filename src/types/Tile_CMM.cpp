/*
 *  Tile_CMM.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_CMM.h"


Tile_CMM::Tile_CMM():Tile() {
    
    
}

void Tile_CMM::setCellStructure(int structure){
    cellType = structure%2;
    switch (structure%2) {
        case 0:
            latticeType = ORNAMENT_RHOMBIC;
            break;
        case 1:
            latticeType = ORNAMENT_SQUARE;
            break;
    }
    updateTile();
}

void Tile_CMM::updateOrnamentBase(){
    ornamentBase.clear();
    switch (latticeType) {
        case ORNAMENT_RHOMBIC:
            ornamentBase.push_back(p4);
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p1 + (p3-p1)/2);
            break;
        case ORNAMENT_SQUARE:
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(p1 + (p3-p1)/2);
            break;
        default:
            break;
    }
    
    
    
}

