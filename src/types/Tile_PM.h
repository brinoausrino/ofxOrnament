/*
 *  Tile_PM.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 05.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_PM
#define _Tile_PM


#include "ofMain.h"
#include "Tile.h"

class Tile_PM : public Tile {
    
public:
    
    Tile_PM();
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
