#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //init video stream
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(800, 600);
    
    //init ornament
    ornament.setup(1024,768);
    
    //assign video input to ornament
    ornament.loadTexture(vidGrabber.getTexture());
    
    //setup gui
    tileSize.set("tile size", 150, 30, 400);
    tileSize.addListener(this, &ofApp::onTileSizeChanged);
    wallpaperGroup.set("group", 12, 9, 16);
    wallpaperGroup.addListener(this, &ofApp::onWallpaperGroupChanged);
    angle.set("angle", 0, 2*PI, 0);
    angle.addListener(this, &ofApp::onAngleChanged);
    panel.setup();
    panel.add(tileSize);
    panel.add(wallpaperGroup);
    panel.add(angle);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    //update vidgrabber
    vidGrabber.update();
    
    //update ornament
    if(vidGrabber.isFrameNew()){ 
        ornament.update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //draw ornament
    ornament.draw(0,0);
    
    //draw debug view to see ornament part in camera picture
    ornament.drawDebug(0, 300,400,300);
    
    //draw gui
    ofDrawBitmapStringHighlight("wallpaperGroup: " + ofToString(ornament.getWallpaperGroupAsInt()), 10, 580);
    ofDrawBitmapStringHighlight("cellStructure: " + ofToString(ornament.getCellStructure()), 10, 600);
    panel.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    //manipulate inputs
    if (key == 'm'){
        ornament.setCellStructure(ornament.getCellStructure()+1);
    }
    if (key == 'n'){
        ornament.setCellStructure(ornament.getCellStructure()-1);
    }
    if (key == 'c'){
        int wg = ornament.getWallpaperGroupAsInt() + 1;
        ornament.setWallpaperGroup(wg);
    }
    if (key == 'v'){
        ornament.setWallpaperGroup(ornament.getWallpaperGroupAsInt()-1);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

void ofApp::onTileSizeChanged(int& t){
    ornament.setTileSize(t);
}

void ofApp::onWallpaperGroupChanged(int& t){
    ornament.setWallpaperGroup(t);
}

void ofApp::onAngleChanged(float& t){
    ornament.setAngle(t);
}
