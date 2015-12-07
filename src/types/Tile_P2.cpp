/*
 *  Tile_P2.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_P2.h"


//------------------------------------------------------------------
Tile_P2::Tile_P2():Tile() {
    
    
}


void Tile_P2::updateOrnamentBase(){
    ornamentBase.clear();
    switch (latticeType) {
        case ORNAMENT_RECTANGLE:
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(ofVec2f( p3.x,p3.y/2));
            ornamentBase.push_back(ofVec2f(p4.x,p4.y/2));
            break;
        case ORNAMENT_SQUARE:
        {
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(ofVec2f( p3.x,p3.y/2));
            ornamentBase.push_back(ofVec2f(p4.x,p4.y/2));
            break;
        }
        case ORNAMENT_RHOMBIC:
        {
            ornamentBase.push_back(p4);
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);

            break;
        }
        case ORNAMENT_OBLIQUE:
        {
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p2);
            ornamentBase.push_back(p2 + (p3-p2)/2);
            ornamentBase.push_back(p1 + (p4-p1)/2);
            break;
        }
        case ORNAMENT_HEXAGONAL:
        {
            ornamentBase.push_back(p1);
            ornamentBase.push_back(p3);
            ornamentBase.push_back(p4);
            break;
        }
    }
    
}