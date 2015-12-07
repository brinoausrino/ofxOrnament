/*
 *  Tile_P4MG.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 07.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile_P4MG
#define _Tile_P4MG

#include "ofMain.h"
#include "Tile.h"

class Tile_P4G : public Tile {
    
public:
    
    Tile_P4G();
    
    void setCellStructure(int structure);
    
protected:
    void updateOrnamentBase();
    

    
};

#endif
