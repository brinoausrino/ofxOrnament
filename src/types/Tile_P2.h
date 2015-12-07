/*
 *  Tile_P2.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P2
#define _Tile_P2

#include "ofMain.h"
#include "Tile.h"

class Tile_P2 : public Tile {
    
public:
    Tile_P2();
    
protected:
    void updateOrnamentBase();
    
    ofFbo subTileMask;
    ofTexture subTileTex;
    
};

#endif
