/*
 *  Tile_P2MM.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P2MM
#define _Tile_P2MM

#include "ofMain.h"
#include "Tile.h"

class Tile_PMM : public Tile {
    
public:
    
    Tile_PMM();

    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
