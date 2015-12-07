#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(800, 600);
    
    ornament.setup(1024,768);
    tex = img.getTexture();
    ornament.loadTexture(vidGrabber.getTexture());
    
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
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    vidGrabber.update();
    
    if(vidGrabber.isFrameNew()){ 
        ornament.update();
    }
	
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
   // ofDrawRectangle(0, 0, 23, 23);
    
    ornament.draw(0,0);
    
    ofDrawBitmapStringHighlight("wallpaperGroup: " + ofToString(ornament.getWallpaperGroupAsInt()), 10, 580);
    ofDrawBitmapStringHighlight("cellStructure: " + ofToString(ornament.getCellStructure()), 10, 600);
    vector<ofVec2f> base = ornament.getOrnamentBase();
    vector<ofVec2f> base2 = ornament.getTilePoly();
    
    
    
    ofPushMatrix();
    ofTranslate(0, 300);
    ofScale(0.3, 0.3);
    ofSetColor(255);
    vidGrabber.draw(0, 0,1024,768);
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofBeginShape();
    for (auto point : base) {
        ofVertex(point.x,point.y);
    }
    ofVertex(base[0].x,base[0].y);
    
    for (auto point : base2) {
        ofVertex(point.x,point.y);
    }
    ofVertex(base2[0].x,base2[0].y);
    ofEndShape();
    ofSetColor(255);
    ofPopMatrix();
    
    
    panel.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
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
