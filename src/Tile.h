/*
 *  Tile.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Tile
#define _Tile

#include "ofMain.h"
#include "OrnamentTypes.h"

class Tile {
    
public:
    
    Tile(){};
    ~Tile(){};
    void setup(int width, int height);
    
    
    virtual void setCellStructure(int structure);
    int getCellStructure();
    
    void draw(int x=0,int y = 0);
    
    vector<ofVec2f> getOrnamentBase();
    vector<ofVec2f> getTilePoly();
    
    ofVec2f nextNorth();
    ofVec2f nextSouth();
    ofVec2f nextEast();
    ofVec2f nextWest();
    
    void updateTile();
    
protected:
    
    void updateMask();
    void updateVecNeighbors();
    virtual void updateOrnamentBase();
    void updateCornerPoints(float length_side = 0.7);
    
    
    OrnamentCellStructureType latticeType;
    int cellType;
    
    
    ofVec2f p1,p2,p3,p4;
    vector<ofVec2f> ornamentBase;
    ofVec2f nextCellNorth, nextCellSouth, nextCellEast, nextCellWest;
    
    int width, height;
};

#endif
