/*
 *  Tile_P4M.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P4M
#define _Tile_P4M

#include "ofMain.h"
#include "Tile.h"

class Tile_P4M : public Tile {
    
public:
    
    Tile_P4M();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    

    
};

#endif
