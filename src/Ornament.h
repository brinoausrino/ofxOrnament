/*
 *  Ornament.h
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _Ornament
#define _Ornament

#define STRINGIFY(...) STRINGIFY_AUX(__VA_ARGS__)
#define STRINGIFY_AUX(...) #__VA_ARGS__

#include "ofMain.h"
#include "Tile.h"
#include "TileFactory.h"
#include "OrnamentTypes.h"

class Ornament {
    
public:
    
    Ornament(){};
    
    void setup(int w = 512, int h = 512, WALLPAPER_GROUP wallpaperGroup = WPG_P3, int tileSize = 150, float angle = 0);
    void update();
    void draw(int x, int y);
    
    void loadTexture(ofTexture texture);
    void setWallpaperGroup(WALLPAPER_GROUP group);
    void setWallpaperGroup(int group);
    WALLPAPER_GROUP getWallpaperGroup();
    int getWallpaperGroupAsInt();
    
    ofTexture& getTexture();
    vector<ofVec2f> getOrnamentBase();
    vector<ofVec2f> getTilePoly();
    
    void setCellStructure(int s);
    int getCellStructure();
    
    void setTileSize(float t);
    int getTileSize();
    
    void setAngle(float angleRad);
    float getAngle();
    
private:
    void createOrnament();
    
    ofTexture inputTexture;
    ofTexture outputTexture;
    WALLPAPER_GROUP wallpaperGroup;
    ofFbo fbo;
    ofFbo tileFbo;
    
    float tileSize;
    float angle;
    
    int width,height;
    
    ofShader wallpaperShader;
    ofShader ornamentShader;
    
    std::unique_ptr<Tile> tile;
};

#endif
