/*
 *  Tile_CM.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_CM.h"


//------------------------------------------------------------------
Tile_CM::Tile_CM():Tile() {
    
    
}

void Tile_CM::setCellStructure(int structure){
    //0 - horizontal mirroring
    //1 - vertical mirroring
    cellType = structure%2;
    switch (structure%2) {
        case 0:
            latticeType = ORNAMENT_RHOMBIC;
            break;
        case 1:
            latticeType = ORNAMENT_RHOMBIC;
            break;
    }
    updateTile();
}


void Tile_CM::updateOrnamentBase(){
    ornamentBase.clear();
    switch (cellType) {
        case 0: // horizontal
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(p4);
            break;
        case 1: // vertical
        {
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p3);
            ornamentBase.push_back(p4);
            break;
        }
    }
    
}