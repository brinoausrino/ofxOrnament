/*
 *  Tile_PG.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_PG.h"


//------------------------------------------------------------------
Tile_PG::Tile_PG():Tile() {
    
    
}

void Tile_PG::setCellStructure(int structure){
    //0 - horizontal glides
    //1 - vertical glides
    cellType = structure%2;
    switch (structure%2) {
        case 0:
            latticeType = ORNAMENT_RECTANGLE;
            break;
        case 1:
            latticeType = ORNAMENT_RECTANGLE;
            break;
    }
    updateTile();
}


void Tile_PG::updateOrnamentBase(){
    ornamentBase.clear();
    switch (cellType) {
        case 0: // horizontal
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(ofVec2f( p3.x,p3.y/2));
            ornamentBase.push_back(ofVec2f(p4.x,p4.y/2));
            break;
        case 1: // vertical
        {
            ornamentBase.push_back(p1);
            ornamentBase.push_back(ofVec2f( p2.x/2,p2.y));
            ornamentBase.push_back(ofVec2f( p3.x/2,p3.y));
            ornamentBase.push_back(ofVec2f(p4.x,p4.y));
            break;
        }
    }
    
}
