/*
 *  Tile_PMG.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 06.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_PMG
#define _Tile_PMG

#include "ofMain.h"
#include "Tile.h"

class Tile_PMG : public Tile {
    
public:
    
    Tile_PMG();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
