/*
 *  Tile_PG.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_PG
#define _Tile_PG

#include "ofMain.h"
#include "Tile.h"

class Tile_PG : public Tile {
    
public:
    
    Tile_PG();
    
    void updateTexture();
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
