/*
 *  TileFactory.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TileFactory
#define _TileFactory

#include "ofMain.h"
#include "Tile.h"
#include "OrnamentTypes.h"


class TileFactory {
	
  public:
	static std::unique_ptr<Tile> createTile(WALLPAPER_GROUP tileType);
};

#endif
