/*
 *  Tile_P3.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P3
#define _Tile_P3

#include "ofMain.h"
#include "Tile.h"

class Tile_P3 : public Tile {
    
public:
    
    Tile_P3();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    

    
};

#endif
