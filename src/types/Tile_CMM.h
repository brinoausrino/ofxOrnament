/*
 *  Tile_CMM.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_CMM
#define _Tile_CMM

#include "ofMain.h"
#include "Tile.h"

class Tile_CMM : public Tile {
    
public:
    
    Tile_CMM();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
