/*
 *  Tile_P4.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P4
#define _Tile_P4

#include "ofMain.h"
#include "Tile.h"

class Tile_P4 : public Tile {
    
public:
    
    Tile_P4();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
