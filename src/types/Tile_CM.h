/*
 *  Tile_CM.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_CM
#define _Tile_CM

#include "ofMain.h"
#include "Tile.h"

class Tile_CM : public Tile {
    
public:
    
    Tile_CM();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
