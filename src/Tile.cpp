/*
 *  Tile.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Tile.h"


void Tile::setup(int width_, int height_){
    setCellStructure(0);
    width = width_;
    height = height_;
}


void Tile::setCellStructure(int structure){
    cellType = structure%5;
    switch (structure%5) {
        case 0:
            latticeType = ORNAMENT_RECTANGLE;
            break;
        case 1:
            latticeType = ORNAMENT_SQUARE;
            break;
        case 2:
            latticeType = ORNAMENT_RHOMBIC;
            break;
        case 3:
            latticeType = ORNAMENT_HEXAGONAL;
            break;
        case 4:
            latticeType = ORNAMENT_OBLIQUE;
            break;
        default:
            break;
    }
    updateTile();
}

int Tile::getCellStructure(){
    return latticeType;
    //return cellType;
}

void Tile::updateCornerPoints(float length_side){
    int w = width;
    int h = height;
    
    switch (latticeType) {
        case ORNAMENT_RECTANGLE:
            p1 = ofVec2f(0, 0);
            p2 = ofVec2f(w, 0);
            p3 = ofVec2f(w, h);
            p4 = ofVec2f(0, h);
            break;
        case ORNAMENT_SQUARE:
        {
            int length = MIN(w, h);
            p1 = ofVec2f((w-length)/2, (h-length)/2);
            p2 = ofVec2f((w-length)/2 + length, (h-length)/2);
            p3 = ofVec2f((w-length)/2 + length, (h-length)/2 + length);
            p4 = ofVec2f((w-length)/2, (h-length)/2 + length);
            break;
        }
        case ORNAMENT_RHOMBIC:
        {
            p1 = ofVec2f(w/2,0);
            p2 = ofVec2f(w,h/2);
            p3 = ofVec2f(w/2,h);
            p4 = ofVec2f(0,h/2);
            break;
        }
        case ORNAMENT_OBLIQUE:
        {
            float l = w*(1-length_side);
            p1 = ofVec2f(l,0);
            p2 = ofVec2f(w,0);
            p3 = ofVec2f(w-l,h);
            p4 = ofVec2f(0,h);
            break;
        }
        case ORNAMENT_HEXAGONAL:
        {
            float hmax = w*sqrt(3)/3;
            float wmax = w;
            
            if (hmax>h) {
                hmax = h;
                wmax = hmax*3/sqrt(3);
            }
            
            p1 = ofVec2f(wmax*1/3,0);
            p2 = ofVec2f(wmax,0);
            p3 = ofVec2f(wmax*2/3,hmax);
            p4 = ofVec2f(0,hmax);
            
            break;
        }
        default:
            break;
    }
    
    
}

void Tile::updateVecNeighbors(){
    //calculate vector to neighbors
    switch (latticeType) {
        case ORNAMENT_RECTANGLE:
            nextCellSouth = ofVec2f(0, height);
            nextCellEast = ofVec2f(width, 0);
            nextCellNorth = nextCellSouth * -1;
            nextCellWest = nextCellEast * -1;
            break;
        case ORNAMENT_SQUARE:
            nextCellSouth = ofVec2f(0, abs(p1.y-p4.y));
            nextCellEast = ofVec2f(abs(p1.x-p2.x), 0);
            nextCellNorth = nextCellSouth * -1;
            nextCellWest = nextCellEast * -1;
            break;
        case ORNAMENT_HEXAGONAL:
            nextCellSouth = ofVec2f(-p1.x, p4.y-1);
            nextCellEast = ofVec2f(p3.x-1,0);
            nextCellNorth = nextCellSouth * -1;
            nextCellWest = nextCellEast * -1;
            break;
        case ORNAMENT_OBLIQUE:
            nextCellSouth = ofVec2f(-p1.x, p4.y);
            nextCellEast = ofVec2f(p2.x-p1.x,0);
            nextCellNorth = nextCellSouth * -1;
            nextCellWest = nextCellEast * -1;
            break;
        case ORNAMENT_RHOMBIC:
            nextCellSouth = ofVec2f(-p1.x, p4.y);
            nextCellEast = ofVec2f(p1.x,p2.y);
            nextCellNorth = nextCellSouth * -1;
            nextCellWest = nextCellEast * -1;
            break;
        default:
            break;
    }
}

void Tile::updateOrnamentBase(){
    ornamentBase.clear();
    ornamentBase.push_back(p1);
    ornamentBase.push_back(p2);
    ornamentBase.push_back(p3);
    ornamentBase.push_back(p4);
}

vector<ofVec2f> Tile::getOrnamentBase(){
    return ornamentBase;
}

vector<ofVec2f> Tile::getTilePoly(){
    vector<ofVec2f> out;
    out.push_back(p1);
    out.push_back(p2);
    out.push_back(p3);
    out.push_back(p4);
    return out;
}

ofVec2f Tile::nextNorth(){
    return nextCellNorth;
}
ofVec2f Tile::nextSouth(){
    return nextCellSouth;
}
ofVec2f Tile::nextEast(){
    return nextCellEast;
}
ofVec2f Tile::nextWest(){
    return nextCellWest;
}

void Tile::updateTile(){
    updateCornerPoints();
    updateOrnamentBase();
    updateVecNeighbors();
}
