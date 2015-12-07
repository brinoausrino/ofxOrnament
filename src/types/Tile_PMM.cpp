/*
 *  Tile_P2MM.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_PMM.h"


Tile_PMM::Tile_PMM():Tile() {
    
    
}

void Tile_PMM::setCellStructure(int structure){
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

void Tile_PMM::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ornamentBase.push_back(ofVec2f(width/2,0));
    ornamentBase.push_back(ofVec2f(width/2,height/2));
    ornamentBase.push_back(ofVec2f(p4.x,height/2));

}