/*
 *  Ornament.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ornament.h"


//------------------------------------------------------------------
void Ornament::setup(int w, int h, WALLPAPER_GROUP wallpaperGroup_, int tileSize_, float angle_) {
    
    width = w;
    height = h;
    wallpaperGroup = wallpaperGroup_;
    tileSize = tileSize_;
    angle = angle_;
    fbo.allocate(width, height);
    ornamentShader.load("Shaders/ornament");
    wallpaperShader.load("Shaders/wallpaper");
}

void Ornament::loadTexture(ofTexture texture){
    inputTexture = texture;
    
    int w = width;
    int h = height;
    if (texture.getWidth() > w) {
        w = texture.getWidth();
    }
    if (texture.getHeight() > h) {
        h = texture.getHeight();
    }
    
    
    if (!tileFbo.isAllocated() || tileFbo.getWidth() != w || tileFbo.getHeight()!=h) {
        tileFbo.allocate(w, h);
    }
    createOrnament();
}

void Ornament::setWallpaperGroup(int group){
    setWallpaperGroup((WALLPAPER_GROUP)(group%17));
}

void Ornament::setWallpaperGroup(WALLPAPER_GROUP group){
    wallpaperGroup = group;
    createOrnament();
}

WALLPAPER_GROUP Ornament::getWallpaperGroup(){
    return wallpaperGroup;
}

int Ornament::getWallpaperGroupAsInt(){
    return wallpaperGroup;
}

void Ornament::setTileSize(int t){
    tileSize = t;
}

int Ornament::getTileSize(){
    return tileSize;
}

void Ornament::setAngle(float angleRad){
    angle = angleRad;
}

float Ornament::getAngle(){
    return angle;
}

void Ornament::createOrnament(){
    tile = TileFactory::createTile(wallpaperGroup);
    tile->setup(width,height);
    update();
}

//------------------------------------------------------------------
void Ornament::update() {
    
    tileFbo.begin();
    ofClear(0, 0, 0, 0);
    ornamentShader.begin();
    wallpaperShader.setUniform1i("cell_structure", tile->getCellStructure() );
    ornamentShader.setUniform1i("wallpaper_group", wallpaperGroup );
    ornamentShader.setUniform1f("width", inputTexture.getWidth() );
    ornamentShader.setUniform1f("height", inputTexture.getHeight() );
    inputTexture.draw(0, 0);
    ornamentShader.end();
    tileFbo.end();
    
    
    fbo.begin();
    ofClear(255,255,255, 0);
    ofSetColor(255,255,255, 255);
    wallpaperShader.begin();
    wallpaperShader.setUniform1i("cell_structure", tile->getCellStructure() );
    wallpaperShader.setUniform1f("width", width );
    wallpaperShader.setUniform1f("height", height );
    wallpaperShader.setUniform1f("tile_size", tileSize );
    wallpaperShader.setUniform1f("angle", angle );
    wallpaperShader.setUniform1f("tex_width", inputTexture.getWidth() );
    wallpaperShader.setUniform1f("tex_height",inputTexture.getHeight() );
    tileFbo.draw(0, 0);
    wallpaperShader.end();
    fbo.end();
    
    outputTexture = fbo.getTexture();
    
    tile->updateTile();
}

void Ornament::setCellStructure(int s){
    tile->setCellStructure(s);
    update();
}

int Ornament::getCellStructure(){
    return tile->getCellStructure();
}

//------------------------------------------------------------------
void Ornament::draw(int x, int y) {
    outputTexture.draw(x, y);
}

ofTexture& Ornament::getTexture(){
    return outputTexture;
}

vector<ofVec2f> Ornament::getOrnamentBase(){
    return tile->getOrnamentBase();
}

vector<ofVec2f> Ornament::getTilePoly(){
    return tile->getTilePoly();
}



