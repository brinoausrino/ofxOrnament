/*
 *  Tile_PMG.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile_PMG.h"



Tile_PMG::Tile_PMG():Tile() {
    
    
}

void Tile_PMG::setCellStructure(int structure){
    //0 - horizontal 1 - vertical
    cellType = structure%2;
    latticeType = ORNAMENT_RECTANGLE;
    updateTile();
}

void Tile_PMG::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ornamentBase.push_back(ofVec2f(width/2,0));
    ornamentBase.push_back(ofVec2f(width/2,height/2));
    ornamentBase.push_back(ofVec2f(p4.x,height/2));
    
}