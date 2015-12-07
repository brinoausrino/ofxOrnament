/*
 *  Tile_PGG.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_PGG
#define _Tile_PGG

#include "ofMain.h"
#include "Tile.h"

class Tile_PGG : public Tile {
    
public:
    
    Tile_PGG();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
