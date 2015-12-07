/*
 *  Tile_P6M.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 08.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P6M
#define _Tile_P6M

#include "ofMain.h"
#include "Tile.h"

class Tile_P6M : public Tile {
    
public:
    
    Tile_P6M();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    
};

#endif
