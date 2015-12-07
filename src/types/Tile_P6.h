/*
 *  Tile_P6.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 08.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P6
#define _Tile_P6

#include "ofMain.h"
#include "Tile.h"

class Tile_P6 : public Tile {
    
public:
    
    Tile_P6();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
