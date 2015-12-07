/*
 *  Tile_P31M.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 08.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P31M
#define _Tile_P31M

#include "ofMain.h"
#include "Tile.h"

class Tile_P31M : public Tile {
    
public:
    
    Tile_P31M();

    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();

    
};

#endif
