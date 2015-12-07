/*
 *  Tile_P3M1.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P3M1
#define _Tile_P3M1

#include "ofMain.h"
#include "Tile.h"

class Tile_P3M1 : public Tile {
    
public:
    
    Tile_P3M1();

    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    

    
};

#endif
